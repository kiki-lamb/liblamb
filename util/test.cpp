#include <stdio.h>
#include <inttypes.h>

//////////////////////////////////////////////////////////////////////////////////////////

template <bool, class T = void> 
struct enable_if 
{};

template <class T> 
struct enable_if<true, T> 
{ 
 typedef T type; 
};

//////////////////////////////////////////////////////////////////////////////////////////

class base {
public:
 typedef uint8_t value_type;
 
 value_type value;

 static constexpr bool has_cons = true;
 
 struct cons {
  value_type x;
  value_type y;
 };

 base(value_type const & v) : value(v) {}

 base(cons const & c) : value(c.x + c.y) {} 
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename base_t>
class derived: public base_t {
public:
 typedef base_t base;

// template <typename U = base, bool enabled = U::has_cons>
// derived (typename U::cons obj) : base(obj) {}
 

 template <typename U = base, bool enabled = U::has_cons>
 derived (typename U::cons obj) : base(obj) {}

 derived (typename base::value_type val) : base(val) {}
};
//////////////////////////////////////////////////////////////////////////////////////////
 
int main() {

 derived<base> x0({1, 2});
 derived<base> x1(4);
 
 printf("x0: %u \n", x0.value);
 printf("x1: %u \n", x1.value);
}
