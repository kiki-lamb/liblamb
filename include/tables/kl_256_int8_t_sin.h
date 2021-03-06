#ifndef kl_256_int8_t_sin_h
#define kl_256_int8_t_sin_h

#define KL_256_int8_t_sin_cells 256

namespace lamb {
  namespace tables {
    namespace sin256_int8_t {
      typedef int8_t value_type;
      const   size_t length = 256;
      const   int8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,        3,        6,        9,       12,       15,       18,       21, 
            24,       27,       30,       34,       37,       39,       42,       45, 
            48,       51,       54,       57,       60,       62,       65,       68, 
            70,       73,       75,       78,       80,       83,       85,       87, // 31
    
            90,       92,       94,       96,       98,      100,      102,      104, 
           106,      107,      109,      110,      112,      113,      115,      116, 
           117,      118,      120,      121,      122,      122,      123,      124, 
           125,      125,      126,      126,      126,      127,      127,      127, // 63
    
           127,      127,      127,      127,      126,      126,      126,      125, 
           125,      124,      123,      122,      122,      121,      120,      118, 
           117,      116,      115,      113,      112,      110,      109,      107, 
           106,      104,      102,      100,       98,       96,       94,       92, // 95
    
            90,       87,       85,       83,       80,       78,       75,       73, 
            70,       68,       65,       62,       60,       57,       54,       51, 
            48,       45,       42,       39,       37,       34,       30,       27, 
            24,       21,       18,       15,       12,        9,        6,        3, // 127
    
             0,       -3,       -6,       -9,      -12,      -15,      -18,      -21, 
           -24,      -27,      -30,      -34,      -37,      -39,      -42,      -45, 
           -48,      -51,      -54,      -57,      -60,      -62,      -65,      -68, 
           -70,      -73,      -75,      -78,      -80,      -83,      -85,      -87, // 159
    
           -90,      -92,      -94,      -96,      -98,     -100,     -102,     -104, 
          -106,     -107,     -109,     -110,     -112,     -113,     -115,     -116, 
          -117,     -118,     -120,     -121,     -122,     -122,     -123,     -124, 
          -125,     -125,     -126,     -126,     -126,     -127,     -127,     -127, // 191
    
          -127,     -127,     -127,     -127,     -126,     -126,     -126,     -125, 
          -125,     -124,     -123,     -122,     -122,     -121,     -120,     -118, 
          -117,     -116,     -115,     -113,     -112,     -110,     -109,     -107, 
          -106,     -104,     -102,     -100,      -98,      -96,      -94,      -92, // 223
    
           -90,      -87,      -85,      -83,      -80,      -78,      -75,      -73, 
           -70,      -68,      -65,      -62,      -60,      -57,      -54,      -51, 
           -48,      -45,      -42,      -39,      -37,      -34,      -30,      -27, 
           -24,      -21,      -18,      -15,      -12,       -9,       -6,       -3, // 255
    
      };
    }
  }
}
#endif
