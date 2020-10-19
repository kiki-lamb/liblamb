#ifndef LAMB_SAMPLE_TYPE_TRAITS
#define LAMB_SAMPLE_TYPE_TRAITS

#include "../uint12_t.h"

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// Basic integer types
////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t size_>
  class unsigned_int {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_int<1> {
  public:
    typedef uint8_t type;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_int<2> {
  public:
    typedef uint16_t type;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_int<4> {
  public:
    typedef uint32_t type;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_int<8> {
  public:
    typedef uint64_t type;
  };

////////////////////////////////////////////////////////////////////////////////

  template <uint8_t size_>
  class signed_int {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_int<1> {
  public:
    typedef int8_t type;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_int<2> {
  public:
    typedef int16_t type;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_int<4> {
  public:
    typedef int32_t type;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_int<8> {
  public:
    typedef int64_t type;
  };

////////////////////////////////////////////////////////////////////////////////
// Sample type traits
////////////////////////////////////////////////////////////////////////////////
  
  template <typename sample_type>
  class sample_type_traits {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<int8_t> {
  public:
    typedef      int8_t                                              value_type;     
    typedef      typename signed_int<sizeof(value_type) << 1>::type  mix_type;
    typedef      value_type                                          unmixed_type;         
    typedef      typename unsigned_int<sizeof(value_type)>::type     unsigned_type;
    typedef      typename signed_int<sizeof(value_type)>::type       signed_type;

    static const uint8_t    unmix_shift      = (sizeof(mix_type) - sizeof(value_type)) * 8;
    static const bool       is_signed        = true;    
    static const value_type maximum          = 127;
    static const value_type silence          = 0;
    static const value_type minimum          = -128;
    static const value_type bias_to_signed   = 0;
    static const mix_type   bias_to_unsigned = 128;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<int16_t> {
  public:
    typedef      int16_t                                               value_type;     
    typedef      typename signed_int<(sizeof(value_type) << 1)>::type  mix_type;
    typedef      typename signed_int<(sizeof(value_type) >> 1)>::type  unmixed_type;
    typedef      typename unsigned_int<sizeof(value_type)>::type       unsigned_type;
    typedef      typename signed_int<sizeof(value_type)>::type         signed_type;

    static const uint8_t    unmix_shift      = (sizeof(mix_type) - sizeof(value_type)) * 8;
    static const bool       is_signed        = true;    
    static const value_type maximum          = 0x7fff;
    static const value_type silence          = 0;
    static const value_type minimum          = 0xffff;
    static const value_type bias_to_signed   = 0;
    static const mix_type   bias_to_unsigned = 0x10000;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<int32_t> {
  public:
    typedef      int32_t                                               value_type;     
    typedef      typename signed_int<(sizeof(value_type) << 1)>::type  mix_type;
    typedef      typename signed_int<(sizeof(value_type) >> 1)>::type  unmixed_type;
    typedef      typename unsigned_int<sizeof(value_type)>::type       unsigned_type;
    typedef      typename signed_int<sizeof(value_type)>::type         signed_type;

    static const uint8_t    unmix_shift      = (sizeof(mix_type) - sizeof(value_type)) * 8;
    static const bool       is_signed        = true;    
    static const value_type maximum          = 0x7fffffff;
    static const value_type silence          = 0;
    static const value_type minimum          = 0xffffffff;
    static const value_type bias_to_signed   = 0;
    static const mix_type   bias_to_unsigned = 0x100000000;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<uint8_t> {
  public:
    typedef      uint8_t                                               value_type;
    typedef      typename signed_int<(sizeof(value_type) << 1)>::type  mix_type;
    typedef      value_type                                            unmixed_type;
    typedef      typename unsigned_int<sizeof(value_type)>::type       unsigned_type;
    typedef      typename signed_int<sizeof(value_type)>::type         signed_type;

    static const uint8_t    unmix_shift      = (sizeof(mix_type) - sizeof(value_type)) * 8;
    static const bool       is_signed        = true;    
    static const value_type maximum          = 0xff;
    static const value_type silence          = 0;
    static const value_type minimum          = 0;
    static const value_type bias_to_signed   = 0;
    static const mix_type   bias_to_unsigned = 0;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<uint16_t> {
  public:
    typedef      uint16_t                                              value_type;     
    typedef      typename signed_int<(sizeof(value_type) << 1)>::type  mix_type;
    typedef      typename signed_int<(sizeof(value_type) >> 1)>::type  unmixed_type;
    typedef      typename unsigned_int<sizeof(value_type)>::type       unsigned_type;
    typedef      typename signed_int<sizeof(value_type)>::type         signed_type;

    static const uint8_t    unmix_shift      = (sizeof(mix_type) - sizeof(value_type)) * 8;
    static const bool       is_signed        = true;    
    static const value_type maximum          = 0xffff;
    static const value_type silence          = 0;
    static const value_type minimum          = 0;
    static const value_type bias_to_signed   = 0;
    static const mix_type   bias_to_unsigned = 0;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<uint32_t> {
  public:
    typedef      uint32_t                                              value_type;
    typedef      typename signed_int<(sizeof(value_type) << 1)>::type  mix_type;
    typedef      typename signed_int<(sizeof(value_type) >> 1)>::type  unmixed_type;
    typedef      typename unsigned_int<sizeof(value_type)>::type       unsigned_type;
    typedef      typename signed_int<sizeof(value_type)>::type         signed_type;

    static const uint8_t    unmix_shift      = (sizeof(mix_type) - sizeof(value_type)) * 8;
    static const bool       is_signed        = true;    
    static const value_type maximum          = 0xffffffff;
    static const value_type silence          = 0;
    static const value_type minimum          = 0;
    static const value_type bias_to_signed   = 0;
    static const mix_type   bias_to_unsigned = 0;
  };

////////////////////////////////////////////////////////////////////////////////
// Fixed point types 
////////////////////////////////////////////////////////////////////////////////

// 8 bits //////////////////////////////////////////////////////////////////////

  typedef uint8_t  q0n8_t;                        

  typedef int8_t   q0n7_t;                        

// '12' bits (not really) //////////////////////////////////////////////////////

  typedef uint12_t q0n12_t;
  
// 16 bits /////////////////////////////////////////////////////////////////////

  typedef uint16_t  q0n16_t;                      

  typedef int16_t   q0n15_t;                      

  typedef uint16_t  q8n8_t;                       

  typedef int16_t   q7n8_t;                        

  typedef uint32_t  q0n32_t;                    

  typedef int32_t   q0n31_t;                      

  typedef uint32_t  q16n16_t;                     

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
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_frac<0, 12> {
  public:
    typedef q0n12_t type;
    static const q0n12_t one = 0xfff;
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
