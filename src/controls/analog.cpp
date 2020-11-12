#include "../../include/controls/analog.h"
#include <Arduino.h>
#include <math.h>

lamb::controls::analog::analog(
#ifdef __AVR__
  uint8_t  const & pin_,
  uint8_t  const & signal_number,
#else
  uint32_t const & pin_,
  uint32_t const & signal_number,
#endif
  uint8_t  const & buffer_size_,
  uint8_t  const & averaging_
) :
  _pin(pin_),
  _signal_number(signal_number),
  _accum(0),
  _averaging(averaging_),
  _event_ready(false),
  _event(analog_event(_signal_number, 0)) {
// dynamic_light_buffer_resize(analog_event, analog_events, buffer_size_);

#ifdef __AVR__
  if (_signal_number == 0xff)
   _signal_number = _pin;
#else
  if (_signal_number == 0xffff'ffff)
   _signal_number = _pin;
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

  _event       = analog_event(_signal_number, _accum);
  _event_ready = true;
  // light_buffer_write(
  //   analog_events,
  //   (analog_event(_signal_number, _accum))
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
