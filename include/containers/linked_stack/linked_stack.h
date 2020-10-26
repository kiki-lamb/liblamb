#ifndef LAMBOS_LINKED_STACK_H
#define LAMBOS_LINKED_STACK_H

#include <inttypes.h>
#include "../linked_list/linked_list.h"
#include "../abstract_stack/abstract_stack.h"

namespace lamb {
  template<typename T0>
  class linked_stack : public abstract_stack<T0>, private linked_list<T0, delete_traits::non_owner> {
    typedef linked_list<T0, delete_traits::non_owner> base_t;

  public:
    linked_stack() : base_t() {}
	 
    virtual ~linked_stack() {}

    void push(T0 const & element) {
      base_t::add(element);
    }
	 
    T0 pop() {
      size_t ix = base_t::size() - 1;
      T0 tmp = base_t::operator[](ix);
      base_t::remove(ix);
      return tmp;
    }
	 
    void clear() {
      base_t::clear();
    }

    bool empty() {
      return base_t::size() == 0;
    }
  };
}

#endif
