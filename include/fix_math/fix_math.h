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
//
// Multiply tests:
//
// L/R     u0,8   u0,16  u0,32  u8,8  u16,16  s0,7  s0,15  s0,31  s7,8  s15,16
// u0,8    Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u0,16   Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u0,32   Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u8,8    Yes    Yes    Yes    ?     ?       EXCL  EXCL   EXCL   EXCL  EXCL
// u16,16  Yes    Yes    Yes    ?     ?       EXCL  EXCL   EXCL   EXCL  EXCL
// s0,7    Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,15   Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,31   Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s7,8    Yes    Yes    Yes    ?     ?       Redo  Redo   Redo   EXCL  EXCL
// s15,16  Yes    Yes    Yes    ?     ?       Redo  Redo   Redo   EXCL  EXCL
//
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////

namespace lamb {

///////////////////////////////////////////////////////////////////////////////

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
 class type_if {
  
 };

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
  template <uint8_t char_, uint8_t mant_, bool sat_> class derived_template,
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
   >::type type;

  typedef
  typename type_if<
   SIGNED,
   typename signed_int<(SIZE << 1)>::type,
   typename unsigned_int<(SIZE << 1)>::type
   >::type big_type;

  typedef
  derived_template<CHARACTERISTIC, MANTISSA, (! SATURATE )>
  sat_cast_type;
  
  typedef
  derived_template<CHARACTERISTIC, MANTISSA, SATURATE>
  derived_type;

  typedef
  typename type_if<
   SIGNED,
   unsigned_frac<CHARACTERISTIC, MANTISSA, SATURATE>,
   signed_frac<CHARACTERISTIC, MANTISSA, SATURATE>
   >::type opposite_signedness_type;
  
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

  type bottom() const { // return smaller type?
   return val & mask();
  }
  
////////////////////////////////////////////////////////////////////////////////

  type top() const {    // return smaller type?
   if (CHARACTERISTIC == 0) {
    return 0;
   }
   else {
    return (val & (~mask())) >> MANTISSA;
   }
  }     
  
////////////////////////////////////////////////////////////////////////////////

  explicit constexpr
  frac_base(type const & tmp_) : val(tmp_), overflow(false) {}

////////////////////////////////////////////////////////////////////////////////

  CHECK_OVERFLOW;

////////////////////////////////////////////////////////////////////////////////
  
  float to_float() const {
   return val / (ONE * 1.0);
  }

////////////////////////////////////////////////////////////////////////////////

  sat_cast_type sat_cast () const {
   return sat_cat_type(val);
  }
  
///////////////////////////////////////////////////////////////////////////////

  static constexpr derived_type from_float(float const & tmp_) {
   int           divisor = int(tmp_);
   float         modulus = tmp_ - divisor;
   type          ipart   = ONE * divisor + int(ONE * modulus);
   
   return derived_type(ipart);
  }

////////////////////////////////////////////////////////////////////////////////
    
  template <bool saturate__> 
  bool
  operator == (
   derived_template<CHARACTERISTIC, MANTISSA, saturate__> const & other
  ) const {
   return val == other.val;
  }    

///////////////////////////////////////////////////////////////////////////////
  
  template <bool saturate__>
  operator
  derived_template<
   (CHARACTERISTIC << 1),
   (MANTISSA << 1),
   saturate__
   > () const {
   derived_template<(CHARACTERISTIC << 1), (MANTISSA << 1), saturate__> tmp(
    val << 1
   );

   return tmp;
  }

  template <bool saturate__>
  operator
  derived_template<
   (CHARACTERISTIC >> 1),
   (MANTISSA >> 1),
   saturate__
   > () const {
   derived_template<(CHARACTERISTIC >> 1), (MANTISSA >> 1), saturate__> tmp(
    val >> 1
   );

   return tmp;
  }


///////////////////////////////////////////////////////////////////////////////
    
  template <bool saturate__> 
  derived_type
  operator + (
   derived_template<CHARACTERISTIC,MANTISSA,saturate__> const & other
  ) const {
   type          old    = val;
   big_type      new_   = old + other.val;
   derived_type ret    = derived_type(new_);

   if (check_overflow('+', old, other.val, ret.val)) {
    overflow = true;
   }

   return ret;
  }    

  template <bool saturate__>
  derived_type &
  operator += (
   derived_template<CHARACTERISTIC,MANTISSA,saturate__> const & other
  ) {
   val = ((*this) + other).val;

   return *(static_cast<derived_type *>(this));
  }

  ///////////////////////////////////////////////////////////////////////////////
    
  template <uint8_t c, uint8_t m, bool s>
  derived_type
  operator - (
   derived_template<c,m,s> const & other
  ) const {
   type          old  = val;
   big_type      new_ = old - other.val;
   derived_type  ret  = derived_type(new_);

   if (check_overflow('-', old, other.val, ret.val)) {
    overflow = true;
   }

   return ret;
  }    

  template <uint8_t c, uint8_t m, bool s>
  derived_type &
  operator -= (
   derived_template<c,m,s> const & other
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

   typedef unsigned_frac<other_charac,other_mantissa, other_saturate>
    other_type;
   typedef typename other_type::big_type
    right_big_type;
   typedef typename unsigned_int<(sizeof(right_big_type))>::type
    pseudo_right_big_type;

   derived_type            ret(0);
   type                    old(val);

   if constexpr(sizeof(other_type) > sizeof(derived_type)) {
    pseudo_right_big_type tmp   =
     ((pseudo_right_big_type)val) * other.val;

    tmp                       >>= other.mantissa;     
    ret.val                     = (type)tmp;

    if (check_overflow('x', old, other.val, ret.val)) {
     overflow = true;
    }
   }
   else {
    big_type              tmp   = ((big_type)val) * other.val;
    tmp                       >>= other_mantissa;
    ret.val                     = (type)tmp;
 
    if (check_overflow('*', old, other.val, ret.val)) {
     overflow = true;
    }
   }
   
   return ret;
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
   
   typedef signed_frac<other_charac,other_mantissa, other_saturate>
    other_type;
   typedef typename other_type::big_type
    right_big_type;
   typedef typename unsigned_int<(sizeof(right_big_type))>::type
    pseudo_right_big_type;

   derived_type            ret(0);
   type                    old(val);

   if constexpr(sizeof(other_type) > sizeof(derived_type)) {
    pseudo_right_big_type tmp   =
     ((pseudo_right_big_type)val) * other.val;

    tmp                       >>= other.mantissa;     
    ret.val                     = (type)tmp;

    if (check_overflow('x', old, other.val, ret.val)) {
     overflow = true;
    }
   }
   else {
    big_type              tmp   = ((big_type)val) * other.val;
    tmp                       >>= other_mantissa;
    ret.val                     = (type)tmp;
 
    if (check_overflow('*', old, other.val, ret.val)) {
     overflow = true;
    }
   }
   
   return ret;
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
   derived_template<other_charac,other_mantissa,other_saturate> const & other
  ) const {
   typedef derived_template<other_charac,other_mantissa, other_saturate>
    other_type;
   typedef typename other_type::big_type
    right_big_type;
   typedef typename unsigned_int<(sizeof(right_big_type))>::type
    pseudo_right_big_type;

   derived_type          ret(0);
   type                   old(val);

   if constexpr(sizeof(other_type) > sizeof(derived_type)) {
    pseudo_right_big_type tmp   = ((pseudo_right_big_type)val) * other.val;
    ret.val                     = (type)(tmp >> other_mantissa);

    if (check_overflow('x', old, other.val, ret.val)) {
     overflow = true;
    }
   }
   else {    
    big_type              tmp   = ((big_type)val) << other_mantissa;
    tmp                        /= other.val;
    ret.val                     = (type)tmp;
  
    if (check_overflow('/', old, other.val, ret.val)) {
     overflow = true;
    }
   }
   
   return ret;
  }

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
  derived_type & 
  operator /= (
   derived_template<other_charac,other_mantissa, saturate__> const & other
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
  unsigned_frac,
  characteristic_,
  mantissa_,
  saturate_
  > {

 public:
  typedef frac_base<unsigned_frac, characteristic_, mantissa_, saturate_> base;
  
  operator int ()                    = delete;
  operator unsigned int ()           = delete;
  operator long int ()               = delete;
  operator unsigned long int ()      = delete;
  operator long long int ()          = delete;
  operator unsigned long long int () = delete;

  explicit constexpr unsigned_frac(typename base::type const & tmp_) :
   base(tmp_) {}

  explicit constexpr unsigned_frac(
   typename base::type const & characteristic__,
   typename base::type const & mantissa__
  ) :
   base((characteristic__ * base::ONE) + mantissa__) {}
  
 };
 
///////////////////////////////////////////////////////////////////////////////
// Signed fixed point numbers
///////////////////////////////////////////////////////////////////////////////
  
 template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_>
 class signed_frac : public frac_base<
  signed_frac,
  characteristic_,
  mantissa_,
  saturate_
  > {

 public:
  typedef frac_base<signed_frac, characteristic_, mantissa_, saturate_> base;
      
  operator int ()                    = delete;
  operator unsigned int ()           = delete;
  operator long int ()               = delete;
  operator unsigned long int ()      = delete;
  operator long long int ()          = delete;
  operator unsigned long long int () = delete;    

  explicit constexpr
  signed_frac(typename base::type const & tmp_) :
   base(tmp_) {}

  // v should use smaller types and non-negative mantissa value  
  explicit constexpr
  signed_frac(
   typename base::type const & characteristic__,
   typename base::type const & mantissa__
  ) :
   base((characteristic__ * base::ONE) + mantissa__) {}
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

