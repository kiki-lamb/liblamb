#ifndef LAMB_INTEGER_HELPERS_H
#define LAMB_INTEGER_HELPERS_H

#include "../uint12_t.h"

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// Size helper
////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t bits_>
  constexpr uint8_t at_least_bits = (bits_ + 7) / 8;

////////////////////////////////////////////////////////////////////////////////
// Basic integer types
////////////////////////////////////////////////////////////////////////////////
  
  template <uint8_t size_>
  class unsigned_int {
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_int<1> {
  public:
   static const uint8_t SIZE = 1;
   typedef uint8_t type;
    static const type MIN = 0;
    static const type MAX = UINT8_MAX;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class unsigned_int<2> {
  public:
   static const uint8_t SIZE = 2;
   typedef uint16_t type;
    static const type MIN = 0;
    static const type MAX = UINT16_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_int<4> {
  public:
   static const uint8_t SIZE = 4;
   typedef uint32_t type;
    static const type MIN = 0;
    static const type MAX = UINT32_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class unsigned_int<8> {
  public:
   static const uint8_t SIZE = 8;
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
   static const uint8_t SIZE = 1;
   typedef int8_t type;
    static const type MIN = INT8_MIN;
    static const type MAX = INT8_MAX;
  };

////////////////////////////////////////////////////////////////////////////////

  template <> class signed_int<2> {
  public:
   static const uint8_t SIZE = 2;
   typedef int16_t type;
    static const type MIN = INT16_MIN;
    static const type MAX = INT16_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_int<4> {
  public:
   static const uint8_t SIZE = 4;
   typedef int32_t type;
    static const type MIN = INT32_MIN;
    static const type MAX = INT32_MAX;
  };

////////////////////////////////////////////////////////////////////////////////
  
  template <> class signed_int<8> {
  public:
   static const uint8_t SIZE = 8;
   typedef int64_t type; 
    static const type MIN = INT64_MIN;
    static const type MAX = INT64_MAX;
  };
  
////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////

#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
