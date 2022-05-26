#ifndef LAMBOS_POSITIONAL_FIXED_ARRAY_H
#define LAMBOS_POSITIONAL_FIXED_ARRAY_H

#include <inttypes.h>
#include <stdlib.h>

namespace lamb {
  template <size_t size_, class item_t_>
  class positional_fixed_array {
  private:
    item_t_ _items[size_];
    size_t  _index;

    static const size_t _size = size_;
  public:
    
    #if __cplusplus >= 201402L
      void operator delete(void * ptr) { free(ptr); }
    #endif

    typedef item_t_ item_t;

    explicit positional_fixed_array() : _index(0) {
      for (size_t ix = 0; ix < size(); ix++)
        _items[ix] = item_t();
    }

    ~positional_fixed_array() {}

    bool decrement_index() {
      if (_index > 0) {
        _index--;

        return true;
      }

      return false;
    }

    bool increment_index() {
      if (_index < (size() - 1)) {
        _index++;

        return true;
      }

      return false;
    }

    bool operator++(int) {
      return increment_index();
    }

    bool operator--(int) {
      return decrement_index();
    }

    size_t index() const {
      return _index;
    }

    static constexpr size_t size() {
      return _size;
    }

    item_t const & operator[](size_t const & index_) const {
      return _items[index_];
    }

    item_t & operator[](size_t const & index_) {
      return _items[index_];
    }

    item_t const & current() const {
      return _items[index()];
    }

    item_t & current() {
      return _items[index()];
    }

    bool jump(size_t const & index) {
      if (index >= size())
        return false;

//      Serial.print(F("JUMP TO "));
//      Serial.println(index);
      
      _index = index;
      
      return true;
    }
  };
}
#endif
