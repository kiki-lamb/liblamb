#ifndef LAMBOS_ARRAY_QUEUE_H
#define LAMBOS_ARRAY_QUEUE_H

#include <inttypes.h>
#include "../array_list/array_list.h"
#include "../abstract_queue/abstract_queue.h"

// Dequeue is going to be remarkably inefficient for now
// because ArrayList<T0>::remove(0) is suboptimal.

namespace lamb {
  template<typename T0>
  class array_queue : public abstract_queue<T0>, private array_list<T0, delete_traits::non_owner> {
  public:
    explicit array_queue() : array_list<T0, delete_traits::non_owner>() {}

    virtual ~array_queue() {}

    void enqueue(T0 const & element) {
      array_list<T0, delete_traits::non_owner>::add(element);
    }

    T0 dequeue() {
      T0 tmp = array_list<T0, delete_traits::non_owner>::operator[](0);
      array_list<T0, delete_traits::non_owner>::remove(0);
      return tmp;
    }

    void clear() {
      array_list<T0, delete_traits::non_owner>::clear();
    }

    bool empty() {
      return array_list<T0, delete_traits::non_owner>::size() == 0;
    }
  };
}

#endif
