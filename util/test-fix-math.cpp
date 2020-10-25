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

#define TEST_EQ(fmt,x, y)                                 \
 if (x == y) {                                            \
  successes ++;                                           \
 }                                                        \
 else {                                                   \
  char buff[32];                                          \
  snprintf(buff, 32, "FAILED %%%s == %%%s.\n", fmt, fmt); \
  printf(buff, x, y);                                     \
  errors ++;                                              \
 }


#define TEST_FLEQ(fmt,x, y, precis)                       \
 if (compare_floats(x, y, precis)) {                      \
  successes ++;                                           \
 }                                                        \
 else {                                                   \
  char buff[32];                                          \
  snprintf(buff, 32, "FAILED %%%s == %%%s.\n", fmt, fmt); \
  printf(buff, x, y);                                     \
  errors ++;                                              \
 }                     

#define TEST_STREQ(x, y)                          \
 if (strcmp(x, y) == 0) {                         \
  successes ++;                                   \
 } else {                                         \
  printf("FAILED %s streq %s.\n", x, y);          \
  errors ++;                                      \
 }                     

#define NL \
 printf("\n")

#define CONVERSIONS(x, y, z0, z1, fprecis)              \
{                                               \
 fix_t a(fix_t::from_float(x));                 \
 fix_t b(y);                                    \
 fix_t c(z0, z1);                               \
                                                \
 PRINT("u", "a", a);                            \
 PRINT("u", "b", b);                            \
 PRINT("u", "c", c);                            \
                                                \
 TEST_EQ("u", a, b);                            \
 TEST_EQ("u", b, c);                            \
 TEST_EQ("u", a, c);                            \
                                                \
 TEST_FLEQ("lf", x, a.to_float(), fprecis);                \
 TEST_FLEQ("lf", x, b.to_float(), fprecis);                \
 TEST_FLEQ("lf", x, c.to_float(), fprecis);                \
}

#define TEST_PI(pi_precis)                      \
 {                                              \
  char buff0[32];                               \
  snprintf(buff0, 32, "% 05.10lf", M_PI);       \
  buff0[pi_precis+3] = 0;                       \
  printf("M_PI    : %s\n", buff0);              \
                                                \
  fix_t fix_pi = fix_t::from_float(M_PI);       \
  float unfix_pi = fix_pi.to_float();           \
  char buff1[32];                               \
  snprintf(buff1, 32, "% 05.10lf", unfix_pi);   \
  buff1[pi_precis+3] = 0;                       \
  printf("FIX_PI  : %s\n", buff1);              \
                                                \
  TEST_STREQ(buff0, buff1);                     \
}                                               

////////////////////////////////////////////////////////////////////////////////

template <typename fix_t, uint8_t f_precis, uint8_t pi_precis>
void test_fix_math_type() {
 size_t successes = 0;
 size_t errors    = 0;

 printf("[TESTING q%un%u:]\n\n", fix_t::CHARACTERISTIC, fix_t::MANTISSA);

 printf("Test converted 1:\n");
 CONVERSIONS(
  1.0,
  fix_t::ONE,
  1, 0,
  f_precis
 );
 NL;
 
 
 printf("Test converted 0.5:\n");
 CONVERSIONS(
  0.5,
  fix_t::ONE >> 1,
  0, fix_t::ONE >> 1,
  f_precis
 );
 NL;

 
 if (fix_t::CHARACTERISTIC > 0) {
  printf("Test converted 2.0:\n");
  CONVERSIONS(
   2.0,
   fix_t::ONE << 1,
   0, 1 << (fix_t::MANTISSA + 1),
   f_precis
  );
  NL;
 }

 if ((fix_t::MANTISSA % 2) == 1) {
  printf("Test converted -1.0:\n");
  CONVERSIONS(
   -1.0,
   fix_t::ONE * -1,
   1, 0,
   f_precis
  );
  NL;
 }
 
 if (fix_t::CHARACTERISTIC > 0) {
  printf("Test pi:\n");

  TEST_PI(pi_precis);
 }
 
 printf("\nPassed: %u / %u", successes, successes + errors);

 if (errors > 0) {
  printf(" [ERRRORS]");
 }
 
 printf("\n\n");
}

////////////////////////////////////////////////////////////////////////////////

int main() {
 NL;
 NL;

// test_fix_math_type<q0n8,   2, 5>();
 test_fix_math_type<q0n7,   2, 5>();

// test_fix_math_type<q0n16,  3, 5>();
// test_fix_math_type<q0n15,  3, 5>();
// test_fix_math_type<q8n8,   3, 2>();
// test_fix_math_type<q7n8,   3, 5>();

// test_fix_math_type<q0n32,  3, 5>();
// test_fix_math_type<q0n31,  3, 5>();
// test_fix_math_type<q16n16, 3, 5>();
// test_fix_math_type<q15n16, 3, 5>();


}
