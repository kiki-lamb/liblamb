#ifndef kl_512_int8_t_silence_h
#define kl_512_int8_t_silence_h

#define KL_512_int8_t_silence_cells 512

namespace lamb {
  namespace tables {
    namespace silence512_int8_t {
      typedef int8_t value_type;
      const   size_t length = 512;
      const   int8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 31
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 63
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 95
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 127
    
             0,        0,        0,        0,        0,        0,        0,        0, 
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
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 287
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 319
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 351
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 383
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 415
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 447
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 479
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 511
    
      };
    }
  }
}
#endif
