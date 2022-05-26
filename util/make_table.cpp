#include "./make_table.h"

double wf_sin(double in) {
  double pifrac = in*M_PI;
  return -sin(pifrac);
}

bool bitsqr(double in) {
  return in > 0.0;
}

double wf_sqr(double in) {
  return bitsqr(in) ? -1.0 : 1.0;
}

double wf_saw(double in) {
  return bitsqr(in) ? in - 1.0 : in + 1.0;
}

double wf_tri(double in) {
  in = wf_saw(in);

  if (in >= 0.5)
    return 2 * (0.5 - (in - 0.5));
  if (in <= -0.5)
    return 2 * (-0.5 - (in + 0.5));
  else
    return 2 * in;
}

double wf_silence(double in) {
  return 0.0;
}

int main() {
  if (false) {
    printf("saw\tsqr\tsin\ttri\t\n");
    for (int16_t ix = -100; ix <100; ix++) {
      double tmp = 0.01 * ix;
      printf("%16.06lf %16.06lf %16.06lf %16.06lf %16.06lf \n", tmp, wf_saw(tmp), wf_sqr(tmp), wf_sin(tmp), wf_tri(tmp));
    }
    return 0;
  }
  
  const   size_t sizes_len = 6;
  const   size_t sizes[sizes_len] = { 128, 256, 512, 1024, 2048, 4096 };

  typedef double(*wf_f)(double);
  const   size_t funcs_len = 5;
  const   wf_f   funcs[funcs_len] = { &wf_sin, &wf_sqr, &wf_saw, &wf_tri, &wf_silence };
  const   char   func_names[funcs_len][8] = { "sin", "sqr", "saw", "tri", "silence" };
  
  for (size_t funcs_ix = 0; funcs_ix < funcs_len; funcs_ix++)
    for (size_t sizes_ix = 0; sizes_ix < sizes_len; sizes_ix++) {
      make_table<uint8_t>(
        func_names[funcs_ix],
        funcs[funcs_ix],
        "uint8_t",
        "uint8_t",
        UINT8_MAX,
        "%12u",
        128,
        sizes[sizes_ix]
      );
      
      make_table<int8_t>(
        func_names[funcs_ix],
        funcs[funcs_ix],
        "int8_t",
        "int8_t",
        UINT8_MAX,
        "%12d",
        0,
        sizes[sizes_ix]
      );
      
      make_table<uint16_t>(
        func_names[funcs_ix],
        funcs[funcs_ix],
        "uint16_t",
        "uint16_t",
        UINT16_MAX,
        "%12u",
        32768,
        sizes[sizes_ix]
      );
      
      make_table<int16_t>(
        func_names[funcs_ix],
        funcs[funcs_ix],
        "int16_t",
        "int16_t",
        UINT16_MAX,
        "%12d",
        0,
        sizes[sizes_ix]
      );

          
      make_table<uint16_t>(
        func_names[funcs_ix],
        funcs[funcs_ix],
        "uint12_t",
        "uint16_t",
        4095,
        "%12u",
        2048,
        sizes[sizes_ix]
      );
      
      make_table<int16_t>(
        func_names[funcs_ix],
        funcs[funcs_ix],
        "int12_t",
        "int16_t",
        4095,
        "%12d",
        0,
        sizes[sizes_ix]
      );
    }

  ////////////////////////////////////////////////////////////////////////////////
  
  for (size_t sizes_ix = 0; sizes_ix < 2; sizes_ix++) {
    make_quarter_table<uint8_t>(
      "qsin",
      &wf_sin,
      "uint8_t",
      "uint8_t",
      UINT8_MAX,
      "%12u",
      0,
      sizes[sizes_ix]
    );
    
    make_quarter_table<uint16_t>(
      "qsin",
      &wf_sin,
      "uint16_t",
      "uint16_t",
      UINT16_MAX,
      "%12u",
      0,
      sizes[sizes_ix]
    );

    make_quarter_table<uint16_t>(
      "qsin",
      &wf_sin,
      "uint12_t",
      "uint16_t",
      4095,
      "%12u",
      2048,
      sizes[sizes_ix]
    );
  }
}


