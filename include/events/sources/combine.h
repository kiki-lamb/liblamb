#ifndef LAMB_DRUMMER_EVENT_SOURCE_COMBINE_H
#define LAMB_DRUMMER_EVENT_SOURCE_COMBINE_H

#include "source.h"

namespace lamb {
  namespace events {
    namespace sources {
      template <class event, size_t sources_count_>
      class combine : public source<event> {
      public:
        source<event> * sources[sources_count_];

        combine() : sources() {}

      private:
        virtual uint8_t impl_queue_count() const {
          size_t tmp = 0;
          for (size_t ix = 0; ix < sources_count_; ix++)
            tmp += sources[ix]->queue_count();
          return tmp;
        }

        virtual void impl_poll() {
          for (size_t ix = 0; ix < sources_count_; ix++) {
            sources[ix]->poll();
          }
        }

        virtual event impl_dequeue_event() {
          for (size_t ix = 0; ix < sources_count_; ix++) {
            if (sources[ix]->ready()) {
              return sources[ix]->dequeue_event();
            }
          }

          return event();
        }
      };
    }
  }
}

#endif
