#include "../include/lamb.h"
#include <stdio.h>

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

using namespace lamb;

int main() {

  printf("Start...\n");
  fflush(stdout);
 
  fx_chamberlin cf;
  
  sat_q15n16 acc(q15n16::MIN);
  
  for (size_t qix = 1; qix < 300; qix += 2) {
   cf.Q = sat_q15n16::from_float(qix);
   
   cf.set_q();
   
   for (size_t fix = 1000; fix > 100; fix -= 100) {
    cf.F    = sat_q15n16(fix, 0);
    acc.val = 0;
    
    cf.set_frequency();
    
    for(size_t ix = 0; ix < 64; ix ++) {
     acc += 65536L / 64;
     
     // q15n16_value_type y = (acc.val > 32768u ) ? sat_q15n16::MAX : 0;
     
     auto x = cf.process(acc);
     
     printf("\n");
     }
   }
  }
}
