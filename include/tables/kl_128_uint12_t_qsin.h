#ifndef kl_128_uint12_t_qsin_h
#define kl_128_uint12_t_qsin_h

#define KL_128_uint12_t_qsin_cells 128

namespace lamb {
  namespace tables {
    namespace qsin128_uint12_t {
      typedef uint16_t value_type;
      const   size_t length = 128;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
= {
           0,       50,      100,      150,      200,      251,      301,      351, 
         401,      451,      501,      551,      600,      650,      700,      749, 
         798,      848,      897,      946,      995,     1043,     1092,     1140, 
        1188,     1236,     1284,     1332,     1379,     1426,     1473,     1520, // 31
    
        1567,     1613,     1659,     1705,     1750,     1796,     1841,     1885, 
        1930,     1974,     2018,     2061,     2105,     2148,     2190,     2233, 
        2275,     2316,     2357,     2398,     2439,     2479,     2519,     2558, 
        2597,     2636,     2674,     2712,     2750,     2787,     2823,     2859, // 63
    
        2895,     2930,     2965,     3000,     3034,     3067,     3100,     3133, 
        3165,     3197,     3228,     3258,     3289,     3318,     3348,     3376, 
        3404,     3432,     3459,     3486,     3512,     3537,     3563,     3587, 
        3611,     3634,     3657,     3680,     3701,     3723,     3743,     3763, // 95
    
        3783,     3802,     3820,     3838,     3855,     3872,     3888,     3903, 
        3918,     3932,     3946,     3959,     3972,     3984,     3995,     4006, 
        4016,     4025,     4034,     4042,     4050,     4057,     4064,     4070, 
        4075,     4079,     4083,     4087,     4090,     4092,     4093,     4094, // 127
    
    };
    }
  }
}
#endif
