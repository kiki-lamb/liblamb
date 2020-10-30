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

 static constexpr bool has_constructible_type = true;
 
 struct constructible_type {
  value_type x;
  value_type y;
 };

 explicit
 base(value_type const & v) : value(v) {}

 explicit 
 base(constructible_type const & c) : value(c.x + c.y) {}
 
};
//////////////////////////////////////////////////////////////////////////////////////////

template <typename base_t>
class derived: public base_t {
public:
 typedef base_t base;

 explicit derived(typename base::value_type const & v) : base(v) {}

 derived(
  typename base::constructible_type const & obj
 ) : base(obj) {}
 
};
//////////////////////////////////////////////////////////////////////////////////////////
 
int main() {

 derived<base> b({8, 4});

 printf("b: %u \n", b.value);
 
 printf("Done.\n");
}
