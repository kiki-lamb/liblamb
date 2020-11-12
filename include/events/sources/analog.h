#ifndef LAMB_DRUMMER_ANALOG_SOURCE_H
#define LAMB_DRUMMER_ANALOG_SOURCE_H

#include <Arduino.h>

 namespace lamb {
  namespace events {
    namespace sources {    
      template <
        class analog_t_,
        typename event,
        uint8_t  event_number
        >
      class analog :
        public source<event>{
        
      public:
        typedef analog_t_ analog_type;
        
      private:
        analog_type  * _device;

      public:
        analog(
          analog_t_    * device_
             ) : 
          _device(device_) {}

      private:
        virtual void    impl_poll() {
          _device->read();
        }

        virtual uint8_t impl_queue_count() const {
         return _device->ready() ? 1 : 0;
        }

        virtual event impl_dequeue_event() {
         if (_device->ready()) {                 
          typename analog_type::analog_event tmp =
           _device->dequeue();
          
          uint16_t event_arg = (tmp.signal_number << 12) | tmp.adc_value;
          
          return event { (typename event::event_type)event_number, event_arg };
         }

         Serial.print("Give null analog event.");

         return event { (typename event::event_type)0, 0 };
        };
      };
    }
  }
}
#endif
