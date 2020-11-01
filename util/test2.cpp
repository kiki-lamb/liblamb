#include <stdio.h>
#include <inttypes.h>
#include <cmath>
#include "../include/lamb.h"

//////////////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test2.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr
 
//////////////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------

int main() {
 typedef s2q13 index_t;
 index_t index = index_t::MIN;

 uint32_t lines = 0;
 
// double last    = 0.0;
// double lim     = 4.0;
// double incr    = 4.0 / 512.0;

 printf("%d, % 10.5lf  \n", (int16_t)index, float(index));

 for (
  uint32_t ix = 0;
  ix < 512;
  ix++, lines++
 ) {

  float tmp = tanh((float)index);
  
  printf("%u, %d, % 10.5lf, % 10.5lf  \n", lines, (int16_t)index, float(index), tmp);

  index += (((uint32_t)UINT16_MAX) + 1) / 512;
 }
 
 // for (
 //  double ix = -lim;
 //  ix < lim;
 //  ix+= incr,
 //  lines++
 // ) {
 //  double next = tanh(ix);
  
 //  printf("% 10.5lf, % 10.5lf, % 10.5lf \n", lines, ix, next, next - last);

 //  last = next;
 // }
 
 printf("%lu lines.\n", lines);
}

