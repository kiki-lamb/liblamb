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
 typedef s0q15 table_t;
 
 index_t index  = index_t::MIN;
 size_t count   = 512;
 uint32_t lines = 0;

 printf("%d, % 10.5lf  \n", (int16_t)index, float(index));

 s0q15 out_table[count];
 
 for (
  uint32_t ix = 0;
  ix < count;
  ix++, lines++
 ) {

  float tmp  = tanh((float)index);
  
  s0q15 qtmp = s0q15::from_float(tmp);
  s0q15 table[count];
  
  printf(
   "% 8u, % 8d, % 10.5lf, % 10.5lf, % 8u, % 10.5lf  \n",
   lines,
   int16_t(index),
   float  (index),
   tmp,
   int16_t(qtmp),
   float  (qtmp)
  );

  out_table[ix] = qtmp;
  
  index += (((uint32_t)UINT16_MAX) + 1) / count;
 }
  
 printf("%lu lines.\n\n", lines);

 printf("const size_t length = %d; \n", count);
 printf("const s0q15  data[] \n");
 printf("#ifdef __AVR__ \n");
 printf("PROGMEM \n");
 printf("#endif \n");
 printf("= { \n ");

 for (
  uint32_t ix = 0;
  ix < count;
  ix++
 ) {

  char buff[32];
  snprintf(buff, 32, "s0q15(%6d), ", out_table[ix].value);
   
  printf("%-16s", buff);

  if (((ix + 1) % 8) == 0)
   printf("\n ");
  fflush(stdout);
 }

 printf("\b};\n");
 
}

