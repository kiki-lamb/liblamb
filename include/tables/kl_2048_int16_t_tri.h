#ifndef kl_2048_int16_t_tri_h
#define kl_2048_int16_t_tri_h

#define KL_2048_int16_t_tri_cells 2048

namespace lamb {
  namespace Tables {
    namespace tri2048_int16_t {
      typedef int16_t value_type;
      const   size_t length = 2048;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,       63,      127,      191,      255,      319,      383,      447, 
           511,      575,      639,      703,      767,      831,      895,      959, 
          1023,     1087,     1151,     1215,     1279,     1343,     1407,     1471, 
          1535,     1599,     1663,     1727,     1791,     1855,     1919,     1983, // 31
    
          2047,     2111,     2175,     2239,     2303,     2367,     2431,     2495, 
          2559,     2623,     2687,     2751,     2815,     2879,     2943,     3007, 
          3071,     3135,     3199,     3263,     3327,     3391,     3455,     3519, 
          3583,     3647,     3711,     3775,     3839,     3903,     3967,     4031, // 63
    
          4095,     4159,     4223,     4287,     4351,     4415,     4479,     4543, 
          4607,     4671,     4735,     4799,     4863,     4927,     4991,     5055, 
          5119,     5183,     5247,     5311,     5375,     5439,     5503,     5567, 
          5631,     5695,     5759,     5823,     5887,     5951,     6015,     6079, // 95
    
          6143,     6207,     6271,     6335,     6399,     6463,     6527,     6591, 
          6655,     6719,     6783,     6847,     6911,     6975,     7039,     7103, 
          7167,     7231,     7295,     7359,     7423,     7487,     7551,     7615, 
          7679,     7743,     7807,     7871,     7935,     7999,     8063,     8127, // 127
    
          8191,     8255,     8319,     8383,     8447,     8511,     8575,     8639, 
          8703,     8767,     8831,     8895,     8959,     9023,     9087,     9151, 
          9215,     9279,     9343,     9407,     9471,     9535,     9599,     9663, 
          9727,     9791,     9855,     9919,     9983,    10047,    10111,    10175, // 159
    
         10239,    10303,    10367,    10431,    10495,    10559,    10623,    10687, 
         10751,    10815,    10879,    10943,    11007,    11071,    11135,    11199, 
         11263,    11327,    11391,    11455,    11519,    11583,    11647,    11711, 
         11775,    11839,    11903,    11967,    12031,    12095,    12159,    12223, // 191
    
         12287,    12351,    12415,    12479,    12543,    12607,    12671,    12735, 
         12799,    12863,    12927,    12991,    13055,    13119,    13183,    13247, 
         13311,    13375,    13439,    13503,    13567,    13631,    13695,    13759, 
         13823,    13887,    13951,    14015,    14079,    14143,    14207,    14271, // 223
    
         14335,    14399,    14463,    14527,    14591,    14655,    14719,    14783, 
         14847,    14911,    14975,    15039,    15103,    15167,    15231,    15295, 
         15359,    15423,    15487,    15551,    15615,    15679,    15743,    15807, 
         15871,    15935,    15999,    16063,    16127,    16191,    16255,    16319, // 255
    
         16383,    16447,    16511,    16575,    16639,    16703,    16767,    16831, 
         16895,    16959,    17023,    17087,    17151,    17215,    17279,    17343, 
         17407,    17471,    17535,    17599,    17663,    17727,    17791,    17855, 
         17919,    17983,    18047,    18111,    18175,    18239,    18303,    18367, // 287
    
         18431,    18495,    18559,    18623,    18687,    18751,    18815,    18879, 
         18943,    19007,    19071,    19135,    19199,    19263,    19327,    19391, 
         19455,    19519,    19583,    19647,    19711,    19775,    19839,    19903, 
         19967,    20031,    20095,    20159,    20223,    20287,    20351,    20415, // 319
    
         20479,    20543,    20607,    20671,    20735,    20799,    20863,    20927, 
         20991,    21055,    21119,    21183,    21247,    21311,    21375,    21439, 
         21503,    21567,    21631,    21695,    21759,    21823,    21887,    21951, 
         22015,    22079,    22143,    22207,    22271,    22335,    22399,    22463, // 351
    
         22527,    22591,    22655,    22719,    22783,    22847,    22911,    22975, 
         23039,    23103,    23167,    23231,    23295,    23359,    23423,    23487, 
         23551,    23615,    23679,    23743,    23807,    23871,    23935,    23999, 
         24063,    24127,    24191,    24255,    24319,    24383,    24447,    24511, // 383
    
         24575,    24639,    24703,    24767,    24831,    24895,    24959,    25023, 
         25087,    25151,    25215,    25279,    25343,    25407,    25471,    25535, 
         25599,    25663,    25727,    25791,    25855,    25919,    25983,    26047, 
         26111,    26175,    26239,    26303,    26367,    26431,    26495,    26559, // 415
    
         26623,    26687,    26751,    26815,    26879,    26943,    27007,    27071, 
         27135,    27199,    27263,    27327,    27391,    27455,    27519,    27583, 
         27647,    27711,    27775,    27839,    27903,    27967,    28031,    28095, 
         28159,    28223,    28287,    28351,    28415,    28479,    28543,    28607, // 447
    
         28671,    28735,    28799,    28863,    28927,    28991,    29055,    29119, 
         29183,    29247,    29311,    29375,    29439,    29503,    29567,    29631, 
         29695,    29759,    29823,    29887,    29951,    30015,    30079,    30143, 
         30207,    30271,    30335,    30399,    30463,    30527,    30591,    30655, // 479
    
         30719,    30783,    30847,    30911,    30975,    31039,    31103,    31167, 
         31231,    31295,    31359,    31423,    31487,    31551,    31615,    31679, 
         31743,    31807,    31871,    31935,    31999,    32063,    32127,    32191, 
         32255,    32319,    32383,    32447,    32511,    32575,    32639,    32703, // 511
    
         32767,    32703,    32639,    32575,    32511,    32447,    32383,    32319, 
         32255,    32191,    32127,    32063,    31999,    31935,    31871,    31807, 
         31743,    31679,    31615,    31551,    31487,    31423,    31359,    31295, 
         31231,    31167,    31103,    31039,    30975,    30911,    30847,    30783, // 543
    
         30719,    30655,    30591,    30527,    30463,    30399,    30335,    30271, 
         30207,    30143,    30079,    30015,    29951,    29887,    29823,    29759, 
         29695,    29631,    29567,    29503,    29439,    29375,    29311,    29247, 
         29183,    29119,    29055,    28991,    28927,    28863,    28799,    28735, // 575
    
         28671,    28607,    28543,    28479,    28415,    28351,    28287,    28223, 
         28159,    28095,    28031,    27967,    27903,    27839,    27775,    27711, 
         27647,    27583,    27519,    27455,    27391,    27327,    27263,    27199, 
         27135,    27071,    27007,    26943,    26879,    26815,    26751,    26687, // 607
    
         26623,    26559,    26495,    26431,    26367,    26303,    26239,    26175, 
         26111,    26047,    25983,    25919,    25855,    25791,    25727,    25663, 
         25599,    25535,    25471,    25407,    25343,    25279,    25215,    25151, 
         25087,    25023,    24959,    24895,    24831,    24767,    24703,    24639, // 639
    
         24575,    24511,    24447,    24383,    24319,    24255,    24191,    24127, 
         24063,    23999,    23935,    23871,    23807,    23743,    23679,    23615, 
         23551,    23487,    23423,    23359,    23295,    23231,    23167,    23103, 
         23039,    22975,    22911,    22847,    22783,    22719,    22655,    22591, // 671
    
         22527,    22463,    22399,    22335,    22271,    22207,    22143,    22079, 
         22015,    21951,    21887,    21823,    21759,    21695,    21631,    21567, 
         21503,    21439,    21375,    21311,    21247,    21183,    21119,    21055, 
         20991,    20927,    20863,    20799,    20735,    20671,    20607,    20543, // 703
    
         20479,    20415,    20351,    20287,    20223,    20159,    20095,    20031, 
         19967,    19903,    19839,    19775,    19711,    19647,    19583,    19519, 
         19455,    19391,    19327,    19263,    19199,    19135,    19071,    19007, 
         18943,    18879,    18815,    18751,    18687,    18623,    18559,    18495, // 735
    
         18431,    18367,    18303,    18239,    18175,    18111,    18047,    17983, 
         17919,    17855,    17791,    17727,    17663,    17599,    17535,    17471, 
         17407,    17343,    17279,    17215,    17151,    17087,    17023,    16959, 
         16895,    16831,    16767,    16703,    16639,    16575,    16511,    16447, // 767
    
         16383,    16319,    16255,    16191,    16127,    16063,    15999,    15935, 
         15871,    15807,    15743,    15679,    15615,    15551,    15487,    15423, 
         15359,    15295,    15231,    15167,    15103,    15039,    14975,    14911, 
         14847,    14783,    14719,    14655,    14591,    14527,    14463,    14399, // 799
    
         14335,    14271,    14207,    14143,    14079,    14015,    13951,    13887, 
         13823,    13759,    13695,    13631,    13567,    13503,    13439,    13375, 
         13311,    13247,    13183,    13119,    13055,    12991,    12927,    12863, 
         12799,    12735,    12671,    12607,    12543,    12479,    12415,    12351, // 831
    
         12287,    12223,    12159,    12095,    12031,    11967,    11903,    11839, 
         11775,    11711,    11647,    11583,    11519,    11455,    11391,    11327, 
         11263,    11199,    11135,    11071,    11007,    10943,    10879,    10815, 
         10751,    10687,    10623,    10559,    10495,    10431,    10367,    10303, // 863
    
         10239,    10175,    10111,    10047,     9983,     9919,     9855,     9791, 
          9727,     9663,     9599,     9535,     9471,     9407,     9343,     9279, 
          9215,     9151,     9087,     9023,     8959,     8895,     8831,     8767, 
          8703,     8639,     8575,     8511,     8447,     8383,     8319,     8255, // 895
    
          8191,     8127,     8063,     7999,     7935,     7871,     7807,     7743, 
          7679,     7615,     7551,     7487,     7423,     7359,     7295,     7231, 
          7167,     7103,     7039,     6975,     6911,     6847,     6783,     6719, 
          6655,     6591,     6527,     6463,     6399,     6335,     6271,     6207, // 927
    
          6143,     6079,     6015,     5951,     5887,     5823,     5759,     5695, 
          5631,     5567,     5503,     5439,     5375,     5311,     5247,     5183, 
          5119,     5055,     4991,     4927,     4863,     4799,     4735,     4671, 
          4607,     4543,     4479,     4415,     4351,     4287,     4223,     4159, // 959
    
          4095,     4031,     3967,     3903,     3839,     3775,     3711,     3647, 
          3583,     3519,     3455,     3391,     3327,     3263,     3199,     3135, 
          3071,     3007,     2943,     2879,     2815,     2751,     2687,     2623, 
          2559,     2495,     2431,     2367,     2303,     2239,     2175,     2111, // 991
    
          2047,     1983,     1919,     1855,     1791,     1727,     1663,     1599, 
          1535,     1471,     1407,     1343,     1279,     1215,     1151,     1087, 
          1023,      959,      895,      831,      767,      703,      639,      575, 
           511,      447,      383,      319,      255,      191,      127,       63, // 1023
    
             0,      -63,     -127,     -191,     -255,     -319,     -383,     -447, 
          -511,     -575,     -639,     -703,     -767,     -831,     -895,     -959, 
         -1023,    -1087,    -1151,    -1215,    -1279,    -1343,    -1407,    -1471, 
         -1535,    -1599,    -1663,    -1727,    -1791,    -1855,    -1919,    -1983, // 1055
    
         -2047,    -2111,    -2175,    -2239,    -2303,    -2367,    -2431,    -2495, 
         -2559,    -2623,    -2687,    -2751,    -2815,    -2879,    -2943,    -3007, 
         -3071,    -3135,    -3199,    -3263,    -3327,    -3391,    -3455,    -3519, 
         -3583,    -3647,    -3711,    -3775,    -3839,    -3903,    -3967,    -4031, // 1087
    
         -4095,    -4159,    -4223,    -4287,    -4351,    -4415,    -4479,    -4543, 
         -4607,    -4671,    -4735,    -4799,    -4863,    -4927,    -4991,    -5055, 
         -5119,    -5183,    -5247,    -5311,    -5375,    -5439,    -5503,    -5567, 
         -5631,    -5695,    -5759,    -5823,    -5887,    -5951,    -6015,    -6079, // 1119
    
         -6143,    -6207,    -6271,    -6335,    -6399,    -6463,    -6527,    -6591, 
         -6655,    -6719,    -6783,    -6847,    -6911,    -6975,    -7039,    -7103, 
         -7167,    -7231,    -7295,    -7359,    -7423,    -7487,    -7551,    -7615, 
         -7679,    -7743,    -7807,    -7871,    -7935,    -7999,    -8063,    -8127, // 1151
    
         -8191,    -8255,    -8319,    -8383,    -8447,    -8511,    -8575,    -8639, 
         -8703,    -8767,    -8831,    -8895,    -8959,    -9023,    -9087,    -9151, 
         -9215,    -9279,    -9343,    -9407,    -9471,    -9535,    -9599,    -9663, 
         -9727,    -9791,    -9855,    -9919,    -9983,   -10047,   -10111,   -10175, // 1183
    
        -10239,   -10303,   -10367,   -10431,   -10495,   -10559,   -10623,   -10687, 
        -10751,   -10815,   -10879,   -10943,   -11007,   -11071,   -11135,   -11199, 
        -11263,   -11327,   -11391,   -11455,   -11519,   -11583,   -11647,   -11711, 
        -11775,   -11839,   -11903,   -11967,   -12031,   -12095,   -12159,   -12223, // 1215
    
        -12287,   -12351,   -12415,   -12479,   -12543,   -12607,   -12671,   -12735, 
        -12799,   -12863,   -12927,   -12991,   -13055,   -13119,   -13183,   -13247, 
        -13311,   -13375,   -13439,   -13503,   -13567,   -13631,   -13695,   -13759, 
        -13823,   -13887,   -13951,   -14015,   -14079,   -14143,   -14207,   -14271, // 1247
    
        -14335,   -14399,   -14463,   -14527,   -14591,   -14655,   -14719,   -14783, 
        -14847,   -14911,   -14975,   -15039,   -15103,   -15167,   -15231,   -15295, 
        -15359,   -15423,   -15487,   -15551,   -15615,   -15679,   -15743,   -15807, 
        -15871,   -15935,   -15999,   -16063,   -16127,   -16191,   -16255,   -16319, // 1279
    
        -16383,   -16447,   -16511,   -16575,   -16639,   -16703,   -16767,   -16831, 
        -16895,   -16959,   -17023,   -17087,   -17151,   -17215,   -17279,   -17343, 
        -17407,   -17471,   -17535,   -17599,   -17663,   -17727,   -17791,   -17855, 
        -17919,   -17983,   -18047,   -18111,   -18175,   -18239,   -18303,   -18367, // 1311
    
        -18431,   -18495,   -18559,   -18623,   -18687,   -18751,   -18815,   -18879, 
        -18943,   -19007,   -19071,   -19135,   -19199,   -19263,   -19327,   -19391, 
        -19455,   -19519,   -19583,   -19647,   -19711,   -19775,   -19839,   -19903, 
        -19967,   -20031,   -20095,   -20159,   -20223,   -20287,   -20351,   -20415, // 1343
    
        -20479,   -20543,   -20607,   -20671,   -20735,   -20799,   -20863,   -20927, 
        -20991,   -21055,   -21119,   -21183,   -21247,   -21311,   -21375,   -21439, 
        -21503,   -21567,   -21631,   -21695,   -21759,   -21823,   -21887,   -21951, 
        -22015,   -22079,   -22143,   -22207,   -22271,   -22335,   -22399,   -22463, // 1375
    
        -22527,   -22591,   -22655,   -22719,   -22783,   -22847,   -22911,   -22975, 
        -23039,   -23103,   -23167,   -23231,   -23295,   -23359,   -23423,   -23487, 
        -23551,   -23615,   -23679,   -23743,   -23807,   -23871,   -23935,   -23999, 
        -24063,   -24127,   -24191,   -24255,   -24319,   -24383,   -24447,   -24511, // 1407
    
        -24575,   -24639,   -24703,   -24767,   -24831,   -24895,   -24959,   -25023, 
        -25087,   -25151,   -25215,   -25279,   -25343,   -25407,   -25471,   -25535, 
        -25599,   -25663,   -25727,   -25791,   -25855,   -25919,   -25983,   -26047, 
        -26111,   -26175,   -26239,   -26303,   -26367,   -26431,   -26495,   -26559, // 1439
    
        -26623,   -26687,   -26751,   -26815,   -26879,   -26943,   -27007,   -27071, 
        -27135,   -27199,   -27263,   -27327,   -27391,   -27455,   -27519,   -27583, 
        -27647,   -27711,   -27775,   -27839,   -27903,   -27967,   -28031,   -28095, 
        -28159,   -28223,   -28287,   -28351,   -28415,   -28479,   -28543,   -28607, // 1471
    
        -28671,   -28735,   -28799,   -28863,   -28927,   -28991,   -29055,   -29119, 
        -29183,   -29247,   -29311,   -29375,   -29439,   -29503,   -29567,   -29631, 
        -29695,   -29759,   -29823,   -29887,   -29951,   -30015,   -30079,   -30143, 
        -30207,   -30271,   -30335,   -30399,   -30463,   -30527,   -30591,   -30655, // 1503
    
        -30719,   -30783,   -30847,   -30911,   -30975,   -31039,   -31103,   -31167, 
        -31231,   -31295,   -31359,   -31423,   -31487,   -31551,   -31615,   -31679, 
        -31743,   -31807,   -31871,   -31935,   -31999,   -32063,   -32127,   -32191, 
        -32255,   -32319,   -32383,   -32447,   -32511,   -32575,   -32639,   -32703, // 1535
    
        -32767,   -32703,   -32639,   -32575,   -32511,   -32447,   -32383,   -32319, 
        -32255,   -32191,   -32127,   -32063,   -31999,   -31935,   -31871,   -31807, 
        -31743,   -31679,   -31615,   -31551,   -31487,   -31423,   -31359,   -31295, 
        -31231,   -31167,   -31103,   -31039,   -30975,   -30911,   -30847,   -30783, // 1567
    
        -30719,   -30655,   -30591,   -30527,   -30463,   -30399,   -30335,   -30271, 
        -30207,   -30143,   -30079,   -30015,   -29951,   -29887,   -29823,   -29759, 
        -29695,   -29631,   -29567,   -29503,   -29439,   -29375,   -29311,   -29247, 
        -29183,   -29119,   -29055,   -28991,   -28927,   -28863,   -28799,   -28735, // 1599
    
        -28671,   -28607,   -28543,   -28479,   -28415,   -28351,   -28287,   -28223, 
        -28159,   -28095,   -28031,   -27967,   -27903,   -27839,   -27775,   -27711, 
        -27647,   -27583,   -27519,   -27455,   -27391,   -27327,   -27263,   -27199, 
        -27135,   -27071,   -27007,   -26943,   -26879,   -26815,   -26751,   -26687, // 1631
    
        -26623,   -26559,   -26495,   -26431,   -26367,   -26303,   -26239,   -26175, 
        -26111,   -26047,   -25983,   -25919,   -25855,   -25791,   -25727,   -25663, 
        -25599,   -25535,   -25471,   -25407,   -25343,   -25279,   -25215,   -25151, 
        -25087,   -25023,   -24959,   -24895,   -24831,   -24767,   -24703,   -24639, // 1663
    
        -24575,   -24511,   -24447,   -24383,   -24319,   -24255,   -24191,   -24127, 
        -24063,   -23999,   -23935,   -23871,   -23807,   -23743,   -23679,   -23615, 
        -23551,   -23487,   -23423,   -23359,   -23295,   -23231,   -23167,   -23103, 
        -23039,   -22975,   -22911,   -22847,   -22783,   -22719,   -22655,   -22591, // 1695
    
        -22527,   -22463,   -22399,   -22335,   -22271,   -22207,   -22143,   -22079, 
        -22015,   -21951,   -21887,   -21823,   -21759,   -21695,   -21631,   -21567, 
        -21503,   -21439,   -21375,   -21311,   -21247,   -21183,   -21119,   -21055, 
        -20991,   -20927,   -20863,   -20799,   -20735,   -20671,   -20607,   -20543, // 1727
    
        -20479,   -20415,   -20351,   -20287,   -20223,   -20159,   -20095,   -20031, 
        -19967,   -19903,   -19839,   -19775,   -19711,   -19647,   -19583,   -19519, 
        -19455,   -19391,   -19327,   -19263,   -19199,   -19135,   -19071,   -19007, 
        -18943,   -18879,   -18815,   -18751,   -18687,   -18623,   -18559,   -18495, // 1759
    
        -18431,   -18367,   -18303,   -18239,   -18175,   -18111,   -18047,   -17983, 
        -17919,   -17855,   -17791,   -17727,   -17663,   -17599,   -17535,   -17471, 
        -17407,   -17343,   -17279,   -17215,   -17151,   -17087,   -17023,   -16959, 
        -16895,   -16831,   -16767,   -16703,   -16639,   -16575,   -16511,   -16447, // 1791
    
        -16383,   -16319,   -16255,   -16191,   -16127,   -16063,   -15999,   -15935, 
        -15871,   -15807,   -15743,   -15679,   -15615,   -15551,   -15487,   -15423, 
        -15359,   -15295,   -15231,   -15167,   -15103,   -15039,   -14975,   -14911, 
        -14847,   -14783,   -14719,   -14655,   -14591,   -14527,   -14463,   -14399, // 1823
    
        -14335,   -14271,   -14207,   -14143,   -14079,   -14015,   -13951,   -13887, 
        -13823,   -13759,   -13695,   -13631,   -13567,   -13503,   -13439,   -13375, 
        -13311,   -13247,   -13183,   -13119,   -13055,   -12991,   -12927,   -12863, 
        -12799,   -12735,   -12671,   -12607,   -12543,   -12479,   -12415,   -12351, // 1855
    
        -12287,   -12223,   -12159,   -12095,   -12031,   -11967,   -11903,   -11839, 
        -11775,   -11711,   -11647,   -11583,   -11519,   -11455,   -11391,   -11327, 
        -11263,   -11199,   -11135,   -11071,   -11007,   -10943,   -10879,   -10815, 
        -10751,   -10687,   -10623,   -10559,   -10495,   -10431,   -10367,   -10303, // 1887
    
        -10239,   -10175,   -10111,   -10047,    -9983,    -9919,    -9855,    -9791, 
         -9727,    -9663,    -9599,    -9535,    -9471,    -9407,    -9343,    -9279, 
         -9215,    -9151,    -9087,    -9023,    -8959,    -8895,    -8831,    -8767, 
         -8703,    -8639,    -8575,    -8511,    -8447,    -8383,    -8319,    -8255, // 1919
    
         -8191,    -8127,    -8063,    -7999,    -7935,    -7871,    -7807,    -7743, 
         -7679,    -7615,    -7551,    -7487,    -7423,    -7359,    -7295,    -7231, 
         -7167,    -7103,    -7039,    -6975,    -6911,    -6847,    -6783,    -6719, 
         -6655,    -6591,    -6527,    -6463,    -6399,    -6335,    -6271,    -6207, // 1951
    
         -6143,    -6079,    -6015,    -5951,    -5887,    -5823,    -5759,    -5695, 
         -5631,    -5567,    -5503,    -5439,    -5375,    -5311,    -5247,    -5183, 
         -5119,    -5055,    -4991,    -4927,    -4863,    -4799,    -4735,    -4671, 
         -4607,    -4543,    -4479,    -4415,    -4351,    -4287,    -4223,    -4159, // 1983
    
         -4095,    -4031,    -3967,    -3903,    -3839,    -3775,    -3711,    -3647, 
         -3583,    -3519,    -3455,    -3391,    -3327,    -3263,    -3199,    -3135, 
         -3071,    -3007,    -2943,    -2879,    -2815,    -2751,    -2687,    -2623, 
         -2559,    -2495,    -2431,    -2367,    -2303,    -2239,    -2175,    -2111, // 2015
    
         -2047,    -1983,    -1919,    -1855,    -1791,    -1727,    -1663,    -1599, 
         -1535,    -1471,    -1407,    -1343,    -1279,    -1215,    -1151,    -1087, 
         -1023,     -959,     -895,     -831,     -767,     -703,     -639,     -575, 
          -511,     -447,     -383,     -319,     -255,     -191,     -127,      -63, // 2047
    
      };
    }
  }
}
#endif
