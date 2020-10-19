#ifndef KL_TABLE_OSC_H
#define KL_TABLE_OSC_H

#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#ifndef __AVR__
#include <stdio.h>
#endif

namespace lamb {
  template<typename PHACC_T, typename OUT_T>
  class i_osc {
  public:
    typedef OUT_T   output_value_type;
    typedef PHACC_T phase_type;
    
    output_value_type read       () = 0;    
  protected:
  };

  ////////////////////////////////////////////////////////////////////////////////
  
  template <typename IN_T, typename OUT_T = IN_T, typename PHACC_T = uint32_t>
  class table_osc /* : public i_osc<PHACC_T, OUT_T> */ {
  public:    
    typedef IN_T    value_type;
    typedef OUT_T   output_value_type;
    typedef PHACC_T phase_type;
    phase_type         _phacc;
    phase_type         _phincr;
  
  private:
    const value_type * _table;
  
  protected:
    size_t             _length;
    uint8_t            _index_rshift;
  
  protected:
    __attribute__((always_inline)) output_value_type get(size_t index) {
#ifdef __AVR__
      return (value_type)(pgm_read_byte(_table+index*sizeof(value_type))); // This is gonna fuck up once sizeof(value_type) > 1.
#else
      return _table[index];
#endif
    }

  public:
    explicit table_osc(
      const value_type * table_ = NULL,
      size_t len_ = 0
    ) : _phacc(0),
        _phincr(0),
        _table(NULL),
        _length(0),
        _index_rshift(0) {
      set_table(table_, len_);
    }

    __attribute__((always_inline))
    void set_table(
      const value_type * table_,
      size_t len_
    ) {
      _table        = table_;
      _length       = len_;
      size_t siz    = _length;
      _index_rshift = (sizeof(_phacc)*8)+1;
      for (; _index_rshift > 0 && siz != 0; _index_rshift--, siz >>= 1);
    }

    __attribute__((always_inline))
    output_value_type read() { // impl i_osc
      output_value_type const & r = get(_phacc >> _index_rshift);
      _phacc += _phincr;
      return r;
    }
  };

////////////////////////////////////////////////////////////////////////////////
  
  // v meant for an unsigned input and signed output type (e.g., from uint8_t
  //   to int8_t, with RSHIFT = 1 reducing the output from +/- UINT8_MAX to
  //   INT8_MAX.
  
  template <typename IN_T, typename OUT_T, uint8_t RSHIFT = 1>
  class quarter_table_osc : public table_osc<IN_T, OUT_T, uint32_t> {
  public:
    typedef IN_T       value_type;
    typedef value_type output_value_type;
    typedef typename   table_osc<uint32_t, output_value_type>::phase_type
    phase_type;
  
  public:
    explicit quarter_table_osc(
      const value_type * table_ = NULL,
      size_t len_ = 0
    ) : table_osc<value_type, output_value_type, uint32_t>(table_, len_) {}
  
    __attribute__((always_inline))
    output_value_type read() {
      // Hex constants blow assume that phase_type is still uint32_t
      // and would need to be changed if phase_type was changed.
      bool   const & reverse = (this->_phacc & 0x40000000);
      bool   const & negate  = (this->_phacc & 0x80000000);
      size_t const & index   = (this->_phacc << 2) >> this->_index_rshift;
    
      output_value_type r = this->get(
        reverse ?
        this->_length - 1 - index:
        index
      ) >> RSHIFT; 
    
      if (negate)
        r *= -1;
    
      this->_phacc += this->_phincr; // this->incr_phacc();
    
      return r;
    }
  };
  
////////////////////////////////////////////////////////////////////////////////
  
  template <typename IN_T, typename OUT_T = IN_T, uint8_t LSHIFT = 0>
  class interp_table_osc : public table_osc<IN_T, OUT_T> {
  public:
    typedef IN_T     value_type;
    typedef OUT_T    output_value_type;
    typedef typename table_osc<value_type, output_value_type>::phase_type
    phase_type;
  
  protected:
    phase_type mask_bottom;
  
    __attribute__((always_inline))
    void update_mask_bottom() {
      mask_bottom                  = ~((phase_type)0);
      phase_type const & mask_top  = mask_bottom - ((((phase_type)1)<<this->_index_rshift)-1);
      mask_bottom                 -= mask_top;
    }

  public:
    explicit interp_table_osc(
      const value_type * table_ = NULL,
      size_t len_ = 0
    ) : table_osc<value_type, output_value_type>(table_, len_) {
      update_mask_bottom();
      printf("value\ta_value\t\n");
    }

    __attribute__((always_inline))
    output_value_type read() {
      uint8_t           index       = this->_phacc       >> this->_index_rshift;
      output_value_type value       = this->get(index++) << LSHIFT;
      output_value_type delta       = this->get(index)   << LSHIFT;
      delta                        -= value;
      phase_type const & sub_index  = this->_phacc        & mask_bottom;
      int32_t    const & deltasi    = delta               * sub_index; // this should probably be a PHACC_T? 
      this->_phacc                 += this->_phincr; 
      value                        += deltasi            >> this->_index_rshift;
      return value;
      
    }
  };
}

#endif
