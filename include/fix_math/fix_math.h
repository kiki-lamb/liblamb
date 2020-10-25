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
   if (SATURATE) {                                        \
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
 class typedef_if {
  
 };

 template <typename left, typename right>
 class typedef_if<true, left, right> {
 public:
  typedef left type;
 };

 template <typename left, typename right>
 class typedef_if<false, left, right> {
 public:
  typedef right type;
 };
 
////////////////////////////////////////////////////////////////////////////////
// Base
////////////////////////////////////////////////////////////////////////////////

 template <
  uint8_t characteristic_,
  uint8_t mantissa_,
  bool saturate_ = false
  >
 class frac_base {
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

  typedef typename typedef_if<
   SIGNED,
   typename signed_int<SIZE>::type,
   typename unsigned_int<SIZE>::type
   >::type type;

  typedef typename typedef_if<
   SIGNED,
   typename signed_int<(SIZE << 1)>::type,
   typename unsigned_int<(SIZE << 1)>::type
   >::type big_type;

  static constexpr type    ONE = (
   (CHARACTERISTIC == 0) ? 
   ((((big_type)1) << MANTISSA) - 1) :
   (1 << MANTISSA)
  );
  
  static constexpr type    MAX = (
   SIGNED ?
   signed_int<SIZE>::MAX :
   unsigned_int<SIZE>::MAX
  );
   
  static constexpr type    MIN = (
   SIGNED?
   signed_int<SIZE>::MIN :
   unsigned_int<SIZE>::MIN
  );
  
  static constexpr type mask() {
   type m = 0;
   
   for (uint8_t ix = 0; ix < MANTISSA; ix++) {
    m |= 1 << ix;
   }
   
   return m;
  }

  CHECK_OVERFLOW;
 };
 
//////////////////////////////////////////////////////////////////////////////// 
// Advance declaration:
////////////////////////////////////////////////////////////////////////////////

 template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_ = false>
 class signed_frac;
    
///////////////////////////////////////////////////////////////////////////////
// Unsigned fixed point numbers
///////////////////////////////////////////////////////////////////////////////
  
 template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_ = false>
 class unsigned_frac : public frac_base<characteristic_, mantissa_, saturate_> {

 public:
  typedef frac_base<characteristic_, mantissa_, saturate_> base;
  typedef typename base::type                              type;
  typedef typename base::big_type                          big_type;
  
  type bottom() const { // return smaller type?
   return val & base::mask();
  }
  
  type top() const {    // return smaller type?
   if (base::CHARACTERISTIC == 0) {
    return 0;
   }
   else {
    return (val & (~base::mask())) >> base::MANTISSA;
   }
  }     
  
  type val;
  
  mutable bool overflow;
  
///////////////////////////////////////////////////////////////////////////////
  
  unsigned_frac<base::CHARACTERISTIC, base::MANTISSA, ( ! base::SATURATE )> sat_cast () const {
   return unsigned_frac<base::CHARACTERISTIC, base::MANTISSA, ( ! base::SATURATE)>(val);
  }
  
///////////////////////////////////////////////////////////////////////////////

 public:
  template <bool saturate__>
  operator
  unsigned_frac<(base::CHARACTERISTIC << 1), (base::MANTISSA << 1), saturate__> () const {
   unsigned_frac<(base::CHARACTERISTIC << 1), (base::MANTISSA << 1), saturate__> tmp(
    val << 1
   );

   return tmp;
  }

  template <bool saturate__>
  operator
  unsigned_frac<(base::CHARACTERISTIC >> 1), (base::MANTISSA >> 1), saturate__> () const {
   unsigned_frac<(base::CHARACTERISTIC >> 1), (base::MANTISSA >> 1), saturate__> tmp(
    val >> 1
   );

   return tmp;
  }

  template <bool saturate__>
  operator
  signed_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> () const {
   unsigned_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> tmp(
    val >> 1
   );
   
   return tmp;
  }

///////////////////////////////////////////////////////////////////////////////

  // v This can overflow, especially if val > 1.0 and base::CHARACTERISTIC == 0;
  
  static constexpr unsigned_frac from_float(float const & val_) {
   int           divisor = int(val_);
   float         modulus = val_ - divisor;
   type          ipart   = base::ONE * divisor + int(base::ONE * modulus);
   
   return unsigned_frac(ipart);
  }

  float to_float() const {
   return val / (base::ONE * 1.0);
  }

////////////////////////////////////////////////////////////////////////////////
  
  explicit constexpr unsigned_frac(type const & val_ = 0) :
   val(val_)
   , overflow(false)
   {}

  explicit constexpr unsigned_frac(
   type const & characteristic__,
   type const & mantissa__
  ) : val((characteristic__ * base::ONE) + mantissa__), overflow(false)
   {}

//////////////////////////////////////////////////////////////////////////////
    
  template <bool saturate__> 
  bool
  operator == (
   unsigned_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
  ) const {
   return val == other.val;
  }    

///////////////////////////////////////////////////////////////////////////////
    
  template <bool saturate__> 
  unsigned_frac
  operator + (
   unsigned_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
  ) const {
   type          old    = val;
   big_type      new_   = old + other.val;
   unsigned_frac ret    = unsigned_frac(new_);

   if (base::check_overflow('+', old, other.val, ret.val)) {
    overflow = true;
   }

   return ret;
  }    

  template <bool saturate__>
  unsigned_frac &
  operator += (
   unsigned_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
  ) {
   val = ((*this) + other).val;

   return *this;
  }

///////////////////////////////////////////////////////////////////////////////
    
  template <uint8_t c, uint8_t m, bool s>
  unsigned_frac
  operator - (
   unsigned_frac<c,m,s> const & other
  ) const {
   type          old    = val;
   big_type      new_   = old - other.val;
   unsigned_frac ret    = unsigned_frac(new_);

   if (base::check_overflow('-', old, other.val, ret.val)) {
    overflow = true;
   }

   return ret;
  }    

  template <uint8_t c, uint8_t m, bool s>
  unsigned_frac &
  operator -= (
   unsigned_frac<c,m,s> const & other
  ) {
   unsigned_frac tmp = (*this) - other;
  
   val = tmp.val;

   return *this;
  }

///////////////////////////////////////////////////////////////////////////////

  template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
  unsigned_frac
  operator * (
   unsigned_frac<other_charac,other_mantissa,other_saturate> const & other
  ) const {
   typedef unsigned_frac<other_charac,other_mantissa, other_saturate>
    other_type;
   typedef typename other_type::big_type
    right_big_type;
   typedef typename unsigned_int<(sizeof(right_big_type))>::type
    pseudo_right_big_type;

   unsigned_frac          ret(0);
   type                   old(val);

   if constexpr(sizeof(other_type) > sizeof(unsigned_frac)) {
     static const uint8_t  shift = other_mantissa;
    
     pseudo_right_big_type tmp   = ((pseudo_right_big_type)val) * other.val;
     ret.val                     = (type)(tmp >> shift);

     if (base::check_overflow('x', old, other.val, ret.val)) {
      overflow = true;
     }
    }
    else {
     static const uint8_t  shift = other_mantissa;

     big_type              tmp   = ((big_type)val) * other.val;

     ret.val                     = (type)(tmp >> shift);
 
     if (base::check_overflow('*', old, other.val, ret.val)) {
      overflow = true;
     }
    }
   
    return ret;
   }
  

  template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
    unsigned_frac & 
    operator *= (
     unsigned_frac<other_charac,other_mantissa, saturate__> const & other
    ) {
    val = ((*this) * other).val;

    return *this;
   }

///////////////////////////////////////////////////////////////////////////////

   template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
    unsigned_frac
    operator / (
     unsigned_frac<other_charac,other_mantissa,other_saturate> const & other
    ) const {
    typedef unsigned_frac<other_charac,other_mantissa, other_saturate>
     other_type;
    typedef typename other_type::big_type
     right_big_type;
    typedef typename unsigned_int<(sizeof(right_big_type))>::type
     pseudo_right_big_type;

    unsigned_frac          ret(0);
    type                   old(val);

    if constexpr(sizeof(other_type) > sizeof(unsigned_frac)) {
      static const uint8_t  shift = other_mantissa;
    
      pseudo_right_big_type tmp   = ((pseudo_right_big_type)val) * other.val;
      ret.val                     = (type)(tmp >> shift);

      if (base::check_overflow('x', old, other.val, ret.val)) {
       overflow = true;
      }
     }
     else {    
      static const uint8_t  shift = other_mantissa;
      big_type              tmp   = ((big_type)val) << shift;
      tmp                        /= other.val;
      ret.val                     = (type)tmp;
  
      if (base::check_overflow('/', old, other.val, ret.val)) {
       overflow = true;
      }
     }
   
     return ret;
    }

    template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
     unsigned_frac & 
     operator /= (
      unsigned_frac<other_charac,other_mantissa, saturate__> const & other
     ) {
     val = ((*this) / other).val;

     return *this;
    }
   };
  
///////////////////////////////////////////////////////////////////////////////
// Signed fixed point numbers
///////////////////////////////////////////////////////////////////////////////
  
   template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_>
    class signed_frac : public frac_base<characteristic_, mantissa_, saturate_> {

   public:
    typedef frac_base<characteristic_, mantissa_, saturate_> base;
    typedef typename base::type                              type;
    typedef typename base::big_type                          big_type;  
    
    type bottom() const { // return smaller type?
     return val & base::mask();
    }

    type top() const {    // return smaller type?
     return (val & (~base::mask())) >> base::MANTISSA;
    }     
  
    type val;

    mutable bool overflow;

////////////////////////////////////////////////////////////////////////////////
  
    signed_frac<base::CHARACTERISTIC, base::MANTISSA, ( ! base::SATURATE )> sat_cast () const {
     return signed_frac<base::CHARACTERISTIC, base::MANTISSA, ( ! base::SATURATE)>(val);
    }
  
///////////////////////////////////////////////////////////////////////////////

    operator unsigned int () = delete;
    operator int ()          = delete;

///////////////////////////////////////////////////////////////////////////////

   public:
    template <bool saturate__>
    operator
    signed_frac<(
     base::CHARACTERISTIC << 1), (base::MANTISSA << 1), saturate__> () const {
     signed_frac<(base::CHARACTERISTIC << 1), (base::MANTISSA << 1), saturate__> tmp(
      val << 1
     );
   
     return tmp;
    }
   
    template <bool saturate__>
    operator
    signed_frac<(base::CHARACTERISTIC >> 1), (base::MANTISSA >> 1), saturate__> () const {
     signed_frac<(base::CHARACTERISTIC >> 1), (base::MANTISSA >> 1), saturate__> tmp(
      val >> 1
     );
    
     return tmp;
    }

///////////////////////////////////////////////////////////////////////////////

    // v This can overflow, especially if val > 1.0 and base::CHARACTERISTIC == 0;
    //   Not yet well tested.
  
    static constexpr signed_frac from_float(float val_) {
     bool          neg     = val_ < 0;
     int           divisor = int(val_);
     float         modulus = val_ - divisor;
     type          ipart   = base::ONE * divisor + int(base::ONE * modulus);
   
     return signed_frac(ipart);
    }

    float to_float() const {
//   printf("%lld ", val);
     return val / (base::ONE * 1.0);
    }

    explicit constexpr signed_frac(type const & val_) :
     val(val_), overflow(false)
     {}

    // v should use smaller types.
  
    explicit constexpr signed_frac(type const & characteristic__, type const & mantissa__) :
     val((characteristic__ * base::ONE) + mantissa__), overflow(false)
     {}
  
///////////////////////////////////////////////////////////////////////////////
    
    template <bool saturate__> 
    bool
    operator == (
     signed_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
    ) const {
     return val == other.val;
    }    

///////////////////////////////////////////////////////////////////////////////
    
    template <bool saturate__>
    signed_frac
    operator + (
     signed_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
    ) const {
     type        old  = val;
     big_type    new_ = val + other.val;
     signed_frac ret  = signed_frac(new_);

     if (base::check_overflow('+', old, other.val, ret.val)) {
      overflow = true;
     }

     return ret;
    }

    template <bool saturate__>
    signed_frac const &
    operator += (
     signed_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
    ) {
     val = ((*this) + other).val;

     return *this;
    }

    template <bool saturate__>
    signed_frac
    operator - (
     signed_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
    ) const {
     type        old   = val;
     big_type    new_  = val - other.val;
     signed_frac ret   = signed_frac(new_);

     if (base::check_overflow('-', old, other.val, ret.val)) {
      overflow = true;
     }

     return ret;
    }

    template <bool saturate__>
    signed_frac &
    operator -= (
     signed_frac<base::CHARACTERISTIC,base::MANTISSA,saturate__> const & other
    ) {
     val = ((*this) - other).val;

     return *this;
    }

   public:      
    template <uint8_t other_charac,uint8_t other_mantissa, bool other_saturate>
    signed_frac
    operator * (
     unsigned_frac<other_charac,other_mantissa,other_saturate> const & other
    ) const {

     typedef unsigned_frac<other_charac,other_mantissa, other_saturate>
      other_type;
     typedef typename other_type::big_type
      right_big_type;
     typedef typename unsigned_int<(sizeof(right_big_type))>::type
      pseudo_right_big_type;

     signed_frac ret(0);
     type        old(val);

     if constexpr(sizeof(other_type) > sizeof(signed_frac)) {
       pseudo_right_big_type tmp     =
        ((pseudo_right_big_type)val) * other.val;        
       static const uint8_t  shift   = other_type::base::MANTISSA;
       tmp                         >>= shift;
       ret.val                       = (type)tmp;

       if (base::check_overflow('*', old, other.val, ret.val)) {
        overflow = true;
       }
      }
      else {
       big_type              tmp     = ((big_type)val) * other.val;      
       uint8_t               shift   = other_type::base::MANTISSA;
       tmp                         >>= shift;
       ret.val                       = (type)tmp;

       if (base::check_overflow('*', old, other.val, ret.val)) {
        overflow = true;
       }
      }     

      return ret;
     }    

     template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
      signed_frac &
      operator *= (
       unsigned_frac<other_charac,other_mantissa,other_saturate> const & other
      ) {
      val = ((*this) * other).val;

      return *this;
     }

///////////////////////////////////////////////////////////////////////////////

     template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
      signed_frac
      operator * (
       signed_frac<other_charac,other_mantissa,other_saturate> const & other
      ) const {
      //static_assert(0 == other_charac, "Reverse operand order!");

      typedef signed_frac<other_charac,other_mantissa,other_saturate>
       other_type;
      typedef typename other_type::big_type
       right_big_type;
      typedef typename signed_int<(sizeof(right_big_type))>::type
       pseudo_right_big_type;

      signed_frac r(0);
      type        old(val);
   
      if constexpr(sizeof(other_type) > sizeof(signed_frac)) {
       type              tmp   =
        ((pseudo_right_big_type)val) *
        other.val >>
        other_type::base::MANTISSA;
      
        if (base::check_overflow('*', old, other.val, r.val)) {
         overflow = true;
        }

        return r;
       }
       else {
        type              tmp   =
         ((big_type)val) *
         other.val >>
         other_type::base::MANTISSA;;
      
        if (base::check_overflow('*', old, other.val, r.val)) {
         overflow = true;
        }

        return signed_frac(tmp);
       }
      }    

      template <uint8_t other_charac,uint8_t other_mantissa, bool other_saturate>
       signed_frac &
       operator *= (
        signed_frac<other_charac,other_mantissa,other_saturate> const & other
       ) {
       val = ((*this) * other).val;
   
       return *this;
      }

///////////////////////////////////////////////////////////////////////////////

      template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
       signed_frac
       operator / (
        signed_frac<other_charac,other_mantissa,other_saturate> const & other
       ) const {
       typedef signed_frac<other_charac,other_mantissa, other_saturate>
        other_type;
       typedef typename other_type::big_type
        right_big_type;
       typedef typename signed_int<(sizeof(right_big_type))>::type
        pseudo_right_big_type;

       signed_frac          ret(0);
       type                   old(val);

       if constexpr(sizeof(other_type) > sizeof(signed_frac)) {
         static const uint8_t  shift = other_mantissa;
         pseudo_right_big_type tmp   = ((pseudo_right_big_type)val) * other.val;
         ret.val                     = (type)(tmp >> shift);

         if (base::check_overflow('x', old, other.val, ret.val)) {
          overflow = true;
         }
        }
        else {    
         static const uint8_t  shift = other_mantissa;
         big_type              tmp   = ((big_type)val) << shift;
         tmp                        /= other.val;
         ret.val                     = (type)tmp;

         if (base::check_overflow('/', old, other.val, ret.val)) {
          overflow = true;
         }
        }
   
        return ret;
       }

       template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
        signed_frac & 
        operator /= (
         signed_frac<other_charac,other_mantissa, saturate__> const & other
        ) {
        val = ((*this) / other).val;

        return *this;
       }
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

