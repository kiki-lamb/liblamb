#include <stdio.h>
#include <inttypes.h>
#include <cmath>

#define LAMB_NO_ARDUINO

#include "../include/lamb.h"

//////////////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 make_trig_tables.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr
 
//////////////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

//////////////////////////////////////////////////////////////////////////////////////////


typedef s0q31 tan_t;

tan_t tan_table[256] =
{
 tan_t(0L),      tan_t(804L),    tan_t(1609L),   tan_t(2414L),
 tan_t(3220L),   tan_t(4026L),   tan_t(4834L),   tan_t(5644L),
 tan_t(6455L),   tan_t(7268L),   tan_t(8083L),   tan_t(8901L),
 tan_t(9721L),   tan_t(10545L),  tan_t(11372L),  tan_t(12202L),
 
 tan_t(13036L),  tan_t(13874L),  tan_t(14717L),  tan_t(15564L),
 tan_t(16416L),  tan_t(17273L),  tan_t(18136L),  tan_t(19005L),
 tan_t(19880L),  tan_t(20762L),  tan_t(21650L),  tan_t(22546L),
 tan_t(23449L),  tan_t(24360L),  tan_t(25280L),  tan_t(26208L),
 
 tan_t(27146L),  tan_t(28093L),  tan_t(29050L),  tan_t(30018L),
 tan_t(30996L),  tan_t(31986L),  tan_t(32988L),  tan_t(34002L),
 tan_t(35030L),  tan_t(36071L),  tan_t(37126L),  tan_t(38196L),
 tan_t(39281L),  tan_t(40382L),  tan_t(41500L),  tan_t(42636L),
 
 tan_t(43790L),  tan_t(44963L),  tan_t(46156L),  tan_t(47369L),
 tan_t(48605L),  tan_t(49863L),  tan_t(51145L),  tan_t(52451L),
 tan_t(53784L),  tan_t(55144L),  tan_t(56532L),  tan_t(57950L),
 tan_t(59398L),  tan_t(60880L),  tan_t(62395L),  tan_t(63947L),
 
 tan_t(65536L),  tan_t(67165L),  tan_t(68835L),  tan_t(70548L),
 tan_t(72308L),  tan_t(74116L),  tan_t(75974L),  tan_t(77887L),
 tan_t(79856L),  tan_t(81885L),  tan_t(83977L),  tan_t(86135L),
 tan_t(88365L),  tan_t(90670L),  tan_t(93054L),  tan_t(95523L),
 
 tan_t(98082L),  tan_t(100736L), tan_t(103493L), tan_t(106358L),
 tan_t(109340L), tan_t(112447L), tan_t(115687L), tan_t(119071L),
 tan_t(122609L), tan_t(126314L), tan_t(130198L), tan_t(134276L),
 tan_t(138564L), tan_t(143081L), tan_t(147847L), tan_t(152884L),
 
 tan_t(158218L), tan_t(163878L), tan_t(169896L), tan_t(176309L),
 tan_t(183161L), tan_t(190499L), tan_t(198380L), tan_t(206870L),
 tan_t(216043L), tan_t(225990L), tan_t(236817L), tan_t(248648L),
 tan_t(261634L), tan_t(275959L), tan_t(291845L), tan_t(309568L),
 
 tan_t(329472L), tan_t(351993L), tan_t(377693L), tan_t(407305L),
 tan_t(441808L), tan_t(482534L), tan_t(531352L), tan_t(590958L),
 tan_t(665398L), tan_t(761030L), tan_t(888450L), tan_t(1066730L),
 tan_t(1334016L),tan_t(1779314L),tan_t(2669641L),tan_t(5340086L),
 
 -tan_t(2147483647L), -tan_t(5340086L), -tan_t(2669641L), -tan_t(1779314L),
 -tan_t(1334016L),    -tan_t(1066730L), -tan_t(888450L),  -tan_t(761030L),
 -tan_t(665398L),     -tan_t(590958L),  -tan_t(531352L),  -tan_t(482534L),
 -tan_t(441808L),     -tan_t(407305L),  -tan_t(377693L),  -tan_t(351993L),
 
 -tan_t(329472L),-tan_t(309568L),-tan_t(291845L),-tan_t(275959L),
 -tan_t(261634L),-tan_t(248648L),-tan_t(236817L),-tan_t(225990L),
 -tan_t(216043L),-tan_t(206870L),-tan_t(198380L),-tan_t(190499L),
 -tan_t(183161L),-tan_t(176309L),-tan_t(169896L),-tan_t(163878L),
 
 -tan_t(158218L),-tan_t(152884L),-tan_t(147847L),-tan_t(143081L),
 -tan_t(138564L),-tan_t(134276L),-tan_t(130198L),-tan_t(126314L),
 -tan_t(122609L),-tan_t(119071L),-tan_t(115687L),-tan_t(112447L),
 -tan_t(109340L),-tan_t(106358L),-tan_t(103493L),-tan_t(100736L),
 
 -tan_t(98082L), -tan_t(95523L), -tan_t(93054L), -tan_t(90670L),
 -tan_t(88365L), -tan_t(86135L), -tan_t(83977L), -tan_t(81885L),
 -tan_t(79856L), -tan_t(77887L), -tan_t(75974L), -tan_t(74116L),
 -tan_t(72308L), -tan_t(70548L), -tan_t(68835L), -tan_t(67165L),
 
 -tan_t(65536L), -tan_t(63947L), -tan_t(62395L), -tan_t(60880L),
 -tan_t(59398L), -tan_t(57950L), -tan_t(56532L), -tan_t(55144L),
 -tan_t(53784L), -tan_t(52451L), -tan_t(51145L), -tan_t(49863L),
 -tan_t(48605L), -tan_t(47369L), -tan_t(46156L), -tan_t(44963L),
 
 -tan_t(43790L), -tan_t(42636L), -tan_t(41500L), -tan_t(40382L),
 -tan_t(39281L), -tan_t(38196L), -tan_t(37126L), -tan_t(36071L),
 -tan_t(35030L), -tan_t(34002L), -tan_t(32988L), -tan_t(31986L),
 -tan_t(30996L), -tan_t(30018L), -tan_t(29050L), -tan_t(28093L),
 
 -tan_t(27146L), -tan_t(26208L), -tan_t(25280L), -tan_t(24360L),
 -tan_t(23449L), -tan_t(22546L), -tan_t(21650L), -tan_t(20762L),
 -tan_t(19880L), -tan_t(19005L), -tan_t(18136L), -tan_t(17273L),
 -tan_t(16416L), -tan_t(15564L), -tan_t(14717L), -tan_t(13874L),
 
 -tan_t(13036L), -tan_t(12202L), -tan_t(11372L), -tan_t(10545L),
 -tan_t(9721L),  -tan_t(8901L),  -tan_t(8083L),  -tan_t(7268L),
 -tan_t(6455L),  -tan_t(5644L),  -tan_t(4834L),  -tan_t(4026L),
 -tan_t(3220L),  -tan_t(2414L),  -tan_t(1609L),  -tan_t(804L)
 
};

//------------------------------------------------------------------------------

s0q31 qtan(s0q31 const & ba) {
 return tan_table[((ba.value + 0x4000) >> 15) & 0xFF];
}


////////////////////////////////////////////////////////////////////////////////

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
  
  float   tan_arg       = float(func_arg) * M_PI;
  float   func_result   = func(tan_arg); // float(func_arg));

  if (func_result > float(table_t::MAX)) {
   func_result = 169.0; // float(table_t::MAX) - 1;
  }
  
  table_t q_func_result = table_t::from_float(func_result);
  table_t table[count];

  out_table[ix] = q_func_result;  

  if (for_plot) {
   fprintf(fp, "  %6d, ",    int16_t(ix));
   fprintf(fp, "  % 6d",     func_arg.value);
   fprintf(fp, "  % 10.5lf", float(func_arg));
   fprintf(fp, ", % 10.5lf", tan_arg);
   fprintf(fp, ", % 10.5lf", float(q_func_result));
   fprintf(fp, ", % 15d",    q_func_result.value);
   fprintf(fp, ", % 10d",    tan_table[ix >> 2]);
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

 make_trig_table<s8q23>(1024, "s8q23", "tan",    tan, true, true);
}
