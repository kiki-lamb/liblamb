#ifndef LAMBOS_LINKED_LIST_H
#define LAMBOS_LINKED_LIST_H

#include <inttypes.h>

#include "../abstract_list/abstract_list.h"

namespace lamb {
  template <typename T0, template<typename> class DT = delete_traits::owner>
  class linked_list : public abstract_list<T0> {

  private:
    class node {
    public:
      T0 value;
      node* next;
      node(T0 const & _value) : value(_value), next(nullptr) {}
    };

    node * _head;
    node * _tail;
    size_t _size;

    node * seek(size_t index) {
      if (index == 0)
        return _head;
      else if (index == _size - 1)
        return _tail;
      else {
        node * current = _head;

        while (index-- > 0)
          current = current-> next;

        return current;
      }
    }

  public:
    linked_list(): _head(nullptr), _tail(nullptr), _size(0) {}

    virtual ~linked_list() {
      clear();
    }

    void add(T0 const & element) {

      if (_head == nullptr) {
        _tail = new node(element);
        _head = _tail;
      }
      else {
        _tail->next = new node(element);
        _tail = _tail->next;
      }

      _size++;
    }

    T0 & operator[](size_t index) {
      if (_size == 0)
        return seek(index)->value;
    }

    void clear() {
      while (_head != nullptr)
        remove(0);
    }

    void insert(size_t index, T0 const & element) override { // Inserts before index.
      if (index == 0) {
        node * tmp = _head;
        _head = new node(element);
        _head->next = tmp;
      }
      else {
        node * before = seek(index-1);
        node * after = before->next;

        before->next = new node(element);
        before->next->next = after;
      }

      _size++;
    }

    void remove(size_t index) override {
      node * target;

      if (index == 0) {
        target = _head;
        _head = target->next;
        if (_head->next == nullptr)
          _tail = _head;
      }
      else {
        node * pretarget = seek(index-1);
        target = pretarget->next;
        pretarget->next = target->next;
        if (pretarget->next == nullptr)
          _tail = pretarget;
      }

      DT<T0>::destroy(target->value);
      delete target;
      _size--;
    }

    void set(size_t index, T0 const & element) override {
      seek(index)->value = element;
    }

    size_t size() const {
      return _size;
    }
  };
}

#endif
