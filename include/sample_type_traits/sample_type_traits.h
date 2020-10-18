#ifndef LAMB_SAMPLE_TYPE_TRAITS
#define LAMB_SAMPLE_TYPE_TRAITS

namespace lamb {

////////////////////////////////////////////////////////////////////////////////

  template <uint8_t>
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
  
  template <> class unsigned_int<6> {
  public:
    typedef uint64_t type;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_int<8> {
  public:
    typedef uint64_t type;
  };

////////////////////////////////////////////////////////////////////////////////

  template <uint8_t>
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
  
  template <> class signed_int<6> {
  public:
    typedef int64_t type;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_int<8> {
  public:
    typedef int64_t type;
  };

////////////////////////////////////////////////////////////////////////////////

  template <typename sample_type>
  class sample_type_traits {
  public:
  typedef sample_type value_type;
//  public:
//    typedef sample_type value_type;
//    static const limits_t maximum;
//    static const limits_t silence;
//    static const limits_t minimum;
//    static const limits_t bias_to_signed;
//    static const limits_t bias_to_unsigned;
//    static const value_type * sine_table;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<int8_t> {
  public:
    typedef int8_t  value_type;
    typedef int16_t mix_type;
    typedef int8_t  unmixed_type;
    typedef uint8_t unsigned_type;
    typedef int8_t  signed_type;

    static const uint8_t unmix_shift      = 8;
    static const bool    is_signed        = true;    
    static const int16_t maximum          = 127;
    static const int16_t silence          = 0;
    static const int16_t minimum          = -128;
    static const int16_t bias_to_signed   = 0;
    static const int16_t bias_to_unsigned = 128;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<int16_t> {
  public:
    typedef int16_t  value_type;
    typedef int32_t  mix_type;
    typedef int8_t   unmixed_type;
    typedef uint16_t unsigned_type;
    typedef int16_t  signed_type;

    static const uint8_t unmix_shift      = 16;
    static const bool    is_signed        = true;
    static const int16_t maximum          = 32767;
    static const int16_t silence          = 0;
    static const int16_t minimum          = -32768;
    static const int16_t bias_to_signed   = 0;
    static const int16_t bias_to_unsigned = -32768;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<int32_t> {
  public:
    typedef int32_t  value_type;
    typedef int64_t  mix_type;
    typedef int16_t  unmixed_type;
    typedef uint32_t unsigned_type;
    typedef int32_t  signed_type;

    static const uint8_t unmix_shift      = 32;
    static const bool    is_signed        = true;
    static const int32_t maximum          = 0xffff;
    static const int32_t silence          = 0;
    static const int32_t minimum          = -0xffff-1;
    static const int32_t bias_to_signed   = 0;
    static const int32_t bias_to_unsigned = -0xffff-1;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<uint8_t> {
  public:
    typedef uint8_t  value_type;
    typedef uint16_t mix_type;
    typedef uint8_t  unmixed_type;
    typedef uint8_t  unsigned_type;
    typedef int8_t   signed_type;

    static const uint8_t unmix_shift      = 8;
    static const bool    is_signed        = true;
    static const int16_t maximum          = 0xff;
    static const int16_t silence          = 0x80;
    static const int16_t minimum          = 0;
    static const int16_t bias_to_signed   = -128;
    static const int16_t bias_to_unsigned = 0;
  };
}

////////////////////////////////////////////////////////////////////////////////

#endif
