#ifndef kl_512_int16_t_sqr_h
#define kl_512_int16_t_sqr_h

#define KL_512_int16_t_sqr_cells 512

namespace lamb {
  namespace tables {
    namespace sqr512_int16_t {
      typedef int16_t value_type;
      const   size_t length = 512;
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
    
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 159
    
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 191
    
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 223
    
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, 
         32767,    32767,    32767,    32767,    32767,    32767,    32767,    32767, // 255
    
         32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 287
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 319
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 351
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 383
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 415
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 447
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 479
    
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, 
        -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767,   -32767, // 511
    
      };
    }
  }
}
#endif
