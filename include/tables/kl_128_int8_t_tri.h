#ifndef kl_128_int8_t_tri_h
#define kl_128_int8_t_tri_h

#define KL_128_int8_t_tri_cells 128

namespace lamb {
  namespace tables {
    namespace tri128_int8_t {
      typedef int8_t value_type;
      const   size_t length = 128;
      const   int8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,        3,        7,       11,       15,       19,       23,       27, 
            31,       35,       39,       43,       47,       51,       55,       59, 
            63,       67,       71,       75,       79,       83,       87,       91, 
            95,       99,      103,      107,      111,      115,      119,      123, // 31
    
           127,      123,      119,      115,      111,      107,      103,       99, 
            95,       91,       87,       83,       79,       75,       71,       67, 
            63,       59,       55,       51,       47,       43,       39,       35, 
            31,       27,       23,       19,       15,       11,        7,        3, // 63
    
             0,       -3,       -7,      -11,      -15,      -19,      -23,      -27, 
           -31,      -35,      -39,      -43,      -47,      -51,      -55,      -59, 
           -63,      -67,      -71,      -75,      -79,      -83,      -87,      -91, 
           -95,      -99,     -103,     -107,     -111,     -115,     -119,     -123, // 95
    
          -127,     -123,     -119,     -115,     -111,     -107,     -103,      -99, 
           -95,      -91,      -87,      -83,      -79,      -75,      -71,      -67, 
           -63,      -59,      -55,      -51,      -47,      -43,      -39,      -35, 
           -31,      -27,      -23,      -19,      -15,      -11,       -7,       -3, // 127
    
      };
    }
  }
}
#endif
