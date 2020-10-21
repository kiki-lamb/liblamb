#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

#ifdef NO_ARDUINO
  #include <stdio.h>
  #include <stdlib.h>
#endif

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
  
  template <uint8_t characteristic_, uint8_t mantissa>
  class unsigned_frac {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_frac<0,8> {
  public:
    typedef      q0n8_t  type;
    typedef      q0n16_t big_type;
    static const type    ONE      = 0xff;
    static const type    MAX      = 0xff;
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit unsigned_frac(type const & val_) :
      val(val_) {}

    uint8_t chararac() const {
      return 0;
    }

    type frac() const {
      return val;
    }

    unsigned_frac operator + (unsigned_frac const & other ) {
      unsigned_frac<0,8> r = unsigned_frac<0,8>(val + other.val);
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

    unsigned_frac operator * (unsigned_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      unsigned_frac<0,8>     r   = unsigned_frac<0,8>((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u * %u = %u\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SAT HI:  %u * %u = %u\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    unsigned_frac operator *= (unsigned_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
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

  template <> class unsigned_frac<0,16> {
  public:
    typedef      q0n16_t type;
    typedef      q0n32_t big_type;
    static const type    ONE      = 0xffff;
    static const type    MAX      = 0xffff;
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit unsigned_frac(type const & val_) :
      val(val_) {}

    uint8_t chararac() const {
      return 0;
    }

    type frac() const {
      return val;
    }

    unsigned_frac operator + (unsigned_frac const & other ) {
      unsigned_frac<0,16> r = unsigned_frac<0,16>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        // printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
#else
        r.val = ONE;
        // printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
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
      unsigned_frac<0,16> r = unsigned_frac<0,16>(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
        // printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
#else
        r.val = 0;
        // printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    unsigned_frac operator -= (unsigned_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

    unsigned_frac operator * (unsigned_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      unsigned_frac<0,16>     r   = unsigned_frac<0,16>((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        // printf("OVERFLOW: %u * %u = %u\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        // printf("SATURATE HI:  %u * %u = %u\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    unsigned_frac operator *= (unsigned_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
    unsigned_frac operator / (unsigned_frac const & other ) {
      unsigned_frac<0,16> r = unsigned_frac<0,16>(val / other.val);
      return r;
    }        
    unsigned_frac operator /= (unsigned_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }

  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_frac<0,32> {
  public:
    typedef      q0n32_t  type;
    typedef      q0n64_t  big_type;
    static const type     ONE      = 0xffff'ffff;
    static const type     MAX      = 0xffff'ffff;
    static const uint8_t  FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit unsigned_frac(type const & val_) :
      val(val_) {}

    uint8_t chararac() const {
      return 0;
    }

    type frac() const {
      return val;
    }

    unsigned_frac operator + (unsigned_frac const & other ) {
      unsigned_frac<0,32> r = unsigned_frac<0,32>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        // printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
#else
        r.val = ONE;
        // printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
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
      unsigned_frac<0,32> r = unsigned_frac<0,32>(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
        // printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
#else
        r.val = 0;
        // printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    unsigned_frac operator -= (unsigned_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

    unsigned_frac operator * (unsigned_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      unsigned_frac<0,32>     r   = unsigned_frac<0,32>((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        // printf("OVERFLOW: %u * %u = %u\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        // printf("SATURATE HI:  %u * %u = %u\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    unsigned_frac operator *= (unsigned_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
    unsigned_frac operator / (unsigned_frac const & other ) {
      unsigned_frac<0,32> r = unsigned_frac<0,32>(val / other.val);
      return r;
    }        
    unsigned_frac operator /= (unsigned_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }

  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_frac<8,8> {
  public:
    typedef      q8n8_t  type;
    typedef      q0n32_t big_type;
    static const type    ONE      = 0x0100;
    static const type    MAX      = 0xffff;
    static const uint8_t FX_SHIFT = (sizeof(type) >> 1) << 3;
    
    type val;

    explicit unsigned_frac(type const & val_) :
      val(val_) {}

    explicit unsigned_frac(uint8_t const & charac_, q0n8_t const & frac_) :
      val((((uint16_t)charac_) << FX_SHIFT) | frac_){}

    uint8_t chararac() const {
      return val >> FX_SHIFT;
    }

    q0n8_t frac() const {
      return val & 0xff;
    }

    unsigned_frac operator + (unsigned_frac const & other ) {
      unsigned_frac<8,8> r = unsigned_frac<8,8>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
#else
        r.val = MAX;
        printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
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
      unsigned_frac<8,8> r = unsigned_frac<8,8>(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
//        printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
#else
        r.val = 0;
        printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    unsigned_frac operator -= (unsigned_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

    unsigned_frac operator * (unsigned_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      unsigned_frac<8,8>     r   = unsigned_frac<8,8>((type)tmp);
      
      if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u * %u = %u\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SATURATE HI:  %u * %u = %u\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    unsigned_frac operator *= (unsigned_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
    unsigned_frac operator / (unsigned_frac const & other ) {
      unsigned_frac<8,8> r = unsigned_frac<8,8>(val / other.val);
      return r;
    }        
    unsigned_frac operator /= (unsigned_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }

  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_frac<16,16> {
  public:
    typedef      q16n16_t  type;
    typedef      q0n64_t   big_type;
    static const type      ONE      = 0x0001'0000;
    static const type      MAX      = 0xffff'ffff;
    static const uint8_t   FX_SHIFT = (sizeof(type) >> 1) << 3;
    
    type val;

    explicit unsigned_frac(type const & val_) :
      val(val_) {}

    explicit unsigned_frac(uint16_t const & charac_, q0n16_t const & frac_) :
      val((((uint32_t)charac_) << FX_SHIFT) | frac_){}

    uint16_t chararac() const {
      return val >> FX_SHIFT;
    }

    q0n16_t frac() const {
      return val & 0xffff;
    }

    unsigned_frac operator + (unsigned_frac const & other ) {
      unsigned_frac<16,16> r = unsigned_frac<16,16>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
#else
        r.val = MAX;
        printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
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
      unsigned_frac<16,16> r = unsigned_frac<16,16>(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
//        printf("UNDERFLOW: %u - %u = %llu\n", val, other.val, r.val);
#else
        r.val = 0;
        printf("SATURATE LO: %u - %u = %llu\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    unsigned_frac operator -= (unsigned_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

    unsigned_frac operator * (unsigned_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      unsigned_frac<16,16>     r   = unsigned_frac<16,16>((type)tmp);
      
      if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u * %u = %llu\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SATURATE HI:  %u * %llu = %u\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    unsigned_frac operator *= (unsigned_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
    unsigned_frac operator / (unsigned_frac const & other ) {
      unsigned_frac<16,16> r = unsigned_frac<16,16>(val / other.val);
      return r;
    }        
    unsigned_frac operator /= (unsigned_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }

  };

////////////////////////////////////////////////////////////////////////////////
  
// Signed
  
  template <uint8_t characteristic_, uint8_t mantissa>
  class signed_frac {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_frac<0,7> {
  public:
    typedef      q0n7_t  type;
    typedef      q0n15_t big_type;

    static const type    ONE      = 0x7f;
    static const type    MAX      = 0x7f;
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit signed_frac(type const & val_) :
      val(val_) {}

    int8_t chararac() const {
      return 0;
    }

    type frac() const {
      return val;
    }

    signed_frac operator + (signed_frac const & other ) {
      signed_frac<0,7> r = signed_frac<0,7>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d + %d = %d\n", val, other.val, r.val);
#else
        r.val = ONE;
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
      signed_frac<0,7> r = signed_frac<0,7>(val - other.val);
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
    
    signed_frac operator * (signed_frac const & other ) {
      big_type    tmp  = (((big_type)val) * other.val) >> (FX_SHIFT - 1);
      signed_frac r    = signed_frac((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
      }        
      return r;
    }    
    signed_frac operator *= (signed_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
////////////////////////////////////////////////////////////////////////////////

    signed_frac operator * (unsigned_frac<0,8> const & other ) {
      big_type tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      signed_frac<0,7>     r   = signed_frac<0,7>((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
      }        
      return r;
    }    
    signed_frac operator *= (unsigned_frac<0,8> const & other) {
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

  template <> class signed_frac<0,15> {
  public:
    typedef      q0n15_t  type;
    typedef      q0n31_t big_type;

    static const type    ONE      = 0x7fff;
    static const type    MAX      = 0x7fff;
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit signed_frac(type const & val_) :
      val(val_) {}

    int16_t chararac() const {
      return 0;
    }

    type frac() const {
      return val;
    }

    signed_frac operator + (signed_frac const & other ) {
      signed_frac<0,15> r = signed_frac<0,15>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d + %d = %d\n", val, other.val, r.val);
#else
        r.val = ONE;
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
      signed_frac<0,15> r = signed_frac<0,15>(val - other.val);
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

    signed_frac operator * (signed_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> (FX_SHIFT - 1);
      signed_frac<0,15>     r   = signed_frac<0,15>((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
      }        
      return r;
    }    
    signed_frac operator *= (signed_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    signed_frac operator * (unsigned_frac<0,16> const & other ) {
      big_type    tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      signed_frac r   = signed_frac((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d * %d = %d\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
      }        
      return r;
    }    
    signed_frac operator *= (unsigned_frac<0,16> const & other) {
      val = ((*this) * other).val;
      return *this;
    }


////////////////////////////////////////////////////////////////////////////////

    signed_frac operator / (signed_frac const & other ) {
      signed_frac<0,15> r = signed_frac<0,15>(val / other.val);
      return r;
    }        
    signed_frac operator /= (signed_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_frac<0,31> {
  public:
    typedef      q0n31_t  type;
    typedef      q0n63_t  big_type;

    static const type    ONE      = 0x7fff'ffff;
    static const type    MAX      = 0x7fff'ffff;
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit signed_frac(type const & val_) :
      val(val_) {}

    int32_t chararac() const {
      return 0;
    }

    type frac() const {
      return val;
    }

    signed_frac operator + (signed_frac const & other ) {
      signed_frac<0,31> r = signed_frac<0,31>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d + %d = %d\n", val, other.val, r.val);
#else
        r.val = ONE;
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
      signed_frac<0,31> r = signed_frac<0,31>(val - other.val);
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
    
    signed_frac operator * (signed_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> (FX_SHIFT - 1);
      signed_frac<0,31>     r   = signed_frac<0,31>((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d * %d = %lld\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    signed_frac operator *= (signed_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
////////////////////////////////////////////////////////////////////////////////

    signed_frac operator * (unsigned_frac<0,32> const & other ) {
      big_type    tmp = (((big_type)val) * other.val) >> FX_SHIFT;
      signed_frac r   = signed_frac((type)tmp);
      
      if (tmp > ONE) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %d * %d = %lld\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SAT HI:  %d * %d = %d\n", val, other.val, r.val);
#endif
      }        
      return r;
    }    
    signed_frac operator *= (unsigned_frac<0,32> const & other) {
      val = ((*this) * other).val;
      return *this;
    }


////////////////////////////////////////////////////////////////////////////////

    signed_frac operator / (signed_frac const & other ) {
      signed_frac<0,31> r = signed_frac<0,31>(val / other.val);
      return r;
    }        
    signed_frac operator /= (signed_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_frac<7,8> {
  public:
    typedef      q7n8_t  type;
    typedef      q0n31_t big_type;
    static const type    ONE      = 0x0100;
    static const type    MAX      = 0x7fff;
    static const uint8_t FX_SHIFT = (sizeof(type) >> 1) << 3;
    
    type val;

    explicit signed_frac(type const & val_) :
      val(val_) {}

    explicit signed_frac(int8_t const & charac_, q0n8_t const & frac_) :
      val((((int8_t)charac_) << FX_SHIFT) | frac_){}

    int8_t chararac() const {
      return val >> FX_SHIFT;
    }

    q0n8_t frac() const {
      return val & 0xff;
    }

    signed_frac operator + (signed_frac const & other ) {
      signed_frac<7,8> r = signed_frac<7,8>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
#else
        r.val = MAX;
        printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
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
      signed_frac<7,8> r = signed_frac<7,8>(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
//        printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
#else
        r.val = 0;
        printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    signed_frac operator -= (signed_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

    signed_frac operator * (signed_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> (FX_SHIFT);
      signed_frac<7,8>     r   = signed_frac<7,8>((type)tmp);
      
      if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u * %u = %u\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SATURATE HI:  %u * %u = %u\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    signed_frac operator *= (signed_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
    signed_frac operator / (signed_frac const & other ) {
      signed_frac<7,8> r = signed_frac<7,8>(val / other.val);
      return r;
    }        
    signed_frac operator /= (signed_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }

  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_frac<15,16> {
  public:
    typedef      q15n16_t type;
    typedef      q0n63_t  big_type;
    static const type     ONE      = 0x0001'0000;
    static const type     MAX      = 0x7fff'ffff;
    static const uint8_t  FX_SHIFT = (sizeof(type) >> 1) << 3;
    
    type val;

    explicit signed_frac(type const & val_) :
      val(val_) {}

    explicit signed_frac(int16_t const & charac_, q0n16_t const & frac_) :
      val((((int16_t)charac_) << FX_SHIFT) | frac_){}

    int16_t chararac() const {
      return val >> FX_SHIFT;
    }

    q0n16_t frac() const {
      return val & 0xff;
    }

    signed_frac operator + (signed_frac const & other ) {
      signed_frac<15,16> r = signed_frac<15,16>(val + other.val);
      if (r.val < val) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u + %u = %u\n", val, other.val, r.val);
#else
        r.val = MAX;
        printf("SATURATE HI:  %u + %u = %u\n", val, other.val, r.val);
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
      signed_frac<15,16> r = signed_frac<15,16>(val - other.val);
      if (r.val > val) {
#ifndef LAMB_FP_SATURATE
//        printf("UNDERFLOW: %u - %u = %u\n", val, other.val, r.val);
#else
        r.val = 0;
        printf("SATURATE LO: %u - %u = %u\n", val, other.val, r.val);
#endif
        fflush(stdout);
      }
      return r;
    }    
    signed_frac operator -= (signed_frac const & other) {
      val = ((*this) - other).val;
      return *this;
    }

    signed_frac operator * (signed_frac const & other ) {      
      big_type tmp = (((big_type)val) * other.val) >> (FX_SHIFT);
      signed_frac<15,16>     r   = signed_frac<15,16>((type)tmp);
      
      if (tmp > MAX) {
#ifndef LAMB_FP_SATURATE
        printf("OVERFLOW: %u * %u = %lld\n", val, other.val, tmp);
        fflush(stdout);
#else
        r.val = ONE;
        printf("SATURATE HI:  %u * %u = %lld\n", val, other.val, r.val);
#endif
      }        

      return r;
    }    
    signed_frac operator *= (signed_frac const & other) {
      val = ((*this) * other).val;
      return *this;
    }
    
    signed_frac operator / (signed_frac const & other ) {
      signed_frac<15,16> r = signed_frac<15,16>(val / other.val);
      return r;
    }        
    signed_frac operator /= (signed_frac const & other) {
      val = ((*this) / other).val;
      return *this;
    }
  };

////////////////////////////////////////////////////////////////////////////////
  
}
#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
