#ifndef LAMB_FIX_MATH_H
#define LAMB_FIX_MATH_H

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

////////////////////////////////////////////////////////////////////////////////
// Fixed type helpers
////////////////////////////////////////////////////////////////////////////////

// Unsigned
  
  template <uint8_t characteristic_, uint8_t mantissa>
  class unsigned_frac {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_frac<0, 8> {
  public:
    typedef q0n8_t type;
    static const q0n8_t one = 0xff;

    type value;

    unsigned_frac(uint8_t const & frac_part) :
      value(frac_part) {}
    
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_frac<0, 16> {
  public:
    typedef q0n16_t type;
    static const q0n16_t one = 0xffff;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_frac<8, 8> {
  public:
    typedef q8n8_t type;
    static const q8n8_t one = 0x0100;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_frac<0, 32> {
  public:
    typedef q0n32_t type;
    static const q0n32_t one = 0xffffffff;
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
