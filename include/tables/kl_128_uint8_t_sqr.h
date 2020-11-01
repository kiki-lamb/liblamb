#ifndef kl_128_uint8_t_sqr_h
#define kl_128_uint8_t_sqr_h

#define KL_128_uint8_t_sqr_cells 128

namespace lamb {
  namespace tables {
    namespace sqr128_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 128;
      const   uint8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 31
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 63
    
           255,        0,        0,        0,        0,        0,        0,        0, 
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
