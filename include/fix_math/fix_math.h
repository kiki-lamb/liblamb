#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

#ifdef NO_ARDUINO
  #include <stdio.h>
  #include <stdlib.h>
  #include <iostream>
#endif

using namespace std;

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// Fixed point types 
////////////////////////////////////////////////////////////////////////////////

// 8 bits //////////////////////////////////////////////////////////////////////

  typedef uint8_t  q0n8_t;                        

  typedef int8_t   q0n7_t;                        
  
// 16 bits /////////////////////////////////////////////////////////////////////

  typedef uint16_t  q0n16_t;                      

  typedef uint16_t  q8n8_t;                       

  typedef int16_t   q0n15_t;                      

  typedef int16_t   q7n8_t;                        

// 32 bits /////////////////////////////////////////////////////////////////////

  typedef uint32_t  q0n32_t;                    

  typedef uint32_t  q16n16_t;                     

  typedef int32_t   q0n31_t;                      

  typedef int32_t   q15n16_t;                     

// 64 bits /////////////////////////////////////////////////////////////////////

// these are used only as the 'big_type' for some operations.

  typedef uint64_t q0n64_t;

  typedef int64_t q0n63_t;
  
////////////////////////////////////////////////////////////////////////////////
// Fixed type helpers
////////////////////////////////////////////////////////////////////////////////
  
// Unsigned
  
  template <uint8_t characteristic_, uint8_t mantissa_>
  class unsigned_frac {
    static_assert(((mantissa_ % 8) == 0), "bad bit count in mantissa");

  public:
    static const uint8_t characteristic = characteristic_;
    static const uint8_t mantissa = mantissa_;
    
    typedef typename unsigned_int<(mantissa / 8)>::type  type;
    typedef typename unsigned_int<((mantissa / 8) << 1)>::type big_type;
    static const type    ONE      = unsigned_int<((mantissa / 8))>::MAX;
    static const type    MAX      = unsigned_int<((mantissa / 8))>::MAX;
    static const type    MIN      = unsigned_int<((mantissa / 8))>::MIN;
    static const uint8_t FX_SHIFT = mantissa;
    
    type val;

    explicit unsigned_frac(type const & val_) :
      val(val_) {}

    unsigned_frac operator + (unsigned_frac const & other ) {
      unsigned_frac r = unsigned_frac(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
#else
        r.val = ONE;
        printf("SAT HI:  %u + %u = %u\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    unsigned_frac operator += (unsigned_frac const & other) {
      val = ((*this) + other).val;
      return *this;
    }

    unsigned_frac operator - (unsigned_frac const & other ) {
      unsigned_frac<0,8> r = unsigned_frac<0,8>(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
        printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
#else
        r.val = 0;
        printf("SAT LO: %u - %u = %u\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    unsigned_frac operator -= (unsigned_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    template <uint8_t other_charac, uint8_t other_mantissa>
    unsigned_frac operator * (unsigned_frac<other_charac,other_mantissa> const & other ) {
      static_assert(0 == other_charac, "Reverse operand order!");

      typedef typename unsigned_frac<other_charac,other_mantissa>::big_type right_big_type;
      typedef typename unsigned_int<(sizeof(right_big_type))>::type pseudo_right_big_type;

      unsigned_frac r(0);

      if ( sizeof(unsigned_frac<other_charac,other_mantissa>) > sizeof(unsigned_frac) ) {
        pseudo_right_big_type tmp = ((pseudo_right_big_type)val) * other.val;

        static const uint8_t shift = unsigned_frac<other_charac,other_mantissa>::FX_SHIFT;

        tmp >>= shift;

        r.val = (type)tmp;

        if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
          printf("OVERFLOW: %d * %d = %hu\n", val, other.val, tmp);
          fflush(stdout);
#else
          r.val = MAX;
          printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
        }
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
        
        printf("tmp2 = %llu\n", tmp);

        static const uint8_t shift =  unsigned_frac<other_charac, other_mantissa>::FX_SHIFT;
      
        tmp >>= shift;

        r.val = (type)tmp;

        printf("shift = %d\n", shift);

        printf("r.val = %d\n", r.val);
      
        if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
          printf("OVERFLOW: %d * %d = %llu\n", val, other.val, tmp);
          fflush(stdout);
#else
          r.val = MAX;
          printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
        }
        
        return r;
      }
    }

    template <uint8_t other_charac, uint8_t other_mantissa>
    unsigned_frac operator *= (unsigned_frac<other_charac,other_mantissa> const & other) {
      val = ((*this) * other).val;
      return *this;
    }

 ////////////////////////////////////////////////////////////////////////////////
    
    unsigned_frac operator / (unsigned_frac const & other ) {
      unsigned_frac<0,8> r = unsigned_frac<0,8>(val / other.val);
      return r;
    }        
    unsigned_frac operator /= (unsigned_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }

  };

////////////////////////////////////////////////////////////////////////////////

// Signed
  
  template <uint8_t characteristic_, uint8_t mantissa_>
  class signed_frac {
    static_assert((((mantissa_ + 1) % 8) == 0), "bad bit count in mantissa");

  public:
    static const uint8_t characteristic = characteristic_;
    static const uint8_t mantissa = mantissa_;
    
    typedef typename signed_int<((characteristic+mantissa+1) >> 3)>::type  type;
    typedef typename signed_int<(sizeof(type) << 1)>::type big_type;
    
    static const type    ONE      = signed_int<(sizeof(type))>::MAX;
    static const type    MAX      = signed_int<(sizeof(type))>::MAX;
    static const type    MIN      = signed_int<(sizeof(type))>::MIN;
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit signed_frac(type const & val_) :
      val(val_) {}

    signed_frac operator + (signed_frac const & other ) {
      signed_frac r = signed_frac(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d + %d = %d\n", val, other.val, r.val);
#else
        r.val = MAX;
        printf("SAT HI:  %d + %d = %d\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    signed_frac operator += (signed_frac const & other) {
      val = ((*this) + other).val;
      return *this;
    }

    signed_frac operator - (signed_frac const & other ) {
      signed_frac r = signed_frac(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
        printf("UNDERFLOW: %d - %d = %d\n", val, other.val, r.val);
#else
        r.val = 0;
        printf("SAT LO: %d - %d = %d\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    signed_frac operator -= (signed_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    template <uint8_t other_charac, uint8_t other_mantissa>
    signed_frac operator * (unsigned_frac<other_charac,other_mantissa> const & other ) {
      static_assert(0 == other_charac, "Reverse operand order!");

      typedef typename unsigned_frac<other_charac,other_mantissa>::big_type   right_big_type;
      typedef typename unsigned_int<(sizeof(right_big_type))>::type pseudo_right_big_type;

      signed_frac r(0);
      
      if ( sizeof(unsigned_frac<other_charac,other_mantissa>) > sizeof(signed_frac) ) {
        pseudo_right_big_type tmp = ((pseudo_right_big_type)val) * other.val;
        
        printf("preTMP0 is  %u.\n", tmp);
        
        uint8_t shift = unsigned_frac<other_charac,other_mantissa>::FX_SHIFT;

        // if (val < 0) {
        //   shift --;
        // }
        
        printf("shift: %d\n", shift);

        tmp >>= shift;

        printf("tmp2: %d\n", tmp);
        
        r.val = (type)tmp;

        printf("SHIFT is %d.\n", shift);
        printf("r.val is %d.\n", r.val);
            
        if (r.val > MAX) {
#ifndef LAMB_FP_SATURATE
          printf("OVERFLOW: %d * ", val);   
          cout << other.val << " = " << r.val << "\n";
          fflush(stdout);
#else
          r.val = MAX;
          printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
        }        
      }
      else {
        big_type tmp = ((big_type)val) * other.val;
      
 //       printf("preTMP1   is %hd.\n", tmp);

        uint8_t shift = unsigned_frac<other_charac,other_mantissa>::FX_SHIFT;

        if (val < 0) {
          shift --;
        }
        
        tmp >>= shift;
        
        r.val = (type)tmp;

//      printf("\nSHIFT is %d.\n", shift);
//      printf("r.val is %d.\n", r.val);
            
        if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
          printf("OVERFLOW: %d * %d = %hd\n", val, other.val, tmp);
          fflush(stdout);
#else
          r.val = MAX;
          printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
        }        
      }
     
      return r;
    }    

    template <uint8_t other_charac, uint8_t other_mantissa>
    signed_frac operator *= (unsigned_frac<other_charac,other_mantissa> const & other) {
      val = ((*this) * other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    template <uint8_t other_charac, uint8_t other_mantissa>
    signed_frac operator * (signed_frac<other_charac,other_mantissa> const & other ) {
      static_assert(0 == other_charac, "Reverse operand order!");

      typedef typename signed_frac<other_charac,other_mantissa>::big_type right_big_type;
      typedef typename signed_int<(sizeof(right_big_type))>::type pseudo_right_big_type;

      signed_frac r(0);
      
      if ( sizeof(signed_frac<other_charac,other_mantissa>) > sizeof(signed_frac) ) {
        pseudo_right_big_type tmp = ((pseudo_right_big_type)val) * other.val;
        
        printf("preTMP0    is %lld\n", tmp);

        tmp >>= signed_frac<other_charac,other_mantissa>::FX_SHIFT - 1;

        r.val = (type)tmp;

        printf("SHIFT is %d.\n", signed_frac<other_charac,other_mantissa>::FX_SHIFT - 1);         
        printf("r.val is %d.\n", r.val);
        
        if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
          printf("OVERFLOW: %d * %d = %lld\n", val, other.val, tmp);
          fflush(stdout);
#else
          r.val = MAX;
          printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
        }
      }
      else {
        big_type tmp = ((big_type)val) * other.val;

        printf("preTMP1   is %hd.\n", tmp);

        tmp >>= signed_frac<other_charac,other_mantissa>::FX_SHIFT - 1;
      
        r.val = (type)tmp;
        
        printf("SHIFT is %d.\n", signed_frac<other_charac,other_mantissa>::FX_SHIFT - 1);
        printf("r.val is %d.\n", r.val);
        
        if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
          printf("OVERFLOW: %d * %d = %hd\n", val, other.val, tmp);
          fflush(stdout);
#else
          r.val = MAX;
          printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
        }
      }

      return r;
    }    

    template <uint8_t other_charac, uint8_t other_mantissa>
    signed_frac operator *= (signed_frac<other_charac,other_mantissa> const & other) {
      val = ((*this) * other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////
    
    signed_frac operator / (signed_frac const & other ) {
      signed_frac<0,7> r = signed_frac<0,7>(val / other.val);
      return r;
    }        
    signed_frac operator /= (signed_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }
  };

////////////////////////////////////////////////////////////////////////////////
//
//  template <> class unsigned_frac<8,8> {
//  public:
//    typedef      q8n8_t  type;
//    typedef typename unsigned_int<(sizeof(type) << 1)>::type big_type;
//    static const type    ONE      = 1 << ((sizeof(type) >> 1) << 3)  ;
//    static const type    MAX      = unsigned_int<(sizeof(type))>::MAX;
//    static const type    MIN      = unsigned_int<(sizeof(type))>::MIN;
//    static const uint8_t FX_SHIFT = (sizeof(type) >> 1) << 3;
//    
//    type val;
//
//    explicit unsigned_frac(type const & val_) :
//      val(val_) {}
//
//    explicit unsigned_frac(uint8_t const & charac_, q0n8_t const & frac_) :
//      val((((uint16_t)charac_) << FX_SHIFT) | frac_){}
//
//    uint8_t chararac() const {
//      return val >> FX_SHIFT;
//    }
//
//    q0n8_t frac() const {
//      return val & 0xff;
//    }
//
//    unsigned_frac operator + (unsigned_frac const & other ) {
//      unsigned_frac<8,8> r = unsigned_frac<8,8>(val + other.val);
//      if (r.val < val) {
//#ifndef LAMB_FP_SATURATE
//        printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
//#else
//        r.val = MAX;
//        printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
//#endif
//        fflush(stdout);
//      }
//      return r;
//    }    
//    unsigned_frac operator += (unsigned_frac const & other) {
//      val = ((*this) + other).val;
//      return *this;
//    }
//
//    unsigned_frac operator - (unsigned_frac const & other ) {
//      unsigned_frac<8,8> r = unsigned_frac<8,8>(val - other.val);
//      if (r.val > val) {
//#ifndef LAMB_FP_SATURATE
////        printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
//#else
//        r.val = 0;
//        printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
//#endif
//        fflush(stdout);
//      }
//      return r;
//    }    
//    unsigned_frac operator -= (unsigned_frac const & other) {
//      val = ((*this) - other).val;
//      return *this;
//    }
//
//////////////////////////////////////////////////////////////////////////////////
//
//    template <uint8_t charac, uint8_t mantissa>
//    unsigned_frac operator * (unsigned_frac<charac,mantissa> const & other ) {
//      static_assert(0 == charac, "Reverse operand order!");
//    
//      typename unsigned_frac<charac,mantissa>::big_type tmp =
//        (((typename unsigned_frac<charac,mantissa>::big_type)val) * other.val) >>
//        unsigned_frac<charac,mantissa>::FX_SHIFT;
//      
//      unsigned_frac r   = unsigned_frac((type)tmp);
//      
////      printf("TMP   is %d.\n", tmp);
////      printf("r.val is %u.\n", r.val);
//
//      if (tmp > MAX) {
//#ifndef LAMB_FP_SATURATE
//        printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
//        fflush(stdout);
//#else
//        r.val = MAX;
//        printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
//#endif
//      }        
//      return r;
//    }    
//
//    template <uint8_t charac, uint8_t mantissa>
//    unsigned_frac operator *= (unsigned_frac<charac,mantissa> const & other) {
//      val = ((*this) * other).val;
//      return *this;
//    }
//
//////////////////////////////////////////////////////////////////////////////////
//    
//    unsigned_frac operator / (unsigned_frac const & other ) {
//      unsigned_frac<8,8> r = unsigned_frac<8,8>(val / other.val);
//      return r;
//    }        
//    unsigned_frac operator /= (unsigned_frac const & other) {
//      val = ((*this) / other).val;
//      return *this;
//    }
//
//  };
//
//////////////////////////////////////////////////////////////////////////////////
//
//  template <> class unsigned_frac<16,16> {
//  public:
//    typedef      q16n16_t  type;
//    typedef typename unsigned_int<(sizeof(type) << 1)>::type big_type;
//    static const type      ONE      = 1 << ((sizeof(type) >> 1) << 3);
//    static const type      MAX      = unsigned_int<(sizeof(type))>::MAX;
//    static const type      MIN      = unsigned_int<(sizeof(type))>::MIN;
//    static const uint8_t   FX_SHIFT = (sizeof(type) >> 1) << 3;
//    
//    type val;
//
//    explicit unsigned_frac(type const & val_) :
//      val(val_) {}
//
//    explicit unsigned_frac(uint16_t const & charac_, q0n16_t const & frac_) :
//      val((((uint32_t)charac_) << FX_SHIFT) | frac_){}
//
//    uint16_t chararac() const {
//      return val >> FX_SHIFT;
//    }
//
//    q0n16_t frac() const {
//      return val & 0xffff;
//    }
//
//    unsigned_frac operator + (unsigned_frac const & other ) {
//      unsigned_frac<16,16> r = unsigned_frac<16,16>(val + other.val);
//      if (r.val < val) {
//#ifndef LAMB_FP_SATURATE
//        printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
//#else
//        r.val = MAX;
//        printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
//#endif
//        fflush(stdout);
//      }
//      return r;
//    }    
//    unsigned_frac operator += (unsigned_frac const & other) {
//      val = ((*this) + other).val;
//      return *this;
//    }
//
//    unsigned_frac operator - (unsigned_frac const & other ) {
//      unsigned_frac<16,16> r = unsigned_frac<16,16>(val - other.val);
//      if (r.val > val) {
//#ifndef LAMB_FP_SATURATE
////        printf("UNDERFLOW: %u - %u = %llu\n", val, other.val, r.val);
//#else
//        r.val = 0;
//        printf("SATURATE LO: %u - %u = %llu\n", val, other.val, r.val);
//#endif
//        fflush(stdout);
//      }
//      return r;
//    }    
//    unsigned_frac operator -= (unsigned_frac const & other) {
//      val = ((*this) - other).val;
//      return *this;
//    }
//
////////////////////////////////////////////////////////////////////////////////
//
//    template <uint8_t charac, uint8_t mantissa>
//      unsigned_frac operator * (unsigned_frac<charac,mantissa> const & other ) {
//      static_assert(0 == charac, "Reverse operand order!");
//      
//      typename unsigned_frac<charac,mantissa>::big_type tmp =
//        (((typename unsigned_frac<charac,mantissa>::big_type)val) * other.val) >>
//        unsigned_frac<charac,mantissa>::FX_SHIFT;
//      
//      unsigned_frac r   = unsigned_frac((type)tmp);
//      
//      if (tmp > MAX) {
//#ifndef LAMB_FP_SATURATE
//        printf("OVERFLOW: %u * %u = %llu\n", val, other.val, tmp);
//        fflush(stdout);
//#else
//        r.val = MAX;
//        printf("SAT HI:  %u * %u = %llu\n", val, other.val, r.val);
//#endif
//      }        
//      return r;
//    }    
//
//    template <uint8_t charac, uint8_t mantissa>
//    unsigned_frac operator *= (unsigned_frac<charac,mantissa> const & other) {
//      val = ((*this) * other).val;
//      return *this;
//    }
//
////////////////////////////////////////////////////////////////////////////////
//    
//    unsigned_frac operator / (unsigned_frac const & other ) {
//      unsigned_frac<16,16> r = unsigned_frac<16,16>(val / other.val);
//      return r;
//    }        
//    unsigned_frac operator /= (unsigned_frac const & other) {
//      val = ((*this) / other).val;
//      return *this;
//    }
//
//  };
//

////////////////////////////////////////////////////////////////////////////////
//   
//   template <> class signed_frac<7,8> {
//   public:
//     typedef      q7n8_t  type;
//     typedef typename signed_int<(sizeof(type) << 1)>::type big_type;
//     static const type    ONE      = 1 << ((sizeof(type) >> 1) << 3);
//     static const type    MAX      = signed_int<(sizeof(type))>::MAX;
//     static const type    MIN      = signed_int<(sizeof(type))>::MIN;
//     static const uint8_t FX_SHIFT = (sizeof(type) >> 1) << 3;
//     
//     type val;
// 
//     explicit signed_frac(type const & val_) :
//       val(val_) {}
// 
//     explicit signed_frac(int8_t const & charac_, q0n8_t const & frac_) :
//       val((((int8_t)charac_) << FX_SHIFT) | frac_){}
// 
//     int8_t chararac() const {
//       return val >> FX_SHIFT;
//     }
// 
//     q0n8_t frac() const {
//       return val & 0xff;
//     }
// 
//     signed_frac operator + (signed_frac const & other ) {
//       signed_frac<7,8> r = signed_frac<7,8>(val + other.val);
//       if (r.val < val) {
// #ifndef LAMB_FP_SATURATE
//         printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
// #else
//         r.val = MAX;
//         printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
// #endif
//         fflush(stdout);
//       }
//       return r;
//     }    
//     signed_frac operator += (signed_frac const & other) {
//       val = ((*this) + other).val;
//       return *this;
//     }
// 
//     signed_frac operator - (signed_frac const & other ) {
//       signed_frac<7,8> r = signed_frac<7,8>(val - other.val);
//       if (r.val > val) {
// #ifndef LAMB_FP_SATURATE
// //        printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
// #else
//         r.val = 0;
//         printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
// #endif
//         fflush(stdout);
//       }
//       return r;
//     }    
//     signed_frac operator -= (signed_frac const & other) {
//       val = ((*this) - other).val;
//       return *this;
//     }
// 
////////////////////////////////////////////////////////////////////////////////
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator * (unsigned_frac<charac,mantissa> const & other ) {
//       big_type    tmp = (((big_type)val) * other.val) >> unsigned_frac<charac,mantissa>::FX_SHIFT;
//       signed_frac r   = signed_frac((type)tmp);
//       
//       if (tmp > MAX) {
// #ifndef LAMB_FP_SATURATE
//         printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
//         fflush(stdout);
// #else
//         r.val = MAX;
//         printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
// #endif
//       }        
//       return r;
//     }    
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator *= (unsigned_frac<charac,mantissa> const & other) {
//       val = ((*this) * other).val;
//       return *this;
//     }
// 
////////////////////////////////////////////////////////////////////////////////
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator * (signed_frac<charac,mantissa> const & other ) {
//       big_type    tmp = (((big_type)val) * other.val) >> (signed_frac<charac,mantissa>::FX_SHIFT - 1);
//       signed_frac r   = signed_frac((type)tmp);
//       
//       if (tmp > ONE) {
// #ifndef LAMB_FP_SATURATE
//         printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
//         fflush(stdout);
// #else
//         r.val = ONE;
//         printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
// #endif
//       }        
//       return r;
//     }    
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator *= (signed_frac<charac,mantissa> const & other) {
//       val = ((*this) * other).val;
//       return *this;
//     }
// 
//  ////////////////////////////////////////////////////////////////////////////////
//     
//     signed_frac operator / (signed_frac const & other ) {
//       signed_frac<7,8> r = signed_frac<7,8>(val / other.val);
//       return r;
//     }        
//     signed_frac operator /= (signed_frac const & other) {
//       val = ((*this) / other).val;
//       return *this;
//     }
// 
//   };
// 
// ////////////////////////////////////////////////////////////////////////////////
//   
//   template <> class signed_frac<15,16> {
//   public:
//     typedef      q15n16_t type;
//     typedef typename signed_int<(sizeof(type) << 1)>::type big_type;
//     static const type     ONE      = 1 << ((sizeof(type) >> 1) << 3);
//     static const type     MAX      = signed_int<(sizeof(type))>::MAX;
//     static const type     MIN      = signed_int<(sizeof(type))>::MIN;
//     static const uint8_t  FX_SHIFT = (sizeof(type) >> 1) << 3;
//     
//     type val;
// 
//     explicit signed_frac(type const & val_) :
//       val(val_) {}
// 
//     explicit signed_frac(int16_t const & charac_, q0n16_t const & frac_) :
//       val((((int16_t)charac_) << FX_SHIFT) | frac_){}
// 
//     int16_t chararac() const {
//       return val >> FX_SHIFT;
//     }
// 
//     q0n16_t frac() const {
//       return val & 0xff;
//     }
// 
//     signed_frac operator + (signed_frac const & other ) {
//       signed_frac<15,16> r = signed_frac<15,16>(val + other.val);
//       if (r.val < val) {
// #ifndef LAMB_FP_SATURATE
//         printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
// #else
//         r.val = MAX;
//         printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
// #endif
//         fflush(stdout);
//       }
//       return r;
//     }    
//     signed_frac operator += (signed_frac const & other) {
//       val = ((*this) + other).val;
//       return *this;
//     }
// 
//     signed_frac operator - (signed_frac const & other ) {
//       signed_frac<15,16> r = signed_frac<15,16>(val - other.val);
//       if (r.val > val) {
// #ifndef LAMB_FP_SATURATE
// //        printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
// #else
//         r.val = 0;
//         printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
// #endif
//         fflush(stdout);
//       }
//       return r;
//     }    
//     signed_frac operator -= (signed_frac const & other) {
//       val = ((*this) - other).val;
//       return *this;
//     }
// 
// ////////////////////////////////////////////////////////////////////////////////
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator * (unsigned_frac<charac,mantissa> const & other ) {
//       big_type    tmp = (((big_type)val) * other.val) >> unsigned_frac<charac,mantissa>::FX_SHIFT;
//       signed_frac r   = signed_frac((type)tmp);
//       
//       if (tmp > MAX) {
// #ifndef LAMB_FP_SATURATE
//         printf("OVERFLOW: %d * %d = %lld\n", val, other.val, tmp);
//         fflush(stdout);
// #else
//         r.val = MAX;
//         printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
// #endif
//       }        
//       return r;
//     }    
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator *= (unsigned_frac<charac,mantissa> const & other) {
//       val = ((*this) * other).val;
//       return *this;
//     }
// 
// ////////////////////////////////////////////////////////////////////////////////
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator * (signed_frac<charac,mantissa> const & other ) {
//       big_type    tmp = (((big_type)val) * other.val) >> (signed_frac<charac,mantissa>::FX_SHIFT - 1);
//       signed_frac r   = signed_frac((type)tmp);
//       
//       if (tmp > ONE) {
// #ifndef LAMB_FP_SATURATE
//         printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
//         fflush(stdout);
// #else
//         r.val = ONE;
//         printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
// #endif
//       }        
//       return r;
//     }    
// 
//     template <uint8_t charac, uint8_t mantissa>
//     signed_frac operator *= (signed_frac<charac,mantissa> const & other) {
//       val = ((*this) * other).val;
//       return *this;
//     }
// 
////////////////////////////////////////////////////////////////////////////////
// 
//     signed_frac operator / (signed_frac const & other ) {
//       signed_frac<15,16> r = signed_frac<15,16>(val / other.val);
//       return r;
//     }        
//     signed_frac operator /= (signed_frac const & other) {
//       val = ((*this) / other).val;
//       return *this;
//     }
//   };
// 
////////////////////////////////////////////////////////////////////////////////
  
}
#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
