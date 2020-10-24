#include "../include/lamb.h"

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

using namespace lamb;

int main() {
 {
  chamberlin cf;
  
  sat_q0n15 acc(q0n15::MIN);
  
  printf("F, I, L, H, B, N, D1, D2 \n");
  
  for (size_t qix = 1; qix < 300; qix += 2) {
   cf.Q = qix;
   cf.set_q();
   
   for (size_t fix = 150; fix > 100; fix -= 10) {
    cf.F    = fix;
    acc.val = 0;
    
    cf.set_frequency();
   
    for(size_t ix = 0; ix < 64; ix ++) {
     acc += 65536L / 64;
     
     // q0n15_value_type y = (acc.val > 32768u ) ? sat_q0n15::MAX : 0;
     
     auto x = cf.process(sat_q0n15(acc));
     
     printf("\n");
    }
   }
  }

  {
   fx_chamberlin cf;
  
   sat_q7n8 acc(q7n8::MIN);
  
   for (size_t qix = 1; qix < 300; qix += 2) {
    cf.Q = sat_q7n8::from_float(qix);
    cf.set_q();
   
    for (size_t fix = 150; fix > 100; fix -= 10) {
     cf.F    = sat_q7n8(fix, 0);
     acc.val = 0;
    
     cf.set_frequency();
   
     for(size_t ix = 0; ix < 64; ix ++) {
      acc += 65536L / 64;
    
      // q7n8_value_type y = (acc.val > 32768u ) ? sat_q7n8::MAX : 0;
    
      auto x = cf.process(acc);
    
      printf("\n");
     }
    }
   }
  }
 }
}
