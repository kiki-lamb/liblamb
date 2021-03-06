#ifndef LAMB_DRUMMER_BUTTON_H
#define LAMB_DRUMMER_BUTTON_H

#include <Arduino.h>
#include "../containers/light_buffer/light_buffer.h"

// Right now, this generally assumes pins are pulled up and brought to ground
// by the button.

namespace lamb {
  namespace controls {
    class button {
    private:
      bool _last_state;
      
#ifdef __AVR__
    private:
     uint8_t       _pin;
    public:
      uint8_t       number;
    private:
     uint8_t       _pin_mode = INPUT_PULLUP;
#else
    private:
      uint32_t      _pin;
    public:
      uint8_t       number;
    private:
      WiringPinMode _pin_mode = INPUT_PULLUP;
#endif
      
    public:
      struct button_event {
        uint8_t number;
        bool button_state;
      };

      declare_light_buffer(button_event, 2, button_events);

      bool read();

      void setup();

      button(
#ifdef __AVR__
        uint8_t pin_,
        uint8_t number_  = 0xff,
        uint8_t pin_mode_       = INPUT_PULLUP
#else
        uint32_t pin_,
        uint8_t number_  = 0xff,
        WiringPinMode pin_mode_ = INPUT_PULLUP
#endif
      );

    };
  }
}

#endif
