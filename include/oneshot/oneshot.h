#ifndef KL_ONESHOT_H
#define KL_ONESHOT_H

#include "../sample_type_interfaces/sample_type_interfaces.h"

namespace lamb {
  template <
    typename value_t_,
    typename phase_t_ = uint32_t,
    typename amplitude_t_ = uint8_t>
  class oneshot :
    public sample_source<value_t_>,
    triggerable,
    stoppable
  {
  protected:
    volatile bool                _trigger;

  public:
    typedef value_t_             value_type;
    typedef phase_t_             phase_type;
    typedef amplitude_t_         amplitude_type;
    typedef typename sample_type_traits<value_type>::mix_type
                                 accum_type; 
    typedef value_type           output_value_type;

    bool                         state;
    uint32_t                     length;
    const  output_value_type *   data;
    amplitude_type               amplitude;
    phase_type                   phacc;
    phase_type                   phincr;
    phase_type                   next_phincr;
    accum_type                   accum;      
    
    explicit oneshot(
      const value_type* data_,
      uint32_t length_
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
      const uint8_t shift     = 16; 
//        ((sizeof(phase_type) - sizeof(value_type)) << 3);
      
      phase_type    phacc_msb = phacc >> shift;
      
      return  phacc_msb;
    }

  protected:
    virtual void stop() {
      _trigger = false;
      state    = false;
      phacc    = 0;
      accum    = 0;
    }

    virtual value_type play() {
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

      if (! state) {
        return 0;
      }

      accum   = amplitude * data[index()];
      accum >>= sizeof(amplitude_type) << 3;
      
      phacc  += phincr;
      
      return accum;
    }
    
  public:
    virtual output_value_type read() {
      return play();
    }
    
    virtual void trigger() {
      _trigger = true;
    }
  };
}
#endif
