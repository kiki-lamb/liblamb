#ifndef kl_256_int12_t_tri_h
#define kl_256_int12_t_tri_h

#define KL_256_int12_t_tri_cells 256

namespace lamb {
  namespace tables {
    namespace tri256_int12_t {
      typedef int16_t value_type;
      const   size_t length = 256;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,       31,       63,       95,      127,      159,      191,      223, 
           255,      287,      319,      351,      383,      415,      447,      479, 
           511,      543,      575,      607,      639,      671,      703,      735, 
           767,      799,      831,      863,      895,      927,      959,      991, // 31
    
          1023,     1055,     1087,     1119,     1151,     1183,     1215,     1247, 
          1279,     1311,     1343,     1375,     1407,     1439,     1471,     1503, 
          1535,     1567,     1599,     1631,     1663,     1695,     1727,     1759, 
          1791,     1823,     1855,     1887,     1919,     1951,     1983,     2015, // 63
    
          2047,     2015,     1983,     1951,     1919,     1887,     1855,     1823, 
          1791,     1759,     1727,     1695,     1663,     1631,     1599,     1567, 
          1535,     1503,     1471,     1439,     1407,     1375,     1343,     1311, 
          1279,     1247,     1215,     1183,     1151,     1119,     1087,     1055, // 95
    
          1023,      991,      959,      927,      895,      863,      831,      799, 
           767,      735,      703,      671,      639,      607,      575,      543, 
           511,      479,      447,      415,      383,      351,      319,      287, 
           255,      223,      191,      159,      127,       95,       63,       31, // 127
    
             0,      -31,      -63,      -95,     -127,     -159,     -191,     -223, 
          -255,     -287,     -319,     -351,     -383,     -415,     -447,     -479, 
          -511,     -543,     -575,     -607,     -639,     -671,     -703,     -735, 
          -767,     -799,     -831,     -863,     -895,     -927,     -959,     -991, // 159
    
         -1023,    -1055,    -1087,    -1119,    -1151,    -1183,    -1215,    -1247, 
         -1279,    -1311,    -1343,    -1375,    -1407,    -1439,    -1471,    -1503, 
         -1535,    -1567,    -1599,    -1631,    -1663,    -1695,    -1727,    -1759, 
         -1791,    -1823,    -1855,    -1887,    -1919,    -1951,    -1983,    -2015, // 191
    
         -2047,    -2015,    -1983,    -1951,    -1919,    -1887,    -1855,    -1823, 
         -1791,    -1759,    -1727,    -1695,    -1663,    -1631,    -1599,    -1567, 
         -1535,    -1503,    -1471,    -1439,    -1407,    -1375,    -1343,    -1311, 
         -1279,    -1247,    -1215,    -1183,    -1151,    -1119,    -1087,    -1055, // 223
    
         -1023,     -991,     -959,     -927,     -895,     -863,     -831,     -799, 
          -767,     -735,     -703,     -671,     -639,     -607,     -575,     -543, 
          -511,     -479,     -447,     -415,     -383,     -351,     -319,     -287, 
          -255,     -223,     -191,     -159,     -127,      -95,      -63,      -31, // 255
    
      };
    }
  }
}
#endif
