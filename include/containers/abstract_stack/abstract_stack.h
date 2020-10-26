#ifndef LAMBOS_ABSTRACT_STACK
#define LAMBOS_ABSTRACT_STACK

namespace lamb {
  template <typename T0>
  class abstract_stack {
  public:
    virtual void push(T0 const & element) = 0;
    virtual T0   pop() = 0;
    virtual void clear() = 0;
    virtual bool empty() = 0;
    virtual ~abstract_stack() {};
  };
}

#endif
