#ifndef KL_ONESHOT_H
#define KL_ONESHOT_H

#include "../sample_type_interfaces/sample_type_interfaces.h"

namespace lamb {
  template <
    typename value_t_,
    typename length_t_    = uint16_t,
    typename phase_t_     = typename unsigned_int<(sizeof(length_t_) + 2)>::type,
    typename amplitude_t_ = typename unsigned_int<(sizeof(value_t_) >> 1)>::type
      >
  class oneshot :
    public sample_source<value_t_>,
    triggerable,
    stoppable
  {
  protected:
    volatile bool                _trigger;

  public:
    typedef value_t_             output_value_type;
    typedef length_t_            length_type;
    typedef phase_t_             phase_type;
    typedef amplitude_t_         amplitude_type;
    typedef typename sample_type_traits<output_value_type>::mix_type
                                 accum_type; 

    bool                         state;
    length_type                  length;
    const output_value_type *    data;
    amplitude_type               amplitude;
    phase_type                   phacc;
    phase_type                   phincr;
    phase_type                   next_phincr;
    accum_type                   accum;      
    
    explicit oneshot(
      const output_value_type* data_,
      length_type       length_
    ) :
      _trigger(false),
      state(false),
      length(length_),
      data(data_),
      amplitude(sample_type_traits<amplitude_type>::maximum),
      phacc(0),
      phincr(0),
      next_phincr(0),
      accum(0) {}

    virtual phase_type index() {
      static const uint8_t shift     = 
        ((sizeof(phase_type) - sizeof(length_type)) << 3);
      
      return  phacc >> shift;
    }

    inline virtual void stop() {
      _trigger = false;
      state    = false;
      phacc    = 0;
      accum    = 0;
    }

    inline virtual output_value_type play() {
      if (_trigger) {
        _trigger = false;
        state    = true;
        phacc    = 0;
        
        if (next_phincr != 0) {
          phincr      = next_phincr;
          next_phincr = 0;
        }
      }
      
      if (index() >= length) {
        stop();
      }

      if (! state) return 0;

      static const uint8_t shift =
        sizeof(amplitude_type) << 3;

      accum   = amplitude * data[index()];
      accum >>= shift;
      
      phacc  += phincr;
      
      return accum;
    }
    
    inline virtual output_value_type read() {
      return play();
    }
    
    inline virtual void trigger() {
      _trigger = true;
    }
  };
}
#endif
