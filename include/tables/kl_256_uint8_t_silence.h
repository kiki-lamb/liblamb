#ifndef kl_256_uint8_t_silence_h
#define kl_256_uint8_t_silence_h

#define KL_256_uint8_t_silence_cells 256

namespace lamb {
  namespace tables {
    namespace silence256_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 256;
      const   uint8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 31
    
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 63
    
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 95
    
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 127
    
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 159
    
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 191
    
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 223
    
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, 
           128,      128,      128,      128,      128,      128,      128,      128, // 255
    
      };
    }
  }
}
#endif
