#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

///////////////////////////////////////////////////////////////////////////////

#ifdef LAMB_NO_ARDUINO
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
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
  bool saturate_ = false
  >
 class fixed {

////////////////////////////////////////////////////////////////////////////////

 private: 

  template <bool use_left, typename left, typename right>
  class type_if {};
  
  template <typename left, typename right>
  class type_if<true, left, right> {
  public:
   typedef left type;
  };
  
  template <typename left, typename right>
  class type_if<false, left, right> {
  public:
   typedef right type;
 };
 
//////////////////////////////////////////////////////////////////////////////// 

 public:

  static const bool    SATURATE       = saturate_;
  static const uint8_t CHARACTERISTIC = characteristic_;
  static const uint8_t MANTISSA       = mantissa_;
  static const bool    SIGNED         = ((CHARACTERISTIC + MANTISSA ) % 2) == 1;
  static const size_t  SIZE           = (
   CHARACTERISTIC +
   MANTISSA +
   (SIGNED ? 1 : 0)
  ) / 8;

////////////////////////////////////////////////////////////////////////////////
  
  typedef
  typename type_if<
   SIGNED,
   typename signed_int<SIZE>::type,
   typename unsigned_int<SIZE>::type
   >::type  
  type;
  
  typedef
  typename type_if<
   SIGNED,
   typename signed_int<(SIZE << 1)>::type,
   typename unsigned_int<(SIZE << 1)>::type
   >::type
  big_type;
  
  template <bool sat>
  using compatible_type = fixed<CHARACTERISTIC, MANTISSA, sat>;

  typedef
  compatible_type<(! SATURATE)>
   sat_cast_type;
  
  typedef
  fixed<CHARACTERISTIC, MANTISSA, SATURATE>
  self_type;

////////////////////////////////////////////////////////////////////////////////

 public:
  
  static constexpr
  type    ONE = (
   (CHARACTERISTIC == 0) ? 
   ((((big_type)1) << MANTISSA) - 1) :
   (1 << MANTISSA)
  );
  
  static constexpr
  type    MAX = (
   SIGNED ?
   signed_int<SIZE>::MAX :
   unsigned_int<SIZE>::MAX
  );
   
  static constexpr
  type    MIN = (
   SIGNED?
   signed_int<SIZE>::MIN :
   unsigned_int<SIZE>::MIN
  );

////////////////////////////////////////////////////////////////////////////////

  type val;
  
  mutable
  bool overflow;  

////////////////////////////////////////////////////////////////////////////////
  
  static constexpr
  type mask() {
   type m = 0;
   
   for (uint8_t ix = 0; ix < MANTISSA; ix++) {
    m |= 1 << ix;
   }
   
   return m;
  }

////////////////////////////////////////////////////////////////////////////////

  type mantissa() const { // return smaller type?
   return val & mask();
  }
  
////////////////////////////////////////////////////////////////////////////////

  type characteristic() const {    // return smaller type?
   if (CHARACTERISTIC == 0) {
    return 0;
   }
   else {
    return (val & (~mask())) >> MANTISSA;
   }
  }     
  
////////////////////////////////////////////////////////////////////////////////

  explicit constexpr
  fixed(type const & tmp_) :
   val(tmp_), overflow(false) {}

  explicit constexpr
  fixed(
   type const & characteristic__,
   type const & mantissa__
  ) :
   val((characteristic__ * ONE) + mantissa__), overflow(false) {}

////////////////////////////////////////////////////////////////////////////////

  operator double() const {
   return val / (ONE * 1.0);
  }

///////////////////////////////////////////////////////////////////////////////

  static constexpr self_type from_double(double const & tmp) {
   int           divisor = tmp;
   double        modulus = tmp - divisor;
   type          ipart   = ONE * divisor + int(ONE * modulus);
   
   return self_type(ipart);
  }

////////////////////////////////////////////////////////////////////////////////

  bool
  operator ~ () const {
   if (SIGNED) {
    return self_type(val * -1);
   }
   else {
    return self_type(~val);
   }
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  bool
  operator ^ (
   compatible_type<sat> const & other
  ) const {
    return self_type(val ^ other.val);
  }  

////////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  bool
  operator == (
   compatible_type<sat> const & other
  ) const {
   return val == other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  bool
  operator != (
   compatible_type<sat> const & other
  ) const {
   return val != other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  bool
  operator > (
   compatible_type<sat> const & other
  ) const {
   return val > other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  bool
  operator < (
   compatible_type<sat> const & other
  ) const {
   return val < other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  bool
  operator >= (
   compatible_type<sat> const & other
  ) const {
   return val >= other.val;
  }    

////////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  bool
  operator <= (
   compatible_type<sat> const & other
  ) const {
   return val <= other.val;
  }    

///////////////////////////////////////////////////////////////////////////////

 private:
  
  template <bool sat>
  class adjacent_types {
  public:
   typedef
   fixed<(CHARACTERISTIC << 1), (MANTISSA << 1), sat>
   larger_type;

   typedef
   fixed<(CHARACTERISTIC >> 1), (MANTISSA >> 1), sat>
   smaller_type;
  };

  typedef typename adjacent_types<SATURATE>::larger_type larger_type;
  typedef typename adjacent_types<SATURATE>::smaller_type smaller_type;
  
////////////////////////////////////////////////////////////////////////////////

 public:

  template <bool saturate__>
  operator
  larger_type () const {
   return larger_type(
    val << 1
   );
  }

  template <bool saturate__>
  operator
  smaller_type () const {
   return smaller_type(
    val >> 1
   );
  }

  operator
  sat_cast_type () const {
   return sat_cast_type(val);
  }
  
///////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  self_type
  operator + (
   compatible_type<sat> const & other
  ) const {
   type          old        = val;
   big_type      big_tmp    = old;
   big_tmp                 += other.val;
   type          small_tmp  = big_tmp;
   
   if (check_overflow('+', old, other.val, small_tmp)) {
    overflow = true;
   }

   return self_type(small_tmp);
  }    

  template <bool sat>
  self_type &
  operator += (
   compatible_type<sat> const & other
  ) {
   val = ((*this) + other).val;

   return *(static_cast<self_type *>(this));
  }

  ///////////////////////////////////////////////////////////////////////////////

  template <bool sat>
  self_type
  operator - (
   compatible_type<sat> const & other
  ) const {
   type          old        = val;
   big_type      big_tmp    = old;
   big_tmp                 -= other.val;
   type          small_tmp  = big_tmp;
   
   if (check_overflow('-', old, other.val, small_tmp)) {
    overflow = true;
   }

   return self_type(small_tmp);
  }    

  template <bool sat>
  self_type &
  operator -= (
   compatible_type<sat> const & other
  ) {
   self_type tmp = (*this) - other;
  
   val = tmp.val;

   return *(static_cast<self_type *>(this));
  }

///////////////////////////////////////////////////////////////////////////////

  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  self_type
  operator * (
   fixed<other_charac, other_mantissa, other_saturate> const & other
  ) const {

   typedef
    fixed<other_charac, other_mantissa, other_saturate>
    other_type;

   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   type                    old(val);

   if constexpr(sizeof(other_type) > sizeof(self_type)) {
    typename
     other_type::big_type big_tmp     = val;
    big_tmp                          *= other.val;
    big_tmp                         >>= other.mantissa;     
    type                  small_tmp   = big_tmp;
    
    if (check_overflow('x', old, other.val, small_tmp)) {
     overflow = true;
    }

    return self_type(small_tmp);
   }
   else {
    big_type              big_tmp     = val;
    big_tmp                          *= other.val;
    big_tmp                         >>= other_mantissa;
    type                  small_tmp   = big_tmp;
     
    if (check_overflow('*', old, other.val, small_tmp)) {
     overflow = true;
    }

    return self_type(small_tmp);
   }
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  self_type & 
  operator *= (
   fixed<other_charac,other_mantissa, saturate__> const & other
  ) {
   val = ((*this) * other).val;

   return *(static_cast<self_type *>(this));
  }

////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  self_type
  operator / (
   fixed<other_charac,other_mantissa,other_saturate> const & other
  ) const {

   typedef
    fixed<other_charac, other_mantissa, other_saturate>
    other_type;
    
   static_assert(
    ( ! ( ( ! SIGNED) && (other_type::SIGNED) ) ),
    "Signedness mismatch!"
   );

   type                   old(val);

   if constexpr(sizeof(other_type) > sizeof(self_type)) {
    typename
     other_type::big_type big_tmp     = val;
    big_tmp                         <<= other_mantissa;
    big_tmp                          /= other.val;
    type                  small_tmp   = big_tmp;

    if (check_overflow('x', old, other.val, small_tmp)) {
     overflow = true;
    }

    return self_type(small_tmp);
   }
   else {    
    big_type              big_tmp     = val;
    big_tmp                         <<= other_mantissa;
    big_tmp                          /= other.val;
    type                  small_tmp   = big_tmp;
  
    if (check_overflow('/', old, other.val, small_tmp)) {
     overflow = true;
    }

    return self_type(small_tmp);
   }
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  self_type & 
  operator /= (
   fixed<other_charac,other_mantissa, saturate__> const & other
  ) {   
   val = ((*this) / other).val;

   return *this;
  }

///////////////////////////////////////////////////////////////////////////////

// This check is currently not effective for multiplication operations and
// should really be re-written entirely:
 
#ifndef LAMB_FP_NO_OVERFLOW_CHECKING
  template <typename delta_t>                                    
  static bool check_overflow(                                    
   char    const & symbol,                                       
   type    const & old_val,                                      
   delta_t const & delta,                                        
   type          & set                                           
  ) {                                                            
   int64_t ttmp = old_val;                                       
   int64_t ttmp_delta = delta;                                   
   
   ttmp += ttmp_delta;                                           
                                                                
   bool over  = ttmp > MAX;                                      
   
   if (over)                                                     
    printf("%lld exceeds %lld.\n", ttmp, MAX);                   
   
   bool under = ttmp < MIN;                                      
   
   if (under)                                                    
    printf("%lld under %lld.\n", ttmp, MIN);                     
   
   if (over || under) {                                          
    if (SATURATE) {                                              
     printf(                                                     
      "SATURATE: %ld %c %ld = %lld MIN: %lld MAX: %lld \n",      
      old_val,                                                   
      symbol,                                                    
      delta,                                                     
      ttmp,                                                      
      MIN,                                                       
      MAX                                                        
     );                                                          
     set = MAX;                                                  
    }                                                            
    else {                                                       
    }                                                            
   }                                                             
   
   return (over || under);                                       
  }                                                
#else
 template <typename big_t, typename delta_t, typename new_t>
 static bool check_overflow(                                
  char    const & symbol,                                   
  type    const & old_val,                                  
  delta_t const & delta,                                    
  new_t   const & new_val,                                  
  type          & set                                       
 ) { return false; }                                                    
#endif
  
 }; // template fixed
 

//////////////////////////////////////////////////////////////////////////////
// Typedefs
//////////////////////////////////////////////////////////////////////////////
  
// Overflow-able types ////////////////////////////////////////////////////////
  
 typedef fixed<  0,  8, false > q0n8;
 typedef fixed<  8,  8, false > q8n8;
 typedef fixed<  0, 16, false > q0n16;
 typedef fixed< 16, 16, false > q16n16;
 typedef fixed<  0, 32, false > q0n32;

 typedef fixed<  2, 14, false > q2n14;
 typedef fixed<  2, 30, false > q2n30;
  
 typedef fixed<  0,  7, false > q0n7;
 typedef fixed<  7,  8, false > q7n8;
 typedef fixed<  0, 15, false > q0n15;
 typedef fixed< 15, 16, false > q15n16;
 typedef fixed<  0, 31, false > q0n31;

// Saturating types ///////////////////////////////////////////////////////////
 
 typedef fixed<  0,  8, true  > q0n8s;
 typedef fixed<  8,  8, true  > q8n8s;
 typedef fixed<  0, 16, true  > q0n16s;
 typedef fixed< 16, 16, true  > q16n16s; 
 typedef fixed<  0, 32, true  > q0n32s;

 typedef fixed<  2, 14, true  > q2n14s;
 typedef fixed<  2, 30, true  > q2n30s;
  
 typedef fixed<  0,  7, true  > q0n7s;
 typedef fixed<  7,  8, true  > q7n8s;
 typedef fixed<  0, 15, true  > q0n15s;
 typedef fixed< 15, 16, true  > q15n16s;
 typedef fixed<  0, 31, true  > q0n31s;
 
///////////////////////////////////////////////////////////////////////////////

} // namespace lamb

///////////////////////////////////////////////////////////////////////////////

#undef CHECK_OVERFLOW
  
#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */

