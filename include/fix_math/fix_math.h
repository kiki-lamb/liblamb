#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

//////////////////////////////////////////////////////////////////////////////////////////

#ifdef LAMB_NO_ARDUINO
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#endif

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

//////////////////////////////////////////////////////////////////////////////////////////

namespace lamb {

/////////////////////////////////////////////////////////////////////////////////////////
 // Fixed_Impl
 /////////////////////////////////////////////////////////////////////////////////////////

 template <
  uint8_t  characteristic_,
  uint8_t  mantissa_,
  bool     saturate_,
  template <
   uint8_t characteristic__,
   uint8_t mantissa__,
   bool    saturate__
   > class parent_template
  >
 class fixed_impl {

 /////////////////////////////////////////////////////////////////////////////////////////

 private:
  
  template <bool signedness, uint8_t size>
  class integer_type {};
  
  template <uint8_t size>
  class integer_type<true, size> {
  public:
   typedef signed_int<(size > 8 ? 8 : size)> traits;
  };
  
  template <uint8_t size>
  class integer_type<false, size> {
  public:
   typedef unsigned_int<(size > 8 ? 8 : size)> traits;
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
  parent_template<CHARACTERISTIC, MANTISSA, SATURATE>
  self_type;
  
  template <bool saturate>
  using
  compatible_type = parent_template<CHARACTERISTIC, MANTISSA, saturate>;

  typedef
  parent_template<CHARACTERISTIC, MANTISSA, (! SATURATE)>
  sat_cast_type;

  typedef
  typename
  integer_type<SIGNED, SIZE>::traits
  traits;

  typedef
  typename
  traits::type
  type;

  typedef
  typename
  integer_type<SIGNED, BIG_SIZE>::traits::type
  big_type;

  /////////////////////////////////////////////////////////////////////////////////////////

  static constexpr self_type MAX = self_type(integer_type<SIGNED, SIZE>::traits::MAX);
  static constexpr self_type MIN = self_type(integer_type<SIGNED, SIZE>::traits::MIN);
  
  static constexpr
  self_type                  ONE = self_type(
   CHARACTERISTIC == 0 ?
   MAX.value :
   (((type)1) << MANTISSA) - 1
  );

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
  fixed_impl(
   type const & tmp_
  ) :
   value(tmp_) {}

  //--------------------------------------------------------------------------------------
  
  explicit
  constexpr
  fixed_impl(
   type const & characteristic,
   type const & mantissa
  ) :
   value((characteristic * ONE.value) + (characteristic < 0 ? - mantissa : mantissa)) {}

  /////////////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t characteristic, uint8_t mantissa, bool saturate>
  explicit
  constexpr 
  operator parent_template<characteristic, mantissa, saturate>() const {
   typedef parent_template<characteristic, mantissa, saturate>
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

   // printf(
   //  "CONV FROM '%15ld' %u.%u (%u) to %u.%u (%u) via %u byte intermediary\n",
   //  value,
   //  CHARACTERISTIC, MANTISSA,
   //  self_type::SIZE,
   //  characteristic, mantissa,
   //  other_type::SIZE,
   //  INTERMED_SIZE
   // );

   // printf("DELTA: %08d \n", mantissa_delta);
   
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
   constexpr double one = ONE.value * 1.0;
   
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
   type              ipart   = ONE.value * divisor + int(ONE.value * modulus);
   
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
 
  ////////////////////////////////////////////////////////////////////////////////////////

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

  ////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator ^ (
   compatible_type<saturate> const & other
  ) const {
    return self_type(value ^ other.value);
  }  

  ////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator == (
   compatible_type<saturate> const & other
  ) const {
   return value == other.value;
  }    

  ////////////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator != (
   compatible_type<saturate> const & other
  ) const {
   return value != other.value;
  }    

  ////////////////////////////////////////////////////////////////////////////////////////

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
   parent_template<other_characteristic, other_mantissa, other_saturate> const & other
  ) const {

   typedef
    parent_template<other_characteristic, other_mantissa, other_saturate>
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
   parent_template<other_characteristic,other_mantissa, saturate> const & other
  ) {
   value = (*this * other).value;

   return *((self_type*)(this));
  }

  /////////////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t other_characteristic, uint8_t other_mantissa, bool other_saturate>
  constexpr
  self_type
  operator / (
   parent_template<other_characteristic,other_mantissa,other_saturate> const & other
  ) const {

   typedef
    parent_template<other_characteristic, other_mantissa, other_saturate>
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
   // big_tmp                      /= 666;.
   type              small_tmp   = big_tmp;

   // if (true) {
   //  printf(
   //   "\nDIV  % 10u.%2u / % 10u.%2u = % 10u.%2u using a %u bit temporary\n",
   //   CHARACTERISTIC,
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
   //   double(self_type(small_tmp))
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
   
   return self_type(small_tmp);
  }

  //--------------------------------------------------------------------------------------

  template <uint8_t other_characteristic, uint8_t other_mantissa, bool saturate__>
  constexpr
  self_type & 
  operator /= (
   parent_template<other_characteristic, other_mantissa, saturate__> const & other
  ) {   
   value = (*this / other).value;

   return *this;
  }

 /////////////////////////////////////////////////////////////////////////////////////////

 }; // template fixed_impl


 /////////////////////////////////////////////////////////////////////////////////////////
 // fixe
 /////////////////////////////////////////////////////////////////////////////////////////

 template <
  uint8_t characteristic_,
  uint8_t mantissa_,
  bool    saturate_
  >
 class fixed : public fixed_impl<characteristic_, mantissa_, saturate_, fixed> {

  typedef fixed_impl<characteristic_, mantissa_, saturate_, fixed> base;
  
 public:
  
  explicit
  constexpr
  fixed(
   typename base::type const & tmp_
  ) : base(tmp_) {}

  //--------------------------------------------------------------------------------------
  
  explicit
  constexpr
  fixed(
   typename base::type const & characteristic,
   typename base::type const & mantissa
  ) : base(characteristic, mantissa) {}

 /////////////////////////////////////////////////////////////////////////////////////////

 }; // class fixed
  
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
 constexpr s0q7  operator ""_s0q7(long double x)    { return s0q7::from_double(x); }
 constexpr s0q7s operator ""_s0q7s(long double x)   { return s0q7s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr u0q8  operator ""_u0q8(long double x)    { return u0q8::from_double(x); }
 constexpr u0q8s operator ""_u0q8s(long double x)   { return u0q8s::from_double(x); }
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
 constexpr u0q16   operator ""_u0q16(long double x)   { return u0q16::from_double(x); }
 constexpr u0q16s  operator ""_u0q16s(long double x)  { return u0q16s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s0q15   operator ""_s0q15(long double x)   { return s0q15::from_double(x); }
 constexpr s0q15s  operator ""_s0q15s(long double x)  { return s0q15s::from_double(x); }
 constexpr u1q15   operator ""_u1q15(long double x)   { return u1q15::from_double(x); }
 constexpr u1q15s  operator ""_u1q15s(long double x)  { return u1q15s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s1q14   operator ""_s1q14(long double x)   { return s1q14::from_double(x); }
 constexpr s1q14s  operator ""_s1q14s(long double x)  { return s1q14s::from_double(x); } 
 constexpr u2q14   operator ""_u2q14(long double x)   { return u2q14::from_double(x); }
 constexpr u2q14s  operator ""_u2q14s(long double x)  { return u2q14s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s2q13   operator ""_s2q13(long double x)   { return s2q13::from_double(x); }
 constexpr s2q13s  operator ""_s2q13s(long double x)  { return s2q13s::from_double(x); }
 constexpr u3q13   operator ""_u3q13(long double x)   { return u3q13::from_double(x); }
 constexpr u3q13s  operator ""_u3q13s(long double x)  { return u3q13s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s3q12   operator ""_s3q12(long double x)   { return s3q12::from_double(x); }
 constexpr s3q12s  operator ""_s3q12s(long double x)  { return s3q12s::from_double(x); }
 constexpr u4q12   operator ""_u4q12(long double x)   { return u4q12::from_double(x); }
 constexpr u4q12s  operator ""_u4q12s(long double x)  { return u4q12s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s4q11   operator ""_s4q11(long double x)   { return s4q11::from_double(x); }
 constexpr s4q11s  operator ""_s4q11s(long double x)  { return s4q11s::from_double(x); }
 constexpr u5q11   operator ""_u5q11(long double x)   { return u5q11::from_double(x); }
 constexpr u5q11s  operator ""_u5q11s(long double x)  { return u5q11s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s5q10   operator ""_s5q10(long double x)   { return s5q10::from_double(x); }
 constexpr s5q10s  operator ""_s5q10s(long double x)  { return s5q10s::from_double(x); }
 constexpr u6q10   operator ""_u6q10(long double x)   { return u6q10::from_double(x); }
 constexpr u6q10s  operator ""_u6q10s(long double x)  { return u6q10s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s6q9    operator ""_s6q9(long double x)    { return s6q9::from_double(x); }
 constexpr s6q9s   operator ""_s6q9s(long double x)   { return s6q9s::from_double(x); }
 constexpr u7q9    operator ""_u7q9(long double x)    { return u7q9::from_double(x); }
 constexpr u7q9s   operator ""_u7q9s(long double x)   { return u7q9s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s7q8    operator ""_s7q8(long double x)    { return s7q8::from_double(x); }
 constexpr s7q8s   operator ""_s7q8s(long double x)   { return s7q8s::from_double(x); }
 constexpr u8q8    operator ""_u8q8(long double x)    { return u8q8::from_double(x); }
 constexpr u8q8s   operator ""_u8q8s(long double x)   { return u8q8s::from_double(x); }
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
 constexpr u0q32    operator ""_u0q32(long double x)  { return u0q32::from_double(x); }
 constexpr u0q32s   operator ""_u0q32s(long double x) { return u0q32s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s0q31    operator ""_s0q31(long double x)  { return s0q31::from_double(x); }
 constexpr s0q31s   operator ""_s0q31s(long double x) { return s0q31s::from_double(x); }
 constexpr u1q31    operator ""_u1q31(long double x)  { return u1q31::from_double(x); }
 constexpr u1q31s   operator ""_u1q31s(long double x) { return u1q31s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s1q30    operator ""_s1q30(long double x)  { return s1q30::from_double(x); }
 constexpr s1q30s   operator ""_s1q30s(long double x) { return s1q30s::from_double(x); }
 constexpr u2q30    operator ""_u2q30(long double x)  { return u2q30::from_double(x); }
 constexpr u2q30s   operator ""_u2q30s(long double x) { return u2q30s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s2q29    operator ""_s2q29(long double x)  { return s2q29::from_double(x); }
 constexpr s2q29s   operator ""_s2q29s(long double x) { return s2q29s::from_double(x); }
 constexpr u3q29    operator ""_u3q29(long double x)  { return u3q29::from_double(x); }
 constexpr u3q29s   operator ""_u3q29s(long double x) { return u3q29s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s3q28    operator ""_s3q28(long double x)  { return s3q28::from_double(x); }
 constexpr s3q28s   operator ""_s3q28s(long double x) { return s3q28s::from_double(x); }
 constexpr u4q28    operator ""_u4q28(long double x)  { return u4q28::from_double(x); }
 constexpr u4q28s   operator ""_u4q28s(long double x) { return u4q28s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr u4q27    operator ""_u4q27(long double x)  { return u4q27::from_double(x); }
 constexpr u4q27s   operator ""_u4q27s(long double x) { return u4q27s::from_double(x); }
 constexpr s5q27    operator ""_s5q27(long double x)  { return s5q27::from_double(x); }
 constexpr s5q27s   operator ""_s5q27s(long double x) { return s5q27s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s5q26    operator ""_s5q26(long double x)  { return s5q26::from_double(x); }
 constexpr s5q26s   operator ""_s5q26s(long double x) { return s5q26s::from_double(x); }
 constexpr u6q26    operator ""_u6q26(long double x)  { return u6q26::from_double(x); }
 constexpr u6q26s   operator ""_u6q26s(long double x) { return u6q26s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s7q25    operator ""_s7q25(long double x)  { return s7q25::from_double(x); }
 constexpr s7q25s   operator ""_s7q25s(long double x) { return s7q25s::from_double(x); }
 constexpr u8q25    operator ""_u8q25(long double x)  { return u8q25::from_double(x); }
 constexpr u8q25s   operator ""_u8q25s(long double x) { return u8q25s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s7q24    operator ""_s7q24(long double x)  { return s7q24::from_double(x); }
 constexpr s7q24s   operator ""_s7q24s(long double x) { return s7q24s::from_double(x); }
 constexpr u8q24    operator ""_u8q24(long double x)  { return u8q24::from_double(x); }
 constexpr u8q24s   operator ""_u8q24s(long double x) { return u8q24s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s11q20   operator ""_s11q20(long double x)  { return s11q20::from_double(x); }
 constexpr s11q20s  operator ""_s11q20s(long double x) { return s11q20s::from_double(x); }
 constexpr u12q20   operator ""_u12q20(long double x)  { return u12q20::from_double(x); }
 constexpr u12q20s  operator ""_u12q20s(long double x) { return u12q20s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s15q16   operator ""_s15q16(long double x)  { return s15q16::from_double(x); }
 constexpr s15q16s  operator ""_s15q16s(long double x) { return s15q16s::from_double(x); }
 constexpr u16q16   operator ""_u16q16(long double x)  { return u16q16::from_double(x); }
 constexpr u16q16s  operator ""_u16q16s(long double x) { return u16q16s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s16q15   operator ""_s16q15(long double x)  { return s16q15::from_double(x); }
 constexpr s16q15s  operator ""_s16q15s(long double x) { return s16q15s::from_double(x); }
 constexpr u17q15   operator ""_u17q15(long double x)  { return u17q15::from_double(x); }
 constexpr u17q15s  operator ""_u17q15s(long double x) { return u17q15s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s17q14   operator ""_s17q14(long double x)  { return s17q14::from_double(x); }
 constexpr s17q14s  operator ""_s17q14s(long double x) { return s17q14s::from_double(x); }
 constexpr u18q14   operator ""_u18q14(long double x)  { return u18q14::from_double(x); }
 constexpr u18q14s  operator ""_u18q14s(long double x) { return u18q14s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s19q12   operator ""_s19q12(long double x)  { return s19q12::from_double(x); }
 constexpr s19q12s  operator ""_s19q12s(long double x) { return s19q12s::from_double(x); }
 constexpr u20q12   operator ""_u20q12(long double x)  { return u20q12::from_double(x); }
 constexpr u20q12s  operator ""_u20q12s(long double x) { return u20q12s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s32q10   operator ""_s32q10(long double x)  { return s32q10::from_double(x); }
 constexpr s32q10s  operator ""_s32q10s(long double x) { return s32q10s::from_double(x); }
 constexpr u22q10   operator ""_u22q10(long double x)  { return u22q10::from_double(x); }
 constexpr u22q10s  operator ""_u22q10s(long double x) { return u22q10s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s23q8    operator ""_s23q8(long double x)   { return s23q8::from_double(x); }
 constexpr s23q8s   operator ""_s23q8s(long double x)  { return s23q8s::from_double(x); }
 constexpr u24q8    operator ""_u24q8(long double x)   { return u24q8::from_double(x); }
 constexpr u24q8s   operator ""_u24q8s(long double x)  { return u24q8s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s27q4    operator ""_s27q4(long double x)   { return s27q4::from_double(x); }
 constexpr s27q4s   operator ""_s27q4s(long double x)  { return s27q4s::from_double(x); }
 constexpr u28q4    operator ""_u28q4(long double x)   { return u28q4::from_double(x); }
 constexpr u28q4s   operator ""_u28q4s(long double x)  { return u28q4s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s29q2    operator ""_s29q2(long double x)   { return s29q2::from_double(x); }
 constexpr s29q2s   operator ""_s29q2s(long double x)  { return s29q2s::from_double(x); }
 constexpr u30q2    operator ""_u30q2(long double x)   { return u30q2::from_double(x); }
 constexpr u30q2s   operator ""_u30q2s(long double x)  { return u30q2s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr s30q1    operator ""_s30q1(long double x)   { return s30q1::from_double(x); }
 constexpr s30q21   operator ""_s30q21(long double x)  { return s30q21::from_double(x); }
 constexpr u31q1    operator ""_u31q1(long double x)   { return u31q1::from_double(x); }
 constexpr u31q21   operator ""_u31q21(long double x)  { return u31q21::from_double(x); }
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
 typedef fixed< 31,  0, false > s31q0;
 typedef fixed< 31,  0, true  > s31q0s;
 //---------------------------------------------------------------------------------------
 constexpr u8q0    operator ""_u8q0(long double x)    { return u8q0::from_double(x); }
 constexpr u8q0s   operator ""_u8q0s(long double x)   { return u8q0s::from_double(x); }
 constexpr s7q0    operator ""_s7q0(long double x)    { return s7q0::from_double(x); }
 constexpr s7q0s   operator ""_s7q0s(long double x)   { return s7q0s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr u16q0   operator ""_u16q0(long double x)   { return u16q0::from_double(x); }
 constexpr u16q0s  operator ""_u16q0s(long double x)  { return u16q0s::from_double(x); }
 constexpr s15q0   operator ""_s15q0(long double x)   { return s15q0::from_double(x); }
 constexpr s15q0s  operator ""_s15q0s(long double x)  { return s15q0s::from_double(x); }
 //---------------------------------------------------------------------------------------
 constexpr u32q0   operator ""_u32q0(long double x)   { return u32q0::from_double(x); }
 constexpr u32q0s  operator ""_u32q0s(long double x)  { return u32q0s::from_double(x); }
 constexpr s31q0   operator ""_s31q0(long double x)   { return s31q0::from_double(x); }
 constexpr s31q0s  operator ""_s31q0s(long double x)  { return s31q0s::from_double(x); }
 //---------------------------------------------------------------------------------------
 
//////////////////////////////////////////////////////////////////////////////////////////

} // namespace lamb

//////////////////////////////////////////////////////////////////////////////////////////

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */

#endif
