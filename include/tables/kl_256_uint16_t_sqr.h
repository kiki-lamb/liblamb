#ifndef kl_256_uint16_t_sqr_h
#define kl_256_uint16_t_sqr_h

#define KL_256_uint16_t_sqr_cells 256

namespace lamb {
  namespace Tables {
    namespace sqr256_uint16_t {
      typedef uint16_t value_type;
      const   size_t length = 256;
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
    
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, // 95
    
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, 
         65535,    65535,    65535,    65535,    65535,    65535,    65535,    65535, // 127
    
         65535,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 159
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 191
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 223
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 255
    
      };
    }
  }
}
#endif
