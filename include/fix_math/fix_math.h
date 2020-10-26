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

///////////////////////////////////////////////////////////////////////////////

// This check is currently not effective for multiplication operations and
// should really be re-written entirely:
 
#ifndef LAMB_FP_NO_OVERFLOW_CHECKING
#define CHECK_OVERFLOW                                          \
 template <typename delta_t>                                    \
 static bool check_overflow(                                    \
  char    const & symbol,                                       \
  type    const & old_val,                                      \
  delta_t const & delta,                                        \
  type          & set                                           \
 ) {                                                            \
  int64_t ttmp = old_val;                                       \
  int64_t ttmp_delta = delta;                                   \
                                                                \
  ttmp += ttmp_delta;                                           \
                                                                \
  bool over  = ttmp > MAX;                                      \
                                                                \
  if (over)                                                     \
   printf("%lld exceeds %lld.\n", ttmp, MAX);                   \
                                                                \
  bool under = ttmp < MIN;                                      \
                                                                \
  if (under)                                                    \
   printf("%lld under %lld.\n", ttmp, MIN);                     \
                                                                \
  if (over || under) {                                          \
   if (SATURATE) {                                              \
    printf(                                                     \
     "SATURATE: %ld %c %ld = %lld MIN: %lld MAX: %lld \n",      \
     old_val,                                                   \
     symbol,                                                    \
     delta,                                                     \
     ttmp,                                                      \
     MIN,                                                       \
     MAX                                                        \
    );                                                          \
    set = MAX;                                                  \
   }                                                            \
   else {                                                       \
   }                                                            \
  }                                                             \
                                                                \
  return (over || under);                                       \
 }                                                
#else
#define CHECK_OVERFLOW                                          \
 template <typename big_t, typename delta_t, typename new_t>    \
 static bool check_overflow(                                    \
  char    const & symbol,                                       \
  type    const & old_val,                                      \
  delta_t const & delta,                                        \
  new_t   const & new_val,                                      \
  type          & set                                           \
 ) { return false; }                                                    
#endif

////////////////////////////////////////////////////////////////////////////////
 
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
// Advance declarations:
////////////////////////////////////////////////////////////////////////////////

 template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_>
 class signed_frac;
    
 template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_>
 class unsigned_frac;
    
////////////////////////////////////////////////////////////////////////////////
// Base
////////////////////////////////////////////////////////////////////////////////

 template <
  uint8_t characteristic_,
  uint8_t mantissa_,
  bool saturate_ = false
  >
 class frac_base {

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
  
  typedef
  typename type_if<
   SIGNED,
   signed_frac<CHARACTERISTIC, MANTISSA, (! SATURATE)>,
   unsigned_frac<CHARACTERISTIC, MANTISSA, (! SATURATE)>
   >::type
  sat_cast_type;
  
  typedef
  typename type_if<
   SIGNED,
   signed_frac<CHARACTERISTIC, MANTISSA, SATURATE>,
   unsigned_frac<CHARACTERISTIC, MANTISSA, SATURATE>
   >::type
  derived_type;
  
  typedef
  typename type_if<
   SIGNED,
   signed_frac<(CHARACTERISTIC << 1), (MANTISSA << 1), SATURATE>,
   unsigned_frac<(CHARACTERISTIC << 1), (MANTISSA << 1), SATURATE>
   >::type
  larger_type;
  
  typedef
  typename type_if<
   SIGNED,
   signed_frac<(CHARACTERISTIC >> 1), (MANTISSA >> 1), SATURATE>,
   unsigned_frac<(CHARACTERISTIC >> 1), (MANTISSA >> 1), SATURATE>
   >::type
  smaller_type;
  
////////////////////////////////////////////////////////////////////////////////

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
  frac_base(type const & tmp_) :
   val(tmp_), overflow(false) {}

  explicit constexpr
  frac_base(
   type const & characteristic__,
   type const & mantissa__
  ) :
   val((characteristic__ * ONE) + mantissa__), overflow(false) {}

////////////////////////////////////////////////////////////////////////////////

  CHECK_OVERFLOW;

////////////////////////////////////////////////////////////////////////////////

  operator double() const {
   return val / (ONE * 1.0);
  }

///////////////////////////////////////////////////////////////////////////////

  static constexpr derived_type from_float(double const & tmp_) {
   int           divisor = int(tmp_);
   double        modulus = tmp_ - divisor;
   type          ipart   = ONE * divisor + int(ONE * modulus);
   
   return derived_type(ipart);
  }

////////////////////////////////////////////////////////////////////////////////

  sat_cast_type sat_cast () const {
   return sat_cat_type(val);
  }
  
////////////////////////////////////////////////////////////////////////////////
  
  bool
  operator == (
   derived_type const & other
  ) const {
   return val == other.val;
  }    

  bool
  operator == (
   sat_cast_type const & other
  ) const {
   return val == other.val;
  }    

///////////////////////////////////////////////////////////////////////////////
  
  template <bool saturate__>
  operator
  typename
  type_if<
   SIGNED,
   signed_frac<
    (CHARACTERISTIC << 1),
    (MANTISSA << 1),
    saturate__
    >,
   unsigned_frac<
    (CHARACTERISTIC << 1),
    (MANTISSA << 1),
    saturate__
    >
   >::type () const {
   return typename
    type_if<
     SIGNED,
    signed_frac<
     (CHARACTERISTIC << 1),
     (MANTISSA << 1),
     saturate__
     >,
    unsigned_frac<
     (CHARACTERISTIC << 1),
     (MANTISSA << 1),
     saturate__
     >
    >::type(
    val << 1
   );
  }

  template <bool saturate__>
  operator
    typename
  type_if<
   SIGNED,
   signed_frac<
   (CHARACTERISTIC >> 1),
   (MANTISSA >> 1),
   saturate__
   >,
   unsigned_frac<
   (CHARACTERISTIC >> 1),
   (MANTISSA >> 1),
   saturate__
   >
   >::type () const {
   return typename
    type_if<
     SIGNED,
    signed_frac<
     (CHARACTERISTIC >> 1),
     (MANTISSA >> 1),
     saturate__
     >,
    unsigned_frac<
     (CHARACTERISTIC >> 1),
     (MANTISSA >> 1),
     saturate__
     >
    >::type(
    val << 1
   );
  }

///////////////////////////////////////////////////////////////////////////////
    
  derived_type
  operator + (
   derived_type const & other
  ) const {
   type          old       = val;
   big_type      big_tmp   = ((big_type)old) + other.val;
   type          small_tmp = (type)big_tmp;
   
   if (check_overflow('+', old, other.val, small_tmp)) {
    overflow = true;
   }

   return derived_type(small_tmp);
  }    

  template <bool saturate__>
  derived_type &
  operator += (
   derived_type const & other
  ) {
   val = ((*this) + other).val;

   return *(static_cast<derived_type *>(this));
  }

  derived_type
  operator + (
   sat_cast_type const & other
  ) const {
   type          old       = val;
   big_type      big_tmp   = ((big_type)old) + other.val;
   type          small_tmp = (type)big_tmp;
   
   if (check_overflow('+', old, other.val, small_tmp)) {
    overflow = true;
   }

   return derived_type(small_tmp);
  }    

  template <bool saturate__>
  derived_type &
  operator += (
   sat_cast_type const & other
  ) {
   val = ((*this) + other).val;

   return *(static_cast<derived_type *>(this));
  }

  ///////////////////////////////////////////////////////////////////////////////
    
  derived_type
  operator - (
   derived_type const & other
  ) const {
   type          old       = val;
   big_type      big_tmp   = ((big_type)old) - other.val;
   type          small_tmp = (type)big_tmp;
   
   if (check_overflow('-', old, other.val, small_tmp)) {
    overflow = true;
   }

   return derived_type(small_tmp);
  }    

  derived_type &
  operator -= (
   derived_type const & other
  ) {
   derived_type tmp = (*this) - other;
  
   val = tmp.val;

   return *(static_cast<derived_type *>(this));
  }

  derived_type
  operator - (
   sat_cast_type const & other
  ) const {
   type          old       = val;
   big_type      big_tmp   = ((big_type)old) - other.val;
   type          small_tmp = (type)big_tmp;
   
   if (check_overflow('-', old, other.val, small_tmp)) {
    overflow = true;
   }

   return derived_type(small_tmp);
  }    

  derived_type &
  operator -= (
   sat_cast_type const & other
  ) {
   derived_type tmp = (*this) - other;
  
   val = tmp.val;

   return *(static_cast<derived_type *>(this));
  }

///////////////////////////////////////////////////////////////////////////////

  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  derived_type
  operator * (
   unsigned_frac<other_charac, other_mantissa, other_saturate> const & other
  ) const {

   typedef
    typename type_if<
     SIGNED,
    signed_frac<other_charac, other_mantissa, other_saturate>,
    unsigned_frac<other_charac, other_mantissa, other_saturate>
    >::type
    other_type;

   typedef typename other_type::big_type
    right_big_type;

   typedef typename unsigned_int<(sizeof(right_big_type))>::type
    pseudo_right_big_type;

   type                    old(val);

   if constexpr(sizeof(other_type) > sizeof(derived_type)) {
    pseudo_right_big_type big_tmp     = ((pseudo_right_big_type)val) * other.val;
    big_tmp                         >>= other.mantissa;     
    type                  small_tmp   = (type)big_tmp;

    
    if (check_overflow('x', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
   else {
    big_type              big_tmp     = ((big_type)val) * other.val;
    big_tmp                         >>= other_mantissa;
    type                  small_tmp   = (type)big_tmp;
     
    if (check_overflow('*', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  derived_type & 
  operator *= (
   unsigned_frac<other_charac,other_mantissa, saturate__> const & other
  ) {
   val = ((*this) * other).val;

   return *(static_cast<derived_type *>(this));
  }

///////////////////////////////////////////////////////////////////////////////

  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  derived_type
  operator * (
   signed_frac<other_charac, other_mantissa, other_saturate> const & other
  ) const {

   static_assert(SIGNED, "must be signed");
   
   typedef
    typename type_if<
     SIGNED,
    signed_frac<other_charac, other_mantissa, other_saturate>,
    unsigned_frac<other_charac, other_mantissa, other_saturate>
    >::type
    other_type;

   typedef typename other_type::big_type
    right_big_type;

   typedef typename unsigned_int<(sizeof(right_big_type))>::type
    pseudo_right_big_type;

   type                    old(val);

   if constexpr(sizeof(other_type) > sizeof(derived_type)) {
    pseudo_right_big_type big_tmp     = ((pseudo_right_big_type)val) * other.val;
    big_tmp                         >>= other.mantissa;     
    type                  small_tmp   = (type)big_tmp;

    if (check_overflow('x', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
   else {
    big_type              big_tmp     = ((big_type)val) * other.val;
    big_tmp                         >>= other_mantissa;
    type                  small_tmp   = (type)big_tmp;
 
    if (check_overflow('*', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  derived_type & 
  operator *= (
   signed_frac<other_charac,other_mantissa, saturate__> const & other
  ) {
   val = ((*this) * other).val;

   return *(static_cast<derived_type *>(this));
  }

////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  derived_type
  operator / (
   unsigned_frac<other_charac,other_mantissa,other_saturate> const & other
  ) const {

   typedef
    unsigned_frac<other_charac, other_mantissa, other_saturate>
    other_type;

   type                   old(val);

   if constexpr(sizeof(other_type) > sizeof(derived_type)) {
    typename
     other_type::big_type big_tmp     = val;
    big_tmp                         <<= other_mantissa;
    big_tmp                          /= other.val;
    type                  small_tmp   = big_tmp;

    if (check_overflow('x', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
   else {    
    big_type              big_tmp     = val;
    big_tmp                         <<= other_mantissa;
    big_tmp                          /= other.val;
    type                  small_tmp   =big_tmp;
  
    if (check_overflow('/', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  derived_type & 
  operator /= (
   unsigned_frac<other_charac,other_mantissa, saturate__> const & other
  ) {
   val = ((*this) / other).val;

   return *this;
  }
  
  
  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  derived_type
  operator / (
   signed_frac<other_charac,other_mantissa,other_saturate> const & other
  ) const {

   static_assert(SIGNED, "must be signed");
   
   typedef
    signed_frac<other_charac, other_mantissa, other_saturate>
    other_type;
   
   type                   old(val);

   if constexpr(sizeof(other_type) > sizeof(derived_type)) {
    typename
     other_type::big_type  big_tmp    = val;
    big_tmp                         <<= other_mantissa;
    big_tmp                          /= other.val;
    type                  small_tmp   = big_tmp;

    if (check_overflow('x', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
   else {    
    big_type              big_tmp     = val;
    big_tmp                         <<= other_mantissa;
    big_tmp                          /= other.val;
    type                  small_tmp   = big_tmp;
  
    if (check_overflow('/', old, other.val, small_tmp)) {
     overflow = true;
    }

    return derived_type(small_tmp);
   }
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  derived_type & 
  operator /= (
   signed_frac<other_charac,other_mantissa, saturate__> const & other
  ) {
   val = ((*this) / other).val;

   return *this;
  }
  
///////////////////////////////////////////////////////////////////////////////

 }; // template frac_base
 
///////////////////////////////////////////////////////////////////////////////
// Unsigned fixed point numbers
///////////////////////////////////////////////////////////////////////////////
  
 template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_ = false>
 class unsigned_frac : public frac_base<
  characteristic_,
  mantissa_,
  saturate_
  > {

 public:
  typedef frac_base<characteristic_, mantissa_, saturate_> base;
  
  operator int ()                    = delete;
  operator unsigned int ()           = delete;
  operator long int ()               = delete;
  operator unsigned long int ()      = delete;
  operator long long int ()          = delete;
  operator unsigned long long int () = delete;

  explicit
  operator double() {
   return double((base)*this);
  }

  explicit constexpr unsigned_frac(typename base::type const & tmp_) :
   base(tmp_) {}

  explicit constexpr unsigned_frac(
   typename base::type const & characteristic__,
   typename base::type const & mantissa__
  ) :
   base(characteristic__, mantissa__) {}
  
 };
 
///////////////////////////////////////////////////////////////////////////////
// Signed fixed point numbers
///////////////////////////////////////////////////////////////////////////////
  
 template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_>
 class signed_frac : public frac_base<
  characteristic_,
  mantissa_,
  saturate_
  > {

 public:
  typedef frac_base<characteristic_, mantissa_, saturate_> base;
      
  operator int ()                    = delete;
  operator unsigned int ()           = delete;
  operator long int ()               = delete;
  operator unsigned long int ()      = delete;
  operator long long int ()          = delete;
  operator unsigned long long int () = delete;    

  explicit
  operator double() {
   return double((base)*this);
  }
  
  explicit constexpr
  signed_frac(typename base::type const & tmp_) :
   base(tmp_) {}

  // v should use smaller types and non-negative mantissa value  
  explicit constexpr
  signed_frac(
   typename base::type const & characteristic__,
   typename base::type const & mantissa__
  ) :
   base(characteristic__, mantissa__) {}
 };

//////////////////////////////////////////////////////////////////////////////
// Typedefs
//////////////////////////////////////////////////////////////////////////////
  
// Value types ///////////////////////////////////////////////////////////////

 typedef uint8_t                        q0n8_value_type;    
 typedef uint16_t                       q8n8_value_type;                       
 typedef uint16_t                       q0n16_value_type;                      
 typedef uint32_t                       q16n16_value_type;                     
 typedef uint32_t                       q0n32_value_type;                    

 typedef int8_t                         q0n7_value_type;        
 typedef int16_t                        q7n8_value_type;                      
 typedef int16_t                        q0n15_value_type;                      
 typedef int32_t                        q15n16_value_type;                     
 typedef int32_t                        q0n31_value_type;                      

 // used only as 'big_type's:
 typedef uint64_t                       q0n64_value_type;
 typedef int64_t                        q0n63_valuete_type;

// Overflow-able types ////////////////////////////////////////////////////////
  
 typedef unsigned_frac<  0,  8, false > q0n8;
 typedef unsigned_frac<  8,  8, false > q8n8;
 typedef unsigned_frac<  0, 16, false > q0n16;
 typedef unsigned_frac< 16, 16, false > q16n16;
 typedef unsigned_frac<  0, 32, false > q0n32;

 typedef unsigned_frac<  2, 14, false > q2n14;
 typedef unsigned_frac<  2, 30, false > q2n30;
  
 typedef signed_frac<    0,  7, false > q0n7;
 typedef signed_frac<    7,  8, false > q7n8;
 typedef signed_frac<    0, 15, false > q0n15;
 typedef signed_frac<   15, 16, false > q15n16;
 typedef signed_frac<    0, 31, false > q0n31;

// Saturating types ///////////////////////////////////////////////////////////
 
 typedef unsigned_frac<  0,  8, true  > sat_q0n8;
 typedef unsigned_frac<  8,  8, true  > sat_q8n8;
 typedef unsigned_frac<  0, 16, true  > sat_q0n16;
 typedef unsigned_frac< 16, 16, true  > sat_q16n16;  
 typedef unsigned_frac<  0, 32, true  > sat_q0n32;

 typedef unsigned_frac<  2, 14, true  > sat_q2n14;
 typedef unsigned_frac<  2, 30, true  > sat_q2n30;
  
 typedef signed_frac<    0,  7, true  > sat_q0n7;
 typedef signed_frac<    7,  8, true  > sat_q7n8;
 typedef signed_frac<    0, 15, true  > sat_q0n15;
 typedef signed_frac<   15, 16, true  > sat_q15n16;
 typedef signed_frac<    0, 31, true  > sat_q0n31;  

 
///////////////////////////////////////////////////////////////////////////////

} // namespace lamb

///////////////////////////////////////////////////////////////////////////////

#undef CHECK_OVERFLOW
  
#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */

