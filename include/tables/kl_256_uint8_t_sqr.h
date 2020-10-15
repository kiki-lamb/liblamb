#ifndef kl_256_uint8_t_sqr_h
#define kl_256_uint8_t_sqr_h

#define KL_256_uint8_t_sqr_cells 256

namespace lamb {
  namespace Tables {
    namespace sqr256_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 256;
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
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 95
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 127
    
           255,        0,        0,        0,        0,        0,        0,        0, 
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
