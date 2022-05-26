#ifndef LAMBOS_GLOBAL_H
#define LAMBOS_GLOBAL_H

#include <inttypes.h>

namespace lamb {
  uint16_t flip_bytes(uint16_t const & value);
  void     print_bits_8(uint8_t const & t0);
  void     print_bits_16(uint16_t const & t0);
  void     print_bits_32(uint32_t const & t0);

  int free_mem();

  extern bool lamb_fixed_overflow;
 
  class delete_traits {
  public:
    template<typename T1>
    struct owner {
      static void destroy(T1&) {}
    };
    
    template<typename T1>
    struct owner<T1*> {
      static void destroy(T1* p) { delete p; }
    };

    template<typename T1>
    struct non_owner {
      static void destroy(T1&) {}
    }; 
  };
}

#endif
