#ifndef LAMB_INTEGER_HELPERS_H
#define LAMB_INTEGER_HELPERS_H

#include "../uint12_t.h"

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// Size helper
////////////////////////////////////////////////////////////////////////////////
  
 template <uint8_t bits>
 constexpr uint8_t at_least_bits  = bits >= 64 ? 64 : (bits + 7) >> 3;

 template <uint8_t bytes>
 constexpr uint8_t at_least_bytes  = bytes >= 8 ? 8 : (bytes + 7) >> 1;

 template <uint8_t bits>
 constexpr uint8_t bytes_at_least_bits = at_least_bytes<at_least_bits<bits>>;

////////////////////////////////////////////////////////////////////////////////

 constexpr uint8_t size_fit_bytes(uint8_t siz) {
  while ((siz < 8) && ((siz & (siz - 1)) != 0))
   siz++;
  
  return siz;
 }
 
 constexpr uint8_t size_fit_bits(uint8_t const & bits) {
  uint8_t siz = bits / 8;
  uint8_t rem = bits % 8;
  
  if (rem != 0) 
   siz ++;
   
  return size_fit_bytes(siz);
  // while ((siz < 8) && ((siz & (siz - 1)) != 0))
  //  siz++;
   
  // return siz;
 }

////////////////////////////////////////////////////////////////////////////////

 template <bool use_left_type, typename left_type, typename right_type>
 class type_if {};
  
 template <typename left_type, typename right_type>
 class type_if<true, left_type, right_type> {
 public:
  typedef left_type type;
 };
  
 template <typename left_type, typename right_type>
 class type_if<false, left_type, right_type> {
 public:
  typedef right_type type;
 };

////////////////////////////////////////////////////////////////////////////////

 template <typename t>
 constexpr t const_max(t const & left, t const & right) {
  if (left > right) {
   return left;
  }

  return right;
 }
 
 template <typename t>
 constexpr t const_min(t const & left, t const & right) {
  if (left > right) {
   return right;
  }

  return left;
 }
 
////////////////////////////////////////////////////////////////////////////////
// Basic integer types
////////////////////////////////////////////////////////////////////////////////
  
 template <uint8_t size_>
 class unsigned_int {
 };

////////////////////////////////////////////////////////////////////////////////

 template <> class unsigned_int<1> {
 public:
  static const bool SIGNED = false;
  static const uint8_t SIZE = 1;
  typedef uint8_t type;
  static const type MIN = 0;
  static const type MAX = UINT8_MAX;
 };

////////////////////////////////////////////////////////////////////////////////

 template <> class unsigned_int<2> {
 public:
  static const bool SIGNED = false;
  static const uint8_t SIZE = 2;
  typedef uint16_t type;
  static const type MIN = 0;
  static const type MAX = UINT16_MAX;
 };

////////////////////////////////////////////////////////////////////////////////
  
 template <> class unsigned_int<4> {
 public:
  static const bool SIGNED = false;
  static const uint8_t SIZE = 4;
  typedef uint32_t type;
  static const type MIN = 0;
  static const type MAX = UINT32_MAX;
 };

////////////////////////////////////////////////////////////////////////////////
  
 template <> class unsigned_int<8> {
 public:
  static const bool SIGNED = false;
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
  static const bool SIGNED = true;
  static const uint8_t SIZE = 1;
  typedef int8_t type;
  static const type MIN = INT8_MIN;
  static const type MAX = INT8_MAX;
 };

////////////////////////////////////////////////////////////////////////////////

 template <> class signed_int<2> {
 public:
  static const bool SIGNED = true;
  static const uint8_t SIZE = 2;
  typedef int16_t type;
  static const type MIN = INT16_MIN;
  static const type MAX = INT16_MAX;
 };

////////////////////////////////////////////////////////////////////////////////
  
 template <> class signed_int<4> {
 public:
  static const bool SIGNED = true;
  static const uint8_t SIZE = 4;
  typedef int32_t type;
  static const type MIN = INT32_MIN;
  static const type MAX = INT32_MAX;
 };

////////////////////////////////////////////////////////////////////////////////
  
 template <> class signed_int<8> {
 public:
  static const bool SIGNED = true;
  static const uint8_t SIZE = 8;
  typedef int64_t type; 
  static const type MIN = INT64_MIN;
  static const type MAX = INT64_MAX;
 };
  
////////////////////////////////////////////////////////////////////////////////

 template <typename t> class integer_traits                                     {};
 template <>           class integer_traits<uint8_t > : public unsigned_int<1>  {};
 template <>           class integer_traits<uint16_t> : public unsigned_int<2>  {};
 template <>           class integer_traits<uint32_t> : public unsigned_int<4>  {};
 template <>           class integer_traits<uint64_t> : public unsigned_int<8>  {};
 template <>           class integer_traits<int8_t  > : public signed_int<1>    {};
 template <>           class integer_traits<int16_t > : public signed_int<2>    {};
 template <>           class integer_traits<int32_t > : public signed_int<4>    {};
 template <>           class integer_traits<int64_t > : public signed_int<8>    {};

 template <bool signedness, uint8_t size> class find_integer                        {};
 template <>           class find_integer<true,  1  > : public signed_int<1>    {};
 template <>           class find_integer<true,  2  > : public signed_int<2>    {};
 template <>           class find_integer<true,  4  > : public signed_int<4>    {};
 template <>           class find_integer<true,  8  > : public signed_int<8>    {};
 template <>           class find_integer<false, 1  > : public unsigned_int<1>  {};
 template <>           class find_integer<false, 2  > : public unsigned_int<2>  {};
 template <>           class find_integer<false, 4  > : public unsigned_int<4>  {};
 template <>           class find_integer<false, 8  > : public unsigned_int<8>  {};
}

////////////////////////////////////////////////////////////////////////////////

#endif

/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
