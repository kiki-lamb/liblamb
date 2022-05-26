#ifndef kl_128_uint12_t_silence_h
#define kl_128_uint12_t_silence_h

#define KL_128_uint12_t_silence_cells 128

namespace lamb {
  namespace tables {
    namespace silence128_uint12_t {
      typedef uint16_t value_type;
      const   size_t length = 128;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, // 31
    
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, // 63
    
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, // 95
    
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, 
          2048,     2048,     2048,     2048,     2048,     2048,     2048,     2048, // 127
    
      };
    }
  }
}
#endif
