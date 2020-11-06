#ifndef KL_ONESHOT_H
#define KL_ONESHOT_H

#include "../sample_type_interfaces/sample_type_interfaces.h"

namespace lamb {
 template <
  typename value_t_,
  typename output_value_t_ = value_t_,
  typename length_t_    = uint16_t,
  typename phase_t_     = typename q<0, 0, 8 * (sizeof(length_t_) + 2)>::value_type,
  typename amplitude_t_ = typename q<0, 0, 8 * (sizeof(value_t_) >> 1)>::value_type
  >
 class oneshot :
  public sample_source<value_t_>,
  triggerable,
  stoppable
 {
 protected:
  volatile bool                _trigger;

 public:
  typedef value_t_             table_value_type;
  typedef output_value_t_      output_value_type;
  typedef length_t_            length_type;
  typedef phase_t_             phase_type;
  typedef amplitude_t_         amplitude_type;

  bool                         state;
  length_type                  length;
  const table_value_type *    data;
  amplitude_type               amplitude;
  phase_type                   phacc;
  phase_type                   phincr;
  phase_type                   next_phincr;
    
  explicit oneshot(
   const table_value_type* data_,
   length_type       length_
  ) :
   _trigger(false),
   state(false),
   length(length_),
   data(data_),
   amplitude(sample_type_traits<amplitude_type>::maximum),
   phacc(0),
   phincr(0),
   next_phincr(0) {}

  virtual phase_type index() {
   static const uint8_t shift     = 
    ((sizeof(phase_type) - sizeof(length_type)) << 3);
      
   return  phacc >> shift;
  }

  inline virtual void stop() {
   // _trigger = false;
   state    = false;
   phacc    = 0;
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

   typename sample_type_traits<table_value_type>::mix_type accum =
    amplitude * data[index()];
   
   accum >>= shift;

   phacc  += phincr;
      
   return output_value_type(accum);
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
