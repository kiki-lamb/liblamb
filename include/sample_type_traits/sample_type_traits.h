#ifndef LAMB_SAMPLE_TYPE_TRAITS
#define LAMB_SAMPLE_TYPE_TRAITS

namespace lamb {
  template <typename sample_type, typename limits_t = int16_t> class sample_type_traits {
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
    typedef int8_t value_type;
    typedef int16_t mix_type;
    typedef uint8_t unsigned_type;
    typedef int8_t signed_type;
    static const int16_t maximum = 127;
    static const int16_t silence = 0;
    static const int16_t minimum = -128;
    static const int16_t bias_to_signed = 0;
    static const int16_t bias_to_unsigned = 128;
    static const value_type * sine_table;
    static inline uint8_t to_uint8_t(value_type v) {
      return v + bias_to_unsigned;
    }
    static inline int8_t to_int8_t(value_type v) {
      return v;
    }
    static inline value_type id(value_type x) { return x; };
  };

  // const int8_t * sample_type_traits<int8_t>::sine_table = lamb::Tables::sin256_int8_t::data;

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

  template <> class sample_type_traits<uint8_t> {
  public:
    typedef uint8_t value_type;
    typedef uint16_t mix_type;
    typedef uint8_t unsigned_type;
    typedef int8_t signed_type;
    static const int16_t maximum = 255;
    static const int16_t silence = 128;
    static const int16_t minimum = 0;
    static const int16_t bias_to_signed = -128;
    static const int16_t bias_to_unsigned = 0;
    static const value_type * sine_table;
    static inline uint8_t to_uint8_t(value_type v) {
      return v;
    }
    static inline int8_t to_int8_t(value_type v) {
      return v + bias_to_signed;
    }
    static inline value_type id(value_type x) { return x; };
  };

  // const uint8_t * sample_type_traits<uint8_t>::sine_table = lamb::Tables::sin256_uint8_t::data;
}

////////////////////////////////////////////////////////////////////////////////

#endif
