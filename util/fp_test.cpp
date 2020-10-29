#include "../include/lamb.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_sine.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

////////////////////////////////////////////////////////////////////////////////

void pprint_bits_32(uint32_t const & t0) {
  {
    for(uint32_t mask = 0x80000000; mask; mask >>= 1) {
      if (mask & t0) {
#ifdef LAMB_NO_ARDUINO
       printf("1");
#else
       Serial.print('1'); Serial.flush();
#endif
      }
      else {
#ifdef LAMB_NO_ARDUINO
       printf("0");
#else
       Serial.print('0'); Serial.flush();
#endif
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

int main() {

 typedef u16q16 f0_type;
 typedef f0_type::type int_type;
 typedef unsigned_int<(sizeof(int_type))> traits;

 constexpr u2q30 one(u2q30::ONE);
 
 for (int64_t ix = traits::MIN + 1; ix < traits::MAX-1; ix += 65536 << 4) {
  // printf(
  //  "% 5.5lf (%lu) / % 5.5lf (%lu) = % 5.5.lf \n",
  //  double(one),
  //  one.value,
  //  double(f0_type(ix)),
  //  f0_type(ix).value,
  //  double(one / f0_type(ix))
  // );
  // fflush(stdout);

  auto x = double(one / f0_type(ix));
  
//  s16q16s q1 = one / t;
  
//  printf("% 12ld, % 12.4lf, % 12ld, % 12.4lf \n", t.value, double(t), q1.value, double(q1));
 }

 printf("Stop.\n");
}
