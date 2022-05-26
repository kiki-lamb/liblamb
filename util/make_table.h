#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#define STR(a) #a

static bool printed_header = false;

template <typename value_t>
inline void make_table(
  const char * WF_NAME,
  double     (*FUNC)(double),
  const char * DECOR_NAME,
  const char * TYPE_NAME,
  size_t       MAX,
  const char * FMT,
  size_t       BIAS,
  size_t       SIZE) {
  FILE *fp = stdout;
  char buff[64];
  snprintf(buff, 64, "kl_%lu_%s_%s.h", SIZE, DECOR_NAME, WF_NAME);

#ifndef PLOT
  printf("#include \"%s\"\n", buff);
  fp = fopen(buff, "w");
  snprintf(buff, 64, "kl_%lu_%s_%s_h", SIZE, DECOR_NAME, WF_NAME);
  fprintf(fp,"#ifndef %s\n", buff);
  fprintf(fp,"#define %s\n", buff);
  fprintf(fp,"\n");
  snprintf(buff, 64, "KL_%lu_%s_%s_cells", SIZE, DECOR_NAME, WF_NAME);
  fprintf(fp,"#define %s %lu\n", buff, SIZE);
  fprintf(fp,"\n");
  fprintf(fp,"namespace lamb {\n");
  fprintf(fp,"  namespace tables {\n");
  fprintf(fp,"    namespace %s%lu_%s {\n", WF_NAME, SIZE, DECOR_NAME);
  fprintf(fp,"      typedef %s value_type;\n", TYPE_NAME);
  fprintf(fp,"      const   size_t length = %lu;\n", SIZE);
  fprintf(fp,"      const   %s data[]\n", TYPE_NAME);
  fprintf(fp,"#ifdef __AVR__\n");
  fprintf(fp,"PROGMEM\n");
  fprintf(fp,"#endif\n");
  fprintf(fp,"      = {\n");
#else
  if (! printed_header) {
    fprintf(fp,"%s\trofrac\ttmp_d\ttmp_v\t\n", buff);
    printed_header = true;
  }
#endif
  
  for (size_t ix = 0; ix < SIZE; ix++) {
#ifndef PLOT
    if (0 == ix)
      fprintf(fp,"      ");
#endif
    double  rofrac = ix / ((double)SIZE);
    double  tmp_d  = ((*FUNC)( (rofrac-0.5)*2 ))*MAX;
    value_t tmp_v  = value_t((tmp_d*0.5) + BIAS);

#ifdef PLOT
    fprintf(fp,"%4lu  %8.4lf  %16.06lf  ", ix, rofrac, tmp_d);
    fprintf(fp,FMT, tmp_v);
    fprintf(fp,"\n");
#else    
    fprintf(fp,"%8d, ", tmp_v);
    if (ix && (0 == (ix + 1) % 32))
      fprintf(fp,"// %lu\n    ", ix);
    if (ix && (0 == (ix + 1) % 8))
      fprintf(fp,"\n      ");
#endif
  }
  
#ifndef PLOT
  fprintf(fp,"};\n");
  fprintf(fp,"    }\n");
  fprintf(fp,"  }\n");
  fprintf(fp,"}\n");
  fprintf(fp,"#endif\n");
#else
  fprintf(fp,"\n");
#endif
}

//================================================================================

  
template <typename value_t>
inline void make_quarter_table(
  const char * WF_NAME,
  double     (*FUNC)(double),
  const char * DECOR_NAME,
  const char * TYPE_NAME,
  size_t       MAX,
  const char * FMT,
  size_t       BIAS,
  size_t       SIZE) {
  FILE *fp = stdout;
  char buff[64];
  snprintf(buff, 64, "kl_%lu_%s_%s.h", SIZE, DECOR_NAME, WF_NAME);

#ifndef PLOT
  printf("#include \"%s\"\n", buff);
  fp = fopen(buff, "w");
  snprintf(buff, 64, "kl_%lu_%s_%s_h", SIZE, DECOR_NAME, WF_NAME);
  fprintf(fp,"#ifndef %s\n", buff);
  fprintf(fp,"#define %s\n", buff);
  fprintf(fp,"\n");
  snprintf(buff, 64, "KL_%lu_%s_%s_cells", SIZE, DECOR_NAME, WF_NAME);
  fprintf(fp,"#define %s %lu\n", buff, SIZE);
  fprintf(fp,"\n");
  fprintf(fp,"namespace lamb {\n");
  fprintf(fp,"  namespace tables {\n");
  fprintf(fp,"    namespace %s%lu_%s {\n", WF_NAME, SIZE, DECOR_NAME);
  fprintf(fp,"      typedef %s value_type;\n", TYPE_NAME);
  fprintf(fp,"      const   size_t length = %lu;\n", SIZE);
  fprintf(fp,"      const   %s data[]\n", TYPE_NAME);
  fprintf(fp,"#ifdef __AVR__\n");
  fprintf(fp,"PROGMEM\n");
  fprintf(fp,"#endif\n");
  fprintf(fp,"= {\n");
#else
  if (! printed_header) {
    fprintf(fp,"%s\trofrac\ttmp_d\ttmp_v\t\n", buff);
    printed_header = true;
  }
#endif
  
  for (size_t ix = 0; ix < SIZE; ix++) {
#ifndef PLOT
    if (0 == ix)
      fprintf(fp,"    ");
#endif
    double  rofrac = ix / ((double)(SIZE<<2));
    double  tmp_d  = ((*FUNC)((rofrac-0.5)*2))*MAX;
    value_t tmp_v  = value_t(tmp_d);

#ifdef PLOT
    fprintf(fp,"%4lu  %8.4lf  %16.06lf  ", ix, rofrac, tmp_d);
    fprintf(fp,FMT, tmp_v);
    fprintf(fp,"\n");
#else    
    fprintf(fp,"%8d, ", tmp_v);
    if (ix && (0 == (ix + 1) % 32))
      fprintf(fp,"// %lu\n    ", ix);
    if (ix && (0 == (ix + 1) % 8))
      fprintf(fp,"\n    ");
#endif
  }
  
#ifndef PLOT
  fprintf(fp,"};\n");
  fprintf(fp,"    }\n");
  fprintf(fp,"  }\n");
  fprintf(fp,"}\n");
  fprintf(fp,"#endif\n");
#else
  fprintf(fp,"\n");
#endif
}

