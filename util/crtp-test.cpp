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
 typedef integer_traits<value_type_> traits;
 typedef typename traits::type   value_type;
 //---------------------------------------------------------------------------------------------------------------------
 value_type value;
 //---------------------------------------------------------------------------------------------------------------------
 explicit
 integer(value_type const & v) : value(v) {}
 //---------------------------------------------------------------------------------------------------------------------
 /**/           operator     value_type(           )    const   = delete;
 //---------------------------------------------------------------------------------------------------------------------
 integer        operator  +  ()                         const   = delete;
 integer        operator  ~  ()                         const   { return integer(       ~ value      ); }
 integer        operator  -  ()                         const   { return integer(       - value      ); }
 //---------------------------------------------------------------------------------------------------------------------
 integer        operator >>  (uint8_t const & shift)    const   { return integer(value >> shift      ); }
 integer        operator <<  (uint8_t const & shift)    const   { return integer(value << shift      ); }
 integer        operator  +  (integer const & other)    const   { return integer(value  + other.value); }
 integer        operator  -  (integer const & other)    const   { return integer(value  - other.value); }
 integer        operator  *  (integer const & other)    const   { return integer(value  * other.value); }
 integer        operator  /  (integer const & other)    const   { return integer(value  / other.value); }
 integer        operator  %  (integer const & other)    const   { return integer(value  % other.value); }
 //---------------------------------------------------------------------------------------------------------------------
 bool           operator  <  (integer const & other)    const   { return        (value  < other.value); }
 bool           operator  >  (integer const & other)    const   { return        (value  > other.value); }
 bool           operator ==  (integer const & other)    const   { return        (value == other.value); }
 //---------------------------------------------------------------------------------------------------------------------
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <uint8_t whole, uint8_t frac>
class q {
//----------------------------------------------------------------------------------------------------------------------
public:
 //---------------------------------------------------------------------------------------------------------------------
 static constexpr uint8_t WHOLE       = whole;
 static constexpr uint8_t FRAC        = frac;
 static constexpr uint8_t SIZE        = size_fit_bits(whole + frac);
 static constexpr uint8_t BIG_SIZE    = size_fit_bits((SIZE + 1) << 3);
 static constexpr bool    SIGNED      = ((WHOLE + FRAC ) % 2) == 1;
 //---------------------------------------------------------------------------------------------------------------------
 typedef find_integer<SIGNED, SIZE>     traits;
 typedef typename traits::type          value_type;
 //---------------------------------------------------------------------------------------------------------------------
 typedef find_integer<SIGNED, BIG_SIZE> big_traits;
 typedef typename traits::type          big_value_type;
 //---------------------------------------------------------------------------------------------------------------------
 static constexpr q       MAX         = q(traits::MAX);
 static constexpr q       MIN         = q(traits::MIN);
 static constexpr q       ONE         = q(  
   WHOLE == 0 ?
   MAX.value :
   (((value_type)1) << FRAC) // - 1 ?
  );

 //---------------------------------------------------------------------------------------------------------------------
 value_type value;
 //---------------------------------------------------------------------------------------------------------------------
 explicit
 q(value_type const & v) : value(v) {}
 //---------------------------------------------------------------------------------------------------------------------
 /**/           operator     value_type(           )    const   = delete;
 //---------------------------------------------------------------------------------------------------------------------
 q              operator  +  ()                         const   = delete;
 q              operator  ~  ()                         const   { return       q(       ~ value      ); }
 q              operator  -  ()                         const   { return       q(       - value      ); }
 //---------------------------------------------------------------------------------------------------------------------
 q              operator >>  (uint8_t const & shift)    const   { return       q(value >> shift      ); }
 q              operator <<  (uint8_t const & shift)    const   { return       q(value << shift      ); }
 q              operator  +  (q       const & other)    const   { return       q(value  + other.value); }
 q              operator  -  (q       const & other)    const   { return       q(value  - other.value); }
 q              operator  *  (q       const & other)    const   { return       q(value  * other.value); }
 q              operator  /  (q       const & other)    const   { return       q(value  / other.value); }
 q              operator  %  (q       const & other)    const   { return       q(value  % other.value); }
 //---------------------------------------------------------------------------------------------------------------------
 bool           operator  <  (q       const & other)    const   { return        (value  < other.value); }
 bool           operator  >  (q       const & other)    const   { return        (value  > other.value); }
 bool           operator ==  (q       const & other)    const   { return        (value == other.value); }
 //---------------------------------------------------------------------------------------------------------------------
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename base>
class mathematized :  public base {
//----------------------------------------------------------------------------------------------------------------------
public:
 //---------------------------------------------------------------------------------------------------------------------
 typedef typename            base::value_type value_type;
 //--------------------------------------------------------------------------------------------------------------------- 
 explicit
 mathematized                (value_type   const & v) : base(v) {}
 //----------------------------------------------------------------------------------------------------------------------
 explicit       operator     value_type(            )   const   { return this->value;                                ; }
 //----------------------------------------------------------------------------------------------------------------------
 mathematized & operator  -- (                      )           { this        -= mathematized(1);        return *this; }
 mathematized & operator  ++ (                      )           { this        += mathematized(1);        return *this; }
  //---------------------------------------------------------------------------------------------------------------------
 mathematized & operator >>= (uint8_t      const & v)           { this->value  = (*this    >> v ).value; return *this; }
 mathematized & operator <<= (uint8_t      const & v)           { this->value  = (*this    << v ).value; return *this; }
  //---------------------------------------------------------------------------------------------------------------------
 mathematized & operator  -= (mathematized const & v)           { this->value  = (*this     - v ).value; return *this; }
 mathematized & operator  += (mathematized const & v)           { this->value  = (*this     + v ).value; return *this; }
 mathematized & operator  *= (mathematized const & v)           { this->value  = (*this     * v ).value; return *this; }
 mathematized & operator  /= (mathematized const & v)           { this->value  = (*this     / v ).value; return *this; }
 mathematized & operator  %= (mathematized const & v)           { this->value  = (*this     % v ).value; return *this; }
  //---------------------------------------------------------------------------------------------------------------------
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

 printf("=> %d \n", (x + y).value);

 x += y;
 x += z;

 printf("=> %d \n", x.value);

 if constexpr(integer_traits<uint16_t>::SIGNED) {
  printf("YES\n");
 }
 else {
  printf("NO\n");
 }
}
