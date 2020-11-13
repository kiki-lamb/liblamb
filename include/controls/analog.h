#ifndef LAMB_DRUMMER_ANALOG_H
#define LAMB_DRUMMER_ANALOG_H

#include <Arduino.h>
#include "../sample_type_traits/sample_type_traits.h"
#include "../containers/light_buffer/light_buffer.h"

namespace lamb {
  namespace controls {
    class analog {
#ifdef __AVR__
    private:
      uint8_t  _pin;
    public:
     uint8_t  number = 0;
#else
    private:
     uint32_t _pin;
    public:
     uint32_t  number = 0;
#endif
      sample_type_traits<uint12_t>::mix_type _accum;
      uint8_t  _averaging;
     
    public:
      analog(
#ifdef __AVR__
  uint8_t  const & pin_,
  uint8_t  const & averaging_ = 2,
  uint8_t  const & number = 0xff
#else
  uint32_t const & pin_,
  uint8_t  const & averaging_ = 2,
  uint32_t const & number = 0xffff'ffff
#endif
      );
      
      struct analog_event {
#ifdef __AVR__
       uint8_t   number;
#else
       uint32_t  number;
#endif
       uint16_t adc_value;
        
        analog_event(
         uint8_t const & number_,
         uint16_t const & adc_value_
        ) :
          number(number_),
          adc_value(adc_value_) {}
      };


     bool _event_ready;
     analog_event _event;
     
     analog_event dequeue();
     bool ready() const;
     bool read();

      void setup();
    };
  }
}

#endif
