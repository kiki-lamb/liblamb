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
  chamberlin    cf;
  fx_chamberlin fx_cf;
  uint16_t      acc(0);

  cf.FF = 5000;
  cf.set_frequency();
  cf.Q = 0.5;
  cf.set_q();
  printf("\n");
  
  fx_cf.f(5000);
  fx_cf.q(fx_chamberlin::sqint::ONE >> 1);

  printf("Af,        I,    FF1,    Q1,        L,              H,         B,         N,         D1,        D2 \n");

  for (double qix = 1.0; qix < 15.0; qix += 3.0) {
   cf.Q = qix;
   cf.set_q();

   fx_cf.q(fx_chamberlin::sqint::from_double(qix).val);

   const size_t fix_incr = 300;
   
   for (size_t fix = 6000 + 5; fix > 4000; fix -= fix_incr) {
    acc          = 0;    
    cf.FF        = fix;        
    cf.set_frequency();

    fx_cf.f(fix);
    
    const size_t fdiv = 256;
    
    for(size_t cycle_ix = 0; cycle_ix < 1; cycle_ix++) {
     for(size_t pix = 0; pix < (65534L / fdiv); pix ++) {
      acc += fdiv;
      
      printf("%lf, ", acc / 65536.0);

        auto y = fx_cf.process(q0n15s(acc >= 32768 ? q0n15::MIN : q0n15::MAX));
      
      printf("\n");
     }
    }
   }
  }
 }
}
