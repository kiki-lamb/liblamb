#ifndef kl_128_int12_t_sqr_h
#define kl_128_int12_t_sqr_h

#define KL_128_int12_t_sqr_cells 128

namespace lamb {
  namespace Tables {
    namespace sqr128_int12_t {
      typedef int16_t value_type;
      const   size_t length = 128;
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
    
          2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, // 95
    
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, 
         -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047,    -2047, // 127
    
      };
    }
  }
}
#endif
