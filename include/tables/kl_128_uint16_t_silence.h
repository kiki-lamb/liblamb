#ifndef kl_128_uint16_t_silence_h
#define kl_128_uint16_t_silence_h

#define KL_128_uint16_t_silence_cells 128

namespace lamb {
  namespace tables {
    namespace silence128_uint16_t {
      typedef uint16_t value_type;
      const   size_t length = 128;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, // 31
    
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, // 63
    
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, // 95
    
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, 
         32768,    32768,    32768,    32768,    32768,    32768,    32768,    32768, // 127
    
      };
    }
  }
}
#endif
