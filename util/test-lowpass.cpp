#include "../include/lamb.h"

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-lowpass.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr
// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-lowpass.cpp && .\a.exe

////////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

void pprint_bits_32(uint32_t t0) {
 for(uint32_t mask = 0x80000000; mask; mask >>= 1) {
  if (mask & t0) {
   printf("1");
  }
  else {
   printf("0");
  }
 }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
 {
  // if (false) {
  //  u17q15s f0(1000  , 0 );
  //  u17q15s fs(44100 , 0 );  
  //  u17q15s x (f0    / fs);
   
  //  printf("R: % 05.05lf \n", double(x));
   
  //  fflush(stdout);
   
  //  return 0;
  // }
   
  lowpass       fx_lp;
  uint16_t      acc(0);
  
  for (uint16_t qix = 0; qix < 256; qix += 16) {
   fx_lp.res(qix);
   
   const size_t fix_incr = 100;
   
   for (uint16_t fix = 0; fix < 256; fix += 16) {
    acc          = 0;    
    fx_lp.freq(fix);
        
    const size_t fdiv = 64;
    
    for(size_t cycle_ix = 0; cycle_ix < 1; cycle_ix++) {
     for(size_t pix = 0; pix < (65534L / fdiv); pix ++) {
      acc += fdiv;

      auto y = fx_lp.process(acc >= 32768 ? s0q15::MIN : s0q15::MAX);
       
      printf("\n");
     }
    }
   }
  }
 }
}

////////////////////////////////////////////////////////////////////////////////
