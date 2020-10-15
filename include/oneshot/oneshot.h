#ifndef KL_ONESHOT_H
#define KL_ONESHOT_H

#include "../sample_type_interfaces/sample_type_interfaces.h"

namespace lamb {
  template <typename value_t_, typename phase_t_>
  class oneshot : sample_source<value_t_>, triggerable {
  public:
    typedef value_t_ output_value_type;
    typedef phase_t_ phase_type;
    
    const    output_value_type * data;
  protected:
    volatile bool                _trigger;
    
  public:
    bool                         state;
    phase_type                   length;
    phase_type                   index;
    phase_type                   r_point;
    
    explicit oneshot(const output_value_type * data_, phase_type length_) :
      data(data_),
      _trigger(false),
      state(false),
      length(length_),
      index(0),
      r_point(length_-256) {}
    
  protected:
    virtual output_value_type play(
      phase_type const & index_,
      phase_type const & incr_
    ) {
      if (_trigger) {
        _trigger = false;
        state   = true;
        index   = 0;
      }
      
      if (state && index_ > length)
        state = false;
      else if (! state)
        return 0;
      
      output_value_type audio = data[index_];
      
      index += incr_;
      
      return audio;
    } 
        
    virtual output_value_type play() {
      output_value_type audio = play(index, 1);
      
      if (index > r_point) {
        phase_type       past_r = index - r_point;
        past_r                  = ~past_r;
        uint16_t const & mul    = audio * past_r;
        audio                   = mul >> 8;
      }
      
      return audio;
    }
    
  public:    
    virtual output_value_type read() {
      return play();
    }

    virtual void trigger() {
      _trigger = true;
    }
  };

  class oneshot_plus : public oneshot<int16_t, uint32_t> {
  public:    
    explicit oneshot_plus(
      const typename oneshot<int16_t, uint32_t>::output_value_type * data_,
      uint32_t length_
    ) :
      oneshot<int16_t, uint32_t>(data_, length_),
      amplitude(255),
      phacc(0),
      phincr(0),
      next_phincr(0),
      accum(0) {
    }

    uint16_t amplitude;

    virtual uint32_t get_index() {
      uint32_t phacc_msb = phacc >> 16;
      return  phacc_msb;
    }

  protected:
    virtual int16_t play() {
      if (_trigger) {
        _trigger = false;
        state   = true;
        phacc   = 0;
        
        if (next_phincr != 0) {
          phincr      = next_phincr;
          next_phincr = 0;
        }
        
        phacc   = 0;
      }
      
      state = state && (get_index() < length);

      if (! state) return 0;
      
      output_value_type audio = oneshot<int16_t, uint32_t>::data[get_index()];

      phacc += phincr;
      
      accum = amplitude * audio;
      accum >>= 8;
      
      return accum;
    }
    
  public:
    uint32_t phacc;
    uint32_t phincr;
    uint32_t next_phincr;
    uint32_t accum;
  };
  
}
#endif
