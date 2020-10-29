#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

//////////////////////////////////////////////////////////////////////////////////////////

#ifdef LAMB_NO_ARDUINO
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#endif

//////////////////////////////////////////////////////////////////////////////////////////

namespace lamb {

 /////////////////////////////////////////////////////////////////////////////////////////
 // Fixed
 /////////////////////////////////////////////////////////////////////////////////////////

 template <
  uint8_t characteristic_,
  uint8_t mantissa_,
  bool    saturate_ = false
  >
 class fixed {

 /////////////////////////////////////////////////////////////////////////////////////////

 private:
  
  template <bool signedness, uint8_t size>
  class integer_type {};
  
  template <uint8_t size>
  class integer_type<true, size> {
  public:
   typedef signed_int<size> traits;
  };
  
  template <uint8_t size>
  class integer_type<false, size> {
  public:
   typedef unsigned_int<size> traits;
  };  

 /////////////////////////////////////////////////////////////////////////////////////////

 public:

  static constexpr bool    SATURATE       = saturate_;
  static constexpr uint8_t CHARACTERISTIC = characteristic_;
  static constexpr uint8_t MANTISSA       = mantissa_;
  static constexpr bool    SIGNED         = ((CHARACTERISTIC + MANTISSA ) % 2) == 1;
  static constexpr uint8_t SIZE           = size_fit_bits(CHARACTERISTIC+MANTISSA);
  static constexpr uint8_t BIG_SIZE       = size_fit_bits((SIZE + 1) * 8);
  
  ////////////////////////////////////////////////////////////////////////////////////////

  typedef
  fixed<CHARACTERISTIC, MANTISSA, SATURATE>
  self_type;
  
  template <bool saturate>
  using
  compatible_type = fixed<CHARACTERISTIC, MANTISSA, saturate>;

  typedef
  compatible_type<(! SATURATE)>
  sat_cast_type;

  typedef
  typename
  integer_type<SIGNED, SIZE>::traits::type
  type;

  typedef
  typename
  integer_type<SIGNED, BIG_SIZE>::traits::type
  big_type;

  /////////////////////////////////////////////////////////////////////////////////////////

  static constexpr type    MAX = integer_type<SIGNED, SIZE>::traits::MAX;
  static constexpr type    MIN = integer_type<SIGNED, SIZE>::traits::MIN;
  
  static constexpr
  type                     ONE =
   CHARACTERISTIC == 0 ?
   MAX :
   (((type)1) << MANTISSA) - 1;  

  /////////////////////////////////////////////////////////////////////////////////////////

  type                     value;  

  /////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  operator sat_cast_type () const {
   return sat_cast_type(value);
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////
  
  static
  constexpr
  type mask() {
   type m = 0;

   return (1ll << MANTISSA) - 1;
  }

  /////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  type mantissa() const { // return smaller type?
   return value & mask();
  }
  

  constexpr
  void mantissa(type const & x)  { 
   type tmp = value & ~mask();
   
   value    = tmp | x;
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  type characteristic() const {    // return smaller type?
   return CHARACTERISTIC == 0 ? 0 : (value & (~mask())) >> MANTISSA;
  }     

  void print_bits_32(uint32_t const & t0) {
   {
    for(uint32_t mask = 0x80000000; mask; mask >>= 1) {
     if (mask & t0) {
#ifdef LAMB_NO_ARDUINO
      printf("1");
#else
      Serial.print('1'); Serial.flush();
#endif
     }
     else {
#ifdef LAMB_NO_ARDUINO
      printf("0");
#else
      Serial.print('0'); Serial.flush();
#endif
     }
    }
   }
  }

  constexpr
  void characteristic(type const & x)  {
   printf("Before: ");
   print_bits_32(value);
   printf("\n");

   type tmp = value & mask();
   
   printf("After:  ");
   print_bits_32((x << MANTISSA) | tmp);
   printf("\n");

   value = (x << MANTISSA) | tmp;
  }     
  
  /////////////////////////////////////////////////////////////////////////////////////////

  explicit
  constexpr
  fixed(
   type const & tmp_
  ) :
   value(tmp_) {}

  //--------------------------------------------------------------------------------------
  
  explicit
  constexpr
  fixed(
   type const & characteristic,
   type const & mantissa
  ) :
   value((characteristic * ONE) + (characteristic < 0 ? - mantissa : mantissa)) {}

  /////////////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t characteristic, uint8_t mantissa, bool saturate>
  explicit
  constexpr 
  operator fixed<characteristic, mantissa, saturate>() const {
   typedef fixed<characteristic, mantissa, saturate>
    other_type;

   constexpr uint8_t INTERMED_SIZE = size_fit_bytes(SIZE+other_type::SIZE);
   
   typedef
    typename integer_type<SIGNED, INTERMED_SIZE>::traits::type
    intermediary_type;

   constexpr bool    from_signed    = SIGNED     && (! other_type::SIGNED);
   constexpr int8_t  mantissa_delta = MANTISSA - mantissa;
   
   if constexpr(from_signed) {
    if (value < 0) {
     return other_type(0);
    }
   }

   printf(
    "CONV FROM %u.%u (%u) to %u.%u (%u) via %u byte intermediary\n",
    CHARACTERISTIC, MANTISSA, characteristic, mantissa,
    size_fit_bits(CHARACTERISTIC+MANTISSA),
    other_type::SIZE,
    INTERMED_SIZE
   );

   printf("DELTA: %08d \n", mantissa_delta);
   
   intermediary_type tmp_value = value;
   
   if constexpr(mantissa_delta >= 0) {
    tmp_value >>= mantissa_delta;
   }
   else {
    tmp_value <<= -mantissa_delta;
   }
   
   return other_type(tmp_value);
  }

  /////////////////////////////////////////////////////////////////////////////////////////

  constexpr explicit
  operator type() const {
   return value;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  explicit
  operator double() const {
   constexpr double one = ONE * 1.0;
   
   return value / one;
  }
   
  ////////////////////////////////////////////////////////////////////////////////////////

  static
  constexpr
  self_type
  from_double(
   double const & tmp
  ) {
   int               divisor = tmp;
   double            modulus = tmp - divisor;
   type              ipart   = ONE * divisor + int(ONE * modulus);
   
   return self_type(ipart);
  }

  ////////////////////////////////////////////////////////////////////////////////////////

 private:

  template <uint8_t c, uint8_t m>
  class constants_helper {
  public:
   static_assert(c >= 2, "characteristic must be at least 2.");
   static constexpr self_type pi = from_double(M_PI);
  };

 public:
  
  typedef constants_helper<CHARACTERISTIC, MANTISSA> constants;
 
  /////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  bool
  operator ~ () const {
   if constexpr(SIGNED) {
    return self_type(value * -1);
   }
   else {
    return self_type(~value);
   }
  }    

  /////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator ^ (
   compatible_type<saturate> const & other
  ) const {
    return self_type(value ^ other.value);
  }  

  /////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator == (
   compatible_type<saturate> const & other
  ) const {
   return value == other.value;
  }    

  /////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator != (
   compatible_type<saturate> const & other
  ) const {
   return value != other.value;
  }    

  /////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator > (
   compatible_type<saturate> const & other
  ) const {
   return value > other.value;
  }    

  /////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator < (
   compatible_type<saturate> const & other
  ) const {
   return value < other.value;
  }    

  ////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator >= (
   compatible_type<saturate> const & other
  ) const {
   return value >= other.value;
  }    

  ////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator <= (
   compatible_type<saturate> const & other
  ) const {
   return value <= other.value;
  }    

  ////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  self_type
  operator >> (
   uint8_t const & shift
  ) const {
   return self_type(value >> shift);  
  }    

  constexpr
  self_type &
  operator >>= (
   uint8_t const & shift
  ) {
   value = self_type(*this >> shift).value;
   
   return *this;
  }    

  ////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  self_type
  operator << (
   uint8_t const & shift
  ) const {
   return self_type(value << shift);  
  }    

  //--------------------------------------------------------------------------------------
  
  constexpr
  self_type &
  operator <<= (
   uint8_t const & shift
  ) {
   value = self_type(*this << shift).value;
   
   return *this;
  }    

  ////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  self_type
  operator + (
   compatible_type<saturate> const & other
  ) const {
   type              old        = value;
   big_type          big_tmp    = old;
   big_tmp                     += other.value;
   type              small_tmp  = big_tmp;
   
   return self_type(small_tmp);
  }    

  //------------------------------------------------------------------------------------
  
  template <bool saturate>
  constexpr
  self_type &
  operator += (
   compatible_type<saturate> const & other
  ) {
   value = (*this + other).value;

   return *this;
  }

  /////////////////////////////////////////////////////////////////////////////////////////

  constexpr
  self_type
  operator - () const {
   return self_type(value * -1);
  }    

  //--------------------------------------------------------------------------------------

  template <bool saturate>
  constexpr
  self_type
  operator - (
   compatible_type<saturate> const & other
  ) const {
   type              old        = value;
   big_type          big_tmp    = old;
   big_tmp                     -= other.value;
   type              small_tmp  = big_tmp;
   
   return self_type(small_tmp);
  }    

  //--------------------------------------------------------------------------------------

  template <bool saturate>
  constexpr
  self_type &
  operator -= (
   compatible_type<saturate> const & other
  ) {
   value = (*this - other).value;

   return *this;
  }

  ////////////////////////////////////////////////////////////////////////////////////////

  template <uint8_t other_characteristic, uint8_t other_mantissa, bool other_saturate>
  constexpr
  self_type
  operator * (
   fixed<other_characteristic, other_mantissa, other_saturate> const & other
  ) const {

   typedef
    fixed<other_characteristic, other_mantissa, other_saturate>
    other_type;
   
   typedef
    typename
    integer_type<SIGNED, (size_fit_bytes(SIZE+other_type::SIZE))>::traits::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   type              old(value);      
   intermediary_type big_tmp     = value;
   big_tmp                      *= other.value;
   big_tmp                     >>= other_mantissa;     
   type              small_tmp   = big_tmp;

   if (false) {
    printf(
     "MUL % 13.05lf * % 13.05lf = % 13.05lf \n",
     double(*this),
     double(other),
     double(self_type(small_tmp))
    );
    printf(
     "MUL % 13lu * % 13lu = % 13lu \n",
     value,
     other.value,
     small_tmp
    );   
   }
   
   return self_type(small_tmp);
  }

  //--------------------------------------------------------------------------------------
  
  template <uint8_t other_characteristic, uint8_t other_mantissa, bool saturate>
  constexpr
  self_type & 
  operator *= (
   fixed<other_characteristic,other_mantissa, saturate> const & other
  ) {
   value = (*this * other).value;

   return *this;
  }

  /////////////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t other_characteristic, uint8_t other_mantissa, bool other_saturate>
  constexpr
  self_type
  operator / (
   fixed<other_characteristic,other_mantissa,other_saturate> const & other
  ) const {

   typedef
    fixed<other_characteristic, other_mantissa, other_saturate>
    other_type;
    
   typedef
    typename
    integer_type<SIGNED, (size_fit_bytes(SIZE+other_type::SIZE))>::traits::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   intermediary_type big_tmp     = value;
   big_tmp                     <<= other_mantissa;
   big_tmp                      /= other.value;
   type              small_tmp   = big_tmp;

   if (false) {
    printf(
     "\nDIV  % 10u.%2u / % 10u.%2u = % 10u.%2u using a %u bit temporary\n",
     CHARACTERISTIC,
     MANTISSA,
     other_characteristic,
     other_mantissa,
     CHARACTERISTIC,
     MANTISSA,
     (sizeof(intermediary_type) << 3)
    );
    printf(
     " div % 13.05lf / % 13.05lf = % 13.05lf \n",
     double(*this),
     double(other),
     double(self_type(small_tmp))
    );
    printf(" big %13llu  after shift %2u \n", (big_tmp << other_mantissa), other_mantissa);
    printf(
     " div % 13ld / % 13ld = % 13ld \n",
     value,
     other.value,
     small_tmp
    );
   }
   
   return self_type(small_tmp);
  }

  //--------------------------------------------------------------------------------------

  template <uint8_t other_characteristic, uint8_t other_mantissa, bool saturate__>
  constexpr
  self_type & 
  operator /= (
   fixed<other_characteristic, other_mantissa, saturate__> const & other
  ) {   
   value = (*this / other).value;

   return *this;
  }

 /////////////////////////////////////////////////////////////////////////////////////////

 }; // template fixed
 
 /////////////////////////////////////////////////////////////////////////////////////////
 // Typedefs
 /////////////////////////////////////////////////////////////////////////////////////////
 
 //---------------------------------------------------------------------------------------
 // 8 bits
 //---------------------------------------------------------------------------------------
 typedef fixed<  0,  7, false > s0q7;
 typedef fixed<  0,  7, true  > s0q7s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  0,  8, false > u0q8;
 typedef fixed<  0,  8, true  > u0q8s;
 //---------------------------------------------------------------------------------------
 
 //---------------------------------------------------------------------------------------
 // 16 bits
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 16, false > u0q16;
 typedef fixed<  0, 16, true  > u0q16s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 15, false > s0q15;
 typedef fixed<  0, 15, true  > s0q15s;
 typedef fixed<  1, 15, false > u1q15;
 typedef fixed<  1, 15, true  > u1q15s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  1, 14, false > s1q14;
 typedef fixed<  1, 14, true  > s1q14s;
 typedef fixed<  2, 14, false > u2q14;
 typedef fixed<  2, 14, true  > u2q14s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  2, 13, false > s2q13;
 typedef fixed<  2, 13, true  > s2q13s;
 typedef fixed<  3, 13, false > u3q13;
 typedef fixed<  3, 13, true  > u3q13s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  3, 12, false > s3q12;
 typedef fixed<  3, 12, true  > s3q12s;
 typedef fixed<  4, 12, false > u4q12;
 typedef fixed<  4, 12, true  > u4q12s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  4, 11, false > s4q11;
 typedef fixed<  4, 11, true  > s4q11s;
 typedef fixed<  5, 11, false > u5q11;
 typedef fixed<  5, 11, true  > u5q11s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  5, 10, false > s5q10;
 typedef fixed<  5, 10, true  > s5q10s;
 typedef fixed<  6, 10, false > u6q10;
 typedef fixed<  6, 10, true  > u6q10s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  6,  9, false > s6q9;
 typedef fixed<  6,  9, true  > s6q9s;
 typedef fixed<  7,  9, false > u7q9;
 typedef fixed<  7,  9, true  > u7q9s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  7,  8, false > s7q8;
 typedef fixed<  7,  8, true  > s7q8s;
 typedef fixed<  8,  8, false > u8q8;
 typedef fixed<  8,  8, true  > u8q8s;
 //---------------------------------------------------------------------------------------

 //---------------------------------------------------------------------------------------
 // 32 bits
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 32, false > u0q32;
 typedef fixed<  0, 32, true  > u0q32s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 31, false > s0q31;
 typedef fixed<  0, 31, true  > s0q31s;
 typedef fixed<  1, 31, false > u1q31;
 typedef fixed<  1, 31, true  > u1q31s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  1, 30, false > s1q30;
 typedef fixed<  1, 30, true  > s1q30s;
 typedef fixed<  2, 30, false > u2q30;
 typedef fixed<  2, 30, true  > u2q30s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  2, 29, false > s2q29;
 typedef fixed<  2, 29, true  > s2q29s;
 typedef fixed<  3, 29, false > u3q29;
 typedef fixed<  3, 29, true  > u3q29s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  3, 28, false > s3q28;
 typedef fixed<  3, 28, true  > s3q28s;
 typedef fixed<  4, 28, false > u4q28;
 typedef fixed<  4, 28, true  > u4q28s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  4, 27, false > u4q27;
 typedef fixed<  4, 27, true  > u4q27s;
 typedef fixed<  5, 27, false > s5q27;
 typedef fixed<  5, 27, true  > s5q27s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  5, 26, false > s5q26;
 typedef fixed<  5, 26, true  > s5q26s;
 typedef fixed<  6, 26, false > u6q26;
 typedef fixed<  6, 26, true  > u6q26s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  7, 25, false > s7q25;
 typedef fixed<  7, 25, true  > s7q25s;
 typedef fixed<  8, 25, false > u8q25;
 typedef fixed<  8, 25, true  > u8q25s;
 //---------------------------------------------------------------------------------------
 typedef fixed<  7, 24, false > s7q24;
 typedef fixed<  7, 24, true  > s7q24s;
 typedef fixed<  8, 24, false > u8q24;
 typedef fixed<  8, 24, true  > u8q24s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 11, 20, false > s11q20;
 typedef fixed< 11, 20, true  > s11q20s;
 typedef fixed< 12, 20, false > u12q20;
 typedef fixed< 12, 20, true  > u12q20s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 15, 16, false > s15q16;
 typedef fixed< 15, 16, true  > s15q16s;
 typedef fixed< 16, 16, false > u16q16;
 typedef fixed< 16, 16, true  > u16q16s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 16, 15, false > s16q15;
 typedef fixed< 16, 15, true  > s16q15s;
 typedef fixed< 17, 15, false > u17q15;
 typedef fixed< 17, 15, true  > u17q15s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 17, 14, false > s17q14;
 typedef fixed< 17, 14, true  > s17q14s;
 typedef fixed< 18, 14, false > u18q14;
 typedef fixed< 18, 14, true  > u18q14s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 19, 12, false > s19q12;
 typedef fixed< 19, 12, true  > s19q12s;
 typedef fixed< 20, 12, false > u20q12;
 typedef fixed< 20, 12, true  > u20q12s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 21, 10, false > s32q10;
 typedef fixed< 21, 10, true  > s32q10s;
 typedef fixed< 22, 10, false > u22q10;
 typedef fixed< 22, 10, true  > u22q10s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 23,  8, false > s23q8;
 typedef fixed< 23,  8, true  > s23q8s;
 typedef fixed< 24,  8, false > u24q8;
 typedef fixed< 24,  8, true  > u24q8s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 23,  8, false > s23q8;
 typedef fixed< 23,  8, true  > s23q8s;
 typedef fixed< 24,  8, false > u24q8;
 typedef fixed< 24,  8, true  > u24q8s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 27,  4, false > s27q4;
 typedef fixed< 27,  4, true  > s27q4s;
 typedef fixed< 28,  4, false > u28q4;
 typedef fixed< 28,  4, true  > u28q4s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 29,  2, false > s29q2;
 typedef fixed< 29,  2, true  > s29q2s;
 typedef fixed< 30,  2, false > u30q2;
 typedef fixed< 30,  2, true  > u30q2s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 30,  1, false > s30q1;
 typedef fixed< 30,  1, true  > s30q21;
 typedef fixed< 31,  1, false > u31q1;
 typedef fixed< 31,  1, true  > u31q21;
 //---------------------------------------------------------------------------------------

 //---------------------------------------------------------------------------------------
 // integrals for convenience in math operations.
 //---------------------------------------------------------------------------------------
 typedef fixed<  8,  0, false > u8q0;
 typedef fixed<  8,  0, true  > u8q0s;
 typedef fixed<  7,  0, false > s7q0;
 typedef fixed<  7,  0, true  > s7q0s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 16,  0, false > u16q0;
 typedef fixed< 16,  0, true  > u16q0s;
 typedef fixed< 15,  0, false > s15q0;
 typedef fixed< 15,  0, true  > s15q0s;
 //---------------------------------------------------------------------------------------
 typedef fixed< 32,  0, false > u32q0;
 typedef fixed< 32,  0, true  > u32q0s;
 typedef fixed< 31,  0, false > s32q0;
 typedef fixed< 31,  0, true  > s32q0s;
 //---------------------------------------------------------------------------------------
 
//////////////////////////////////////////////////////////////////////////////////////////

} // namespace lamb

//////////////////////////////////////////////////////////////////////////////////////////

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */

#endif
