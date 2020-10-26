#ifndef LAMBOS_ABSTRACT_QUEUE
#define LAMBOS_ABSTRACT_QUEUE

namespace lamb {
  template <typename T0>
  class abstract_queue {
  public:
    virtual void enqueue(T0 const & element) = 0;
    virtual T0   dequeue() = 0;
    virtual void clear() = 0;
    virtual bool empty() = 0;
    virtual      ~abstract_queue() {};
  };
}

#endif
