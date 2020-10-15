#ifndef LAMB_RING_BUFFER_H
#define LAMB_RING_BUFFER_H

#include <inttypes.h>

namespace lamb {
  template <typename T, size_t SIZE>
  class ring_buffer : abstract_queue<T> {
  public:
    typedef T         value_type;

  private:
    size_t  write_ix;
     size_t  read_ix;
    size_t  count_;
    value_type buff[SIZE];

  public:
    explicit ring_buffer() : write_ix(0), read_ix(0), count_(0) {}

    bool writable() {
      return count_ < SIZE;
    }

    bool readable() {
      return count_;
    }

    virtual void clear() {
      write_ix = 0;
      read_ix = 0;
      count_ = 0;
    }

    virtual bool empty() {
      return (0 == count_);
    }

    virtual void enqueue(value_type const & t) {
      buff[write_ix] = t;
      count_++;
      write_ix++;
      write_ix %= SIZE;
    }

    virtual value_type dequeue() {
      value_type const & tmp = buff[read_ix];
      count_--;
      read_ix++;
      read_ix %= SIZE;
      return tmp;
    }

    size_t count() const {
      return count_;
    }
  };

  //////////////////////////////////////////////////////////////////////////////

  template <typename T>
  class ring_buffer256 {
    
  public:
    typedef T value_type;

  private:
    size_t  write_ix;
    size_t  read_ix;
    size_t  count_;
    value_type buff[256];

  public:
    explicit ring_buffer256() : write_ix(0), read_ix(0), count_(0) {}

    bool writable() {
      return count_ < 255;
    }

    bool readable() {
      return count_;
    }

    void write(value_type t) {
      buff[write_ix] = t;
      count_++;
      write_ix++;
    }

    value_type read() {
      value_type & tmp = buff[read_ix];
      count_--;
      read_ix++;
      return tmp;
    }

    size_t count() const {
      return count_;
    }
  };

}
#endif
