#ifndef kl_128_int8_t_saw_h
#define kl_128_int8_t_saw_h

#define KL_128_int8_t_saw_cells 128

namespace lamb {
  namespace Tables {
    namespace saw128_int8_t {
      typedef int8_t value_type;
      const   size_t length = 128;
      const   int8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,        1,        3,        5,        7,        9,       11,       13, 
            15,       17,       19,       21,       23,       25,       27,       29, 
            31,       33,       35,       37,       39,       41,       43,       45, 
            47,       49,       51,       53,       55,       57,       59,       61, // 31
    
            63,       65,       67,       69,       71,       73,       75,       77, 
            79,       81,       83,       85,       87,       89,       91,       93, 
            95,       97,       99,      101,      103,      105,      107,      109, 
           111,      113,      115,      117,      119,      121,      123,      125, // 63
    
           127,     -125,     -123,     -121,     -119,     -117,     -115,     -113, 
          -111,     -109,     -107,     -105,     -103,     -101,      -99,      -97, 
           -95,      -93,      -91,      -89,      -87,      -85,      -83,      -81, 
           -79,      -77,      -75,      -73,      -71,      -69,      -67,      -65, // 95
    
           -63,      -61,      -59,      -57,      -55,      -53,      -51,      -49, 
           -47,      -45,      -43,      -41,      -39,      -37,      -35,      -33, 
           -31,      -29,      -27,      -25,      -23,      -21,      -19,      -17, 
           -15,      -13,      -11,       -9,       -7,       -5,       -3,       -1, // 127
    
      };
    }
  }
}
#endif
