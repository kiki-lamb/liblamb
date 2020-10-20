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
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit unsigned_frac(type const & frac_part) :
      val(frac_part) {}

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
    static const uint8_t FX_SHIFT = sizeof(type) << 3;
    
    type val;

    explicit unsigned_frac(type const & frac_part) :
      val(frac_part) {}

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
    static const uint8_t FX_SHIFT  = sizeof(type) << 3;
    
    type val;

    explicit unsigned_frac(type const & frac_part) :
      val(frac_part) {}

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
  
  template <> class unsigned_frac<8, 8> {
  public:
    typedef q8n8_t type;
    static const q8n8_t one = 0x0100;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_frac<16, 16> {
  public:
    typedef q16n16_t type;
    static const q16n16_t one = 0x00010000;
  };

////////////////////////////////////////////////////////////////////////////////
  
// Signed
  
  template <uint8_t characteristic_, uint8_t mantissa>
  class signed_frac {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_frac<0, 7> {
  public:
    typedef q0n7_t type;
    static const q0n7_t one = 0x7f;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_frac<0, 15> {
  public:
    typedef q0n15_t type;
    static const q0n15_t one = 0x7fff; 
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_frac<7, 8> {
  public:
    typedef q7n8_t type;
    static const q7n8_t one = 0x0100;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_frac<0, 31> {
  public:
    typedef q0n31_t type;
    static const q0n31_t one = 0x7fffffff;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_frac<15, 16> {
  public:
    typedef q15n16_t type;
    static const q15n16_t one = 0x00010000;
  };

////////////////////////////////////////////////////////////////////////////////
  
}
#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
