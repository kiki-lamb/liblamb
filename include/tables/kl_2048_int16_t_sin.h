#ifndef kl_2048_int16_t_sin_h
#define kl_2048_int16_t_sin_h

#define KL_2048_int16_t_sin_cells 2048

namespace lamb {
  namespace Tables {
    namespace sin2048_int16_t {
      typedef int16_t value_type;
      const   size_t length = 2048;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,      100,      201,      301,      402,      502,      603,      703, 
           804,      904,     1005,     1105,     1206,     1306,     1406,     1507, 
          1607,     1708,     1808,     1908,     2009,     2109,     2209,     2310, 
          2410,     2510,     2610,     2711,     2811,     2911,     3011,     3111, // 31
    
          3211,     3311,     3411,     3511,     3611,     3711,     3811,     3911, 
          4011,     4110,     4210,     4310,     4409,     4509,     4609,     4708, 
          4807,     4907,     5006,     5106,     5205,     5304,     5403,     5502, 
          5601,     5701,     5799,     5898,     5997,     6096,     6195,     6293, // 63
    
          6392,     6491,     6589,     6688,     6786,     6884,     6983,     7081, 
          7179,     7277,     7375,     7473,     7571,     7668,     7766,     7864, 
          7961,     8059,     8156,     8254,     8351,     8448,     8545,     8642, 
          8739,     8836,     8933,     9029,     9126,     9222,     9319,     9415, // 95
    
          9511,     9608,     9704,     9800,     9895,     9991,    10087,    10183, 
         10278,    10373,    10469,    10564,    10659,    10754,    10849,    10944, 
         11039,    11133,    11228,    11322,    11416,    11510,    11605,    11699, 
         11792,    11886,    11980,    12073,    12167,    12260,    12353,    12446, // 127
    
         12539,    12632,    12725,    12817,    12910,    13002,    13094,    13186, 
         13278,    13370,    13462,    13553,    13645,    13736,    13827,    13918, 
         14009,    14100,    14191,    14281,    14372,    14462,    14552,    14642, 
         14732,    14822,    14911,    15001,    15090,    15179,    15268,    15357, // 159
    
         15446,    15535,    15623,    15711,    15799,    15887,    15975,    16063, 
         16151,    16238,    16325,    16412,    16499,    16586,    16673,    16759, 
         16845,    16932,    17017,    17103,    17189,    17274,    17360,    17445, 
         17530,    17615,    17700,    17784,    17868,    17953,    18037,    18120, // 191
    
         18204,    18288,    18371,    18454,    18537,    18620,    18703,    18785, 
         18867,    18949,    19031,    19113,    19195,    19276,    19357,    19438, 
         19519,    19600,    19680,    19760,    19841,    19920,    20000,    20080, 
         20159,    20238,    20317,    20396,    20475,    20553,    20631,    20709, // 223
    
         20787,    20865,    20942,    21019,    21096,    21173,    21250,    21326, 
         21402,    21478,    21554,    21630,    21705,    21780,    21855,    21930, 
         22005,    22079,    22153,    22227,    22301,    22375,    22448,    22521, 
         22594,    22667,    22739,    22811,    22884,    22955,    23027,    23098, // 255
    
         23170,    23241,    23311,    23382,    23452,    23522,    23592,    23662, 
         23731,    23800,    23869,    23938,    24007,    24075,    24143,    24211, 
         24279,    24346,    24413,    24480,    24547,    24613,    24680,    24746, 
         24811,    24877,    24942,    25007,    25072,    25137,    25201,    25265, // 287
    
         25329,    25393,    25456,    25519,    25582,    25645,    25707,    25770, 
         25832,    25893,    25955,    26016,    26077,    26138,    26198,    26259, 
         26319,    26378,    26438,    26497,    26556,    26615,    26673,    26732, 
         26790,    26847,    26905,    26962,    27019,    27076,    27132,    27189, // 319
    
         27245,    27300,    27356,    27411,    27466,    27521,    27575,    27629, 
         27683,    27737,    27790,    27843,    27896,    27949,    28001,    28053, 
         28105,    28157,    28208,    28259,    28310,    28360,    28410,    28460, 
         28510,    28559,    28609,    28658,    28706,    28754,    28803,    28850, // 351
    
         28898,    28945,    28992,    29039,    29085,    29131,    29177,    29223, 
         29268,    29313,    29358,    29403,    29447,    29491,    29534,    29578, 
         29621,    29664,    29706,    29749,    29791,    29832,    29874,    29915, 
         29956,    29996,    30037,    30077,    30117,    30156,    30195,    30234, // 383
    
         30273,    30311,    30349,    30387,    30424,    30462,    30498,    30535, 
         30571,    30607,    30643,    30679,    30714,    30749,    30783,    30818, 
         30852,    30885,    30919,    30952,    30985,    31017,    31050,    31081, 
         31113,    31145,    31176,    31206,    31237,    31267,    31297,    31327, // 415
    
         31356,    31385,    31414,    31442,    31470,    31498,    31526,    31553, 
         31580,    31607,    31633,    31659,    31685,    31710,    31736,    31760, 
         31785,    31809,    31833,    31857,    31880,    31903,    31926,    31949, 
         31971,    31993,    32014,    32036,    32057,    32077,    32098,    32118, // 447
    
         32137,    32157,    32176,    32195,    32213,    32232,    32250,    32267, 
         32285,    32302,    32318,    32335,    32351,    32367,    32382,    32397, 
         32412,    32427,    32441,    32455,    32469,    32482,    32495,    32508, 
         32521,    32533,    32545,    32556,    32567,    32578,    32589,    32599, // 479
    
         32609,    32619,    32628,    32637,    32646,    32655,    32663,    32671, 
         32678,    32685,    32692,    32699,    32705,    32711,    32717,    32722, 
         32728,    32732,    32737,    32741,    32745,    32748,    32752,    32755, 
         32757,    32759,    32761,    32763,    32765,    32766,    32766,    32767, // 511
    
         32767,    32767,    32766,    32766,    32765,    32763,    32761,    32759, 
         32757,    32755,    32752,    32748,    32745,    32741,    32737,    32732, 
         32728,    32722,    32717,    32711,    32705,    32699,    32692,    32685, 
         32678,    32671,    32663,    32655,    32646,    32637,    32628,    32619, // 543
    
         32609,    32599,    32589,    32578,    32567,    32556,    32545,    32533, 
         32521,    32508,    32495,    32482,    32469,    32455,    32441,    32427, 
         32412,    32397,    32382,    32367,    32351,    32335,    32318,    32302, 
         32285,    32267,    32250,    32232,    32213,    32195,    32176,    32157, // 575
    
         32137,    32118,    32098,    32077,    32057,    32036,    32014,    31993, 
         31971,    31949,    31926,    31903,    31880,    31857,    31833,    31809, 
         31785,    31760,    31736,    31710,    31685,    31659,    31633,    31607, 
         31580,    31553,    31526,    31498,    31470,    31442,    31414,    31385, // 607
    
         31356,    31327,    31297,    31267,    31237,    31206,    31176,    31145, 
         31113,    31081,    31050,    31017,    30985,    30952,    30919,    30885, 
         30852,    30818,    30783,    30749,    30714,    30679,    30643,    30607, 
         30571,    30535,    30498,    30462,    30424,    30387,    30349,    30311, // 639
    
         30273,    30234,    30195,    30156,    30117,    30077,    30037,    29996, 
         29956,    29915,    29874,    29832,    29791,    29749,    29706,    29664, 
         29621,    29578,    29534,    29491,    29447,    29403,    29358,    29313, 
         29268,    29223,    29177,    29131,    29085,    29039,    28992,    28945, // 671
    
         28898,    28850,    28803,    28754,    28706,    28658,    28609,    28559, 
         28510,    28460,    28410,    28360,    28310,    28259,    28208,    28157, 
         28105,    28053,    28001,    27949,    27896,    27843,    27790,    27737, 
         27683,    27629,    27575,    27521,    27466,    27411,    27356,    27300, // 703
    
         27245,    27189,    27132,    27076,    27019,    26962,    26905,    26847, 
         26790,    26732,    26673,    26615,    26556,    26497,    26438,    26378, 
         26319,    26259,    26198,    26138,    26077,    26016,    25955,    25893, 
         25832,    25770,    25707,    25645,    25582,    25519,    25456,    25393, // 735
    
         25329,    25265,    25201,    25137,    25072,    25007,    24942,    24877, 
         24811,    24746,    24680,    24613,    24547,    24480,    24413,    24346, 
         24279,    24211,    24143,    24075,    24007,    23938,    23869,    23800, 
         23731,    23662,    23592,    23522,    23452,    23382,    23311,    23241, // 767
    
         23170,    23098,    23027,    22955,    22884,    22811,    22739,    22667, 
         22594,    22521,    22448,    22375,    22301,    22227,    22153,    22079, 
         22005,    21930,    21855,    21780,    21705,    21630,    21554,    21478, 
         21402,    21326,    21250,    21173,    21096,    21019,    20942,    20865, // 799
    
         20787,    20709,    20631,    20553,    20475,    20396,    20317,    20238, 
         20159,    20080,    20000,    19920,    19841,    19760,    19680,    19600, 
         19519,    19438,    19357,    19276,    19195,    19113,    19031,    18949, 
         18867,    18785,    18703,    18620,    18537,    18454,    18371,    18288, // 831
    
         18204,    18120,    18037,    17953,    17868,    17784,    17700,    17615, 
         17530,    17445,    17360,    17274,    17189,    17103,    17017,    16932, 
         16845,    16759,    16673,    16586,    16499,    16412,    16325,    16238, 
         16151,    16063,    15975,    15887,    15799,    15711,    15623,    15535, // 863
    
         15446,    15357,    15268,    15179,    15090,    15001,    14911,    14822, 
         14732,    14642,    14552,    14462,    14372,    14281,    14191,    14100, 
         14009,    13918,    13827,    13736,    13645,    13553,    13462,    13370, 
         13278,    13186,    13094,    13002,    12910,    12817,    12725,    12632, // 895
    
         12539,    12446,    12353,    12260,    12167,    12073,    11980,    11886, 
         11792,    11699,    11605,    11510,    11416,    11322,    11228,    11133, 
         11039,    10944,    10849,    10754,    10659,    10564,    10469,    10373, 
         10278,    10183,    10087,     9991,     9895,     9800,     9704,     9608, // 927
    
          9511,     9415,     9319,     9222,     9126,     9029,     8933,     8836, 
          8739,     8642,     8545,     8448,     8351,     8254,     8156,     8059, 
          7961,     7864,     7766,     7668,     7571,     7473,     7375,     7277, 
          7179,     7081,     6983,     6884,     6786,     6688,     6589,     6491, // 959
    
          6392,     6293,     6195,     6096,     5997,     5898,     5799,     5701, 
          5601,     5502,     5403,     5304,     5205,     5106,     5006,     4907, 
          4807,     4708,     4609,     4509,     4409,     4310,     4210,     4110, 
          4011,     3911,     3811,     3711,     3611,     3511,     3411,     3311, // 991
    
          3211,     3111,     3011,     2911,     2811,     2711,     2610,     2510, 
          2410,     2310,     2209,     2109,     2009,     1908,     1808,     1708, 
          1607,     1507,     1406,     1306,     1206,     1105,     1005,      904, 
           804,      703,      603,      502,      402,      301,      201,      100, // 1023
    
             0,     -100,     -201,     -301,     -402,     -502,     -603,     -703, 
          -804,     -904,    -1005,    -1105,    -1206,    -1306,    -1406,    -1507, 
         -1607,    -1708,    -1808,    -1908,    -2009,    -2109,    -2209,    -2310, 
         -2410,    -2510,    -2610,    -2711,    -2811,    -2911,    -3011,    -3111, // 1055
    
         -3211,    -3311,    -3411,    -3511,    -3611,    -3711,    -3811,    -3911, 
         -4011,    -4110,    -4210,    -4310,    -4409,    -4509,    -4609,    -4708, 
         -4807,    -4907,    -5006,    -5106,    -5205,    -5304,    -5403,    -5502, 
         -5601,    -5701,    -5799,    -5898,    -5997,    -6096,    -6195,    -6293, // 1087
    
         -6392,    -6491,    -6589,    -6688,    -6786,    -6884,    -6983,    -7081, 
         -7179,    -7277,    -7375,    -7473,    -7571,    -7668,    -7766,    -7864, 
         -7961,    -8059,    -8156,    -8254,    -8351,    -8448,    -8545,    -8642, 
         -8739,    -8836,    -8933,    -9029,    -9126,    -9222,    -9319,    -9415, // 1119
    
         -9511,    -9608,    -9704,    -9800,    -9895,    -9991,   -10087,   -10183, 
        -10278,   -10373,   -10469,   -10564,   -10659,   -10754,   -10849,   -10944, 
        -11039,   -11133,   -11228,   -11322,   -11416,   -11510,   -11605,   -11699, 
        -11792,   -11886,   -11980,   -12073,   -12167,   -12260,   -12353,   -12446, // 1151
    
        -12539,   -12632,   -12725,   -12817,   -12910,   -13002,   -13094,   -13186, 
        -13278,   -13370,   -13462,   -13553,   -13645,   -13736,   -13827,   -13918, 
        -14009,   -14100,   -14191,   -14281,   -14372,   -14462,   -14552,   -14642, 
        -14732,   -14822,   -14911,   -15001,   -15090,   -15179,   -15268,   -15357, // 1183
    
        -15446,   -15535,   -15623,   -15711,   -15799,   -15887,   -15975,   -16063, 
        -16151,   -16238,   -16325,   -16412,   -16499,   -16586,   -16673,   -16759, 
        -16845,   -16932,   -17017,   -17103,   -17189,   -17274,   -17360,   -17445, 
        -17530,   -17615,   -17700,   -17784,   -17868,   -17953,   -18037,   -18120, // 1215
    
        -18204,   -18288,   -18371,   -18454,   -18537,   -18620,   -18703,   -18785, 
        -18867,   -18949,   -19031,   -19113,   -19195,   -19276,   -19357,   -19438, 
        -19519,   -19600,   -19680,   -19760,   -19841,   -19920,   -20000,   -20080, 
        -20159,   -20238,   -20317,   -20396,   -20475,   -20553,   -20631,   -20709, // 1247
    
        -20787,   -20865,   -20942,   -21019,   -21096,   -21173,   -21250,   -21326, 
        -21402,   -21478,   -21554,   -21630,   -21705,   -21780,   -21855,   -21930, 
        -22005,   -22079,   -22153,   -22227,   -22301,   -22375,   -22448,   -22521, 
        -22594,   -22667,   -22739,   -22811,   -22884,   -22955,   -23027,   -23098, // 1279
    
        -23170,   -23241,   -23311,   -23382,   -23452,   -23522,   -23592,   -23662, 
        -23731,   -23800,   -23869,   -23938,   -24007,   -24075,   -24143,   -24211, 
        -24279,   -24346,   -24413,   -24480,   -24547,   -24613,   -24680,   -24746, 
        -24811,   -24877,   -24942,   -25007,   -25072,   -25137,   -25201,   -25265, // 1311
    
        -25329,   -25393,   -25456,   -25519,   -25582,   -25645,   -25707,   -25770, 
        -25832,   -25893,   -25955,   -26016,   -26077,   -26138,   -26198,   -26259, 
        -26319,   -26378,   -26438,   -26497,   -26556,   -26615,   -26673,   -26732, 
        -26790,   -26847,   -26905,   -26962,   -27019,   -27076,   -27132,   -27189, // 1343
    
        -27245,   -27300,   -27356,   -27411,   -27466,   -27521,   -27575,   -27629, 
        -27683,   -27737,   -27790,   -27843,   -27896,   -27949,   -28001,   -28053, 
        -28105,   -28157,   -28208,   -28259,   -28310,   -28360,   -28410,   -28460, 
        -28510,   -28559,   -28609,   -28658,   -28706,   -28754,   -28803,   -28850, // 1375
    
        -28898,   -28945,   -28992,   -29039,   -29085,   -29131,   -29177,   -29223, 
        -29268,   -29313,   -29358,   -29403,   -29447,   -29491,   -29534,   -29578, 
        -29621,   -29664,   -29706,   -29749,   -29791,   -29832,   -29874,   -29915, 
        -29956,   -29996,   -30037,   -30077,   -30117,   -30156,   -30195,   -30234, // 1407
    
        -30273,   -30311,   -30349,   -30387,   -30424,   -30462,   -30498,   -30535, 
        -30571,   -30607,   -30643,   -30679,   -30714,   -30749,   -30783,   -30818, 
        -30852,   -30885,   -30919,   -30952,   -30985,   -31017,   -31050,   -31081, 
        -31113,   -31145,   -31176,   -31206,   -31237,   -31267,   -31297,   -31327, // 1439
    
        -31356,   -31385,   -31414,   -31442,   -31470,   -31498,   -31526,   -31553, 
        -31580,   -31607,   -31633,   -31659,   -31685,   -31710,   -31736,   -31760, 
        -31785,   -31809,   -31833,   -31857,   -31880,   -31903,   -31926,   -31949, 
        -31971,   -31993,   -32014,   -32036,   -32057,   -32077,   -32098,   -32118, // 1471
    
        -32137,   -32157,   -32176,   -32195,   -32213,   -32232,   -32250,   -32267, 
        -32285,   -32302,   -32318,   -32335,   -32351,   -32367,   -32382,   -32397, 
        -32412,   -32427,   -32441,   -32455,   -32469,   -32482,   -32495,   -32508, 
        -32521,   -32533,   -32545,   -32556,   -32567,   -32578,   -32589,   -32599, // 1503
    
        -32609,   -32619,   -32628,   -32637,   -32646,   -32655,   -32663,   -32671, 
        -32678,   -32685,   -32692,   -32699,   -32705,   -32711,   -32717,   -32722, 
        -32728,   -32732,   -32737,   -32741,   -32745,   -32748,   -32752,   -32755, 
        -32757,   -32759,   -32761,   -32763,   -32765,   -32766,   -32766,   -32767, // 1535
    
        -32767,   -32767,   -32766,   -32766,   -32765,   -32763,   -32761,   -32759, 
        -32757,   -32755,   -32752,   -32748,   -32745,   -32741,   -32737,   -32732, 
        -32728,   -32722,   -32717,   -32711,   -32705,   -32699,   -32692,   -32685, 
        -32678,   -32671,   -32663,   -32655,   -32646,   -32637,   -32628,   -32619, // 1567
    
        -32609,   -32599,   -32589,   -32578,   -32567,   -32556,   -32545,   -32533, 
        -32521,   -32508,   -32495,   -32482,   -32469,   -32455,   -32441,   -32427, 
        -32412,   -32397,   -32382,   -32367,   -32351,   -32335,   -32318,   -32302, 
        -32285,   -32267,   -32250,   -32232,   -32213,   -32195,   -32176,   -32157, // 1599
    
        -32137,   -32118,   -32098,   -32077,   -32057,   -32036,   -32014,   -31993, 
        -31971,   -31949,   -31926,   -31903,   -31880,   -31857,   -31833,   -31809, 
        -31785,   -31760,   -31736,   -31710,   -31685,   -31659,   -31633,   -31607, 
        -31580,   -31553,   -31526,   -31498,   -31470,   -31442,   -31414,   -31385, // 1631
    
        -31356,   -31327,   -31297,   -31267,   -31237,   -31206,   -31176,   -31145, 
        -31113,   -31081,   -31050,   -31017,   -30985,   -30952,   -30919,   -30885, 
        -30852,   -30818,   -30783,   -30749,   -30714,   -30679,   -30643,   -30607, 
        -30571,   -30535,   -30498,   -30462,   -30424,   -30387,   -30349,   -30311, // 1663
    
        -30273,   -30234,   -30195,   -30156,   -30117,   -30077,   -30037,   -29996, 
        -29956,   -29915,   -29874,   -29832,   -29791,   -29749,   -29706,   -29664, 
        -29621,   -29578,   -29534,   -29491,   -29447,   -29403,   -29358,   -29313, 
        -29268,   -29223,   -29177,   -29131,   -29085,   -29039,   -28992,   -28945, // 1695
    
        -28898,   -28850,   -28803,   -28754,   -28706,   -28658,   -28609,   -28559, 
        -28510,   -28460,   -28410,   -28360,   -28310,   -28259,   -28208,   -28157, 
        -28105,   -28053,   -28001,   -27949,   -27896,   -27843,   -27790,   -27737, 
        -27683,   -27629,   -27575,   -27521,   -27466,   -27411,   -27356,   -27300, // 1727
    
        -27245,   -27189,   -27132,   -27076,   -27019,   -26962,   -26905,   -26847, 
        -26790,   -26732,   -26673,   -26615,   -26556,   -26497,   -26438,   -26378, 
        -26319,   -26259,   -26198,   -26138,   -26077,   -26016,   -25955,   -25893, 
        -25832,   -25770,   -25707,   -25645,   -25582,   -25519,   -25456,   -25393, // 1759
    
        -25329,   -25265,   -25201,   -25137,   -25072,   -25007,   -24942,   -24877, 
        -24811,   -24746,   -24680,   -24613,   -24547,   -24480,   -24413,   -24346, 
        -24279,   -24211,   -24143,   -24075,   -24007,   -23938,   -23869,   -23800, 
        -23731,   -23662,   -23592,   -23522,   -23452,   -23382,   -23311,   -23241, // 1791
    
        -23170,   -23098,   -23027,   -22955,   -22884,   -22811,   -22739,   -22667, 
        -22594,   -22521,   -22448,   -22375,   -22301,   -22227,   -22153,   -22079, 
        -22005,   -21930,   -21855,   -21780,   -21705,   -21630,   -21554,   -21478, 
        -21402,   -21326,   -21250,   -21173,   -21096,   -21019,   -20942,   -20865, // 1823
    
        -20787,   -20709,   -20631,   -20553,   -20475,   -20396,   -20317,   -20238, 
        -20159,   -20080,   -20000,   -19920,   -19841,   -19760,   -19680,   -19600, 
        -19519,   -19438,   -19357,   -19276,   -19195,   -19113,   -19031,   -18949, 
        -18867,   -18785,   -18703,   -18620,   -18537,   -18454,   -18371,   -18288, // 1855
    
        -18204,   -18120,   -18037,   -17953,   -17868,   -17784,   -17700,   -17615, 
        -17530,   -17445,   -17360,   -17274,   -17189,   -17103,   -17017,   -16932, 
        -16845,   -16759,   -16673,   -16586,   -16499,   -16412,   -16325,   -16238, 
        -16151,   -16063,   -15975,   -15887,   -15799,   -15711,   -15623,   -15535, // 1887
    
        -15446,   -15357,   -15268,   -15179,   -15090,   -15001,   -14911,   -14822, 
        -14732,   -14642,   -14552,   -14462,   -14372,   -14281,   -14191,   -14100, 
        -14009,   -13918,   -13827,   -13736,   -13645,   -13553,   -13462,   -13370, 
        -13278,   -13186,   -13094,   -13002,   -12910,   -12817,   -12725,   -12632, // 1919
    
        -12539,   -12446,   -12353,   -12260,   -12167,   -12073,   -11980,   -11886, 
        -11792,   -11699,   -11605,   -11510,   -11416,   -11322,   -11228,   -11133, 
        -11039,   -10944,   -10849,   -10754,   -10659,   -10564,   -10469,   -10373, 
        -10278,   -10183,   -10087,    -9991,    -9895,    -9800,    -9704,    -9608, // 1951
    
         -9511,    -9415,    -9319,    -9222,    -9126,    -9029,    -8933,    -8836, 
         -8739,    -8642,    -8545,    -8448,    -8351,    -8254,    -8156,    -8059, 
         -7961,    -7864,    -7766,    -7668,    -7571,    -7473,    -7375,    -7277, 
         -7179,    -7081,    -6983,    -6884,    -6786,    -6688,    -6589,    -6491, // 1983
    
         -6392,    -6293,    -6195,    -6096,    -5997,    -5898,    -5799,    -5701, 
         -5601,    -5502,    -5403,    -5304,    -5205,    -5106,    -5006,    -4907, 
         -4807,    -4708,    -4609,    -4509,    -4409,    -4310,    -4210,    -4110, 
         -4011,    -3911,    -3811,    -3711,    -3611,    -3511,    -3411,    -3311, // 2015
    
         -3211,    -3111,    -3011,    -2911,    -2811,    -2711,    -2610,    -2510, 
         -2410,    -2310,    -2209,    -2109,    -2009,    -1908,    -1808,    -1708, 
         -1607,    -1507,    -1406,    -1306,    -1206,    -1105,    -1005,     -904, 
          -804,     -703,     -603,     -502,     -402,     -301,     -201,     -100, // 2047
    
      };
    }
  }
}
#endif
