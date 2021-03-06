#ifndef kl_128_int16_t_sin_h
#define kl_128_int16_t_sin_h

#define KL_128_int16_t_sin_cells 128

namespace lamb {
  namespace tables {
    namespace sin128_int16_t {
      typedef int16_t value_type;
      const   size_t length = 128;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,     1607,     3211,     4807,     6392,     7961,     9511,    11039, 
         12539,    14009,    15446,    16845,    18204,    19519,    20787,    22005, 
         23170,    24279,    25329,    26319,    27245,    28105,    28898,    29621, 
         30273,    30852,    31356,    31785,    32137,    32412,    32609,    32728, // 31
    
         32767,    32728,    32609,    32412,    32137,    31785,    31356,    30852, 
         30273,    29621,    28898,    28105,    27245,    26319,    25329,    24279, 
         23170,    22005,    20787,    19519,    18204,    16845,    15446,    14009, 
         12539,    11039,     9511,     7961,     6392,     4807,     3211,     1607, // 63
    
             0,    -1607,    -3211,    -4807,    -6392,    -7961,    -9511,   -11039, 
        -12539,   -14009,   -15446,   -16845,   -18204,   -19519,   -20787,   -22005, 
        -23170,   -24279,   -25329,   -26319,   -27245,   -28105,   -28898,   -29621, 
        -30273,   -30852,   -31356,   -31785,   -32137,   -32412,   -32609,   -32728, // 95
    
        -32767,   -32728,   -32609,   -32412,   -32137,   -31785,   -31356,   -30852, 
        -30273,   -29621,   -28898,   -28105,   -27245,   -26319,   -25329,   -24279, 
        -23170,   -22005,   -20787,   -19519,   -18204,   -16845,   -15446,   -14009, 
        -12539,   -11039,    -9511,    -7961,    -6392,    -4807,    -3211,    -1607, // 127
    
      };
    }
  }
}
#endif
