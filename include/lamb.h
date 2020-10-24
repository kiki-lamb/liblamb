#ifndef LAMBOS_H
  #define LAMBOS_H

  #ifdef LAMB_NO_ARDUINO
    #include <inttypes.h>
    #include <stddef.h>
  #else
    #include <Arduino.h>
  #endif

  #include "uint12_t.h"

  #include "sample_type_traits/sample_type_traits.h"

  #include "fix_math/fix_math.h"

  #include "sample_type_interfaces/sample_type_interfaces.h"

  #include "dsp/dsp.h"

  #include "global/global.h"
 
  #include "light_buffer/light_buffer.h"

  #include "functions/functions.h"

  #include "abstract_bag/abstract_bag.h"
  #include "abstract_list/abstract_list.h"
  #include "abstract_queue/abstract_queue.h"
  #include "abstract_stack/abstract_stack.h"

  #include "array_list/array_list.h"
  #include "array_queue/array_queue.h"

  #include "linked_list/linked_list.h"
  #include "linked_queue/linked_queue.h"
  #include "linked_stack/linked_stack.h"

  #include "ring_buffer/ring_buffer.h"

  #include "positional_fixed_array/positional_fixed_array.h"

  #include "fonts/fonts.h"

  #include "task/task.h"

#ifndef LAMB_NO_ARDUINO
  #include "encoder/encoder.h"
#endif

  #include "flag/flag.h"
  #include "midi_notes/midi_notes.h"
  #include "tables/tables.h"
  #include "table_osc/table_osc.h"
  #include "oneshot/oneshot.h"

  #include "lowpass_filter/moog_filter.h"
  #include "lowpass_filter/chamberlin.h"
  #include "lowpass_filter/lowpass_filter.h"
  #include "lowpass_filter/lowpass_filter_8.h"

  #ifdef LAMBOS_INCLUDE_SAMPLES
    #include "samples/samples22k.h"
    #include "samples/samples16k.h"
  #endif 

  #if defined(__AVR__)
    #include "fast_math/avr_fast_math.h"
  #endif

  #if !defined(__AVR_ATtiny85__) && !defined(LAMB_NO_ARDUINO) 
    #include "device/mcp4921/mcp4921.h"
  #endif

  #if defined(STM32F1)
    #include "maple_timer/maple_timer.h"
    #include "device/pt8211/pt8211.h"
    #include "device/Adafruit_ILI9341_STM_SPI2/Adafruit_ILI9341_STM_SPI2.h"
  #endif

  #include "events/event.h"
  #include "events/sources/buffer.h"
  #include "events/sources/source.h"
  #include "events/sources/combine.h"

  #ifndef LAMB_NO_ARDUINO
    #include "controls/analog.h"
    #include "controls/button.h"
    #include "controls/mcp23017.h"
    #include "controls/mcp23017_buttons.h"
    #include "controls/mcp23017_encoders.h"
    #include "events/sources/buttons.h"
    #include "events/sources/encoders.h"
    #include "events/sources/analog.h"
  #endif
#endif
