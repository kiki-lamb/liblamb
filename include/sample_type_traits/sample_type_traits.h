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
    static const type MIN = 0;
    static const type MAX = UINT8_MAX;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_int<2> {
  public:
    typedef uint16_t type;
    static const type MIN = 0;
    static const type MAX = UINT16_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_int<4> {
  public:
    typedef uint32_t type;
    static const type MIN = 0;
    static const type MAX = UINT32_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_int<8> {
  public:
    typedef uint64_t type;
    static const type MIN = 0;
    static const type MAX = UINT64_MAX;
  };

////////////////////////////////////////////////////////////////////////////////

  template <uint8_t size_>
  class signed_int {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_int<1> {
  public:
    typedef int8_t type;
    static const type MIN = INT8_MIN;
    static const type MAX = INT8_MAX;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_int<2> {
  public:
    typedef int16_t type;
    static const type MIN = INT16_MIN;
    static const type MAX = INT16_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_int<4> {
  public:
    typedef int32_t type;
    static const type MIN = INT32_MIN;
    static const type MAX = INT32_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_int<8> {
  public:
    typedef int64_t type; 
    static const type MIN = INT64_MIN;
    static const type MAX = INT64_MAX;
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

}

////////////////////////////////////////////////////////////////////////////////

#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
