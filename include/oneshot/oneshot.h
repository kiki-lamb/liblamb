#ifndef KL_ONESHOT_H
#define KL_ONESHOT_H

#include "../sample_type_interfaces/sample_type_interfaces.h"

namespace lamb {
  class oneshot :
    public sample_source<int16_t>,
    triggerable,
    stoppable
  {
  protected:
    volatile bool                _trigger;

  public:
    typedef int16_t              output_value_type;
    typedef uint32_t             phase_type;

    bool                         state;
    phase_type                   length;
    const  output_value_type *   data;
    uint16_t                     amplitude;
    uint32_t                     phacc;
    uint32_t                     phincr;
    uint32_t                     next_phincr;
    uint32_t                     accum;      
    
    explicit oneshot(
      const int16_t* data_,
      uint32_t length_
    ) :
      _trigger(false),
      state(false),
      length(length_),
      data(data_),
      amplitude(255),
      phacc(0),
      phincr(0),
      next_phincr(0),
      accum(0) {}

    virtual uint32_t get_index() {
      uint32_t phacc_msb = phacc >> 16;
      return  phacc_msb;
    }

  protected:
    virtual void stop() {
      _trigger = false;
      state = false;
      phacc = 0;
      accum = 0;
    }

    virtual int16_t play() {
      if (_trigger) {
        _trigger = false;
        state    = true;
        phacc    = 0;
        
        if (next_phincr != 0) {
          phincr      = next_phincr;
          next_phincr = 0;
        }
      }
      
      if (get_index() >= length) {
        stop();
      }

      if (! state) {
        return 0;
      }

      accum = amplitude * data[get_index()];
      accum >>= 8;
      
      phacc += phincr;
      
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
