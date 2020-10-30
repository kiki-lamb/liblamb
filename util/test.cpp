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

 static constexpr bool has_constructable_type = true;
 
 struct constructable_type {
  value_type x;
  value_type y;
 };

 explicit
 base(value_type const & v) : value(v) {}

 explicit 
 base(constructable_type const & c) : value(c.x + c.y) {}
 
};


//////////////////////////////////////////////////////////////////////////////////////////
 
int main() {

 base b({8, 4});

 printf("b: %u \n", b.value);
 
 printf("Done.\n");
}
