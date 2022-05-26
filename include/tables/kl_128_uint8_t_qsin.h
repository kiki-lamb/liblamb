#ifndef kl_128_uint8_t_qsin_h
#define kl_128_uint8_t_qsin_h

#define KL_128_uint8_t_qsin_cells 128

namespace lamb {
  namespace tables {
    namespace qsin128_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 128;
      const   uint8_t data[]
#ifdef __AVR__
PROGMEM
#endif
= {
           0,        3,        6,        9,       12,       15,       18,       21, 
          24,       28,       31,       34,       37,       40,       43,       46, 
          49,       52,       55,       58,       61,       64,       68,       71, 
          74,       77,       79,       82,       85,       88,       91,       94, // 31
    
          97,      100,      103,      106,      109,      111,      114,      117, 
         120,      122,      125,      128,      131,      133,      136,      139, 
         141,      144,      146,      149,      151,      154,      156,      159, 
         161,      164,      166,      168,      171,      173,      175,      178, // 63
    
         180,      182,      184,      186,      188,      191,      193,      195, 
         197,      199,      201,      202,      204,      206,      208,      210, 
         212,      213,      215,      217,      218,      220,      221,      223, 
         224,      226,      227,      229,      230,      231,      233,      234, // 95
    
         235,      236,      237,      239,      240,      241,      242,      243, 
         244,      244,      245,      246,      247,      248,      248,      249, 
         250,      250,      251,      251,      252,      252,      253,      253, 
         253,      254,      254,      254,      254,      254,      254,      254, // 127
    
    };
    }
  }
}
#endif
