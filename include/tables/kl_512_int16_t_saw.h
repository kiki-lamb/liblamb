#ifndef kl_512_int16_t_saw_h
#define kl_512_int16_t_saw_h

#define KL_512_int16_t_saw_cells 512

namespace lamb {
  namespace Tables {
    namespace saw512_int16_t {
      typedef int16_t value_type;
      const   size_t length = 512;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,      127,      255,      383,      511,      639,      767,      895, 
          1023,     1151,     1279,     1407,     1535,     1663,     1791,     1919, 
          2047,     2175,     2303,     2431,     2559,     2687,     2815,     2943, 
          3071,     3199,     3327,     3455,     3583,     3711,     3839,     3967, // 31
    
          4095,     4223,     4351,     4479,     4607,     4735,     4863,     4991, 
          5119,     5247,     5375,     5503,     5631,     5759,     5887,     6015, 
          6143,     6271,     6399,     6527,     6655,     6783,     6911,     7039, 
          7167,     7295,     7423,     7551,     7679,     7807,     7935,     8063, // 63
    
          8191,     8319,     8447,     8575,     8703,     8831,     8959,     9087, 
          9215,     9343,     9471,     9599,     9727,     9855,     9983,    10111, 
         10239,    10367,    10495,    10623,    10751,    10879,    11007,    11135, 
         11263,    11391,    11519,    11647,    11775,    11903,    12031,    12159, // 95
    
         12287,    12415,    12543,    12671,    12799,    12927,    13055,    13183, 
         13311,    13439,    13567,    13695,    13823,    13951,    14079,    14207, 
         14335,    14463,    14591,    14719,    14847,    14975,    15103,    15231, 
         15359,    15487,    15615,    15743,    15871,    15999,    16127,    16255, // 127
    
         16383,    16511,    16639,    16767,    16895,    17023,    17151,    17279, 
         17407,    17535,    17663,    17791,    17919,    18047,    18175,    18303, 
         18431,    18559,    18687,    18815,    18943,    19071,    19199,    19327, 
         19455,    19583,    19711,    19839,    19967,    20095,    20223,    20351, // 159
    
         20479,    20607,    20735,    20863,    20991,    21119,    21247,    21375, 
         21503,    21631,    21759,    21887,    22015,    22143,    22271,    22399, 
         22527,    22655,    22783,    22911,    23039,    23167,    23295,    23423, 
         23551,    23679,    23807,    23935,    24063,    24191,    24319,    24447, // 191
    
         24575,    24703,    24831,    24959,    25087,    25215,    25343,    25471, 
         25599,    25727,    25855,    25983,    26111,    26239,    26367,    26495, 
         26623,    26751,    26879,    27007,    27135,    27263,    27391,    27519, 
         27647,    27775,    27903,    28031,    28159,    28287,    28415,    28543, // 223
    
         28671,    28799,    28927,    29055,    29183,    29311,    29439,    29567, 
         29695,    29823,    29951,    30079,    30207,    30335,    30463,    30591, 
         30719,    30847,    30975,    31103,    31231,    31359,    31487,    31615, 
         31743,    31871,    31999,    32127,    32255,    32383,    32511,    32639, // 255
    
         32767,   -32639,   -32511,   -32383,   -32255,   -32127,   -31999,   -31871, 
        -31743,   -31615,   -31487,   -31359,   -31231,   -31103,   -30975,   -30847, 
        -30719,   -30591,   -30463,   -30335,   -30207,   -30079,   -29951,   -29823, 
        -29695,   -29567,   -29439,   -29311,   -29183,   -29055,   -28927,   -28799, // 287
    
        -28671,   -28543,   -28415,   -28287,   -28159,   -28031,   -27903,   -27775, 
        -27647,   -27519,   -27391,   -27263,   -27135,   -27007,   -26879,   -26751, 
        -26623,   -26495,   -26367,   -26239,   -26111,   -25983,   -25855,   -25727, 
        -25599,   -25471,   -25343,   -25215,   -25087,   -24959,   -24831,   -24703, // 319
    
        -24575,   -24447,   -24319,   -24191,   -24063,   -23935,   -23807,   -23679, 
        -23551,   -23423,   -23295,   -23167,   -23039,   -22911,   -22783,   -22655, 
        -22527,   -22399,   -22271,   -22143,   -22015,   -21887,   -21759,   -21631, 
        -21503,   -21375,   -21247,   -21119,   -20991,   -20863,   -20735,   -20607, // 351
    
        -20479,   -20351,   -20223,   -20095,   -19967,   -19839,   -19711,   -19583, 
        -19455,   -19327,   -19199,   -19071,   -18943,   -18815,   -18687,   -18559, 
        -18431,   -18303,   -18175,   -18047,   -17919,   -17791,   -17663,   -17535, 
        -17407,   -17279,   -17151,   -17023,   -16895,   -16767,   -16639,   -16511, // 383
    
        -16383,   -16255,   -16127,   -15999,   -15871,   -15743,   -15615,   -15487, 
        -15359,   -15231,   -15103,   -14975,   -14847,   -14719,   -14591,   -14463, 
        -14335,   -14207,   -14079,   -13951,   -13823,   -13695,   -13567,   -13439, 
        -13311,   -13183,   -13055,   -12927,   -12799,   -12671,   -12543,   -12415, // 415
    
        -12287,   -12159,   -12031,   -11903,   -11775,   -11647,   -11519,   -11391, 
        -11263,   -11135,   -11007,   -10879,   -10751,   -10623,   -10495,   -10367, 
        -10239,   -10111,    -9983,    -9855,    -9727,    -9599,    -9471,    -9343, 
         -9215,    -9087,    -8959,    -8831,    -8703,    -8575,    -8447,    -8319, // 447
    
         -8191,    -8063,    -7935,    -7807,    -7679,    -7551,    -7423,    -7295, 
         -7167,    -7039,    -6911,    -6783,    -6655,    -6527,    -6399,    -6271, 
         -6143,    -6015,    -5887,    -5759,    -5631,    -5503,    -5375,    -5247, 
         -5119,    -4991,    -4863,    -4735,    -4607,    -4479,    -4351,    -4223, // 479
    
         -4095,    -3967,    -3839,    -3711,    -3583,    -3455,    -3327,    -3199, 
         -3071,    -2943,    -2815,    -2687,    -2559,    -2431,    -2303,    -2175, 
         -2047,    -1919,    -1791,    -1663,    -1535,    -1407,    -1279,    -1151, 
         -1023,     -895,     -767,     -639,     -511,     -383,     -255,     -127, // 511
    
      };
    }
  }
}
#endif
