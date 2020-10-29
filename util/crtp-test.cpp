#include "../include/lamb.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_test.cpp && .\a.exe

////////////////////////////////////////////////////////////////////////////////


template <typename c>
class mathematized;


template <typename value_type_>
class thing {
public:
 typedef value_type_ value_type;

 value_type value;

 explicit
 thing(value_type const & v) : value(v) {}

//  double  Direct.
//       t  Direct.
//       =  Direct.      
// C     +  Direct.
// C     -  Direct.
// C     *  Direct.
// C     /  Direct.
// C     %  Direct.
//      u~  Direct.
//      <<  Direct.
//      >>  Direct.
//       =  Direct.
//       >  Direct.
//       <  Direct.
//      ==  Direct.
//      u-  *
//      !=  ==
//      >=  >,  ==
//      <=  >,  ==
// P    ++  +,  =
// P    --  +,  =
// P    +=  +,  =
// P    -=  -,  =
// P    /=  /,  =
// P    %=  %,  =
// P    *=  *,  =
// P   <<=  <<, =
// P   >>=  >>, =
// C    u+  No.


 thing        operator +  ()                      = delete;
 thing        operator +  (thing   const & other) { return thing(value  + other.value); }
 thing        operator -  (thing   const & other) { return thing(value  - other.value); }
 thing        operator *  (thing   const & other) { return thing(value  * other.value); }
 thing        operator /  (thing   const & other) { return thing(value  / other.value); }
 thing        operator %  (thing   const & other) { return thing(value  % other.value); }
 thing        operator >> (uint8_t const & shift) { return thing(value >> shift      ); }
 thing        operator << (uint8_t const & shift) { return thing(value << shift      ); }
 
};

template <typename base>
class mathematized : public base {
public:
 typedef typename base::value_type value_type;
 explicit
 mathematized             (value_type   const & v) : base(v) {}  
 mathematized operator += (mathematized const & v) { this->value = (*this  + v   ).value; return *this; }
 mathematized operator -= (mathematized const & v) { this->value = (*this  - v   ).value; return *this; }
 mathematized operator ++ ()                       { this += 1;                                         }
 mathematized operator -  ()                       { this  * 1;                                         }
 mathematized operator -- ()                       { this -= 1;                                         }
 mathematized operator *= (mathematized const & v) { this->value = (*this  * v   ).value; return *this; }
 mathematized operator /= (mathematized const & v) { this->value = (*this  / v   ).value; return *this; }
 mathematized operator %= (mathematized const & v) { this->value = (*this  % v   ).value; return *this; }
 mathematized operator >> (uint8_t      const & v) { this->value = (*this >> v   ).value; return *this; }
 mathematized operator << (uint8_t      const & v) { this->value = (*this << v   ).value; return *this; }

 explicit
 operator value_type() {
  return *(value_type*)this;
 }

 explicit
 operator value_type() const {
  return *(value_type*)this;
 }
};


int main() {
 typedef mathematized<thing<uint8_t>> t;
 t x(7);
 t y(9);
 t z(8);

 
 printf("=> %u \n", (x + y).value);

 x += y;
 x += z;

 printf("=> %u \n", x.value);

 if constexpr(integer_traits<uint16_t>::SIGNED) {
  printf("YES\n");
 }
 else {
  printf("NO\n");
 }
}
