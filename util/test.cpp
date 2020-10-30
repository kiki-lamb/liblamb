#include <stdio.h>
#include <inttypes.h>

//////////////////////////////////////////////////////////////////////////////////////////

class base {
public:
 typedef uint8_t value_type;
 
 value_type value;

 static constexpr bool has_constructible_type = true;
 
 struct constructible_type {
  value_type x;
  value_type y;
 };

 base(value_type const & v) : value(v) {}

 base(constructible_type const & c) : value(c.x + c.y) {} 
};

//////////////////////////////////////////////////////////////////////////////////////////

class simple {
public:
 typedef uint8_t value_type;
 
 value_type value;

 static constexpr bool has_constructible_type = false;
 
 simple(value_type const & v) : value(v) {}
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename base_t>
class derived: public base_t {
public:
 typedef base_t base;

// template <typename U = base, bool enabled = U::has_constructible_type>
// derived (typename U::constructible_type obj) : base(obj) {}
 

 template <typename base_ = base, bool enabled = base_::has_constructible_type>
 derived (typename base_::constructible_type obj) : base(obj) {}

 derived (typename base::value_type val) : base(val) {}
};
//////////////////////////////////////////////////////////////////////////////////////////
 
int main() {

 derived<base> x0({1, 2});
 derived<base> x1(4);
 
 printf("x0: %u \n", x0.value);
 printf("x1: %u \n", x1.value);

 derived<simple> x2(5);
 printf("x2: %u \n", x2.value);
}
