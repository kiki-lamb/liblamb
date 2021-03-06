#ifndef kl_1024_uint16_t_tri_h
#define kl_1024_uint16_t_tri_h

#define KL_1024_uint16_t_tri_cells 1024

namespace lamb {
  namespace tables {
    namespace tri1024_uint16_t {
      typedef uint16_t value_type;
      const   size_t length = 1024;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
         32768,    32895,    33023,    33151,    33279,    33407,    33535,    33663, 
         33791,    33919,    34047,    34175,    34303,    34431,    34559,    34687, 
         34815,    34943,    35071,    35199,    35327,    35455,    35583,    35711, 
         35839,    35967,    36095,    36223,    36351,    36479,    36607,    36735, // 31
    
         36863,    36991,    37119,    37247,    37375,    37503,    37631,    37759, 
         37887,    38015,    38143,    38271,    38399,    38527,    38655,    38783, 
         38911,    39039,    39167,    39295,    39423,    39551,    39679,    39807, 
         39935,    40063,    40191,    40319,    40447,    40575,    40703,    40831, // 63
    
         40959,    41087,    41215,    41343,    41471,    41599,    41727,    41855, 
         41983,    42111,    42239,    42367,    42495,    42623,    42751,    42879, 
         43007,    43135,    43263,    43391,    43519,    43647,    43775,    43903, 
         44031,    44159,    44287,    44415,    44543,    44671,    44799,    44927, // 95
    
         45055,    45183,    45311,    45439,    45567,    45695,    45823,    45951, 
         46079,    46207,    46335,    46463,    46591,    46719,    46847,    46975, 
         47103,    47231,    47359,    47487,    47615,    47743,    47871,    47999, 
         48127,    48255,    48383,    48511,    48639,    48767,    48895,    49023, // 127
    
         49151,    49279,    49407,    49535,    49663,    49791,    49919,    50047, 
         50175,    50303,    50431,    50559,    50687,    50815,    50943,    51071, 
         51199,    51327,    51455,    51583,    51711,    51839,    51967,    52095, 
         52223,    52351,    52479,    52607,    52735,    52863,    52991,    53119, // 159
    
         53247,    53375,    53503,    53631,    53759,    53887,    54015,    54143, 
         54271,    54399,    54527,    54655,    54783,    54911,    55039,    55167, 
         55295,    55423,    55551,    55679,    55807,    55935,    56063,    56191, 
         56319,    56447,    56575,    56703,    56831,    56959,    57087,    57215, // 191
    
         57343,    57471,    57599,    57727,    57855,    57983,    58111,    58239, 
         58367,    58495,    58623,    58751,    58879,    59007,    59135,    59263, 
         59391,    59519,    59647,    59775,    59903,    60031,    60159,    60287, 
         60415,    60543,    60671,    60799,    60927,    61055,    61183,    61311, // 223
    
         61439,    61567,    61695,    61823,    61951,    62079,    62207,    62335, 
         62463,    62591,    62719,    62847,    62975,    63103,    63231,    63359, 
         63487,    63615,    63743,    63871,    63999,    64127,    64255,    64383, 
         64511,    64639,    64767,    64895,    65023,    65151,    65279,    65407, // 255
    
         65535,    65407,    65279,    65151,    65023,    64895,    64767,    64639, 
         64511,    64383,    64255,    64127,    63999,    63871,    63743,    63615, 
         63487,    63359,    63231,    63103,    62975,    62847,    62719,    62591, 
         62463,    62335,    62207,    62079,    61951,    61823,    61695,    61567, // 287
    
         61439,    61311,    61183,    61055,    60927,    60799,    60671,    60543, 
         60415,    60287,    60159,    60031,    59903,    59775,    59647,    59519, 
         59391,    59263,    59135,    59007,    58879,    58751,    58623,    58495, 
         58367,    58239,    58111,    57983,    57855,    57727,    57599,    57471, // 319
    
         57343,    57215,    57087,    56959,    56831,    56703,    56575,    56447, 
         56319,    56191,    56063,    55935,    55807,    55679,    55551,    55423, 
         55295,    55167,    55039,    54911,    54783,    54655,    54527,    54399, 
         54271,    54143,    54015,    53887,    53759,    53631,    53503,    53375, // 351
    
         53247,    53119,    52991,    52863,    52735,    52607,    52479,    52351, 
         52223,    52095,    51967,    51839,    51711,    51583,    51455,    51327, 
         51199,    51071,    50943,    50815,    50687,    50559,    50431,    50303, 
         50175,    50047,    49919,    49791,    49663,    49535,    49407,    49279, // 383
    
         49151,    49023,    48895,    48767,    48639,    48511,    48383,    48255, 
         48127,    47999,    47871,    47743,    47615,    47487,    47359,    47231, 
         47103,    46975,    46847,    46719,    46591,    46463,    46335,    46207, 
         46079,    45951,    45823,    45695,    45567,    45439,    45311,    45183, // 415
    
         45055,    44927,    44799,    44671,    44543,    44415,    44287,    44159, 
         44031,    43903,    43775,    43647,    43519,    43391,    43263,    43135, 
         43007,    42879,    42751,    42623,    42495,    42367,    42239,    42111, 
         41983,    41855,    41727,    41599,    41471,    41343,    41215,    41087, // 447
    
         40959,    40831,    40703,    40575,    40447,    40319,    40191,    40063, 
         39935,    39807,    39679,    39551,    39423,    39295,    39167,    39039, 
         38911,    38783,    38655,    38527,    38399,    38271,    38143,    38015, 
         37887,    37759,    37631,    37503,    37375,    37247,    37119,    36991, // 479
    
         36863,    36735,    36607,    36479,    36351,    36223,    36095,    35967, 
         35839,    35711,    35583,    35455,    35327,    35199,    35071,    34943, 
         34815,    34687,    34559,    34431,    34303,    34175,    34047,    33919, 
         33791,    33663,    33535,    33407,    33279,    33151,    33023,    32895, // 511
    
         32768,    32640,    32512,    32384,    32256,    32128,    32000,    31872, 
         31744,    31616,    31488,    31360,    31232,    31104,    30976,    30848, 
         30720,    30592,    30464,    30336,    30208,    30080,    29952,    29824, 
         29696,    29568,    29440,    29312,    29184,    29056,    28928,    28800, // 543
    
         28672,    28544,    28416,    28288,    28160,    28032,    27904,    27776, 
         27648,    27520,    27392,    27264,    27136,    27008,    26880,    26752, 
         26624,    26496,    26368,    26240,    26112,    25984,    25856,    25728, 
         25600,    25472,    25344,    25216,    25088,    24960,    24832,    24704, // 575
    
         24576,    24448,    24320,    24192,    24064,    23936,    23808,    23680, 
         23552,    23424,    23296,    23168,    23040,    22912,    22784,    22656, 
         22528,    22400,    22272,    22144,    22016,    21888,    21760,    21632, 
         21504,    21376,    21248,    21120,    20992,    20864,    20736,    20608, // 607
    
         20480,    20352,    20224,    20096,    19968,    19840,    19712,    19584, 
         19456,    19328,    19200,    19072,    18944,    18816,    18688,    18560, 
         18432,    18304,    18176,    18048,    17920,    17792,    17664,    17536, 
         17408,    17280,    17152,    17024,    16896,    16768,    16640,    16512, // 639
    
         16384,    16256,    16128,    16000,    15872,    15744,    15616,    15488, 
         15360,    15232,    15104,    14976,    14848,    14720,    14592,    14464, 
         14336,    14208,    14080,    13952,    13824,    13696,    13568,    13440, 
         13312,    13184,    13056,    12928,    12800,    12672,    12544,    12416, // 671
    
         12288,    12160,    12032,    11904,    11776,    11648,    11520,    11392, 
         11264,    11136,    11008,    10880,    10752,    10624,    10496,    10368, 
         10240,    10112,     9984,     9856,     9728,     9600,     9472,     9344, 
          9216,     9088,     8960,     8832,     8704,     8576,     8448,     8320, // 703
    
          8192,     8064,     7936,     7808,     7680,     7552,     7424,     7296, 
          7168,     7040,     6912,     6784,     6656,     6528,     6400,     6272, 
          6144,     6016,     5888,     5760,     5632,     5504,     5376,     5248, 
          5120,     4992,     4864,     4736,     4608,     4480,     4352,     4224, // 735
    
          4096,     3968,     3840,     3712,     3584,     3456,     3328,     3200, 
          3072,     2944,     2816,     2688,     2560,     2432,     2304,     2176, 
          2048,     1920,     1792,     1664,     1536,     1408,     1280,     1152, 
          1024,      896,      768,      640,      512,      384,      256,      128, // 767
    
             0,      128,      256,      384,      512,      640,      768,      896, 
          1024,     1152,     1280,     1408,     1536,     1664,     1792,     1920, 
          2048,     2176,     2304,     2432,     2560,     2688,     2816,     2944, 
          3072,     3200,     3328,     3456,     3584,     3712,     3840,     3968, // 799
    
          4096,     4224,     4352,     4480,     4608,     4736,     4864,     4992, 
          5120,     5248,     5376,     5504,     5632,     5760,     5888,     6016, 
          6144,     6272,     6400,     6528,     6656,     6784,     6912,     7040, 
          7168,     7296,     7424,     7552,     7680,     7808,     7936,     8064, // 831
    
          8192,     8320,     8448,     8576,     8704,     8832,     8960,     9088, 
          9216,     9344,     9472,     9600,     9728,     9856,     9984,    10112, 
         10240,    10368,    10496,    10624,    10752,    10880,    11008,    11136, 
         11264,    11392,    11520,    11648,    11776,    11904,    12032,    12160, // 863
    
         12288,    12416,    12544,    12672,    12800,    12928,    13056,    13184, 
         13312,    13440,    13568,    13696,    13824,    13952,    14080,    14208, 
         14336,    14464,    14592,    14720,    14848,    14976,    15104,    15232, 
         15360,    15488,    15616,    15744,    15872,    16000,    16128,    16256, // 895
    
         16384,    16512,    16640,    16768,    16896,    17024,    17152,    17280, 
         17408,    17536,    17664,    17792,    17920,    18048,    18176,    18304, 
         18432,    18560,    18688,    18816,    18944,    19072,    19200,    19328, 
         19456,    19584,    19712,    19840,    19968,    20096,    20224,    20352, // 927
    
         20480,    20608,    20736,    20864,    20992,    21120,    21248,    21376, 
         21504,    21632,    21760,    21888,    22016,    22144,    22272,    22400, 
         22528,    22656,    22784,    22912,    23040,    23168,    23296,    23424, 
         23552,    23680,    23808,    23936,    24064,    24192,    24320,    24448, // 959
    
         24576,    24704,    24832,    24960,    25088,    25216,    25344,    25472, 
         25600,    25728,    25856,    25984,    26112,    26240,    26368,    26496, 
         26624,    26752,    26880,    27008,    27136,    27264,    27392,    27520, 
         27648,    27776,    27904,    28032,    28160,    28288,    28416,    28544, // 991
    
         28672,    28800,    28928,    29056,    29184,    29312,    29440,    29568, 
         29696,    29824,    29952,    30080,    30208,    30336,    30464,    30592, 
         30720,    30848,    30976,    31104,    31232,    31360,    31488,    31616, 
         31744,    31872,    32000,    32128,    32256,    32384,    32512,    32640, // 1023
    
      };
    }
  }
}
#endif
