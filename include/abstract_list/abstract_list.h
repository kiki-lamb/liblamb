#ifndef LAMBOS_ABSTRACT_LIST
#define LAMBOS_ABSTRACT_LIST

#include "../include/abstract_bag/abstract_bag.h"

namespace lamb {
  template <typename T0>
  class abstract_list : public abstract_bag<T0> {
  public:
    virtual void remove(size_t index) = 0;
    virtual void insert(size_t index, T0 const & element) = 0;
    virtual void set(size_t index, T0 const & element) = 0;
    virtual ~abstract_list() {};
  };
}

#endif
