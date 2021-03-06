// TODO:
// - division tests
// - multiplication tests
//
// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-fix-math.cpp && .\a.exe

#define LAMB_TEST_FIX_MATH

#include "../include/lamb.h"
#include <cstring>
#include <cmath>

using namespace std;
using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

bool compare_floats(float x, float y, uint8_t precis) {
 char buff0[32];
 char buff1[32];

 char fmt[32];

 snprintf(fmt, 32, "%%05.0%dlf", precis);

 snprintf(buff0, 32, fmt, x);
 snprintf(buff1, 32, fmt, y);

 bool ret = strcmp(buff0, buff1) == 0;

 if (! ret) {
 printf("Failed compare '%s' <> '%s'\n", buff0, buff1);
 }

 return ret;
}
////////////////////////////////////////////////////////////////////////////////

#define PRINT(fmt, name, x)                                             \
 {                                                                      \
  char  buff[32];                                                       \
  snprintf(buff, 32, "%-8s: %% 05.5lf %%%s.%%%s \n", name, fmt, fmt);   \
  printf(buff, float(x), x.top(), x.bottom());                         \
 }                                               

#define TEST_EQ(fmt,x, y)                                               \
 if (x == y) {                                                          \
  successes ++;                                                         \
 }                                                                      \
 else {                                                                 \
  char buff[32];                                                        \
  snprintf(buff, 32, "FAILED EQ %%%s == %%%s.\n", fmt, fmt);            \
  printf(buff, x, y);                                                   \
  errors ++;                                                            \
 }


#define TEST_FLEQ(fmt, x, y, precis)                                    \
 if (compare_floats(x, y, precis)) {                                    \
  successes ++;                                                         \
 }                                                                      \
 else {                                                                 \
  char buff[32];                                                        \
  snprintf(buff, 32, "FAILED FLEQ %%%s == %%%s.\n", fmt, fmt);          \
  printf(buff, x, y);                                                   \
  errors ++;                                                            \
 }                     

#define TEST_STREQ(x, y)                                                \
 if (strcmp(x, y) == 0) {                                               \
  successes ++;                                                         \
 } else {                                                               \
  printf("FAILED STREQ %s == %s.\n", x, y);                             \
  errors ++;                                                            \
 }                     

#define NL \
 printf("\n")

// TEST_EQ("u", a, b);                          
// TEST_EQ("u", b, c);                            
// TEST_EQ("u", a, c);                            
// PRINT("u", "a", a);
// PRINT("u", "b", b);
// PRINT("u", "c", c);

#define TEST_CONVERSIONS(x, y, z0, z1, fprecis)                         \
 {                                                                      \
  fix_t a(fix_t::from_float(x));                                       \
  fix_t b(y);                                                           \
  fix_t c(z0, z1);                                                      \
                                                                        \
  TEST_FLEQ("lf", x, float(a), fprecis);                               \
  TEST_FLEQ("lf", x, float(b), fprecis);                               \
  TEST_FLEQ("lf", x, float(c), fprecis);                               \
 }

#define TEST_PI(fmt, pi_precis)                                         \
 {                                                                      \
  fix_t fix_pi = fix_t::from_float(M_PI);                              \
  float unfix_pi = float(fix_pi);                                      \
                                                                        \
  char buff0[32];                                                       \
  char buff1[32];                                                       \
                                                                        \
  snprintf(buff0, 32, "% 05.10lf", M_PI);                               \
  buff0[pi_precis+3] = 0;                                               \
  printf("M_PI       : %s\n", buff0);                                   \
                                                                        \
  snprintf(buff1, 32, "% 05.10lf", unfix_pi);                           \
  buff1[pi_precis+3] = 0;                                               \
  printf("FIX_PI     : %s\n", buff1);                                   \
                                                                        \
  TEST_FLEQ(fmt, M_PI, unfix_pi, pi_precis);                            \
                                                                        \
  if (fix_t::WHOLE > 2) {                                               \
   snprintf(buff0, 32, "% 05.10lf", 1.5*M_PI);                          \
   buff0[pi_precis+3] = 0;                                              \
   printf("1.5M_PI    : %s\n", buff0);                                  \
                                                                        \
   fix_pi = fix_t::from_float(1.5*M_PI);                               \
   unfix_pi = float(fix_pi);                                           \
                                                                        \
   snprintf(buff1, 32, "% 05.10lf", unfix_pi);                          \
   buff1[pi_precis+3] = 0;                                              \
   printf("1.5FIX_PI  : %s\n", buff1);                                  \
                                                                        \
   TEST_FLEQ(fmt, 1.5*M_PI, unfix_pi, pi_precis);                       \
  }                                                                     \
                                                                        \
  if (fix_t::WHOLE > 2) {                                               \
   snprintf(buff0, 32, "% 05.10lf", 2*M_PI);                            \
   buff0[pi_precis+3] = 0;                                              \
   printf("2M_PI      : %s\n", buff0);                                  \
                                                                        \
   fix_pi = fix_t::from_float(2*M_PI);                                 \
   unfix_pi = float(fix_pi);                                           \
                                                                        \
   snprintf(buff1, 32, "% 05.10lf", unfix_pi);                          \
   buff1[pi_precis+3] = 0;                                              \
   printf("2FIX_PI    : %s\n", buff1);                                  \
                                                                        \
   TEST_FLEQ(fmt, 2*M_PI, unfix_pi, pi_precis);                         \
  }                                                                     \
                                                                        \
  if (((fix_t::WHOLE+fix_t::FRAC) % 2) == 1) {                          \
   snprintf(buff0, 32, "% 05.10lf", -M_PI);                             \
   buff0[pi_precis+3] = 0;                                              \
   printf("-M_PI      : %s\n", buff0);                                  \
                                                                        \
   fix_pi = fix_t::from_float(-M_PI);                                  \
   unfix_pi = float(fix_pi);                                           \
                                                                        \
   snprintf(buff1, 32, "% 05.10lf", unfix_pi);                          \
   buff1[pi_precis+3] = 0;                                              \
   printf("-FIX_PI    : %s\n", buff1);                                  \
                                                                        \
   TEST_FLEQ(fmt, -M_PI, unfix_pi, pi_precis);                          \
  }                                                                     \
 }                                               

////////////////////////////////////////////////////////////////////////////////

template <typename fix_t, uint8_t f_precis, uint8_t pi_precis>
void test_fix_math_type(size_t & out_successes, size_t & out_errors) {
 size_t successes = 0;
 size_t errors    = 0;

 for (uint8_t ix = 0; ix < 80; ix++) printf("/");

 printf("\n\n[TESTING q%un%u:]\n\n", fix_t::WHOLE, fix_t::FRAC);

 printf("MIN:  %ld \n", fix_t::MIN);
 printf("MAX:  %ld \n", fix_t::MAX);
 printf("ONE:  %ld \n", fix_t::ONE);
 
 printf("Test converted 1...\n");
 TEST_CONVERSIONS(
  1.0,
  fix_t::ONE,
  1u, 0u,
  f_precis
 );
 
 printf("Test converted 0.5...\n");
 TEST_CONVERSIONS(
  0.5,
  fix_t::ONE.value >> 1,
  0, fix_t::ONE.value >> 1,
  f_precis
 );

 
 if (fix_t::WHOLE > 1) {
  printf("Test converted 2.0...\n");
  TEST_CONVERSIONS(
   2.0,
   fix_t::ONE.value << 1,
   0, 1 << (fix_t::FRAC + 1),
   f_precis
  );
 }

 if ((fix_t::FRAC % 2) == 1) {
  printf("Test converted -1.0...\n");
  TEST_CONVERSIONS(
   -1.0,
   fix_t::ONE.value * -1,
   unsigned_int<(sizeof(typename fix_t::value_type))>::MAX, 0,
   f_precis
  );
 }

 if (fix_t::WHOLE > 0) {
  printf("\nTest pi...\n");

  TEST_PI("lf", pi_precis);
 }

 
 printf("\nPASSED: %u / %u", successes, successes + errors);

 if (errors > 0) {
  printf(" [ERRORS]");
 }
 
 printf("\n\n");

 out_successes += successes;
 out_errors += errors;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
 NL;
 NL;

 size_t successes = 0;
 size_t errors = 0;

 goto spot;

 test_fix_math_type<u0q8,   2, 0 >(successes, errors);
 test_fix_math_type<s0q7,   2, 0 >(successes, errors);
 
 test_fix_math_type<u0q16,  3, 0 >(successes, errors);
 test_fix_math_type<s0q15,  3, 0 >(successes, errors);
 
 test_fix_math_type<u8q8,   1, 2 >(successes, errors);
 test_fix_math_type<s7q8,   1, 2 >(successes, errors);
 
 test_fix_math_type<u0q32,  3, 0 >(successes, errors);
 test_fix_math_type<s0q31,  3, 0 >(successes, errors);
 
 test_fix_math_type<u16q16, 3, 4 >(successes, errors);
 test_fix_math_type<s15q16, 3, 4 >(successes, errors);

 test_fix_math_type<u2q14,  3, 3 >(successes, errors);
 test_fix_math_type<u2q30,  6, 5 >(successes, errors); 

 for (uint8_t ix = 0; ix < 80; ix++) printf("/");


 printf("\n\nTOTAL PASSED: %u / %u \n\n", successes, successes + errors);
 
spot:
 {
  u0q8  x0(0, 128);       printf("u0q8:   % 05.05lf % 12u % 12llu \n", float(x0), x0.value,  u0q8::ONE);
  u0q16 x1 = u0q16(x0);   printf("u0q16:  % 05.05lf % 12u % 12llu \n", float(x1), x1.value, u0q16::ONE);
  u0q32 x2 = u0q32(x1);   printf("u0q32:  % 05.05lf % 12u % 12llu \n", float(x2), x2.value, u0q32::ONE);
  u0q16 x3 = u0q16(x2);   printf("u0q16:  % 05.05lf % 12u % 12llu \n", float(x3), x3.value, u0q16::ONE);
  u0q8  x4 = u0q8(x3);    printf("u0q8:   % 05.05lf % 12u % 12llu \n", float(x4), x4.value,  u0q8::ONE);

  printf("\n");
 }


 q<16,8,8> xx(2,0);
 q<0 ,8,8> yy(4,128);

 auto zz = xx * yy;

 printf("==> %5.5lf \n", float(zz));
 
 // {
 //  u0q8  x0(0, 128);       printf("u0q8:   % 05.05lf % 12u % 12llu \n",        float(x0), x0.value,  u0q8::ONE);
 //  s7q8  x1 = s7q8(x0);    printf("s7q8:   % 05.05lf % 12d % 12lld \n",        float(x1), x1.value,  s7q8::ONE);
 //  x1.value = -128;        printf("s7q8:   % 05.05lf % 12d % 12lld \n",        float(x1), x1.value,  s7q8::ONE);  
 //  u0q8  x2 = u0q8(x1);    printf("u0q8:   % 05.05lf % 12u % 12llu \n",        float(x2), x2.value,  u0q8::ONE);

 //  printf("\n");
 // } 

 // {
 //  u0q8   x0(0, 128);      printf("u0q8:   % 05.05lf % 12u % 12llu \n", float(x0), x0.value,  u0q8::ONE);
 //  u8q8   x1 = u8q8(x0);   printf("u8q8:   % 05.05lf % 12u % 12llu \n", float(x1), x1.value,  u8q8::ONE);
 //  u16q16 x2 = u16q16(x1); printf("u16q16: % 05.05lf % 12u % 12llu \n", float(x2), x2.value,u16q16::ONE);
 //  u24q8  x3 = u24q8(x2);  printf("u24q8:  % 05.05lf % 12u % 12llu \n", float(x3), x3.value, u0q32::ONE);
 //  u16q16 x4 = u16q16(x3); printf("u16q16: % 05.05lf % 12u % 12llu \n", float(x4), x4.value,u16q16::ONE);
 //  u8q8   x5 = u8q8(x4);   printf("u8q8:   % 05.05lf % 12u % 12llu \n", float(x5), x5.value,  u8q8::ONE);
 //  u0q8   x6 = u0q8(x5);   printf("u0q8:   % 05.05lf % 12u % 12llu \n", float(x6), x6.value,  u0q8::ONE);

 //  printf("\n");
 // }

 // {
 //  u8q8   x0(1, 0);         printf("u8q8:   % 05.05lf % 12u % 12llu  \n", float(x0), x0.value,    u8q8::ONE);
 //  u16q16 x1 = u16q16(x0);  printf("u16q16: % 05.05lf % 12u % 12llu  \n", float(x1), x1.value,  u16q16::ONE);
 //  u8q8   x2 = u8q8(x1);    printf("u8q8:   % 05.05lf % 12u % 12llu  \n", float(x2), x2.value,    u8q8::ONE);

 //  printf("\n");
 // }

 // {
 //  s0q7  x0(0, 128u);       printf("s0q7:   % 05.05lf % 12d  % 12lld \n", float(x0), x0.value,   s0q7::ONE);
 //  s0q15 x1 = s0q15(x0);    printf("s0q15:  % 05.05lf % 12d  % 12lld \n",  float(x1), x1.value,  s0q15::ONE);
 //  s0q31 x2 = s0q31(x1);    printf("s0q31:  % 05.05lf % 12d  % 12lld \n",  float(x2), x2.value,  s0q31::ONE);
 //  s0q15 x3 = s0q15(x2);    printf("s0q15:  % 05.05lf % 12d  % 12lld \n",  float(x3), x3.value,  s0q15::ONE);
 //  s0q7  x4 = s0q7(x3);     printf("s0q7:   % 05.05lf % 12d  % 12lld \n",  float(x4), x4.value,   s0q7::ONE);

 //  printf("\n");
 // }

 // {
 //  s7q8   x0(1, 0);         printf("s7q8:   % 05.05lf % 12d  % 12lld \n", float(x0), x0.value,   s7q8::ONE);
 //  s15q16 x1 = s15q16(x0);  printf("s15q16: % 05.05lf % 12d  % 12lld \n", float(x1), x1.value, s15q16::ONE);
 //  s7q8   x2 = s7q8(x1);    printf("s7q8:   % 05.05lf % 12d  % 12lld \n", float(x2), x2.value,   s7q8::ONE);

 //  printf("\n");
 // }

 // {
 //  s7q24 x(s7q24::from_float(0.666));      printf("X: % 12ld % 12.10lf \n", x.value, float(x));
 //  s0q15 y(x);                             printf("Y: % 12ld % 12.10lf \n", y.value, float(y));
 // }

 // {
 //  s7q24 x(s7q24::from_float(-0.40));      printf("X: % 12ld % 12.10lf \n", x.value, float(x));
 //  s0q15 y(x);                             printf("Y: % 12d % 12.10lf \n", y.value, float(y));
 // }

 u0q16 _feedback(0);
 u0q8  res(118);

 _feedback = res;

 printf("==> %d \n", _feedback.value);

}
