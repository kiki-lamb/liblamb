#include "../include/lamb.h"

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-chamberlin.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

using namespace std;
using namespace lamb;

int main() {
 {
  chamberlin cf;
  
  uint16_t acc(0);

//  printf("A, AF, F1, I, L, H, B, N, D1, D2 \n");
  printf("Af, I, F1, L, H, B, N, D1, D2 \n");
  
  for (size_t qix = 1; qix == 1; qix += 100) {
   cf.Q = qix;
   cf.set_q();

   const size_t fix_incr = 5;
   
   for (size_t fix = 300; fix > fix_incr; fix -= fix_incr) {
    cf.F    = fix;
    acc     = 0;
    
    cf.set_frequency();

    const size_t fdiv = 2048;

    for(size_t cycle_ix = 0; cycle_ix < 10; cycle_ix++) {
     for(size_t pix = 0; pix < (65534L / fdiv); pix ++) {
      acc += fdiv;
      
      printf("%lf, ", acc / 65536.0);

      auto x = cf.process(sat_q0n15(acc >= 32768 ? q0n15::MIN : q0n15::MAX));
      
      printf("\n");
     }
    }
   }
  }
 }
}
