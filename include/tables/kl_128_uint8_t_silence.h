#ifndef kl_128_uint8_t_silence_h
#define kl_128_uint8_t_silence_h

#define KL_128_uint8_t_silence_cells 128

namespace lamb {
  namespace Tables {
    namespace silence128_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 128;
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
    
      };
    }
  }
}
#endif
