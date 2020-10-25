// TODO:
// - division tests
// - multiplication tests

#define LAMB_TEST_FIX_MATH

#include "../include/lamb.h"
#include <cstring>
#include <cmath>

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-fix-math.cpp && .\a.exe

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
  printf(buff, x.to_float(), x.top(), x.bottom());                      \
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

#define TEST_OVERFLOW                                                   \
 {                                                                      \
  printf("Test for overflow:\n");                                       \
                                                                        \
  fix_t a(fix_t::MAX);                                                  \
                                                                        \
  a += a;                                                               \
                                                                        \
  if (a.overflow) {                                                     \
   successes ++;                                                        \
  }                                                                     \
  else {                                                                \
   fix_t b(fix_t::MAX);                                                 \
                                                                        \
   printf(                                                              \
    "%05.05lf + %05.05lf should have overflowed.",                      \
    b.to_float(),                                                       \
    b.to_float()                                                        \
   );                                                                   \
                                                                        \
   errors ++;                                                           \
  }                                                                     \
 }                                                                      

#define TEST_UNDERFLOW                                                  \
 {                                                                      \
  printf("Test for underflow:\n");                                      \
                                                                        \
  fix_t a(fix_t::MAX);                                                  \
                                                                        \
  a -= fix_t(fix_t::MAX);                                               \
  a -= fix_t(fix_t::MAX);                                               \
                                                                        \
  if (a.overflow) {                                                     \
   successes ++;                                                        \
  }                                                                     \
  else {                                                                \
   fix_t b(fix_t::MAX);                                                 \
                                                                        \
   printf(                                                              \
    "%05.05lf - %05.05lf - %05.05lf should have underflowed.",          \
    b.to_float(),                                                       \
    b.to_float(),                                                       \
    b.to_float()                                                        \
   );                                                                   \
                                                                        \
   errors ++;                                                           \
  }                                                                     \
 }                                                                      

#define TEST_CONVERSIONS(x, y, z0, z1, fprecis)                         \
 {                                                                      \
  fix_t a(fix_t::from_float(x));                                        \
  fix_t b(y);                                                           \
  fix_t c(z0, z1);                                                      \
                                                                        \
  TEST_FLEQ("lf", x, a.to_float(), fprecis);                            \
  TEST_FLEQ("lf", x, b.to_float(), fprecis);                            \
  TEST_FLEQ("lf", x, c.to_float(), fprecis);                            \
 }

#define TEST_PI(fmt, pi_precis)                                         \
 {                                                                      \
  fix_t fix_pi = fix_t::from_float(M_PI);                               \
  float unfix_pi = fix_pi.to_float();                                   \
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
  if (fix_t::CHARACTERISTIC > 0) {                                      \
   snprintf(buff0, 32, "% 05.10lf", 1.5*M_PI);                          \
   buff0[pi_precis+3] = 0;                                              \
   printf("1.5M_PI    : %s\n", buff0);                                  \
                                                                        \
   fix_pi = fix_t::from_float(1.5*M_PI);                                \
   unfix_pi = fix_pi.to_float();                                        \
                                                                        \
   snprintf(buff1, 32, "% 05.10lf", unfix_pi);                          \
   buff1[pi_precis+3] = 0;                                              \
   printf("1.5FIX_PI  : %s\n", buff1);                                  \
                                                                        \
   TEST_FLEQ(fmt, 1.5*M_PI, unfix_pi, pi_precis);                       \
                                                                        \
   snprintf(buff0, 32, "% 05.10lf", 2*M_PI);                            \
   buff0[pi_precis+3] = 0;                                              \
   printf("2M_PI      : %s\n", buff0);                                  \
                                                                        \
   fix_pi = fix_t::from_float(2*M_PI);                                  \
   unfix_pi = fix_pi.to_float();                                        \
                                                                        \
   snprintf(buff1, 32, "% 05.10lf", unfix_pi);                          \
   buff1[pi_precis+3] = 0;                                              \
   printf("2FIX_PI    : %s\n", buff1);                                  \
                                                                        \
   TEST_FLEQ(fmt, 2*M_PI, unfix_pi, pi_precis);                         \
  }                                                                     \
                                                                        \
  if (((fix_t::CHARACTERISTIC+fix_t::MANTISSA) % 2) == 1) {             \
   snprintf(buff0, 32, "% 05.10lf", -M_PI);                             \
   buff0[pi_precis+3] = 0;                                              \
   printf("-M_PI      : %s\n", buff0);                                  \
                                                                        \
   fix_pi = fix_t::from_float(-M_PI);                                   \
   unfix_pi = fix_pi.to_float();                                        \
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

 printf("\n\n[TESTING q%un%u:]\n\n", fix_t::CHARACTERISTIC, fix_t::MANTISSA);

 printf("Test converted 1...\n");
 TEST_CONVERSIONS(
  1.0,
  fix_t::ONE,
  1, 0,
  f_precis
 );
 
 printf("Test converted 0.5...\n");
 TEST_CONVERSIONS(
  0.5,
  fix_t::ONE >> 1,
  0, fix_t::ONE >> 1,
  f_precis
 );

 
 if (fix_t::CHARACTERISTIC > 0) {
  printf("Test converted 2.0...\n");
  TEST_CONVERSIONS(
   2.0,
   fix_t::ONE << 1,
   0, 1 << (fix_t::MANTISSA + 1),
   f_precis
  );
 }

 if ((fix_t::MANTISSA % 2) == 1) {
  printf("Test converted -1.0...\n");
  TEST_CONVERSIONS(
   -1.0,
   fix_t::ONE * -1,
   unsigned_int<(sizeof(typename fix_t::type))>::MAX, 0,
   f_precis
  );
 }

 TEST_OVERFLOW;

 TEST_UNDERFLOW;
 
 if (fix_t::CHARACTERISTIC > 0) {
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
 
 test_fix_math_type<q0n8,   2, 0>(successes, errors);
 test_fix_math_type<q0n7,   2, 0>(successes, errors);
 
 test_fix_math_type<q0n16,  3, 0>(successes, errors);
 test_fix_math_type<q0n15,  3, 0>(successes, errors);
 
 test_fix_math_type<q8n8,   3, 2>(successes, errors);
 test_fix_math_type<q7n8,   3, 2>(successes, errors);
 
 test_fix_math_type<q0n32,  3, 0>(successes, errors);
 test_fix_math_type<q0n31,  3, 0>(successes, errors);
 
 test_fix_math_type<q16n16, 3, 4>(successes, errors);
 test_fix_math_type<q15n16, 3, 4>(successes, errors);

 for (uint8_t ix = 0; ix < 80; ix++) printf("/");

 printf("\n\nTOTAL PASSED: %u / %u \n", successes, successes + errors);
}
