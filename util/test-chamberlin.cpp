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

  cf.F = 5000;
  cf.set_frequency();
  cf.Q = 0.5;
  cf.set_q();
  printf("\n");
  
  fx_cf.F = fx_chamberlin::pqtype(5000);
  fx_cf.set_frequency();
  fx_cf.Q = fx_chamberlin::qtype(fx_chamberlin::qtype::ONE >> 1);
  fx_cf.set_q();

  printf("Af,        I,    F1,     Q1,        L,              H,         B,         N,         D1,        D2 \n");

//  for (double qix = 1.0; qix < 30.0; qix += 1.0) {
  for (double qix = 1.0; qix < 4.0; qix += 1.0) {
   cf.Q = qix;
   cf.set_q();

   fx_cf.Q = fx_chamberlin::qtype::from_float((float)qix);
   fx_cf.set_q();

   const size_t fix_incr = 100;
   
   //for (size_t fix = 8500 + 5; fix > 8505; fix -= fix_incr) {
   for (size_t fix = 8500 + 5; fix == 8505; fix -= fix_incr) {
    acc     = 0;
    
    cf.F    = fix;        
    cf.set_frequency();

    fx_cf.F.val = fix;
    fx_cf.set_frequency();
    
  const size_t fdiv = 512;

    for(size_t cycle_ix = 0; cycle_ix < 1; cycle_ix++) {
     for(size_t pix = 0; pix < (65534L / fdiv); pix ++) {
      acc += fdiv;
      
      printf("%lf, ", acc / 65536.0);

        auto y = fx_cf.process(sat_q0n15(acc >= 32768 ? q0n15::MIN : q0n15::MAX));
      
      printf("\n");
     }
    }
   }
  }
 }
}