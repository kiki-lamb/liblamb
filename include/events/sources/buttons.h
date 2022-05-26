#ifndef LAMB_DRUMMER_BUTTON_PAD_SOURCE_H
#define LAMB_DRUMMER_BUTTON_PAD_SOURCE_H

#include <Arduino.h>

namespace lamb {
  namespace events {
    namespace sources {    
      template <
        class buttons_t_,
        typename event,
        uint8_t  event_number
        >
      class buttons :
        public source<event>{
        
      public:
        typedef buttons_t_ buttons_type;

      private:
        buttons_type  * _device;
        uint8_t _number_mask;

      public:
        buttons(
          buttons_t_    * device_,
          uint8_t number_mask_ = 0
        ) : 
          _device(device_),
          _number_mask(number_mask_) {}

      private:
        virtual void    impl_poll() {
          _device->read();
        }

        virtual uint8_t impl_queue_count() const {
          return _device->button_events_count;
        }

        virtual event impl_dequeue_event() {
         if (! light_buffer_readable(_device->button_events)) {
          Serial.print("Give null button event.");
          return event { (typename event::event_type)0 };
         }

          typename buttons_type::button_event tmp =
            light_buffer_read(_device->button_events);

          uint16_t event_arg = (
            ((tmp.number | _number_mask) << 8) |
            ((uint8_t)tmp.button_state)
          );

          return event { (typename event::event_type)event_number, event_arg };
        };
      };
    }
  }
}
#endif
