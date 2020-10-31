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

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 value_type value;

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 explicit constexpr
 q(value_type const & v) : value(v) {}

//---------------------------------------------------------------------------------------------------------------------
 
 explicit constexpr
 q(value_type const & whole, value_type const & frac) :
  value(value_type(whole * ONE.value + (whole < 0 ? - frac : frac))) {}
 
 /////////////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t whole, uint8_t frac>
  explicit constexpr 
  operator q<whole, frac>() const {

   typedef
    q<whole, frac>
    other_type;

   constexpr uint8_t INTERMED_SIZE = size_fit_bytes(SIZE+other_type::SIZE);

   printf("Convert % 2d.% 2d to % 2d.% 2d via % 0d byte type. \n", WHOLE, FRAC, whole, frac, INTERMED_SIZE);
   
   typedef typename
    find_integer<SIGNED, INTERMED_SIZE>::type
    intermediary_type;

   constexpr bool    FROM_SIGNED   = SIGNED && ! other_type::SIGNED;
   constexpr int8_t  FRAC_DELTA    = FRAC - frac;

   printf("Shift by % 2d \n", FRAC_DELTA);
   
   if constexpr(FROM_SIGNED) {
    if (value < 0) {
     return other_type(0);
    }
   }

   other_type ret(value);
   
   if constexpr(FRAC_DELTA >= 0) {
    ret.value >>= FRAC_DELTA;
   }
   else if constexpr(FRAC_DELTA <= 0) {
    ret.value <<= -FRAC_DELTA;
   }
   
   printf("Final value: % 8ld \n", ret.value);

   return ret;
  }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 explicit constexpr 
 operator float() const {
  constexpr float one = ONE.value * 1.0;

  printf("Float  % 8d from % 2d.% 2d = % 5.5lf \n", value, WHOLE, FRAC, value / one);
  return value / one;
 }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  static constexpr
  q from_float(
   float const & tmp
  ) {
   int        divisor = tmp;
   float     modulus  = tmp - divisor;
   value_type ipart   = ONE.value * divisor + int(ONE.value * modulus + 0.5);
   
   return q(ipart);
  }
 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  static
  q ffrom_float(
   float const & tmp
  ) {
   int        divisor = tmp;
   float     modulus  = tmp - divisor;
   value_type ipart   = ONE.value * divisor + int(ONE.value * modulus + 0.5);
   printf("Un-float % 5.5lf to % 2d.% 2d = % 8d \n", tmp, WHOLE, FRAC, ipart);
//   printf("div % 8ld mod % 8ld ipart % 8ld \n", divisor, modulus, ipart);
   
   return q(ipart);
  }
 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 static constexpr q       PI          = WHOLE >= 2 ? from_float(M_PI) : q(0);
 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 constexpr
  q operator ^ (
   q const & other
  ) const {
   return value ^ other.value;
  }  
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 template <uint8_t other_whole, uint8_t other_frac>
 constexpr
  q scaled_add (
   q<other_whole, other_frac> const & other
  ) const {
  q tmp(other);
  
  return (*this) + tmp;
 }

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    find_integer<SIGNED, INTERMED_SIZE>::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   intermediary_type big_tmp     = value;
   big_tmp                      *= other.value;
   big_tmp                     >>= other_frac;

   // if (false) {
   //  printf(
   //   "MUL % 13.05lf * % 13.05lf = % 13.05lf \n",
   //   float(*this),
   //   float(other),
   //   float(q(small_tmp))
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
   q<other_whole, other_frac> const & other
  ) const {

   typedef
    q<other_whole, other_frac>
    other_type;
    
   constexpr uint8_t INTERMED_SIZE = size_fit_bytes(SIZE+other_type::SIZE);
      
   typedef typename
    find_integer<SIGNED, INTERMED_SIZE>::type
    intermediary_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   intermediary_type big_tmp   = value;
   big_tmp                   <<= other_frac;
   big_tmp                    /= other.value;
   value_type small_tmp        = big_tmp;
   
   // if (true) {
   //  printf(
   //   "\nDIV  % 10u.%2u / % 10u.%2u = % 10u.%2u using a %u bit temporary\n",
   //   WHOLE,
   //   FRAC,
   //   other_whole,
   //   other_frac,
   //   WHOLE,
   //   FRAC,
   //   (sizeof(intermediary_type) << 3)
   //  );
   //  printf(
   //   " div % 16.05lf / % 16.05lf = % 16.05lf \n",
   //   float(*this),
   //   float(other),
   //   float(q(small_tmp))
   //  );
   //  printf(
   //   " big %16lu << ",
   //   ((intermediary_type)value)
   //  );
   //  printf("%lld ", ((intermediary_type)value) << other_frac);
   //  printf(
   //   " after shift %2u \n",
   //   other_frac
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

 
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 constexpr q    operator   + ()                         const = delete;
 constexpr q    operator   ~ ()                         const { return                  q(       ~ value)      ; }
 constexpr q    operator   - ()                         const { return                  q(       - value)      ; }
 //---------------------------------------------------------------------------------------------------------------
 constexpr q    operator  >> (uint8_t    const & shift) const { return                  q(value >> shift)      ; }
 constexpr q    operator  << (uint8_t    const & shift) const { return                  q(value << shift)      ; }
 //---------------------------------------------------------------------------------------------------------------
 constexpr q    operator   + (q          const & other) const { return                  q(value  + other.value); }
 constexpr q    operator   - (q          const & other) const { return                  q(value  - other.value); }
 //---------------------------------------------------------------------------------------------------------------
 constexpr bool operator   < (q          const & other) const { return                   (value  < other.value); }
 constexpr bool operator   > (q          const & other) const { return                   (value  > other.value); }
 constexpr bool operator  == (q          const & other) const { return                   (value == other.value); }
 //---------------------------------------------------------------------------------------------------------------
 constexpr q    operator   + (value_type const & other) const { return                  q(value  + other      ); }
 constexpr q    operator   - (value_type const & other) const { return                  q(value  - other      ); }
 constexpr q    operator   * (value_type const & other) const { return                  q(value  * other      ); }
 constexpr q    operator   / (value_type const & other) const { return                  q(value  / other      ); }
 //---------------------------------------------------------------------------------------------------------------
 constexpr bool operator   < (value_type const & other) const { return                   (value  < other      ); }
 constexpr bool operator   > (value_type const & other) const { return                   (value  > other      ); }
 constexpr bool operator  == (value_type const & other) const { return                   (value == other      ); }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 constexpr q &  operator  -- (                        )       { this        -=               q(1); return *this; }
 constexpr q &  operator  ++ (                        )       { this        +=               q(1); return *this; }
 //---------------------------------------------------------------------------------------------------------------
 constexpr q &  operator >>= (uint8_t    const &     v)       { this->value  = (*this>> v ).value; return *this; }
 constexpr q &  operator <<= (uint8_t    const &     v)       { this->value  = (*this<< v ).value; return *this; }
 //---------------------------------------------------------------------------------------------------------------
 constexpr q &  operator  -= (q          const &     v)       { this->value  = (*this - v ).value; return *this; }
 constexpr q &  operator  += (q          const &     v)       { this->value  = (*this + v ).value; return *this; }
 constexpr q &  operator  *= (q          const &     v)       { this->value  = (*this * v ).value; return *this; }
 constexpr q &  operator  /= (q          const &     v)       { this->value  = (*this / v ).value; return *this; }
 //---------------------------------------------------------------------------------------------------------------
 constexpr bool operator  <= (q          const &     o) const { return         (*this    == o ) || (*this < o) ; }
 constexpr bool operator  >= (q          const &     o) const { return         (*this    == o ) || (*this > o) ; }
 constexpr bool operator  != (q          const &     o) const { return       ! (*this    == o )                ; }
 //---------------------------------------------------------------------------------------------------------------
 constexpr q &  operator  -= (value_type const &     v)       { this->value  = (*this - v ).value; return *this; }
 constexpr q &  operator  += (value_type const &     v)       { this->value  = (*this + v ).value; return *this; }
 constexpr q &  operator  *= (value_type const &     v)       { this->value  = (*this * v ).value; return *this; }
 constexpr q &  operator  /= (value_type const &     v)       { this->value  = (*this / v ).value; return *this; }
 //---------------------------------------------------------------------------------------------------------------
 constexpr bool operator  <= (value_type const &     o) const { return         (*this    == o ) || (*this < o) ; }
 constexpr bool operator  >= (value_type const &     o) const { return         (*this    == o ) || (*this > o) ; }
 constexpr bool operator  != (value_type const &     o) const { return       ! (*this    == o )                ; }
//----------------------------------------------------------------------------------------------------------------
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 template <uint8_t w, uint8_t f>
 using fixed = q<w, f>;
 
 /////////////////////////////////////////////////////////////////////////////////////////
 // Typedefs
 /////////////////////////////////////////////////////////////////////////////////////////
 
 //---------------------------------------------------------------------------------------
 // 8 bits
 //---------------------------------------------------------------------------------------
 typedef fixed<  0,  7 > s0q7;
 //---------------------------------------------------------------------------------------
 typedef fixed<  0,  8 > u0q8;
 //---------------------------------------------------------------------------------------
 constexpr s0q7  operator ""_s0q7(long double x)    { return s0q7::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr u0q8  operator ""_u0q8(long double x)    { return u0q8::from_float(x); }
 //---------------------------------------------------------------------------------------
 
 //---------------------------------------------------------------------------------------
 // 16 bits
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 16 > u0q16;
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 15 > s0q15;
 typedef fixed<  1, 15 > u1q15;
 //---------------------------------------------------------------------------------------
 typedef fixed<  1, 14 > s1q14;
 typedef fixed<  2, 14 > u2q14;
 //---------------------------------------------------------------------------------------
 typedef fixed<  2, 13 > s2q13;
 typedef fixed<  3, 13 > u3q13;
 //---------------------------------------------------------------------------------------
 typedef fixed<  3, 12 > s3q12;
 typedef fixed<  4, 12 > u4q12;
 //---------------------------------------------------------------------------------------
 typedef fixed<  4, 11 > s4q11;
 typedef fixed<  5, 11 > u5q11;
 //---------------------------------------------------------------------------------------
 typedef fixed<  5, 10 > s5q10;
 typedef fixed<  6, 10 > u6q10;
 //---------------------------------------------------------------------------------------
 typedef fixed<  6,  9 > s6q9;
 typedef fixed<  7,  9 > u7q9;
 //---------------------------------------------------------------------------------------
 typedef fixed<  7,  8 > s7q8;
 typedef fixed<  8,  8 > u8q8;
 //---------------------------------------------------------------------------------------
 constexpr u0q16   operator ""_u0q16(long double x)   { return u0q16::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s0q15   operator ""_s0q15(long double x)   { return s0q15::from_float(x); }
 constexpr u1q15   operator ""_u1q15(long double x)   { return u1q15::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s1q14   operator ""_s1q14(long double x)   { return s1q14::from_float(x); }
 constexpr u2q14   operator ""_u2q14(long double x)   { return u2q14::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s2q13   operator ""_s2q13(long double x)   { return s2q13::from_float(x); }
 constexpr u3q13   operator ""_u3q13(long double x)   { return u3q13::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s3q12   operator ""_s3q12(long double x)   { return s3q12::from_float(x); }
 constexpr u4q12   operator ""_u4q12(long double x)   { return u4q12::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s4q11   operator ""_s4q11(long double x)   { return s4q11::from_float(x); }
 constexpr u5q11   operator ""_u5q11(long double x)   { return u5q11::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s5q10   operator ""_s5q10(long double x)   { return s5q10::from_float(x); }
 constexpr u6q10   operator ""_u6q10(long double x)   { return u6q10::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s6q9    operator ""_s6q9(long double x)    { return s6q9::from_float(x);  }
 constexpr u7q9    operator ""_u7q9(long double x)    { return u7q9::from_float(x);  }
 //---------------------------------------------------------------------------------------
 constexpr s7q8    operator ""_s7q8(long double x)    { return s7q8::from_float(x);  }
 constexpr u8q8    operator ""_u8q8(long double x)    { return u8q8::from_float(x);  }
 //---------------------------------------------------------------------------------------
 
 //---------------------------------------------------------------------------------------
 // 32 bits
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 32 > u0q32;
 //---------------------------------------------------------------------------------------
 typedef fixed<  0, 31 > s0q31;
 typedef fixed<  1, 31 > u1q31;
 //---------------------------------------------------------------------------------------
 typedef fixed<  1, 30 > s1q30;
 typedef fixed<  2, 30 > u2q30;
 //---------------------------------------------------------------------------------------
 typedef fixed<  2, 29 > s2q29;
 typedef fixed<  3, 29 > u3q29;
 //---------------------------------------------------------------------------------------
 typedef fixed<  3, 28 > s3q28;
 typedef fixed<  4, 28 > u4q28;
 //---------------------------------------------------------------------------------------
 typedef fixed<  4, 27 > u4q27;
 typedef fixed<  5, 27 > s5q27;
 //---------------------------------------------------------------------------------------
 typedef fixed<  5, 26 > s5q26;
 typedef fixed<  6, 26 > u6q26;
 //---------------------------------------------------------------------------------------
 typedef fixed<  7, 25 > s7q25;
 typedef fixed<  8, 25 > u8q25;
 //---------------------------------------------------------------------------------------
 typedef fixed<  7, 24 > s7q24;
 typedef fixed<  8, 24 > u8q24;
 //---------------------------------------------------------------------------------------
 typedef fixed< 11, 20 > s11q20;
 typedef fixed< 12, 20 > u12q20;
 //---------------------------------------------------------------------------------------
 typedef fixed< 15, 16 > s15q16;
 typedef fixed< 16, 16 > u16q16;
 //---------------------------------------------------------------------------------------
 typedef fixed< 16, 15 > s16q15;
 typedef fixed< 17, 15 > u17q15;
 //---------------------------------------------------------------------------------------
 typedef fixed< 17, 14 > s17q14;
 typedef fixed< 18, 14 > u18q14;
 //---------------------------------------------------------------------------------------
 typedef fixed< 19, 12 > s19q12;
 typedef fixed< 20, 12 > u20q12;
 //---------------------------------------------------------------------------------------
 typedef fixed< 21, 10 > s32q10;
 typedef fixed< 22, 10 > u22q10;
 //---------------------------------------------------------------------------------------
 typedef fixed< 23,  8 > s23q8;
 typedef fixed< 24,  8 > u24q8;
 //---------------------------------------------------------------------------------------
 typedef fixed< 23,  8 > s23q8;
 typedef fixed< 24,  8 > u24q8;
 //---------------------------------------------------------------------------------------
 typedef fixed< 27,  4 > s27q4;
 typedef fixed< 28,  4 > u28q4;
 //---------------------------------------------------------------------------------------
 typedef fixed< 29,  2 > s29q2;
 typedef fixed< 30,  2 > u30q2;
 //---------------------------------------------------------------------------------------
 typedef fixed< 30,  1 > s30q1;
 typedef fixed< 31,  1 > u31q1;
 //---------------------------------------------------------------------------------------
 constexpr u0q32    operator ""_u0q32(long double x)   { return u0q32::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s0q31    operator ""_s0q31(long double x)   { return s0q31::from_float(x); }
 constexpr u1q31    operator ""_u1q31(long double x)   { return u1q31::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s1q30    operator ""_s1q30(long double x)   { return s1q30::from_float(x); }
 constexpr u2q30    operator ""_u2q30(long double x)   { return u2q30::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s2q29    operator ""_s2q29(long double x)   { return s2q29::from_float(x); }
 constexpr u3q29    operator ""_u3q29(long double x)   { return u3q29::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s3q28    operator ""_s3q28(long double x)   { return s3q28::from_float(x); }
 constexpr u4q28    operator ""_u4q28(long double x)   { return u4q28::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr u4q27    operator ""_u4q27(long double x)   { return u4q27::from_float(x); }
 constexpr s5q27    operator ""_s5q27(long double x)   { return s5q27::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s5q26    operator ""_s5q26(long double x)   { return s5q26::from_float(x); }
 constexpr u6q26    operator ""_u6q26(long double x)   { return u6q26::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s7q25    operator ""_s7q25(long double x)   { return s7q25::from_float(x); }
 constexpr u8q25    operator ""_u8q25(long double x)   { return u8q25::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s7q24    operator ""_s7q24(long double x)   { return s7q24::from_float(x); }
 constexpr u8q24    operator ""_u8q24(long double x)   { return u8q24::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s11q20   operator ""_s11q20(long double x)  { return s11q20::from_float(x);}
 constexpr u12q20   operator ""_u12q20(long double x)  { return u12q20::from_float(x);}
 //---------------------------------------------------------------------------------------
 constexpr s15q16   operator ""_s15q16(long double x)  { return s15q16::from_float(x);}
 constexpr u16q16   operator ""_u16q16(long double x)  { return u16q16::from_float(x);}
 //---------------------------------------------------------------------------------------
 constexpr s16q15   operator ""_s16q15(long double x)  { return s16q15::from_float(x);}
 constexpr u17q15   operator ""_u17q15(long double x)  { return u17q15::from_float(x);}
 //---------------------------------------------------------------------------------------
 constexpr s17q14   operator ""_s17q14(long double x)  { return s17q14::from_float(x);}
 constexpr u18q14   operator ""_u18q14(long double x)  { return u18q14::from_float(x);}
 //---------------------------------------------------------------------------------------
 constexpr s19q12   operator ""_s19q12(long double x)  { return s19q12::from_float(x);}
 constexpr u20q12   operator ""_u20q12(long double x)  { return u20q12::from_float(x);}
 //---------------------------------------------------------------------------------------
 constexpr s32q10   operator ""_s32q10(long double x)  { return s32q10::from_float(x);}
 constexpr u22q10   operator ""_u22q10(long double x)  { return u22q10::from_float(x);}
 //---------------------------------------------------------------------------------------
 constexpr s23q8    operator ""_s23q8(long double x)   { return s23q8::from_float(x); }
 constexpr u24q8    operator ""_u24q8(long double x)   { return u24q8::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s27q4    operator ""_s27q4(long double x)   { return s27q4::from_float(x); }
 constexpr u28q4    operator ""_u28q4(long double x)   { return u28q4::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s29q2    operator ""_s29q2(long double x)   { return s29q2::from_float(x); }
 constexpr u30q2    operator ""_u30q2(long double x)   { return u30q2::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr s30q1    operator ""_s30q1(long double x)   { return s30q1::from_float(x); }
 constexpr u31q1    operator ""_u31q1(long double x)   { return u31q1::from_float(x); }
 //---------------------------------------------------------------------------------------

 //---------------------------------------------------------------------------------------
 // integrals for convenience in math operations.
 //---------------------------------------------------------------------------------------
 typedef fixed<  8,  0 > u8q0;   
 typedef fixed<  7,  0 > s7q0;
 //---------------------------------------------------------------------------------------
 typedef fixed< 16,  0 > u16q0;
 typedef fixed< 15,  0 > s15q0;
 //---------------------------------------------------------------------------------------
 typedef fixed< 32,  0 > u32q0;
 typedef fixed< 31,  0 > s31q0;
 //---------------------------------------------------------------------------------------
 constexpr u8q0    operator ""_u8q0(long double x)    { return u8q0::from_float(x);  }
 constexpr s7q0    operator ""_s7q0(long double x)    { return s7q0::from_float(x);  }
 //---------------------------------------------------------------------------------------
 constexpr u16q0   operator ""_u16q0(long double x)   { return u16q0::from_float(x); }
 constexpr s15q0   operator ""_s15q0(long double x)   { return s15q0::from_float(x); }
 //---------------------------------------------------------------------------------------
 constexpr u32q0   operator ""_u32q0(long double x)   { return u32q0::from_float(x); }
 constexpr s31q0   operator ""_s31q0(long double x)   { return s31q0::from_float(x); }
 //---------------------------------------------------------------------------------------
 
//////////////////////////////////////////////////////////////////////////////////////////

} // namespace lamb

//////////////////////////////////////////////////////////////////////////////////////////

/* Local Variables:  */
/* fill-column: 140  */
/* End:              */

#endif
