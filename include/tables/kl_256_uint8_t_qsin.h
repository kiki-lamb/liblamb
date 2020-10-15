#ifndef kl_256_uint8_t_qsin_h
#define kl_256_uint8_t_qsin_h

#define KL_256_uint8_t_qsin_cells 256

namespace lamb {
  namespace Tables {
    namespace qsin256_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 256;
      const   uint8_t data[]
#ifdef __AVR__
PROGMEM
#endif
= {
           0,        1,        3,        4,        6,        7,        9,       10, 
          12,       14,       15,       17,       18,       20,       21,       23, 
          24,       26,       28,       29,       31,       32,       34,       35, 
          37,       38,       40,       42,       43,       45,       46,       48, // 31
    
          49,       51,       52,       54,       55,       57,       58,       60, 
          61,       63,       64,       66,       68,       69,       71,       72, 
          74,       75,       77,       78,       79,       81,       82,       84, 
          85,       87,       88,       90,       91,       93,       94,       96, // 63
    
          97,       99,      100,      101,      103,      104,      106,      107, 
         109,      110,      111,      113,      114,      116,      117,      118, 
         120,      121,      122,      124,      125,      127,      128,      129, 
         131,      132,      133,      135,      136,      137,      139,      140, // 95
    
         141,      142,      144,      145,      146,      148,      149,      150, 
         151,      153,      154,      155,      156,      158,      159,      160, 
         161,      162,      164,      165,      166,      167,      168,      170, 
         171,      172,      173,      174,      175,      176,      178,      179, // 127
    
         180,      181,      182,      183,      184,      185,      186,      187, 
         188,      189,      191,      192,      193,      194,      195,      196, 
         197,      198,      199,      200,      201,      201,      202,      203, 
         204,      205,      206,      207,      208,      209,      210,      211, // 159
    
         212,      212,      213,      214,      215,      216,      217,      217, 
         218,      219,      220,      221,      221,      222,      223,      224, 
         224,      225,      226,      227,      227,      228,      229,      229, 
         230,      231,      231,      232,      233,      233,      234,      234, // 191
    
         235,      236,      236,      237,      237,      238,      239,      239, 
         240,      240,      241,      241,      242,      242,      243,      243, 
         244,      244,      244,      245,      245,      246,      246,      246, 
         247,      247,      248,      248,      248,      249,      249,      249, // 223
    
         250,      250,      250,      250,      251,      251,      251,      252, 
         252,      252,      252,      252,      253,      253,      253,      253, 
         253,      253,      254,      254,      254,      254,      254,      254, 
         254,      254,      254,      254,      254,      254,      254,      254, // 255
    
    };
    }
  }
}
#endif
