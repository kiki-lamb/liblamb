#ifndef kl_512_uint8_t_sqr_h
#define kl_512_uint8_t_sqr_h

#define KL_512_uint8_t_sqr_cells 512

namespace lamb {
  namespace tables {
    namespace sqr512_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 512;
      const   uint8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 31
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 63
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 95
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 127
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 159
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 191
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 223
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 255
    
           255,        0,        0,        0,        0,        0,        0,        0, 
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
