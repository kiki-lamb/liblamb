#ifndef kl_256_uint12_t_sqr_h
#define kl_256_uint12_t_sqr_h

#define KL_256_uint12_t_sqr_cells 256

namespace lamb {
  namespace tables {
    namespace sqr256_uint12_t {
      typedef uint16_t value_type;
      const   size_t length = 256;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, // 31
    
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, // 63
    
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, // 95
    
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, // 127
    
          4095,        0,        0,        0,        0,        0,        0,        0, 
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
