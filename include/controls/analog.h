#ifndef LAMB_DRUMMER_ANALOG_H
#define LAMB_DRUMMER_ANALOG_H

#include <Arduino.h>
#include "../sample_type_traits/sample_type_traits.h"
#include "../containers/light_buffer/light_buffer.h"

namespace lamb {
  namespace controls {
    class analog {
    private:
#ifdef __AVR__
      uint8_t  _pin;
#else
      uint32_t _pin;
#endif
      sample_type_traits<uint12_t>::mix_type _accum;
      uint8_t  _averaging;
      
    public:
      analog(
#ifdef __AVR__
  uint8_t  const & pin_,
  uint8_t  const & buffer_size_,
#else
  uint32_t const & pin_,
  uint8_t  const & buffer_size_,
#endif
  uint8_t  const & averaging_bb = 1
      );
      
      struct analog_event {
        uint8_t  signal_number;
        uint16_t adc_value;
        
        analog_event(
         uint8_t const & signal_number_,
         uint16_t const & adc_value_
        ) :
          signal_number(signal_number_),
          adc_value(adc_value_) {}
      };

      declare_dynamic_light_buffer(analog_event, analog_events);
      
      bool read();

      void setup();
    };
  }
}

#endif
