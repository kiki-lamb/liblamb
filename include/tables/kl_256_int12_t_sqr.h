#ifndef kl_256_int12_t_sqr_h
#define kl_256_int12_t_sqr_h

#define KL_256_int12_t_sqr_cells 256

namespace lamb {
  namespace Tables {
    namespace sqr256_int12_t {
      typedef int16_t value_type;
      const   size_t length = 256;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, // 31
    
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, // 63
    
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, // 95
    
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, 
          2047,     2047,     2047,     2047,     2047,     2047,     2047,     2047, // 127
    
          2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, // 159
    
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, // 191
    
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, // 223
    
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, // 255
    
      };
    }
  }
}
#endif
