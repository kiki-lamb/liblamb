#include "../include/lamb.h"

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-chamberlin.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

using namespace std;
using namespace lamb;

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

int main() {
 {
  if (false) {
   u17q15s f0(1000, 0);
   u17q15s fs(44100, 0);  
   u17q15s x = f0 / fs;
   
   printf("R: % 05.05lf \n", double(x));
   
   fflush(stdout);
   
   return 0;
  }
   
  fx_chamberlin fx_cf;
  uint16_t      acc(0);
  
  // printf("FF1,          Q1,           L,              H,            B,            N,            D1,           D2  \n");

  for (double qix = 1.0; qix < 20.0; qix += 3.0) {
   fx_cf.q(qix);

   const size_t fix_incr = 80;
   
   for (size_t fix = 4000 + 20; fix > 2000; fix -= fix_incr) {
    acc          = 0;    
    fx_cf.f(fix);
        
    const size_t fdiv = 256;
    
    for(size_t cycle_ix = 0; cycle_ix < 1; cycle_ix++) {
     for(size_t pix = 0; pix < (65534L / fdiv); pix ++) {
      acc += fdiv;

      auto y = fx_cf.process(acc >= 32768 ? s0q15::MIN : s0q15::MAX);
       
      printf("\n");
     }
    }
   }
  }
 }
}
