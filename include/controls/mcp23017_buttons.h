#ifndef LAMB_DRUMMER_BUTTON_PAD_P_MCP23017_H
#define LAMB_DRUMMER_BUTTON_PAD_P_MCP23017_H

#include <Arduino.h>
#include "mcp23017.h"
#include "../containers/light_buffer/light_buffer.h"

namespace lamb {
  namespace controls {
    class mcp23017_buttons : public mcp23017 {
    public:
      struct button_event {
        uint8_t number;
        bool button_state;
      };
  
      declare_dynamic_light_buffer(button_event, button_events);

    private:
      mcp23017_buttons();

    public:
      explicit mcp23017_buttons(
        uint8_t button_count_,
        uint8_t button_range_start_
      );

      virtual bool read() override;
    };
  }
}

#endif
