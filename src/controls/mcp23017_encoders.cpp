#include "../../include/controls/mcp23017_encoders.h"

lamb::controls::mcp23017_encoders::mcp23017_encoders(
  uint8_t encoder_count_,
  uint8_t button_range_start_
) :
  mcp23017((encoder_count_ << 1), button_range_start_),
  _encoder_count(encoder_count_),
  _encoder_states(NULL)
{
  dynamic_light_buffer_resize(motion_event, motion_events, _encoder_count);

  _encoder_states = static_cast<encoder_state *>(
    calloc(
      _encoder_count,
      sizeof(encoder_state)
    )
  );
}

bool lamb::controls::mcp23017_encoders::read() {
  if (! mcp23017::read()) return false;
    
  uint16_t tmp_buttons    = apply_button_mask(_buttons);   
  uint16_t partial_mask   = 0b11;  
  partial_mask          <<= (_encoder_count-1) << 1;

  for (uint8_t ix = 0; ix < _encoder_count; ix++, partial_mask >>= 2) {
    uint16_t cut     = partial_mask & tmp_buttons;
    uint8_t  shifted = cut >> (((_encoder_count-1) << 1) - (ix << 1));

    _encoder_states[ix].update(shifted);

    if (_encoder_states[ix].flagged && light_buffer_writable(motion_events)) {
      light_buffer_write(
        motion_events,
        (motion_event { ix, (int8_t)(_encoder_states[ix].motion >> 1) })
      );
      
      _encoder_states[ix].motion = 0;
      _encoder_states[ix].flagged = false;
    }
  }
    
  return light_buffer_readable(motion_events);
}
