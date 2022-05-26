#ifndef LAMBOS_ABSTRACT_BAG
#define LAMBOS_ABSTRACT_BAG

#include <inttypes.h>

namespace lamb {
  template <typename T0>
  class abstract_bag {
  public:
    virtual size_t size() const = 0;
    virtual void add(T0 const & element) = 0;
    virtual T0 & operator[](size_t index) = 0;
    virtual void clear() = 0;
    virtual ~abstract_bag() {};
    
    virtual void for_each(void(*proc)(T0 & obj)) {
      for (size_t ix = 0; ix < size(); ix++)
        proc(this->operator[](ix));
    }
  };
}

#endif
