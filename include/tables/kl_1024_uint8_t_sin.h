#ifndef kl_1024_uint8_t_sin_h
#define kl_1024_uint8_t_sin_h

#define KL_1024_uint8_t_sin_cells 1024

namespace lamb {
  namespace tables {
    namespace sin1024_uint8_t {
      typedef uint8_t value_type;
      const   size_t length = 1024;
      const   uint8_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
           128,      128,      129,      130,      131,      131,      132,      133, 
           134,      135,      135,      136,      137,      138,      138,      139, 
           140,      141,      142,      142,      143,      144,      145,      145, 
           146,      147,      148,      149,      149,      150,      151,      152, // 31
    
           152,      153,      154,      155,      155,      156,      157,      158, 
           158,      159,      160,      161,      162,      162,      163,      164, 
           165,      165,      166,      167,      167,      168,      169,      170, 
           170,      171,      172,      173,      173,      174,      175,      176, // 63
    
           176,      177,      178,      178,      179,      180,      181,      181, 
           182,      183,      183,      184,      185,      186,      186,      187, 
           188,      188,      189,      190,      190,      191,      192,      192, 
           193,      194,      194,      195,      196,      196,      197,      198, // 95
    
           198,      199,      200,      200,      201,      202,      202,      203, 
           203,      204,      205,      205,      206,      207,      207,      208, 
           208,      209,      210,      210,      211,      211,      212,      213, 
           213,      214,      214,      215,      215,      216,      217,      217, // 127
    
           218,      218,      219,      219,      220,      220,      221,      221, 
           222,      222,      223,      224,      224,      225,      225,      226, 
           226,      227,      227,      228,      228,      228,      229,      229, 
           230,      230,      231,      231,      232,      232,      233,      233, // 159
    
           234,      234,      234,      235,      235,      236,      236,      236, 
           237,      237,      238,      238,      238,      239,      239,      240, 
           240,      240,      241,      241,      241,      242,      242,      242, 
           243,      243,      243,      244,      244,      244,      245,      245, // 191
    
           245,      246,      246,      246,      246,      247,      247,      247, 
           248,      248,      248,      248,      249,      249,      249,      249, 
           250,      250,      250,      250,      250,      251,      251,      251, 
           251,      251,      252,      252,      252,      252,      252,      252, // 223
    
           253,      253,      253,      253,      253,      253,      253,      254, 
           254,      254,      254,      254,      254,      254,      254,      254, 
           254,      254,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      255, // 255
    
           255,      255,      255,      255,      255,      255,      255,      255, 
           255,      255,      255,      255,      255,      255,      255,      254, 
           254,      254,      254,      254,      254,      254,      254,      254, 
           254,      254,      253,      253,      253,      253,      253,      253, // 287
    
           253,      252,      252,      252,      252,      252,      252,      251, 
           251,      251,      251,      251,      250,      250,      250,      250, 
           250,      249,      249,      249,      249,      248,      248,      248, 
           248,      247,      247,      247,      246,      246,      246,      246, // 319
    
           245,      245,      245,      244,      244,      244,      243,      243, 
           243,      242,      242,      242,      241,      241,      241,      240, 
           240,      240,      239,      239,      238,      238,      238,      237, 
           237,      236,      236,      236,      235,      235,      234,      234, // 351
    
           234,      233,      233,      232,      232,      231,      231,      230, 
           230,      229,      229,      228,      228,      228,      227,      227, 
           226,      226,      225,      225,      224,      224,      223,      222, 
           222,      221,      221,      220,      220,      219,      219,      218, // 383
    
           218,      217,      217,      216,      215,      215,      214,      214, 
           213,      213,      212,      211,      211,      210,      210,      209, 
           208,      208,      207,      207,      206,      205,      205,      204, 
           203,      203,      202,      202,      201,      200,      200,      199, // 415
    
           198,      198,      197,      196,      196,      195,      194,      194, 
           193,      192,      192,      191,      190,      190,      189,      188, 
           188,      187,      186,      186,      185,      184,      183,      183, 
           182,      181,      181,      180,      179,      178,      178,      177, // 447
    
           176,      176,      175,      174,      173,      173,      172,      171, 
           170,      170,      169,      168,      167,      167,      166,      165, 
           165,      164,      163,      162,      162,      161,      160,      159, 
           158,      158,      157,      156,      155,      155,      154,      153, // 479
    
           152,      152,      151,      150,      149,      149,      148,      147, 
           146,      145,      145,      144,      143,      142,      142,      141, 
           140,      139,      138,      138,      137,      136,      135,      135, 
           134,      133,      132,      131,      131,      130,      129,      128, // 511
    
           128,      127,      126,      125,      124,      124,      123,      122, 
           121,      120,      120,      119,      118,      117,      117,      116, 
           115,      114,      113,      113,      112,      111,      110,      110, 
           109,      108,      107,      106,      106,      105,      104,      103, // 543
    
           103,      102,      101,      100,      100,       99,       98,       97, 
            97,       96,       95,       94,       93,       93,       92,       91, 
            90,       90,       89,       88,       88,       87,       86,       85, 
            85,       84,       83,       82,       82,       81,       80,       79, // 575
    
            79,       78,       77,       77,       76,       75,       74,       74, 
            73,       72,       72,       71,       70,       69,       69,       68, 
            67,       67,       66,       65,       65,       64,       63,       63, 
            62,       61,       61,       60,       59,       59,       58,       57, // 607
    
            57,       56,       55,       55,       54,       53,       53,       52, 
            52,       51,       50,       50,       49,       48,       48,       47, 
            47,       46,       45,       45,       44,       44,       43,       42, 
            42,       41,       41,       40,       40,       39,       38,       38, // 639
    
            37,       37,       36,       36,       35,       35,       34,       34, 
            33,       33,       32,       31,       31,       30,       30,       29, 
            29,       28,       28,       27,       27,       27,       26,       26, 
            25,       25,       24,       24,       23,       23,       22,       22, // 671
    
            21,       21,       21,       20,       20,       19,       19,       19, 
            18,       18,       17,       17,       17,       16,       16,       15, 
            15,       15,       14,       14,       14,       13,       13,       13, 
            12,       12,       12,       11,       11,       11,       10,       10, // 703
    
            10,        9,        9,        9,        9,        8,        8,        8, 
             7,        7,        7,        7,        6,        6,        6,        6, 
             5,        5,        5,        5,        5,        4,        4,        4, 
             4,        4,        3,        3,        3,        3,        3,        3, // 735
    
             2,        2,        2,        2,        2,        2,        2,        1, 
             1,        1,        1,        1,        1,        1,        1,        1, 
             1,        1,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        0, // 767
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             0,        0,        0,        0,        0,        0,        0,        1, 
             1,        1,        1,        1,        1,        1,        1,        1, 
             1,        1,        2,        2,        2,        2,        2,        2, // 799
    
             2,        3,        3,        3,        3,        3,        3,        4, 
             4,        4,        4,        4,        5,        5,        5,        5, 
             5,        6,        6,        6,        6,        7,        7,        7, 
             7,        8,        8,        8,        9,        9,        9,        9, // 831
    
            10,       10,       10,       11,       11,       11,       12,       12, 
            12,       13,       13,       13,       14,       14,       14,       15, 
            15,       15,       16,       16,       17,       17,       17,       18, 
            18,       19,       19,       19,       20,       20,       21,       21, // 863
    
            21,       22,       22,       23,       23,       24,       24,       25, 
            25,       26,       26,       27,       27,       27,       28,       28, 
            29,       29,       30,       30,       31,       31,       32,       33, 
            33,       34,       34,       35,       35,       36,       36,       37, // 895
    
            37,       38,       38,       39,       40,       40,       41,       41, 
            42,       42,       43,       44,       44,       45,       45,       46, 
            47,       47,       48,       48,       49,       50,       50,       51, 
            52,       52,       53,       53,       54,       55,       55,       56, // 927
    
            57,       57,       58,       59,       59,       60,       61,       61, 
            62,       63,       63,       64,       65,       65,       66,       67, 
            67,       68,       69,       69,       70,       71,       72,       72, 
            73,       74,       74,       75,       76,       77,       77,       78, // 959
    
            79,       79,       80,       81,       82,       82,       83,       84, 
            85,       85,       86,       87,       88,       88,       89,       90, 
            90,       91,       92,       93,       93,       94,       95,       96, 
            97,       97,       98,       99,      100,      100,      101,      102, // 991
    
           103,      103,      104,      105,      106,      106,      107,      108, 
           109,      110,      110,      111,      112,      113,      113,      114, 
           115,      116,      117,      117,      118,      119,      120,      120, 
           121,      122,      123,      124,      124,      125,      126,      127, // 1023
    
      };
    }
  }
}
#endif
