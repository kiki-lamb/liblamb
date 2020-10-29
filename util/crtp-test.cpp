#include "../include/lamb.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_test.cpp && .\a.exe

////////////////////////////////////////////////////////////////////////////////


template <typename c>
class parent;


template <typename integer_>
class child {
public:
 typedef integer_ integer;
 integer value;

 inline child(integer const & v) : value(v) {}
 
 inline child operator + (child const & other) {
  child r(0);

  r.value = value + other.value;

  return r;
 }
};

template <typename c>
class parent : public c {
public:
 inline parent(typename c::integer const & v) : c(v) {}

 parent operator += (parent const & v) {
  c::value = ((*this) + v).value;
  
  return *this;
 }

 operator c() {
  return *((c*)this);
 }
 
 operator c() const {
  return *((c*)this);
 }
};


int main() {
 parent<child<uint8_t>> x(7);
 parent<child<uint8_t>> y(9);

 
 printf("=> %u \n", (x + y).value);

 x += y;

 printf("=> %u \n", x.value);
}
