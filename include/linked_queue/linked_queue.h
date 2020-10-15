#ifndef LAMBOS_LINKED_QUEUE_H
#define LAMBOS_LINKED_QUEUE_H

#include <inttypes.h>
#include "../linked_list/linked_list.h"
#include "../abstract_queue/abstract_queue.h"

namespace lamb {
  template<typename T0>
  class linked_queue : public abstract_queue<T0>, private linked_list<T0, delete_traits::non_owner> {
  public:
    linked_queue() : linked_list<T0, delete_traits::non_owner>() {}

    virtual ~linked_queue() {}
	 
    void enqueue(T0 const & element) {
      linked_list<T0, delete_traits::non_owner>::add(element);
    }
	 
    T0 dequeue() {
      T0 tmp = linked_list<T0, delete_traits::non_owner>::operator[](0);
      linked_list<T0, delete_traits::non_owner>::remove(0);
      return tmp;
    }
	 
    void clear() {
      linked_list<T0, delete_traits::non_owner>::clear();
    }

    bool empty() {
      return linked_list<T0, delete_traits::non_owner>::size() == 0;
    }
  };
}

#endif
