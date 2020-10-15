#ifndef LAMB_DRUMMER_ENCODER_P_PAD_MCP23017_H
#define LAMB_DRUMMER_ENCODER_P_PAD_MCP23017_H

#include <inttypes.h>
#include "mcp23017.h"
#include "encoder_state/encoder_state.h"
#include "../light_buffer/light_buffer.h"

namespace lamb {
  namespace controls {
    class mcp23017_encoders : public mcp23017 {
    private:
      uint8_t _encoder_count;

      encoder_state * _encoder_states;
  
    public:
      struct motion_event {
        uint8_t encoder_number;
        int8_t motion;
      };

      declare_dynamic_light_buffer(motion_event, motion_events);

    private:
      mcp23017_encoders();

    public:
      explicit mcp23017_encoders(
        uint8_t encoder_count_,
        uint8_t button_range_start_
      );

      virtual bool read() override;
    };
  }
}

#endif
 
