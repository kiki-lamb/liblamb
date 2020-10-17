#ifndef LAMB_DSP
#define LAMB_DSP

namespace lamb {
  
////////////////////////////////////////////////////////////////////////////////

  template <
    typename input_type,
    typename amplitude_type = input_type
    >
  input_type amplify(
    input_type const & input,
    amplitude_type const & ampl,
    uint8_t const & shift = sizeof(amplitude_type) << 3
  ) {

    typename sample_type_traits<input_type>::mix_type tmp = input;

    tmp         *=  ampl;
    tmp        >>= shift;

    return tmp;
  }


////////////////////////////////////////////////////////////////////////////////

  template <
    typename t,
    typename amplitude_type = typename t::output_type
    >
  class amplifier :
    public sample_source<typename t::output_type> {
  private:
    t * _source;

  public:
    amplitude_type amplitude;
    uint8_t shift;
    
  public:
    explicit amplifier(
      t * source_,
      amplitude_type const & amplitude_,
      uint8_t const & shift_
    ) :
    _source(source_),
    amplitude(amplitude_),
    shift(shift_) {}

    virtual ~amplifier() = default;
    
    virtual
    typename t::output_type
    read() {
      return amplify(_source->read(), amplitude, shift);
    }
  };
  
////////////////////////////////////////////////////////////////////////////////

//  template <typename t>
//  class mixer :
//    public sample_source<typename t::output_type> {
//  private:
//    t **  _sources;
//    size_t  _count;
//    
//  public:
//    mixer(t ** sources_, size_t count_) :
//    _sources(sources_),
//    _count(count_) {}
//
//    virtual ~mixer() = default;
//    
//    virtual
//    typename t::output_type
//    read() {
//      return mix(_sources, _count);
//    }
//  };

////////////////////////////////////////////////////////////////////////////////

  template <typename t>
  inline __attribute__((always_inline))
  void mix(
    t ** sources_,
    size_t const & count,
    typename sample_type_traits<typename t::value_type>::mix_type & out
  ) {
    for (size_t ix = 0; ix < count; ix++) {
      
// #define USE_CAST
      
#ifdef USE_CAST
      sample_source<int16_t> * s = sources_[ix];

      out += s->read();
#else
      out += sources_[ix]->read();
#endif
    }
  }

////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type, typename output_type = input_type>
  class identity : public lamb::sample_processor<input_type, output_type> {
  public:
    virtual ~identity() = default;

    inline identity(lamb::sample_source<input_type> * in = NULL) {
      this->connect(in);
    }
  };

////////////////////////////////////////////////////////////////////////////////
  
  // This should be a template...
  template <typename input_type>
  class unity_mix : public lamb::sample_source<input_type> {
  public:
    identity<input_type> input1;
    identity<input_type> input2;

    inline virtual ~unity_mix() {}; 

    inline unity_mix(sample_source<input_type> * in1, sample_source<input_type> * in2) {
      input1.connect(in1);
      input2.connect(in2);
    }

    inline virtual input_type read() {
      uint16_t tmp = 0;
      tmp += input1.read();
      tmp += input2.read();
      return tmp / 2;
    }
  };

////////////////////////////////////////////////////////////////////////////////

  template <typename input_type>
  class convert_to_unsigned :
    public lamb::sample_processor<input_type, typename lamb::sample_type_traits<input_type>::unsigned_type> {
  public:
    inline virtual ~convert_to_unsigned() {};

    inline convert_to_unsigned(lamb::sample_source<input_type> * in) {
      this->connect(in);
    }

    inline
    virtual typename lamb::sample_type_traits<input_type>::unsigned_type
    process(input_type v) {
      return lamb::sample_type_traits<input_type>::to_uint8_t(v);
    }
  };

/////////////////////////////////////////////////////////////////////////////////

  template <typename input_type>
  class convert_to_signed : public lamb::sample_processor<input_type, typename lamb::sample_type_traits<input_type>::signed_type> {
  public:
    inline virtual ~convert_to_signed() {};

    inline convert_to_signed(lamb::sample_source<input_type> * in) {
      connect(in);
    }

    inline
    virtual typename lamb::sample_type_traits<input_type>::unsigned_type process(input_type v) {
      return lamb::sample_type_traits<input_type>::to_int8_t(v);
    }
  };
};

#endif


/* Local Variables:  */
/* fill-column: 120  */
/* End:              */
