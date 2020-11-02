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

// make_trig_table<s0q15>(512);

template <typename table_t>
void make_trig_table(
 size_t const & count,
 const char * type_label,
 const char * func_label,
 double (*func) (double),
 bool to_stdout,
 bool for_plot
) {
 // typedef q<0, table_t::WHOLE + 2, table_t::FRAC - 2> index_t;
 typedef s0q15 index_t;
  
 char fname[64];
 snprintf(fname, 64, "kl_%lu_%s_%s.h", count, type_label, func_label);
 FILE *fp = to_stdout ? stdout : fopen(fname, "w");

 if (! for_plot) {
  printf("#include \"%s\" \n", fname);
 }
 
 index_t  func_arg = index_t::MIN;
 uint32_t lines = 0;

 s0q15 out_table[count];

 for (
  uint32_t ix = 0;
  ix < count;
  ix++, lines++
 ) {
  float tmp  = func((float)func_arg);
  
  table_t qtmp = table_t::from_float(tmp);
  table_t table[count];

  out_table[ix] = qtmp;

  if (for_plot) {
   fprintf(fp, "  %8d, ",    int16_t(ix));
   fprintf(fp, "  % 10d",    func_arg.value);
   fprintf(fp, "  % 10.5lf", float(func_arg));
   fprintf(fp, ", % 10.5lf", tmp);
  }
  
  func_arg += (((uint16_t)UINT16_MAX) + 1) / count;

  fprintf(fp, "\n");
 }

 if (! for_plot) {
  fprintf(fp, "#ifndef KL_%u_%s_%s_h \n", count, type_label, func_label);
  fprintf(fp, "#define KL_%u_%s_%s_h \n\n", count, type_label, func_label);
  fprintf(fp, "#define KL_%u_%s_%s_h_cells % \n\n", count, type_label, func_label, count);
  fprintf(fp, "namespace lamb {\n");
  fprintf(fp, " namespace tables {\n");
  fprintf(fp, "  namespace %s%d_%s {\n", func_label, count, type_label);
  fprintf(fp, "   typedef %s q_t; \n", type_label);
  fprintf(fp, "   const size_t length = %d; \n", count);
  fprintf(fp, "   const q_t  data[] \n");
  fprintf(fp, "#ifdef __AVR__ \n");
  fprintf(fp, "   PROGMEM \n");
  fprintf(fp, "#endif \n");
  fprintf(fp, "   = { \n    ");

  for (
   uint32_t ix = 0;
   ix < count;
   ix++
  ) {
   
   if (! for_plot) {
    char buff[32];
    snprintf(buff, 32, "q_t(%6d), ", out_table[ix].value);

    fprintf(fp, "%-12s", buff);
    
    if (((ix + 1) % 4) == 0) {
     fprintf(fp, " // %u \n    ", ix - 3);
    }
    
    fflush(stdout);
   }
   
   fprintf(fp, "}; \n");
   fprintf(fp, "  } \n");
   fprintf(fp, " } \n");
   fprintf(fp, "} \n");
   fprintf(fp, "\n");
   fprintf(fp, "#endif");
  }
 }
 
 if (! to_stdout)
  fclose(fp);
}

////////////////////////////////////////////////////////////////////////////////

template <typename table_t>
void make_trig_tables(
 const char * type_label
) {
 const size_t sizes[] = { 256, 512, 1024, 2048, 4096 };
 
 for (
  size_t ix = 2;
  ix < 3;
  ix++
 ) {
  make_trig_table<table_t>(sizes[ix], type_label, "acos",   acos);
  make_trig_table<table_t>(sizes[ix], type_label, "acosh",  acosh);
  make_trig_table<table_t>(sizes[ix], type_label, "atan",   atan);
  make_trig_table<table_t>(sizes[ix], type_label, "cos",    cos);
  make_trig_table<table_t>(sizes[ix], type_label, "tan",    tan);
  make_trig_table<table_t>(sizes[ix], type_label, "cosh",   cosh);
  make_trig_table<table_t>(sizes[ix], type_label, "sinh",   sinh);
  make_trig_table<table_t>(sizes[ix], type_label, "tanh",   tanh);
  make_trig_table<table_t>(sizes[ix], type_label, "atanh",  atanh);        
 }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
// make_trig_tables<s0q7> ("s0q7");
// make_trig_tables<s0q15>("s0q15");
// make_trig_tables<s0q31>("s0q31");

 make_trig_table<s0q15>(1024, "s0q15", "tan",    tan, true, true);
}
