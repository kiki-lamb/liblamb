#ifndef kl_128_uint16_t_sqr_h
#define kl_128_uint16_t_sqr_h

#define KL_128_uint16_t_sqr_cells 128

namespace lamb {
  namespace tables {
    namespace sqr128_uint16_t {
      typedef uint16_t value_type;
      const   size_t length = 128;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, // 31
    
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, // 63
    
         65535,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 95
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 127
    
      };
    }
  }
}
#endif
