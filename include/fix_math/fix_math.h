
#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

///////////////////////////////////////////////////////////////////////////////

#ifdef LAMB_NO_ARDUINO
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#endif

///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// Fixed
////////////////////////////////////////////////////////////////////////////////

 template <
  uint8_t characteristic_,
  uint8_t mantissa_,
  bool    saturate_ = false
  >
 class fixed {

////////////////////////////////////////////////////////////////////////////////

 private:
  
  template <bool signedness, uint8_t size>
  class integer_type {};
  
  template <uint8_t size>
  class integer_type<true, size> {
  public:
   typedef signed_int<size> type;
  };
  
  template <uint8_t size>
  class integer_type<false, size> {
  public:
   typedef unsigned_int<size> type;
  };  

//////////////////////////////////////////////////////////////////////////////// 

 public:

  static constexpr bool    SATURATE       = saturate_;
  static constexpr uint8_t CHARACTERISTIC = characteristic_;
  static constexpr uint8_t MANTISSA       = mantissa_;
  static constexpr bool    SIGNED         = ((CHARACTERISTIC + MANTISSA ) % 2) == 1;
  static constexpr uint8_t SIZE           = size_fit_bits(CHARACTERISTIC+MANTISSA);
  static constexpr uint8_t BIG_SIZE       = size_fit_bits((SIZE + 1) * 8);

////////////////////////////////////////////////////////////////////////////////

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
  integer_type<SIGNED, SIZE>::type::type
  type;

  typedef
  typename
  integer_type<SIGNED, BIG_SIZE>::type::type
  big_type;

////////////////////////////////////////////////////////////////////////////////

  static constexpr type    MAX = integer_type<SIGNED, SIZE>::type::MAX;
  static constexpr type    MIN = integer_type<SIGNED, SIZE>::type::MIN;

  // typedef
  // typename
  // integer_type<SIGNED, (size_fit_bits(MANTISSA + 1))>::type::type
  // one_type;
  
  static constexpr
  type                     ONE =
   CHARACTERISTIC == 0 ?
   MAX :
   (((type)1) << MANTISSA) - 1;  

  static constexpr big_type TRUE_ONE =
   (((big_type)1) << MANTISSA);

//////////////////////////////////////////////////////////////////////////////

  type                     val;  

////////////////////////////////////////////////////////////////////////////////

  constexpr
  operator sat_cast_type () const {
   return sat_cast_type(val);
  }
  
////////////////////////////////////////////////////////////////////////////////
  
  static
  constexpr
  type mask() {
   type m = 0;

   return (1ll << MANTISSA) - 1;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  type mantissa() const { // return smaller type?
   return val & mask();
  }
  
////////////////////////////////////////////////////////////////////////////////

  constexpr
  type characteristic() const {    // return smaller type?
   return CHARACTERISTIC == 0 ? 0 : (val & (~mask())) >> MANTISSA;
  }     
  
////////////////////////////////////////////////////////////////////////////////

  explicit
  constexpr
  fixed(
   type const & tmp_
  ) :
   val(tmp_) {}

  explicit
  constexpr
  fixed(
   type const & characteristic,
   type const & mantissa
  ) :
   val((characteristic * ONE) + mantissa) {}

////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t characteristic, uint8_t mantissa, bool saturate>
  explicit
  constexpr 
  operator fixed<characteristic, mantissa, saturate>() const {
   printf("CONV...\n");
   
   typedef fixed<characteristic, mantissa, saturate>
    other_type;

   typedef
    typename integer_type<SIGNED, (size_fit_bytes(SIZE+other_type::SIZE))>::type::type
    intermediary_type;

   constexpr bool    to_signed      = (! SIGNED) && other_type::SIGNED;
   constexpr bool    from_signed    = SIGNED     && (! other_type::SIGNED);
   constexpr uint8_t sign_shift     = to_signed ? 1 : 0;
   constexpr int8_t  mantissa_delta = MANTISSA - mantissa + sign_shift;
   
   if constexpr(from_signed) {
    if (val < 0) {
     return other_type(0);
    }
   }
   
   intermediary_type tmp_val = val;
   
   if constexpr(mantissa_delta >= 0) {
    tmp_val >>= mantissa_delta;
   }
   else {
    tmp_val <<= -mantissa_delta;
   }
   
   return other_type(tmp_val);
  }
  
////////////////////////////////////////////////////////////////////////////////

  constexpr
  explicit
  operator double() const {
    return val / (ONE * 1.0);
  }

///////////////////////////////////////////////////////////////////////////////

  static
  constexpr
  self_type
  from_double(
   double const & tmp
  ) {
   int           divisor = tmp;
   double        modulus = tmp - divisor;
   type          ipart   = ONE * divisor + int(ONE * modulus);
   
   return self_type(ipart);
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  bool
  operator ~ () const {
   return SIGNED ? self_type(val * -1) :  self_type(~val);
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator ^ (
   compatible_type<saturate> const & other
  ) const {
    return self_type(val ^ other.val);
  }  

////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator == (
   compatible_type<saturate> const & other
  ) const {
   return val == other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator != (
   compatible_type<saturate> const & other
  ) const {
   return val != other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator > (
   compatible_type<saturate> const & other
  ) const {
   return val > other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator < (
   compatible_type<saturate> const & other
  ) const {
   return val < other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator >= (
   compatible_type<saturate> const & other
  ) const {
   return val >= other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  bool
  operator <= (
   compatible_type<saturate> const & other
  ) const {
   return val <= other.val;
  }    

///////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  self_type
  operator + (
   compatible_type<saturate> const & other
  ) const {
   type          old        = val;
   big_type      big_tmp    = old;
   big_tmp                 += other.val;
   type          small_tmp  = big_tmp;
   
   return self_type(small_tmp);
  }    

  template <bool saturate>
  constexpr
  self_type &
  operator += (
   compatible_type<saturate> const & other
  ) {
   val = ((*this) + other).val;

   return *(static_cast<self_type *>(this));
  }

  ///////////////////////////////////////////////////////////////////////////////

  template <bool saturate>
  constexpr
  self_type
  operator - (
   compatible_type<saturate> const & other
  ) const {
   type          old        = val;
   big_type      big_tmp    = old;
   big_tmp                 -= other.val;
   type          small_tmp  = big_tmp;
   
   return self_type(small_tmp);
  }    

  template <bool saturate>
  constexpr
  self_type &
  operator -= (
   compatible_type<saturate> const & other
  ) {
   self_type tmp = (*this) - other;
  
   val = tmp.val;

   return *(static_cast<self_type *>(this));
  }

///////////////////////////////////////////////////////////////////////////////

  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  constexpr
  self_type
  operator * (
   fixed<other_charac, other_mantissa, other_saturate> const & other
  ) const {

   typedef
    fixed<other_charac, other_mantissa, other_saturate>
    other_type;
   
   typedef
    typename
    integer_type<SIGNED, (size_fit_bytes(SIZE+other_type::SIZE))>::type::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   type              old(val);      
   intermediary_type big_tmp     = val;
   big_tmp                      *= other.val;
   big_tmp                     >>= other_mantissa;     
   type              small_tmp   = big_tmp;
   
   return self_type(small_tmp);
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate>
  constexpr
  self_type & 
  operator *= (
   fixed<other_charac,other_mantissa, saturate> const & other
  ) {
   val = ((*this) * other).val;

   return *(static_cast<self_type *>(this));
  }

////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  constexpr
  self_type
  operator / (
   fixed<other_charac,other_mantissa,other_saturate> const & other
  ) const {

   typedef
    fixed<other_charac, other_mantissa, other_saturate>
    other_type;
    
   typedef
    typename
    integer_type<SIGNED, (size_fit_bytes(SIZE+other_type::SIZE))>::type::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   type              old(val);       
   intermediary_type big_tmp     = val;
   big_tmp                     <<= other_mantissa;
   big_tmp                      /= other.val;
   type              small_tmp   = big_tmp;
   
   return self_type(small_tmp);
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  constexpr
  self_type & 
  operator /= (
   fixed<other_charac,other_mantissa, saturate__> const & other
  ) {   
   val = ((*this) / other).val;

   return *this;
  }

///////////////////////////////////////////////////////////////////////////////

 }; // template fixed
 
////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////
// 8 bits
////////////////////////////////////////////////////////////////////////////////
 /*  7 */ typedef fixed<  0,  7, false > s0q7;
 /*  7 */ typedef fixed<  0,  7, true  > s0q7s;
 /*  8 */ typedef fixed<  0,  8, false > u0q8;
 /*  8 */ typedef fixed<  0,  8, true  > u0q8s;
 //-----------------------------------------------------------------------------
 
////////////////////////////////////////////////////////////////////////////////
// 16 bits
//////////////////////////////////////////////////////////////////////////////// 
 /*  0 */ typedef fixed<  0, 15, false > s0q15;
 /*  0 */ typedef fixed<  0, 15, true  > s0q15s;
 /*  0 */ typedef fixed<  0, 16, false > u0q16;
 /*  0 */ typedef fixed<  0, 16, true  > u0q16s;
 //-----------------------------------------------------------------------------
 /*  1 */ typedef fixed<  1, 14, false > s1q14;
 /*  1 */ typedef fixed<  1, 14, true  > s1q14s;
 /*  1 */ typedef fixed<  1, 15, false > u1q15;
 /*  1 */ typedef fixed<  1, 15, true  > u1q15s;
 //-----------------------------------------------------------------------------
 /*  2 */ typedef fixed<  2, 13, false > s2q13;
 /*  2 */ typedef fixed<  2, 13, true  > s2q13s;
 /*  2 */ typedef fixed<  2, 14, false > u2q14;
 /*  2 */ typedef fixed<  2, 14, true  > u2q14s;
 //-----------------------------------------------------------------------------
 /*  3 */ typedef fixed<  3, 12, false > s3q12;
 /*  3 */ typedef fixed<  3, 12, true  > s3q12s;
 /*  3 */ typedef fixed<  3, 13, false > u3q13;
 /*  3 */ typedef fixed<  3, 13, true  > u3q13s;
 //-----------------------------------------------------------------------------
 /*  4 */ typedef fixed<  4, 11, false > s4q11;
 /*  4 */ typedef fixed<  4, 11, true  > s4q11s;
 /*  4 */ typedef fixed<  4, 12, false > u4q12;
 /*  4 */ typedef fixed<  4, 12, true  > u4q12s;
 //-----------------------------------------------------------------------------
 /*  5 */ typedef fixed<  5, 10, false > s5q10;
 /*  5 */ typedef fixed<  5, 10, true  > s5q10s;
 /*  5 */ typedef fixed<  5, 11, false > u5q11;
 /*  5 */ typedef fixed<  5, 11, true  > u5q11s;
 //-----------------------------------------------------------------------------
 /*  6 */ typedef fixed<  6,  9, false > s6q9;
 /*  6 */ typedef fixed<  6,  9, true  > s6q9s;
 /*  6 */ typedef fixed<  6, 10, false > u6q10;
 /*  6 */ typedef fixed<  6, 10, true  > u6q10s;
 //-----------------------------------------------------------------------------
 /*  7 */ typedef fixed<  7,  8, false > s7q8;
 /*  7 */ typedef fixed<  7,  8, true  > s7q8s;
 /*  8 */ typedef fixed<  8,  8, false > u8q8;
 /*  8 */ typedef fixed<  8,  8, true  > u8q8s;
 //-----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// 32 bits
//////////////////////////////////////////////////////////////////////////////// 
 /*  0 */ typedef fixed<  0, 31, false > s0q31;
 /*  0 */ typedef fixed<  0, 31, true  > s0q31s;
 /*  0 */ typedef fixed<  0, 32, false > u0q32;
 /*  0 */ typedef fixed<  0, 32, true  > u0q32s;
 //-----------------------------------------------------------------------------
 /*  1 */ typedef fixed<  1, 30, false > s1q30;
 /*  1 */ typedef fixed<  1, 30, true  > s1q30s;
 /*  1 */ typedef fixed<  1, 31, false > u1q31;
 /*  1 */ typedef fixed<  1, 31, true  > u1q31s;
 //-----------------------------------------------------------------------------
 /*  2 */ typedef fixed<  2, 29, false > s2q29;
 /*  2 */ typedef fixed<  2, 29, true  > s2q29s;
 /*  2 */ typedef fixed<  2, 30, false > u2q30;
 /*  2 */ typedef fixed<  2, 30, true  > u2q30s;
 //-----------------------------------------------------------------------------
 /*  3 */ typedef fixed<  3, 28, false > s3q28;
 /*  3 */ typedef fixed<  3, 28, true  > s3q28s;
 /*  3 */ typedef fixed<  3, 29, false > u3q29;
 /*  3 */ typedef fixed<  3, 29, true  > u3q29s;
 //-----------------------------------------------------------------------------
 /*  4 */ typedef fixed<  4, 27, false > u4q27;
 /*  4 */ typedef fixed<  4, 27, true  > u4q27s;
 /*  4 */ typedef fixed<  4, 28, false > u4q28;
 /*  4 */ typedef fixed<  4, 28, true  > u4q28s;
 //-----------------------------------------------------------------------------
 /*  5 */ typedef fixed<  5, 26, false > s5q26;
 /*  5 */ typedef fixed<  5, 26, true  > s5q26s;
 /*  5 */ typedef fixed<  5, 27, false > s5q27;
 /*  5 */ typedef fixed<  5, 27, true  > s5q27s;
 //-----------------------------------------------------------------------------
 /*  6 */ typedef fixed<  6, 25, false > u6q25;
 /*  6 */ typedef fixed<  6, 25, true  > u6q25s;
 /*  6 */ typedef fixed<  6, 26, false > u6q26;
 /*  6 */ typedef fixed<  6, 26, true  > u6q26s;
 //-----------------------------------------------------------------------------
 /*  7 */ typedef fixed<  7, 25, false > s7q25;
 /*  7 */ typedef fixed<  7, 25, true  > s7q25s;
 /*  7 */ typedef fixed<  7, 24, false > s7q24;
 /*  7 */ typedef fixed<  7, 24, true  > s7q24s;
 //-----------------------------------------------------------------------------
 /*  8 */ typedef fixed<  8, 25, false > u8q25;
 /*  8 */ typedef fixed<  8, 25, true  > u8q25s;
 /*  8 */ typedef fixed<  8, 24, false > u8q24;
 /*  8 */ typedef fixed<  8, 24, true  > u8q24s;
 //-----------------------------------------------------------------------------
 /* 15 */ typedef fixed< 15, 16, false > s15q16;
 /* 15 */ typedef fixed< 15, 16, true  > s15q16s;
 /* 16 */ typedef fixed< 16, 16, false > u16q16;
 /* 16 */ typedef fixed< 16, 16, true  > u16q16s;
 //-----------------------------------------------------------------------------
 /* 23 */ typedef fixed< 23,  8, false > s23q8;
 /* 23 */ typedef fixed< 23,  8, true  > s23q8s;
 /* 24 */ typedef fixed< 24,  8, false > u24q8;
 /* 24 */ typedef fixed< 24,  8, true  > u24q8s;
 //-----------------------------------------------------------------------------
 
///////////////////////////////////////////////////////////////////////////////

} // namespace lamb

///////////////////////////////////////////////////////////////////////////////


/* Local Variables:  */
/* fill-column: 100  */
/* End:              */

#endif
