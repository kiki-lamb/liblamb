#include <Arduino.h>
#include "../../include/controls/mcp23017.h"

lamb::controls::mcp23017::mcp23017(
    uint8_t button_count_,
    uint8_t button_range_start_
) :
  _button_count(button_count_), 
  _button_range_start(button_range_start_), 
  _device(NULL),             
  _buttons(0),
  _prev_buttons(0),           
  _button_mask(0), 
  _button_shift(0) {}

void lamb::controls::mcp23017::setup(Adafruit_MCP23017 * device_) {
  _device = device_;

  for (uint8_t ix = _button_range_start;
       ix < (_button_range_start + _button_count);
       ix++) {
    _device->pinMode(ix, INPUT);
    _device->pullUp(ix, HIGH);
  }

  uint16_t partial_mask = 0x8000;
    
  for (
    uint8_t ix = 0;
    ix < _button_count;
    ix++, partial_mask >>= 1) {
    _button_mask |= partial_mask;
  }

  _button_mask  >>= _button_range_start;
  _button_shift   = 16 - _button_count - _button_range_start;
}

uint16_t lamb::controls::mcp23017::apply_button_mask(
  uint16_t value
) {
  value  &= _button_mask;
  value >>= _button_shift;
  
  return value;  
}

bool lamb::controls::mcp23017::read() {
  _prev_buttons = _buttons;
  _buttons      = ~_device->readGPIOAB();
  
  if (_buttons == _prev_buttons) return false;
  
  return true;
}
