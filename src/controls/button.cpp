#include "../../include/controls/button.h"

void lamb::controls::button::setup() {
  pinMode(_pin, _pin_mode);
}

bool lamb::controls::button::read() {
  bool val = digitalRead(_pin);

  if ((! val) && (_last_state)) {
    light_buffer_write(
      button_events,
      (button_event { number, true })
    );

    _last_state = val;
    
    return true;
  }

  _last_state = val;
  
  return false;
}

lamb::controls::button::button(
#ifdef __AVR__
  uint8_t       pin_,
  uint8_t       number_,
  uint8_t       pin_mode_
#else
  uint32_t      pin_,
  uint8_t       number_,
  WiringPinMode pin_mode_
#endif
) :
  _pin(pin_),
  number(number_),
  _pin_mode(pin_mode_) {
  if (number_ == 0xff) {
    number = (uint8_t)_pin;
  }
}
  
