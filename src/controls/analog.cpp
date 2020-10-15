#include "../../include/controls/analog.h"
#include <Arduino.h>
#include <math.h>

lamb::controls::analog::analog(
#ifdef __AVR__
  uint8_t  const & pin_,
  uint8_t  const & buffer_size_,
#else
  uint32_t const & pin_,
  uint8_t  const & buffer_size_,
#endif
  uint8_t  const & averaging_
) :
  _pin(pin_),
  _accum(0),
  _averaging(averaging_) {
  dynamic_light_buffer_resize(analog_event, analog_events, buffer_size_);
}

void lamb::controls::analog::setup() {
  pinMode(_pin, INPUT);
}

bool lamb::controls::analog::read() {
  if (! light_buffer_writable(analog_events)) {
    Serial.println("Buffer full.");
    
    return false;
  }

  uint32_t tmp = _accum;
  
  _accum     <<= _averaging;
  _accum      -= tmp;
  
  tmp          = analogRead(_pin);

  _accum      += tmp;
  _accum     >>= _averaging;

  light_buffer_write(
    analog_events,
    (analog_event(((uint8_t)_pin), _accum))
  );
  
  return true;
}
