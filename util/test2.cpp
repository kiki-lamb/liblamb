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
 s0q15 lines = s0q15::MIN;

 double last    = 0.0;
 double lim     = 4.0;
 double incr    = 4.0 / 512.0;

 for (
  double ix = -lim;
  ix < lim;
  ix+= incr,
  lines++
 ) {
  double next = tanh(ix);
  
  printf("% 10.5lf, % 10.5lf, % 10.5lf \n", lines, ix, next, next - last);

  last = next;
 }
 
 printf("%lu lines.\n", lines);
}

