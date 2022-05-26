#ifndef LAMB_DRUMMER_EVENT_SOURCE_BUFFER_H
#define LAMB_DRUMMER_EVENT_SOURCE_BUFFER_H

#include "source.h"
#include "../../containers/light_buffer/light_buffer.h"

namespace lamb {
  namespace events {
    namespace sources {
      template <class event, size_t queue_size_>
      class buffer : public source<event> {
      public:
        sources::source<event> * source;
        
        buffer() : source(NULL) {}
        
      private:
        declare_light_buffer(event, queue_size_, event_queue);
        
        virtual uint8_t impl_queue_count() const {
          return event_queue_count;
        }
        
        virtual void impl_poll() {
          if (! source->poll())
            return;

          while (event e = source->dequeue_event()) {
           if (! e) {
#ifdef LAMB_DEBUG_EVENTS
            Serial.print("Queue null event from buffer's source.");
            Serial.println();
#endif
           }
           else {
#ifdef LAMB_DEBUG_EVENTS
            Serial.print("Queue ");
            Serial.print(e.type);
            Serial.print(" event from buffer's source.");
            Serial.println();
#endif
            light_buffer_write(event_queue, e);
           }
          }
        }
        
        virtual event impl_dequeue_event() {
          if (! light_buffer_readable(event_queue) ) {
#ifdef LAMB_DEBUG_EVENTS            
           Serial.print("Return a null event.");
           Serial.println();
#endif
           
           return event();
          }
          
          return light_buffer_read(event_queue);
        }
      };
    }
  }
}

#endif
