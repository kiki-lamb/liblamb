#include "../include/lamb.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

// P double  Direct.
// P      t  Direct.
// _      =  Default.
// P      ~  Direct.
// P      +  Direct.
// P      -  Direct.
// P      *  Direct.
// P      /  Direct.
// P      %  Direct.
// P     u~  Direct.
// P     <<  Direct.
// P     >>  Direct.
// P      >  Direct.
// P      <  Direct
// P     ==  Direct.
// P     u-  *
// C     !=  ==
// C     >=  >,  ==
// C     <=  >,  ==
// C     ++  +,  =
// C     --  +,  =
// C     +=  +,  =
// C     -=  -,  =
// C     /=  /,  =
// C     %=  %,  =
// C     *=  *,  =
// C    <<=  <<, =
// C    >>=  >>, =
// P     u+  No.

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_test.cpp && .\a.exe

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename value_type_>
class integer {
//----------------------------------------------------------------------------------------------------------------------
public:
 //---------------------------------------------------------------------------------------------------------------------
 typedef value_type_ value_type;
 //---------------------------------------------------------------------------------------------------------------------
 value_type value;
 //---------------------------------------------------------------------------------------------------------------------
 explicit
 integer(value_type const & v) : value(v) {}
 //---------------------------------------------------------------------------------------------------------------------
 /**/           operator     value_type(           )    const   = delete;
 //---------------------------------------------------------------------------------------------------------------------
 integer          operator  +  ()                         const   = delete;
 integer          operator  ~  ()                         const   { return integer(       ~ value      ); }
 integer          operator  -  ()                         const   { return integer(       - value      ); }
 integer          operator >>  (uint8_t const & shift)    const   { return integer(value >> shift      ); }
 integer          operator <<  (uint8_t const & shift)    const   { return integer(value << shift      ); }
 integer          operator  +  (integer   const & other)    const   { return integer(value  + other.value); }
 integer          operator  -  (integer   const & other)    const   { return integer(value  - other.value); }
 integer          operator  *  (integer   const & other)    const   { return integer(value  * other.value); }
 integer          operator  /  (integer   const & other)    const   { return integer(value  / other.value); }
 integer          operator  %  (integer   const & other)    const   { return integer(value  % other.value); }
 bool           operator  <  (integer   const & other)    const   { return      (value  < other.value); }
 bool           operator  >  (integer   const & other)    const   { return      (value  > other.value); }
 bool           operator ==  (integer   const & other)    const   { return      (value == other.value); }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename base>
class mathematized : public base {
//----------------------------------------------------------------------------------------------------------------------
public:
 //---------------------------------------------------------------------------------------------------------------------
 typedef typename base::value_type value_type;
 //--------------------------------------------------------------------------------------------------------------------- 
 explicit
 mathematized                (value_type   const & v) : base(v) {}
 //----------------------------------------------------------------------------------------------------------------------
 explicit       operator     value_type(            )   const   { return this->value;                                ; }
 //----------------------------------------------------------------------------------------------------------------------
 mathematized & operator  -- (                      )           { this        -= mathematized(1);        return *this; }
 mathematized & operator  ++ (                      )           { this        += mathematized(1);        return *this; }
 mathematized & operator >>= (uint8_t      const & v)           { this->value  = (*this    >> v ).value; return *this; }
 mathematized & operator <<= (uint8_t      const & v)           { this->value  = (*this    << v ).value; return *this; }
 mathematized & operator  -= (mathematized const & v)           { this->value  = (*this     - v ).value; return *this; }
 mathematized & operator  += (mathematized const & v)           { this->value  = (*this     + v ).value; return *this; }
 mathematized & operator  *= (mathematized const & v)           { this->value  = (*this     * v ).value; return *this; }
 mathematized & operator  /= (mathematized const & v)           { this->value  = (*this     / v ).value; return *this; }
 mathematized & operator  %= (mathematized const & v)           { this->value  = (*this     % v ).value; return *this; }
 bool           operator  <= (mathematized const & o)   const   { return         (*this    == o )     || (*this < o) ; }
 bool           operator  >= (mathematized const & o)   const   { return         (*this    == o )     || (*this > o) ; }
 bool           operator  != (mathematized const & o)   const   { return       ! (*this    == o )                    ; } 
//----------------------------------------------------------------------------------------------------------------------
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
 typedef mathematized<integer<uint8_t>> t;
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
