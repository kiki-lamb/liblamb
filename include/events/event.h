#ifndef LAMB_DRUMMER_EVENT_BASE_H
#define LAMB_DRUMMER_EVENT_BASE_H

#include <inttypes.h>

namespace lamb {
 namespace events {
  template <
   typename enum_t_,
   typename data_t_ = uint16_t,
   uint8_t bottom_bits_ = sizeof(data_t_) * 4,
   uint8_t top_bits_ = sizeof(data_t_) * 4
   >
  class event {
  public:
   typedef enum_t_ enum_t;
   typedef data_t_ data_t;

   static constexpr uint8_t top_bits = top_bits_;
   static constexpr uint8_t bottom_bits = bottom_bits_;
   static constexpr data_t  bottom_mask = ((uint64_t)1 << bottom_bits) - 1;
    
   typedef enum_t_ event_type;   
    
   event_type type;
   data_t parameter;

   inline event(
    event_type type_ = event_type(),
    data_t parameter_ = data_t()
   ) :
    type(type_),
    parameter(parameter_) {}
    
   inline data_t parameter_hi() const {
    return parameter >> bottom_bits;
   }

   inline data_t parameter_lo() const {
    return parameter & bottom_mask;
   }
    
   inline operator bool() const {
    return type != event_type();
   }
  };
 }
}

#endif
