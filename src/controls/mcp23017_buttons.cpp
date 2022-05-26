#include "../../include/controls/mcp23017_buttons.h"

lamb::controls::mcp23017_buttons::mcp23017_buttons(
  uint8_t button_count_,
  uint8_t button_range_start_
) :
  mcp23017(button_count_, button_range_start_)
{
  dynamic_light_buffer_resize(button_event, button_events, _button_count);
}

bool lamb::controls::mcp23017_buttons::read() {
  if (! mcp23017::read()) return false;
  
  uint16_t tmp_buttons    = apply_button_mask(_buttons & ~_prev_buttons);
  uint16_t partial_mask   = 0b1;
  partial_mask          <<= (_button_count-1);
  
  for (uint8_t ix = 0; ix < _button_count; ix++, partial_mask >>=1 ) {
    if (tmp_buttons & partial_mask) {
      light_buffer_write(
        button_events,
        (button_event { ix, true })
      );
    }
  }

  return light_buffer_readable(button_events);
}
