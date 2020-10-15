#ifndef kl_128_int12_t_tri_h
#define kl_128_int12_t_tri_h

#define KL_128_int12_t_tri_cells 128

namespace lamb {
  namespace Tables {
    namespace tri128_int12_t {
      typedef int16_t value_type;
      const   size_t length = 128;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,       63,      127,      191,      255,      319,      383,      447, 
           511,      575,      639,      703,      767,      831,      895,      959, 
          1023,     1087,     1151,     1215,     1279,     1343,     1407,     1471, 
          1535,     1599,     1663,     1727,     1791,     1855,     1919,     1983, // 31
    
          2047,     1983,     1919,     1855,     1791,     1727,     1663,     1599, 
          1535,     1471,     1407,     1343,     1279,     1215,     1151,     1087, 
          1023,      959,      895,      831,      767,      703,      639,      575, 
           511,      447,      383,      319,      255,      191,      127,       63, // 63
    
             0,      -63,     -127,     -191,     -255,     -319,     -383,     -447, 
          -511,     -575,     -639,     -703,     -767,     -831,     -895,     -959, 
         -1023,    -1087,    -1151,    -1215,    -1279,    -1343,    -1407,    -1471, 
         -1535,    -1599,    -1663,    -1727,    -1791,    -1855,    -1919,    -1983, // 95
    
         -2047,    -1983,    -1919,    -1855,    -1791,    -1727,    -1663,    -1599, 
         -1535,    -1471,    -1407,    -1343,    -1279,    -1215,    -1151,    -1087, 
         -1023,     -959,     -895,     -831,     -767,     -703,     -639,     -575, 
          -511,     -447,     -383,     -319,     -255,     -191,     -127,      -63, // 127
    
      };
    }
  }
}
#endif
