#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

#ifdef NO_ARDUINO
  #include <stdio.h>
  #include <stdlib.h>
  #include <iostream>
#endif

#ifndef LAMB_FP_NO_OVERFLOW_CHECKING
#define CHECK_OVERFLOW                                  \
  template <typename delta_t, typename new_t>           \
  static void check_overflow(                           \
    char    const & symbol,                             \
    type    const & old_val,                            \
    delta_t const & delta,                              \
    new_t   const & new_val,                            \
    type          & set                                 \
  ) {                                                   \
    bool over  = new_val > MAX;                         \
    bool under = new_val < MIN;                         \
                                                        \
    if (over || under) {                                \
      if (SATURATE) {                                   \
        set = MAX;                                      \
        printf("SAT %s:  ", over ? "HI" : "LO");        \
        cout << old_val;                                \
        printf(" %c ", symbol);                         \
        cout << delta;                                  \
        printf(" = ");                                  \
        cout << new_val << "\n";                        \
      }                                                 \
      else {                                            \
        printf("%sFLOW: ", over ? "OVER" : "UNDER");    \
        cout << old_val;                                \
        printf(" %c ", symbol);                         \
        cout << delta << " = " << new_val << "\n";      \
      }                                                 \
    }                                                   \
  }                                                     
#else
#define CHECK_OVERFLOW                                    \
  template <typename delta_t, typename new_t>             \
  static void check_overflow(                             \
    char    const & symbol,                               \
      type    const & old_val,                            \
      delta_t const & delta,                              \
      new_t   const & new_val,                            \
      type          & set                                 \
  ) {}                                                    
#endif

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
// s15,16  Redo   Redo   Redo   ?     ?       Redo  Redo   Redo   EXCL  EXCL

using namespace std;

namespace lamb {

// Advance declaration:

  template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_ = false>
  class signed_frac;
    
////////////////////////////////////////////////////////////////////////////////
// Unsigned fixed point numbers
////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_ = false>
  class unsigned_frac {
    
  public:
    static const bool    SATURATE       = saturate_;
    static const uint8_t CHARACTERISTIC = characteristic_;
    static const uint8_t MANTISSA       = mantissa_;
    static const uint8_t FX_SHIFT       = CHARACTERISTIC + MANTISSA;
    static const size_t  SIZE           = FX_SHIFT / 8;

    static_assert(((FX_SHIFT % 8) == 0), "bad bit count for this type");
    
    typedef typename unsigned_int<SIZE>::type         type;
    typedef typename unsigned_int<(SIZE << 1)>::type  big_type;

    static const type     ONE      = (
      (CHARACTERISTIC == 0) ? 
      ((((big_type)1) << MANTISSA) - 1) :
      (1 << MANTISSA)
    );
    
    static const type    MAX            = unsigned_int<SIZE>::MAX;
    static const type    MIN            = unsigned_int<SIZE>::MIN;
    
    type val;

////////////////////////////////////////////////////////////////////////////////

  private:
    CHECK_OVERFLOW;

////////////////////////////////////////////////////////////////////////////////

  public:
    template <bool saturate__>
    operator unsigned_frac<(CHARACTERISTIC << 1), (MANTISSA << 1), saturate__> () const {
      unsigned_frac<(CHARACTERISTIC << 1), (MANTISSA << 1), saturate__> tmp(val << 1);

      return tmp;
    }

    template <bool saturate__>
    operator unsigned_frac<(CHARACTERISTIC >> 1), (MANTISSA >> 1), saturate__> () const {
      unsigned_frac<(CHARACTERISTIC >> 1), (MANTISSA >> 1), saturate__> tmp(val >> 1);

      return tmp;
    }

    template <bool saturate__>
    operator signed_frac<CHARACTERISTIC,MANTISSA,saturate__> () const {
      unsigned_frac<CHARACTERISTIC,MANTISSA,saturate__> tmp(val >> 1);

      return tmp;
    }

////////////////////////////////////////////////////////////////////////////////

    explicit unsigned_frac(type const & val_) :
      val(val_) {}

////////////////////////////////////////////////////////////////////////////////
    
    template <bool saturate__> 
    unsigned_frac operator + (unsigned_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other ) {
      type     old  = val;
      big_type new_ = old + other.val;
      unsigned_frac r = unsigned_frac(new_);
      check_overflow('+', old, other.val, new_, r.val);
      return r;
    }    

    template <bool saturate__>
    unsigned_frac operator += (unsigned_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other) {
      val = ((*this) + other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////
    
    template <bool saturate__>
    unsigned_frac operator - (unsigned_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other ) {
      type     old  = val;
      big_type new_ = old - other.val;
      unsigned_frac r = unsigned_frac(new_);
      check_overflow('-', old, other.val, new_, r.val);
      return r;
    }    

    template <bool saturate__>
    unsigned_frac operator -= (unsigned_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other) {
      val = ((*this) - other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
    unsigned_frac operator * (unsigned_frac<other_charac,other_mantissa,other_saturate> const & other ) {
      static_assert(0 == other_charac, "Reverse operand order!");

      typedef unsigned_frac<other_charac,other_mantissa, other_saturate> other_type;
      typedef typename other_type::big_type right_big_type;
      typedef typename unsigned_int<(sizeof(right_big_type))>::type pseudo_right_big_type;

      unsigned_frac r(0);
      type          old(val);
      
      if (sizeof(other_type) > sizeof(unsigned_frac)) {
        pseudo_right_big_type tmp = ((pseudo_right_big_type)val) * other.val;
        static const uint8_t shift = other_type::FX_SHIFT;
        tmp >>= shift;
        r.val = (type)tmp;
        check_overflow('*', old, other.val, tmp, r.val);
      }
      else {
        printf("\n");
        printf("sizeof(type) = %lu\n", sizeof(type));
        printf("sizeof(big_type) = %lu\n", sizeof(big_type));
        printf("me.val = %d\n", val);
        printf("other.val = %d\n", other.val);
        printf("other.charac = %d\n", other_charac);
        printf("other.mantissa = %d\n", other_mantissa);        
        big_type      tmp = ((big_type)val) * other.val;        
        printf("tmp2 = %u\n", tmp);
        static const uint8_t shift =  unsigned_frac<other_charac, other_mantissa>::FX_SHIFT;      
        tmp >>= shift;
        r.val = (type)tmp;
        printf("shift = %d\n", shift);
        printf("r.val = %d\n", r.val);
        check_overflow('*', old, other.val, tmp, r.val);        
        return r;
      }
    }

    template <uint8_t other_charac, uint8_t other_mantissa, bool saturate__>
    unsigned_frac operator *= (unsigned_frac<other_charac,other_mantissa, saturate__> const & other) {
      val = ((*this) * other).val;
      return *this;
    }

 ////////////////////////////////////////////////////////////////////////////////

    template <bool saturate__>
    unsigned_frac operator / (unsigned_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other ) {
      unsigned_frac<0,8> r = unsigned_frac<0,8>(val / other.val);
      return r;
    }        

    template <bool saturate__>
    unsigned_frac operator /= (unsigned_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other) {
      val = ((*this) / other).val;
      return *this;
    }
  };

////////////////////////////////////////////////////////////////////////////////
// Signed fixed point numbers
////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t characteristic_, uint8_t mantissa_, bool saturate_>
  class signed_frac {

  public:
    static const uint8_t CHARACTERISTIC = characteristic_;
    static const uint8_t MANTISSA       = mantissa_;
    static const bool    SATURATE       = saturate_;
    static const uint8_t FX_SHIFT       = CHARACTERISTIC + MANTISSA;
    static const size_t  SIZE           = (FX_SHIFT + 1) / 8;

    static_assert((((FX_SHIFT + 1) % 8) == 0), "bad bit count for this type");

    typedef typename signed_int<SIZE>::type         type;
    typedef typename signed_int<(SIZE << 1)>::type  big_type;
    
    static const type     ONE      = (
      (CHARACTERISTIC == 0) ? 
      ((((big_type)1) << MANTISSA) - 1) :
      (1 << MANTISSA)
    );
    
    static const type     MAX      = signed_int<(SIZE)>::MAX;
    static const type     MIN      = signed_int<(SIZE)>::MIN;
        
    type val;

////////////////////////////////////////////////////////////////////////////////

  private:
    CHECK_OVERFLOW;

////////////////////////////////////////////////////////////////////////////////

  public:
    template <bool saturate__>
    operator signed_frac<(CHARACTERISTIC << 1), (MANTISSA << 1), saturate__> () const {
      signed_frac<(CHARACTERISTIC << 1), (MANTISSA << 1), saturate__> tmp(val << 1);

      return tmp;
    }

    template <bool saturate__>
    operator signed_frac<(CHARACTERISTIC >> 1), (MANTISSA >> 1), saturate__> () const {
      signed_frac<(CHARACTERISTIC >> 1), (MANTISSA >> 1), saturate__> tmp(val >> 1);
      return tmp;
    }

////////////////////////////////////////////////////////////////////////////////
    
    explicit signed_frac(type const & val_) :
      val(val_) {}

////////////////////////////////////////////////////////////////////////////////
    
    template <bool saturate__>
    signed_frac operator + (signed_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other ) {
      type     old   = val;
      big_type new_ = val + other.val;
      signed_frac r = signed_frac(new_);
      check_overflow('+', old, other.val, new_, r.val);
      return r;
    }

    template <bool saturate__>
    signed_frac operator += (signed_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other) {
      val = ((*this) + other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////
    
    template <bool saturate__>
    signed_frac operator - (signed_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other ) {
      type     old   = val;
      big_type new_  = val - other.val;
      signed_frac r = signed_frac(new_);
      check_overflow('-', old, other.val, new_, r.val);
      return r;
    }

    template <bool saturate__>
    signed_frac operator -= (signed_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other) {
      val = ((*this) - other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

  public:      
    template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
    signed_frac operator * (unsigned_frac<other_charac,other_mantissa,other_saturate> const & other ) {
      static_assert(0 == other_charac, "Reverse operand order!");

      typedef unsigned_frac<other_charac,other_mantissa, other_saturate> other_type;
      typedef typename other_type::big_type   right_big_type;
      typedef typename unsigned_int<(sizeof(right_big_type))>::type pseudo_right_big_type;

      signed_frac r(0);
      type        old(val);

      if (sizeof(other_type) > sizeof(signed_frac)) {
        pseudo_right_big_type tmp = ((pseudo_right_big_type)val) * other.val;        
        uint8_t shift = other_type::FX_SHIFT;
        printf("shift: %d\n", shift);
        tmp >>= shift;
        printf("tmp2: %d\n", tmp);        
        r.val = (type)tmp;
        printf("SHIFT is %d.\n", shift);
        printf("r.val is %d.\n", r.val);
        check_overflow('*', old, other.val, tmp, r.val);
      }
      else {
        big_type tmp = ((big_type)val) * other.val;      
        uint8_t   shift = other_type::FX_SHIFT;
        if (val < 0) {
          shift --;
        }        
        tmp >>= shift;        
        r.val = (type)tmp;
        printf("\nSHIFT is %d.\n", shift);
        printf("r.val is %d.\n", r.val);            
        check_overflow('*', old, other.val, tmp, r.val);
      }     
      return r;
    }    

    template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
    signed_frac operator *= (unsigned_frac<other_charac,other_mantissa,other_saturate> const & other) {
      val = ((*this) * other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
    signed_frac operator * (signed_frac<other_charac,other_mantissa,other_saturate> const & other ) {
      static_assert(0 == other_charac, "Reverse operand order!");

      typedef signed_frac<other_charac,other_mantissa,other_saturate>     other_type;
      typedef typename other_type::big_type right_big_type;
      typedef typename signed_int<(sizeof(right_big_type))>::type         pseudo_right_big_type;

      signed_frac r(0);
      type        old(val);

      if (sizeof(other_type) > sizeof(signed_frac)) {
        pseudo_right_big_type tmp = ((pseudo_right_big_type)val) * other.val;        
        tmp >>= other_type::FX_SHIFT - 1;
        r.val = (type)tmp;
        printf("SHIFT is %d.\n", other_type::FX_SHIFT - 1);         
        printf("r.val is %d.\n", r.val);
        check_overflow('*', old, other.val, tmp, r.val);
      }
      else {
        big_type tmp = ((big_type)val) * other.val;
        tmp >>= other_type::FX_SHIFT - 1;     
        r.val = (type)tmp;        
        printf("SHIFT is %d.\n", other_type::FX_SHIFT - 1);
        printf("r.val is %d.\n", r.val);        
        check_overflow('*', old, other.val, tmp, r.val);
      }
      return r;
    }    

    template <uint8_t other_charac, uint8_t other_mantissa, bool other_saturate>
    signed_frac operator *= (signed_frac<other_charac,other_mantissa,other_saturate> const & other) {
      val = ((*this) * other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    template <bool saturate__>
    signed_frac operator / (signed_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other ) {
      signed_frac r = signed_frac(val / other.val);
      return r;
    }        

    template <bool saturate__>
    signed_frac operator /= (signed_frac<CHARACTERISTIC,MANTISSA,saturate__> const & other) {
      val = ((*this) / other).val;
      return *this;
    }
  };

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////
  
// Value types ////////////////////////////////////////////////////////////////

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

  typedef uint64_t                       q0n64_value_type; // used only as a 'big_type'.
  typedef int64_t                        q0n63_value_type; // used only as a 'big_type'.

// Overflow-able types /////////////////////////////////////////////////////////
  
  typedef unsigned_frac<  0,  8, false > q0n8;
  typedef unsigned_frac<  8,  8, false > q8n8;
  typedef unsigned_frac<  0, 16, false > q0n16;
  typedef unsigned_frac< 16, 16, false > q16n16;
  typedef unsigned_frac<  0, 32, false > q0n32;

  typedef signed_frac<    0,  7, false > q0n7;
  typedef signed_frac<    7,  8, false > q7n8;
  typedef signed_frac<    0, 15, false > q0n15;
  typedef signed_frac<   15, 16, false > q15n16;
  typedef signed_frac<    0, 31, false > q0n31;

// Saturating types ////////////////////////////////////////////////////////////
  
  typedef unsigned_frac<  0,  8, true  > sat_q0n8;
  typedef unsigned_frac<  8,  8, true  > sat_q8n8;
  typedef unsigned_frac<  0, 16, true  > sat_q0n16;
  typedef unsigned_frac< 16, 16, true  > sat_q16n16;  
  typedef unsigned_frac<  0, 32, true  > sat_q0n32;

  typedef signed_frac<    0,  7, true  > sat_q0n7;
  typedef signed_frac<    7,  8, true  > sat_q7n8;
  typedef signed_frac<    0, 15, true  > sat_q0n15;
  typedef signed_frac<   15, 16, true  > sat_q15n16;
  typedef signed_frac<    0, 31, true  > sat_q0n31;  
  
////////////////////////////////////////////////////////////////////////////////

} // namespace lamb

////////////////////////////////////////////////////////////////////////////////

#undef CHECK_OVERFLOW
  
#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
