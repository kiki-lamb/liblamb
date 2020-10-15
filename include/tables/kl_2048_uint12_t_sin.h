#ifndef kl_2048_uint12_t_sin_h
#define kl_2048_uint12_t_sin_h

#define KL_2048_uint12_t_sin_cells 2048

namespace lamb {
  namespace Tables {
    namespace sin2048_uint12_t {
      typedef uint16_t value_type;
      const   size_t length = 2048;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
          2048,     2054,     2060,     2066,     2073,     2079,     2085,     2091, 
          2098,     2104,     2110,     2117,     2123,     2129,     2135,     2142, 
          2148,     2154,     2161,     2167,     2173,     2179,     2186,     2192, 
          2198,     2204,     2211,     2217,     2223,     2229,     2236,     2242, // 31
    
          2248,     2254,     2261,     2267,     2273,     2279,     2286,     2292, 
          2298,     2304,     2311,     2317,     2323,     2329,     2335,     2342, 
          2348,     2354,     2360,     2367,     2373,     2379,     2385,     2391, 
          2398,     2404,     2410,     2416,     2422,     2428,     2435,     2441, // 63
    
          2447,     2453,     2459,     2465,     2472,     2478,     2484,     2490, 
          2496,     2502,     2508,     2514,     2521,     2527,     2533,     2539, 
          2545,     2551,     2557,     2563,     2569,     2575,     2581,     2588, 
          2594,     2600,     2606,     2612,     2618,     2624,     2630,     2636, // 95
    
          2642,     2648,     2654,     2660,     2666,     2672,     2678,     2684, 
          2690,     2696,     2702,     2708,     2714,     2720,     2725,     2731, 
          2737,     2743,     2749,     2755,     2761,     2767,     2773,     2779, 
          2784,     2790,     2796,     2802,     2808,     2814,     2819,     2825, // 127
    
          2831,     2837,     2843,     2848,     2854,     2860,     2866,     2871, 
          2877,     2883,     2889,     2894,     2900,     2906,     2912,     2917, 
          2923,     2929,     2934,     2940,     2946,     2951,     2957,     2962, 
          2968,     2974,     2979,     2985,     2990,     2996,     3002,     3007, // 159
    
          3013,     3018,     3024,     3029,     3035,     3040,     3046,     3051, 
          3057,     3062,     3068,     3073,     3078,     3084,     3089,     3095, 
          3100,     3106,     3111,     3116,     3122,     3127,     3132,     3138, 
          3143,     3148,     3154,     3159,     3164,     3169,     3175,     3180, // 191
    
          3185,     3190,     3195,     3201,     3206,     3211,     3216,     3221, 
          3226,     3232,     3237,     3242,     3247,     3252,     3257,     3262, 
          3267,     3272,     3277,     3282,     3287,     3292,     3297,     3302, 
          3307,     3312,     3317,     3322,     3327,     3332,     3337,     3342, // 223
    
          3346,     3351,     3356,     3361,     3366,     3371,     3375,     3380, 
          3385,     3390,     3394,     3399,     3404,     3408,     3413,     3418, 
          3423,     3427,     3432,     3436,     3441,     3446,     3450,     3455, 
          3459,     3464,     3468,     3473,     3477,     3482,     3486,     3491, // 255
    
          3495,     3500,     3504,     3509,     3513,     3517,     3522,     3526, 
          3530,     3535,     3539,     3543,     3548,     3552,     3556,     3560, 
          3565,     3569,     3573,     3577,     3581,     3586,     3590,     3594, 
          3598,     3602,     3606,     3610,     3614,     3618,     3622,     3626, // 287
    
          3630,     3634,     3638,     3642,     3646,     3650,     3654,     3658, 
          3662,     3665,     3669,     3673,     3677,     3681,     3685,     3688, 
          3692,     3696,     3700,     3703,     3707,     3711,     3714,     3718, 
          3722,     3725,     3729,     3732,     3736,     3739,     3743,     3746, // 319
    
          3750,     3753,     3757,     3760,     3764,     3767,     3771,     3774, 
          3777,     3781,     3784,     3787,     3791,     3794,     3797,     3800, 
          3804,     3807,     3810,     3813,     3816,     3820,     3823,     3826, 
          3829,     3832,     3835,     3838,     3841,     3844,     3847,     3850, // 351
    
          3853,     3856,     3859,     3862,     3865,     3868,     3871,     3874, 
          3876,     3879,     3882,     3885,     3888,     3890,     3893,     3896, 
          3898,     3901,     3904,     3906,     3909,     3912,     3914,     3917, 
          3919,     3922,     3924,     3927,     3929,     3932,     3934,     3937, // 383
    
          3939,     3942,     3944,     3946,     3949,     3951,     3953,     3956, 
          3958,     3960,     3962,     3965,     3967,     3969,     3971,     3973, 
          3975,     3977,     3980,     3982,     3984,     3986,     3988,     3990, 
          3992,     3994,     3996,     3997,     3999,     4001,     4003,     4005, // 415
    
          4007,     4009,     4010,     4012,     4014,     4016,     4017,     4019, 
          4021,     4022,     4024,     4026,     4027,     4029,     4031,     4032, 
          4034,     4035,     4037,     4038,     4040,     4041,     4042,     4044, 
          4045,     4047,     4048,     4049,     4051,     4052,     4053,     4054, // 447
    
          4056,     4057,     4058,     4059,     4060,     4062,     4063,     4064, 
          4065,     4066,     4067,     4068,     4069,     4070,     4071,     4072, 
          4073,     4074,     4075,     4076,     4076,     4077,     4078,     4079, 
          4080,     4080,     4081,     4082,     4083,     4083,     4084,     4085, // 479
    
          4085,     4086,     4086,     4087,     4087,     4088,     4088,     4089, 
          4089,     4090,     4090,     4091,     4091,     4092,     4092,     4092, 
          4093,     4093,     4093,     4093,     4094,     4094,     4094,     4094, 
          4094,     4095,     4095,     4095,     4095,     4095,     4095,     4095, // 511
    
          4095,     4095,     4095,     4095,     4095,     4095,     4095,     4095, 
          4094,     4094,     4094,     4094,     4094,     4093,     4093,     4093, 
          4093,     4092,     4092,     4092,     4091,     4091,     4090,     4090, 
          4089,     4089,     4088,     4088,     4087,     4087,     4086,     4086, // 543
    
          4085,     4085,     4084,     4083,     4083,     4082,     4081,     4080, 
          4080,     4079,     4078,     4077,     4076,     4076,     4075,     4074, 
          4073,     4072,     4071,     4070,     4069,     4068,     4067,     4066, 
          4065,     4064,     4063,     4062,     4060,     4059,     4058,     4057, // 575
    
          4056,     4054,     4053,     4052,     4051,     4049,     4048,     4047, 
          4045,     4044,     4042,     4041,     4040,     4038,     4037,     4035, 
          4034,     4032,     4031,     4029,     4027,     4026,     4024,     4022, 
          4021,     4019,     4017,     4016,     4014,     4012,     4010,     4009, // 607
    
          4007,     4005,     4003,     4001,     3999,     3997,     3996,     3994, 
          3992,     3990,     3988,     3986,     3984,     3982,     3980,     3977, 
          3975,     3973,     3971,     3969,     3967,     3965,     3962,     3960, 
          3958,     3956,     3953,     3951,     3949,     3946,     3944,     3942, // 639
    
          3939,     3937,     3934,     3932,     3929,     3927,     3924,     3922, 
          3919,     3917,     3914,     3912,     3909,     3906,     3904,     3901, 
          3898,     3896,     3893,     3890,     3888,     3885,     3882,     3879, 
          3876,     3874,     3871,     3868,     3865,     3862,     3859,     3856, // 671
    
          3853,     3850,     3847,     3844,     3841,     3838,     3835,     3832, 
          3829,     3826,     3823,     3820,     3816,     3813,     3810,     3807, 
          3804,     3800,     3797,     3794,     3791,     3787,     3784,     3781, 
          3777,     3774,     3771,     3767,     3764,     3760,     3757,     3753, // 703
    
          3750,     3746,     3743,     3739,     3736,     3732,     3729,     3725, 
          3722,     3718,     3714,     3711,     3707,     3703,     3700,     3696, 
          3692,     3688,     3685,     3681,     3677,     3673,     3669,     3665, 
          3662,     3658,     3654,     3650,     3646,     3642,     3638,     3634, // 735
    
          3630,     3626,     3622,     3618,     3614,     3610,     3606,     3602, 
          3598,     3594,     3590,     3586,     3581,     3577,     3573,     3569, 
          3565,     3560,     3556,     3552,     3548,     3543,     3539,     3535, 
          3530,     3526,     3522,     3517,     3513,     3509,     3504,     3500, // 767
    
          3495,     3491,     3486,     3482,     3477,     3473,     3468,     3464, 
          3459,     3455,     3450,     3446,     3441,     3436,     3432,     3427, 
          3423,     3418,     3413,     3408,     3404,     3399,     3394,     3390, 
          3385,     3380,     3375,     3371,     3366,     3361,     3356,     3351, // 799
    
          3346,     3342,     3337,     3332,     3327,     3322,     3317,     3312, 
          3307,     3302,     3297,     3292,     3287,     3282,     3277,     3272, 
          3267,     3262,     3257,     3252,     3247,     3242,     3237,     3232, 
          3226,     3221,     3216,     3211,     3206,     3201,     3195,     3190, // 831
    
          3185,     3180,     3175,     3169,     3164,     3159,     3154,     3148, 
          3143,     3138,     3132,     3127,     3122,     3116,     3111,     3106, 
          3100,     3095,     3089,     3084,     3078,     3073,     3068,     3062, 
          3057,     3051,     3046,     3040,     3035,     3029,     3024,     3018, // 863
    
          3013,     3007,     3002,     2996,     2990,     2985,     2979,     2974, 
          2968,     2962,     2957,     2951,     2946,     2940,     2934,     2929, 
          2923,     2917,     2912,     2906,     2900,     2894,     2889,     2883, 
          2877,     2871,     2866,     2860,     2854,     2848,     2843,     2837, // 895
    
          2831,     2825,     2819,     2814,     2808,     2802,     2796,     2790, 
          2784,     2779,     2773,     2767,     2761,     2755,     2749,     2743, 
          2737,     2731,     2725,     2720,     2714,     2708,     2702,     2696, 
          2690,     2684,     2678,     2672,     2666,     2660,     2654,     2648, // 927
    
          2642,     2636,     2630,     2624,     2618,     2612,     2606,     2600, 
          2594,     2588,     2581,     2575,     2569,     2563,     2557,     2551, 
          2545,     2539,     2533,     2527,     2521,     2514,     2508,     2502, 
          2496,     2490,     2484,     2478,     2472,     2465,     2459,     2453, // 959
    
          2447,     2441,     2435,     2428,     2422,     2416,     2410,     2404, 
          2398,     2391,     2385,     2379,     2373,     2367,     2360,     2354, 
          2348,     2342,     2335,     2329,     2323,     2317,     2311,     2304, 
          2298,     2292,     2286,     2279,     2273,     2267,     2261,     2254, // 991
    
          2248,     2242,     2236,     2229,     2223,     2217,     2211,     2204, 
          2198,     2192,     2186,     2179,     2173,     2167,     2161,     2154, 
          2148,     2142,     2135,     2129,     2123,     2117,     2110,     2104, 
          2098,     2091,     2085,     2079,     2073,     2066,     2060,     2054, // 1023
    
          2048,     2041,     2035,     2029,     2022,     2016,     2010,     2004, 
          1997,     1991,     1985,     1978,     1972,     1966,     1960,     1953, 
          1947,     1941,     1934,     1928,     1922,     1916,     1909,     1903, 
          1897,     1891,     1884,     1878,     1872,     1866,     1859,     1853, // 1055
    
          1847,     1841,     1834,     1828,     1822,     1816,     1809,     1803, 
          1797,     1791,     1784,     1778,     1772,     1766,     1760,     1753, 
          1747,     1741,     1735,     1728,     1722,     1716,     1710,     1704, 
          1697,     1691,     1685,     1679,     1673,     1667,     1660,     1654, // 1087
    
          1648,     1642,     1636,     1630,     1623,     1617,     1611,     1605, 
          1599,     1593,     1587,     1581,     1574,     1568,     1562,     1556, 
          1550,     1544,     1538,     1532,     1526,     1520,     1514,     1507, 
          1501,     1495,     1489,     1483,     1477,     1471,     1465,     1459, // 1119
    
          1453,     1447,     1441,     1435,     1429,     1423,     1417,     1411, 
          1405,     1399,     1393,     1387,     1381,     1375,     1370,     1364, 
          1358,     1352,     1346,     1340,     1334,     1328,     1322,     1316, 
          1311,     1305,     1299,     1293,     1287,     1281,     1276,     1270, // 1151
    
          1264,     1258,     1252,     1247,     1241,     1235,     1229,     1224, 
          1218,     1212,     1206,     1201,     1195,     1189,     1183,     1178, 
          1172,     1166,     1161,     1155,     1149,     1144,     1138,     1133, 
          1127,     1121,     1116,     1110,     1105,     1099,     1093,     1088, // 1183
    
          1082,     1077,     1071,     1066,     1060,     1055,     1049,     1044, 
          1038,     1033,     1027,     1022,     1017,     1011,     1006,     1000, 
           995,      989,      984,      979,      973,      968,      963,      957, 
           952,      947,      941,      936,      931,      926,      920,      915, // 1215
    
           910,      905,      900,      894,      889,      884,      879,      874, 
           869,      863,      858,      853,      848,      843,      838,      833, 
           828,      823,      818,      813,      808,      803,      798,      793, 
           788,      783,      778,      773,      768,      763,      758,      753, // 1247
    
           749,      744,      739,      734,      729,      724,      720,      715, 
           710,      705,      701,      696,      691,      687,      682,      677, 
           672,      668,      663,      659,      654,      649,      645,      640, 
           636,      631,      627,      622,      618,      613,      609,      604, // 1279
    
           600,      595,      591,      586,      582,      578,      573,      569, 
           565,      560,      556,      552,      547,      543,      539,      535, 
           530,      526,      522,      518,      514,      509,      505,      501, 
           497,      493,      489,      485,      481,      477,      473,      469, // 1311
    
           465,      461,      457,      453,      449,      445,      441,      437, 
           433,      430,      426,      422,      418,      414,      410,      407, 
           403,      399,      395,      392,      388,      384,      381,      377, 
           373,      370,      366,      363,      359,      356,      352,      349, // 1343
    
           345,      342,      338,      335,      331,      328,      324,      321, 
           318,      314,      311,      308,      304,      301,      298,      295, 
           291,      288,      285,      282,      279,      275,      272,      269, 
           266,      263,      260,      257,      254,      251,      248,      245, // 1375
    
           242,      239,      236,      233,      230,      227,      224,      221, 
           219,      216,      213,      210,      207,      205,      202,      199, 
           197,      194,      191,      189,      186,      183,      181,      178, 
           176,      173,      171,      168,      166,      163,      161,      158, // 1407
    
           156,      153,      151,      149,      146,      144,      142,      139, 
           137,      135,      133,      130,      128,      126,      124,      122, 
           120,      118,      115,      113,      111,      109,      107,      105, 
           103,      101,       99,       98,       96,       94,       92,       90, // 1439
    
            88,       86,       85,       83,       81,       79,       78,       76, 
            74,       73,       71,       69,       68,       66,       64,       63, 
            61,       60,       58,       57,       55,       54,       53,       51, 
            50,       48,       47,       46,       44,       43,       42,       41, // 1471
    
            39,       38,       37,       36,       35,       33,       32,       31, 
            30,       29,       28,       27,       26,       25,       24,       23, 
            22,       21,       20,       19,       19,       18,       17,       16, 
            15,       15,       14,       13,       12,       12,       11,       10, // 1503
    
            10,        9,        9,        8,        8,        7,        7,        6, 
             6,        5,        5,        4,        4,        3,        3,        3, 
             2,        2,        2,        2,        1,        1,        1,        1, 
             1,        0,        0,        0,        0,        0,        0,        0, // 1535
    
             0,        0,        0,        0,        0,        0,        0,        0, 
             1,        1,        1,        1,        1,        2,        2,        2, 
             2,        3,        3,        3,        4,        4,        5,        5, 
             6,        6,        7,        7,        8,        8,        9,        9, // 1567
    
            10,       10,       11,       12,       12,       13,       14,       15, 
            15,       16,       17,       18,       19,       19,       20,       21, 
            22,       23,       24,       25,       26,       27,       28,       29, 
            30,       31,       32,       33,       35,       36,       37,       38, // 1599
    
            39,       41,       42,       43,       44,       46,       47,       48, 
            50,       51,       53,       54,       55,       57,       58,       60, 
            61,       63,       64,       66,       68,       69,       71,       73, 
            74,       76,       78,       79,       81,       83,       85,       86, // 1631
    
            88,       90,       92,       94,       96,       98,       99,      101, 
           103,      105,      107,      109,      111,      113,      115,      118, 
           120,      122,      124,      126,      128,      130,      133,      135, 
           137,      139,      142,      144,      146,      149,      151,      153, // 1663
    
           156,      158,      161,      163,      166,      168,      171,      173, 
           176,      178,      181,      183,      186,      189,      191,      194, 
           197,      199,      202,      205,      207,      210,      213,      216, 
           219,      221,      224,      227,      230,      233,      236,      239, // 1695
    
           242,      245,      248,      251,      254,      257,      260,      263, 
           266,      269,      272,      275,      279,      282,      285,      288, 
           291,      295,      298,      301,      304,      308,      311,      314, 
           318,      321,      324,      328,      331,      335,      338,      342, // 1727
    
           345,      349,      352,      356,      359,      363,      366,      370, 
           373,      377,      381,      384,      388,      392,      395,      399, 
           403,      407,      410,      414,      418,      422,      426,      430, 
           433,      437,      441,      445,      449,      453,      457,      461, // 1759
    
           465,      469,      473,      477,      481,      485,      489,      493, 
           497,      501,      505,      509,      514,      518,      522,      526, 
           530,      535,      539,      543,      547,      552,      556,      560, 
           565,      569,      573,      578,      582,      586,      591,      595, // 1791
    
           600,      604,      609,      613,      618,      622,      627,      631, 
           636,      640,      645,      649,      654,      659,      663,      668, 
           672,      677,      682,      687,      691,      696,      701,      705, 
           710,      715,      720,      724,      729,      734,      739,      744, // 1823
    
           749,      753,      758,      763,      768,      773,      778,      783, 
           788,      793,      798,      803,      808,      813,      818,      823, 
           828,      833,      838,      843,      848,      853,      858,      863, 
           869,      874,      879,      884,      889,      894,      900,      905, // 1855
    
           910,      915,      920,      926,      931,      936,      941,      947, 
           952,      957,      963,      968,      973,      979,      984,      989, 
           995,     1000,     1006,     1011,     1017,     1022,     1027,     1033, 
          1038,     1044,     1049,     1055,     1060,     1066,     1071,     1077, // 1887
    
          1082,     1088,     1093,     1099,     1105,     1110,     1116,     1121, 
          1127,     1133,     1138,     1144,     1149,     1155,     1161,     1166, 
          1172,     1178,     1183,     1189,     1195,     1201,     1206,     1212, 
          1218,     1224,     1229,     1235,     1241,     1247,     1252,     1258, // 1919
    
          1264,     1270,     1276,     1281,     1287,     1293,     1299,     1305, 
          1311,     1316,     1322,     1328,     1334,     1340,     1346,     1352, 
          1358,     1364,     1370,     1375,     1381,     1387,     1393,     1399, 
          1405,     1411,     1417,     1423,     1429,     1435,     1441,     1447, // 1951
    
          1453,     1459,     1465,     1471,     1477,     1483,     1489,     1495, 
          1501,     1507,     1514,     1520,     1526,     1532,     1538,     1544, 
          1550,     1556,     1562,     1568,     1574,     1581,     1587,     1593, 
          1599,     1605,     1611,     1617,     1623,     1630,     1636,     1642, // 1983
    
          1648,     1654,     1660,     1667,     1673,     1679,     1685,     1691, 
          1697,     1704,     1710,     1716,     1722,     1728,     1735,     1741, 
          1747,     1753,     1760,     1766,     1772,     1778,     1784,     1791, 
          1797,     1803,     1809,     1816,     1822,     1828,     1834,     1841, // 2015
    
          1847,     1853,     1859,     1866,     1872,     1878,     1884,     1891, 
          1897,     1903,     1909,     1916,     1922,     1928,     1934,     1941, 
          1947,     1953,     1960,     1966,     1972,     1978,     1985,     1991, 
          1997,     2004,     2010,     2016,     2022,     2029,     2035,     2041, // 2047
    
      };
    }
  }
}
#endif
