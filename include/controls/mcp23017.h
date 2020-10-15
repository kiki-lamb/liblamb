#ifndef LAMB_DRUMMER_PAD_MCP23017_H
#define LAMB_DRUMMER_PAD_MCP23017_H

#include <inttypes.h>
#include "Adafruit_MCP23017.h"

namespace lamb {
  namespace controls {
    class mcp23017 {
    protected:
      uint8_t             _button_count;
      uint8_t             _button_range_start;
      Adafruit_MCP23017 * _device;
      uint16_t            _buttons;
      uint16_t            _prev_buttons;
      uint16_t            _button_mask;
      uint8_t             _button_shift;       
  
    public:
      explicit mcp23017(
        uint8_t button_count_,
        uint8_t button_range_start_
      );

      void setup(Adafruit_MCP23017 * _device);

      virtual bool read();

    protected:
      uint16_t apply_button_mask(uint16_t value);
    };
  }
}

#endif
