#ifndef kl_256_uint8_t_tri_h
#define kl_256_uint8_t_tri_h

#define KL_256_uint8_t_tri_cells 256

namespace lamb {
  namespace tables {
    namespace tri256_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 256;
      const   uint8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
           128,      129,      131,      133,      135,      137,      139,      141, 
           143,      145,      147,      149,      151,      153,      155,      157, 
           159,      161,      163,      165,      167,      169,      171,      173, 
           175,      177,      179,      181,      183,      185,      187,      189, // 31
    
           191,      193,      195,      197,      199,      201,      203,      205, 
           207,      209,      211,      213,      215,      217,      219,      221, 
           223,      225,      227,      229,      231,      233,      235,      237, 
           239,      241,      243,      245,      247,      249,      251,      253, // 63
    
           255,      253,      251,      249,      247,      245,      243,      241, 
           239,      237,      235,      233,      231,      229,      227,      225, 
           223,      221,      219,      217,      215,      213,      211,      209, 
           207,      205,      203,      201,      199,      197,      195,      193, // 95
    
           191,      189,      187,      185,      183,      181,      179,      177, 
           175,      173,      171,      169,      167,      165,      163,      161, 
           159,      157,      155,      153,      151,      149,      147,      145, 
           143,      141,      139,      137,      135,      133,      131,      129, // 127
    
           128,      126,      124,      122,      120,      118,      116,      114, 
           112,      110,      108,      106,      104,      102,      100,       98, 
            96,       94,       92,       90,       88,       86,       84,       82, 
            80,       78,       76,       74,       72,       70,       68,       66, // 159
    
            64,       62,       60,       58,       56,       54,       52,       50, 
            48,       46,       44,       42,       40,       38,       36,       34, 
            32,       30,       28,       26,       24,       22,       20,       18, 
            16,       14,       12,       10,        8,        6,        4,        2, // 191
    
             0,        2,        4,        6,        8,       10,       12,       14, 
            16,       18,       20,       22,       24,       26,       28,       30, 
            32,       34,       36,       38,       40,       42,       44,       46, 
            48,       50,       52,       54,       56,       58,       60,       62, // 223
    
            64,       66,       68,       70,       72,       74,       76,       78, 
            80,       82,       84,       86,       88,       90,       92,       94, 
            96,       98,      100,      102,      104,      106,      108,      110, 
           112,      114,      116,      118,      120,      122,      124,      126, // 255
    
      };
    }
  }
}
#endif
