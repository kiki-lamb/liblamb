#ifndef LAMBOS_ARRAY_LIST_H
#define LAMBOS_ARRAY_LIST_H

#include <inttypes.h>

#include "../abstract_list/abstract_list.h"

namespace lamb {
  template <typename T0, template<typename> class DT = delete_traits::non_owner>
  class array_list : public abstract_list<T0> {
  private:
    T0*    _array = 0;
    size_t _used = 0;
    size_t _capacity = 0;		
		
    void grow_if_full() {
      if (_used == _capacity) {				
        set_capacity(_capacity + 1);
      }
    }
			
  public:
    explicit array_list(size_t capacity = 0) {
      set_capacity(capacity);
    }

    virtual ~array_list() {
      set_capacity(0);
      free(_array);
    }
		
    void set_capacity(size_t new_capacity) {
      if (new_capacity < _used) {
        for (size_t ix = new_capacity; ix < _used; ix++) {
          DT<T0>::destroy(_array[ix]);
          
          _used = new_capacity; 			
        }
      }
        
      _capacity = new_capacity;
      _array = (T0 *)realloc(_array, _capacity * sizeof(T0));

#ifndef LAMB_NO_ARDUINO
      Serial.print("PTR: ");
      Serial.println((size_t)_array, HEX);
#endif
    }

    T0 & operator[](size_t index) {			
      return _array[index];
    }

    void add(T0 const & element) {			
      grow_if_full();
			
      _array[_used] = element;
      _used++;


    }
		
    void clear() {
      set_capacity(0);
    }

    void insert(size_t index, T0 const & element) override { // Inserts before index.
      grow_if_full();

      for (size_t ix = _used + 1; ix > index; ix--)
        _array[ix] = _array[ix - 1];

      _used++;		

      set(index, element);
    }

    void remove(size_t index) override {
      // NOTE TO SELF: Optimize 0 case.

      DT<T0>::destroy(_array[index]);
					
      for (;index < _used - 1; index++)
        _array[index] = _array[index + 1];
      _used--;

    }

    void set(size_t index, T0 const & element) override {
      DT<T0>::destroy(_array[index]);
      _array[index] = element;
    }
		
    size_t size() const {
      return _used;
    }
		
    size_t capacity() const {			
      return _capacity;
    }
		
    void compact() {			
      if (_capacity > _used)
        set_capacity(_used);
    }
  };
}

#endif
