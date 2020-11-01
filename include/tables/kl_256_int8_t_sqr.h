#ifndef kl_256_int8_t_sqr_h
#define kl_256_int8_t_sqr_h

#define KL_256_int8_t_sqr_cells 256

namespace lamb {
  namespace tables {
    namespace sqr256_int8_t {
      typedef int8_t value_type;
      const   size_t length = 256;
      const   int8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, // 31
    
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, // 63
    
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, // 95
    
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, 
           127,      127,      127,      127,      127,      127,      127,      127, // 127
    
           127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, // 159
    
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, // 191
    
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, // 223
    
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, 
          -127,     -127,     -127,     -127,     -127,     -127,     -127,     -127, // 255
    
      };
    }
  }
}
#endif
