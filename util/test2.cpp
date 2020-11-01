#include <stdio.h>
#include <inttypes.h>
#include <cmath>

#define LAMB_NO_ARDUINO

#include "../include/lamb.h"

//////////////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test2.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr
 
//////////////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------

// make_tanh_table<s0q15>(512);

template <typename table_t>
void make_tanh_table(const char * type_label, const char * func_label, size_t const & count, bool const & noisy = false) {
 typedef q<0, table_t::WHOLE + 2, table_t::FRAC - 2> index_t;
  
 index_t  index = index_t::MIN;
 uint32_t lines = 0;

 if (noisy)
  printf("%d, % 10.5lf  \n", (typename index_t::value_type)index, float(index));

 s0q15 out_table[count];

 for (
  uint32_t ix = 0;
  ix < count;
  ix++, lines++
 ) {

  float tmp  = tanh((float)index);
  
  table_t qtmp = table_t::from_float(tmp);
  table_t table[count];

  if (noisy) {
   printf(
    "% 8u, % 8d, % 10.5lf, % 10.5lf, % 8u, % 10.5lf  \n",
    lines,
    int16_t(index),
    float  (index),
    tmp,
    int16_t(qtmp),
    float  (qtmp)
   );
  }
  
  out_table[ix] = qtmp;
  
  index += (((uint32_t)UINT16_MAX) + 1) / count;
 }
  
 if (noisy) 
  printf("%lu lines.\n\n", lines);

 printf("#ifndef KL_%u_%s_%s_h \n", count, type_label, func_label);
 printf("#define KL_%u_%s_%s_h \n\n", count, type_label, func_label);
 printf("#define KL_%u_%s_%s_h_cells % \n\n", count, type_label, func_label, count);
 printf("namespace lamb {\n");
 printf(" namespace tables {\n");
 printf("  namespace %s%d_%s {\n", func_label, count, type_label);
 printf("   typedef %s q_t; \n", type_label);
 printf("   const size_t length = %d; \n", count);
 printf("   const q_t  data[] \n");
 printf("#ifdef __AVR__ \n");
 printf("   PROGMEM \n");
 printf("#endif \n");
 printf("   = { \n    ");

 for (
  uint32_t ix = 0;
  ix < count;
  ix++
 ) {

  char buff[32];
  snprintf(buff, 32, "q_t(%6d), ", out_table[ix].value);
   
  printf("%-12s", buff);

  if (((ix + 1) % 4) == 0)
   printf(" // %u \n    ", ix - 3);
  
  fflush(stdout);
 }

 printf("}; \n");
 printf("  } \n");
 printf(" } \n");
 printf("} \n");
 printf("\n");
 printf("#endif");

}


int main() {
 make_tanh_table<s0q15>("s0q14", "tanh", 512);
}
