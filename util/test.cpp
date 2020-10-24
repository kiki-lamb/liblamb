#include "../include/lamb.h"

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

using namespace lamb;

int main() {
 chamberlin cf;

 sat_q0n15 acc(q0n15::MIN);

 printf("A, F, I, L, H, B, N, D1, D2 \n");
 
 for (size_t fix = 300; fix > 5; fix -= 5) {
  cf.F    = fix;
  acc.val = 0;
  
  cf.set_frequency();
  
  for(size_t ix = 0; ix < 5120; ix ++) {
   acc += 65536L / 128;

   q0n15_value_type y = (acc.val > 32768u ) ? sat_q0n15::MAX : 0;

   auto x = cf.process(sat_q0n15(y));
   
   printf("\n");
  }
 }
}
