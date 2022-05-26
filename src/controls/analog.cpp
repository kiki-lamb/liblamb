#include "../../include/controls/analog.h"
#include <Arduino.h>
#include <math.h>

lamb::controls::analog::analog(
#ifdef __AVR__
  uint8_t  const & pin_,  
  uint8_t  const & averaging_,
  uint8_t  const & number_
#else
  uint32_t const & pin_,
  uint8_t  const & averaging_,
  uint32_t const & number_
#endif
) :
  _pin(pin_),
  number(number_),
  _accum(0),
  _averaging(averaging_),
  _event_ready(false),
  _event(analog_event(number_, 0)) {

#ifdef __AVR__
  if (number == 0xff)
   number = _pin;
#else
  if (number == 0xffff'ffff)
   number = _pin;
#endif
}

void lamb::controls::analog::setup() {
  pinMode(_pin, INPUT);
}

bool lamb::controls::analog::read() {
  // if (! light_buffer_writable(analog_events)) {
  //   Serial.println("Buffer full.");
    
  //   return false;
  // }

  sample_type_traits<uint12_t>::mix_type tmp = _accum;
  
  _accum     <<= _averaging;
  _accum      -= tmp;
  
  tmp          = analogRead(_pin);

  _accum      += tmp;
  _accum     >>= _averaging;

  _event       = analog_event(number, _accum);
  _event_ready = true;
  // light_buffer_write(
  //   analog_events,
  //   (analog_event(number, _accum))
  // );
  
  return true;
}

bool lamb::controls::analog::ready() const {
 return _event_ready;
}

lamb::controls::analog::analog_event lamb::controls::analog::dequeue() {
 _event_ready = false;
 return _event;
}
