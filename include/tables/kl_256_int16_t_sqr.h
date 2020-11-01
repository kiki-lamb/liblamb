#ifndef kl_256_int16_t_sqr_h
#define kl_256_int16_t_sqr_h

#define KL_256_int16_t_sqr_cells 256

namespace lamb {
  namespace tables {
    namespace sqr256_int16_t {
      typedef int16_t value_type;
      const   size_t length = 256;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 31
    
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 63
    
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 95
    
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 127
    
         32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 159
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 191
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 223
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 255
    
      };
    }
  }
}
#endif
