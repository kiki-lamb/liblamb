#include "../include/lamb.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO crtp-test.cpp && .\a.exe

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
// integer        operator  %  (integer const & other)    const   { return integer(value  % other.value); }
 //---------------------------------------------------------------------------------------------------------------------
 bool           operator  <  (integer const & other)    const   { return        (value  < other.value); }
 bool           operator  >  (integer const & other)    const   { return        (value  > other.value); }
 bool           operator ==  (integer const & other)    const   { return        (value == other.value); }
 //---------------------------------------------------------------------------------------------------------------------
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <uint8_t whole_, uint8_t frac_>
class q {
//----------------------------------------------------------------------------------------------------------------------
public:
 //---------------------------------------------------------------------------------------------------------------------

 static constexpr uint8_t WHOLE       = whole_;
 static constexpr uint8_t FRAC        = frac_;
 static constexpr uint8_t SIZE        = size_fit_bits(WHOLE + FRAC);
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

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 explicit
 q(value_type const & v) : value(v) {}

//---------------------------------------------------------------------------------------------------------------------
 
 explicit
 q(value_type const & w, value_type const & f) :
  value(value_type(WHOLE * ONE + (WHOLE < 0 ? - FRAC : FRAC))) {}
 
 /////////////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t whole, uint8_t frac>
  explicit constexpr 
  operator q<whole, frac>() const {

   typedef
    q<whole, frac>
    other_type;

   constexpr uint8_t INTERMED_SIZE = size_fit_bytes(SIZE+other_type::SIZE);

   typedef typename
    find_integer<SIGNED, INTERMED_SIZE>::traits::type
    intermediary_type;

   constexpr bool    FROM_SIGNED   = SIGNED && ! other_type::SIGNED;
   constexpr int8_t  FRAC_DELTA    = FRAC - frac;
   
   if constexpr(FROM_SIGNED) {
    if (value < 0) {
     return other_type(0);
    }
   }

   other_type ret(value);
   
   if constexpr(FRAC_DELTA >= 0) {
    ret.value >>= FRAC_DELTA;
   }
   else {
    ret.value <<= -FRAC_DELTA;
   }
   
   return ret;
  }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 explicit constexpr 
 operator double() const {
  constexpr double one = ONE.value * 1.0;
   
  return value / one;
 }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  static constexpr
  q from_double(
   double const & tmp
  ) {
   int        divisor = tmp;
   double     modulus = tmp - divisor;
   value_type ipart   = ONE.value * divisor + int(ONE.value * modulus);
   
   return q(ipart);
  }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 static constexpr q       PI          = WHOLE <= 2 ? from_double(M_PI) : 0;

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // constexpr
 // q operator ~ () const {
 //    return q(~value);
 // }    

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  q operator ^ (
   q const & other
  ) const {
   return value ^ other.value;
  }  

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // constexpr
  // bool
  // operator == (
  //  q const & other
  // ) const {
  //  return value == other.value;
  // }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // constexpr
 // bool operator > (
 //  q const & other
 // ) const {
 //  return value > other.value;
 // }    

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // constexpr
 // bool operator < (
 //  q const & other
 // ) const {
 //  return value < other.value;
 // }    

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // constexpr
 // q operator >> (
 //  uint8_t const & shift
 // ) const {
 //  return q(value >> shift);  
 // }    

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 // constexpr
 // q operator << (
 //  uint8_t const & shift
 // ) const {
 //  return q(value <<shift);  
 // }    

 ////////////////////////////////////////////////////////////////////////////////////////

 // constexpr
 // q operator + (
 //  q const & other
 // ) const {
 //  return q(value + other.val);
 // }    

 ////////////////////////////////////////////////////////////////////////////////////////

 // constexpr
 // q operator - (
 //  q const & other
 // ) const {
 //  return q(value - other.val);
 // }    

 ////////////////////////////////////////////////////////////////////////////////////////

  template <uint8_t other_whole, uint8_t other_frac>
  constexpr
  q operator * (
   q<other_whole, other_frac> const & other
  ) const {

   typedef
    q<other_whole, other_frac>
    other_type;

   constexpr uint8_t INTERMED_SIZE = size_fit_bytes(SIZE+other_type::SIZE);
      
   typedef typename
    find_integer<SIGNED, INTERMED_SIZE>::traits::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   intermediary_type big_tmp     = value;
   big_tmp                      *= other.value;
   big_tmp                     >>= other_type::FRAC;

   // if (false) {
   //  printf(
   //   "MUL % 13.05lf * % 13.05lf = % 13.05lf \n",
   //   double(*this),
   //   double(other),
   //   double(q(small_tmp))
   //  );
   //  printf(
   //   "MUL % 13lu * % 13lu = % 13lu \n",
   //   value,
   //   other.value,
   //   small_tmp
   //  );   
   // }
   
   return q((value_type)big_tmp);
  }

   /////////////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t other_whole, uint8_t other_frac>
  constexpr
  q
  operator / (
   fixed<other_whole, other_frac> const & other
  ) const {

   typedef
    fixed<other_whole, other_frac>
    other_type;
    
   constexpr uint8_t INTERMED_SIZE = size_fit_bytes(SIZE+other_type::SIZE);
      
   typedef typename
    find_integer<SIGNED, INTERMED_SIZE>::traits::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   intermediary_type big_tmp     = value;
   big_tmp                     <<= other_type::FRAC;
   big_tmp                      /= other.value;

   // if (true) {
   //  printf(
   //   "\nDIV  % 10u.%2u / % 10u.%2u = % 10u.%2u using a %u bit temporary\n",
   //   WHOLE,
   //   MANTISSA,
   //   other_characteristic,
   //   other_mantissa,
   //   CHARACTERISTIC,
   //   MANTISSA,
   //   (sizeof(intermediary_type) << 3)
   //  );
   //  printf(
   //   " div % 16.05lf / % 16.05lf = % 16.05lf \n",
   //   double(*this),
   //   double(other),
   //   double(q(small_tmp))
   //  );
   //  printf(
   //   " big %16lu << ",
   //   ((intermediary_type)value)
   //  );
   //  printf("%lld ", ((intermediary_type)value) << other_mantissa);
   //  printf(
   //   " after shift %2u \n",
   //   other_mantissa
   //  );
   //  printf(
   //   " div % 16lu / % 16lu = % 16lu \n",
   //   value,
   //   other.value,
   //   small_tmp
   //  );
   // }
   
   return q((value_type)big_tmp);
  }

 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
// q              operator  *  (q       const & other)    const   { return       q(value  * other.value); }
// q              operator  /  (q       const & other)    const   { return       q(value  / other.value); }
// q              operator  %  (q       const & other)    const   { return       q(value  % other.value); }
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
// mathematized & operator  %= (mathematized const & v)           { this->value  = (*this     % v ).value; return *this; }
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

 t a({0,192});

  printf("=> %d \n", a.value);
}
