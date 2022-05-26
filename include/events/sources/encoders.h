#ifndef LAMB_DRUMMER_I_ENCODER_PAD_SOURCE_H
#define LAMB_DRUMMER_I_ENCODER_PAD_SOURCE_H

#include <Arduino.h>

namespace lamb {
  namespace events {
    namespace sources {
      template <
        class encoders_t_,
        typename event,
        uint8_t event_number
        >
      class encoders :
        public sources::source<event> {

      public:
        typedef encoders_t_ encoders_type;
  
      private:
        encoders_type * _device;
        uint8_t _button_number_mask;
  
      public:
        encoders(
          encoders_type * device_,
          uint8_t button_number_mask_
        ) :
          _device(device_),
          _button_number_mask(button_number_mask_) {}

      private:
        virtual void    impl_poll() {
          _device->read();
        }

        virtual uint8_t impl_queue_count() const {
          return _device->motion_events_count;
        }

        virtual event impl_dequeue_event() {
          if (! light_buffer_readable(_device->motion_events))
            return event { (typename event::event_type)0 };

          typename encoders_type::motion_event tmp =
            light_buffer_read(_device->motion_events);

          uint16_t event_arg = (
            ((tmp.encoder_number | _button_number_mask) << 8) |
            ((uint8_t)tmp.motion)
          );

          return event { (typename event::event_type)event_number, event_arg };
        };
      };
    }
  }
}

#endif
