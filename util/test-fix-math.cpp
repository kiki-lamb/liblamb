#include "../include/lamb.h"
#include <cstring>
#include <cmath>

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-fix-math.cpp && .\a.exe

using namespace lamb;

#define PRINT(fmt, name, x)                                             \
 {                                                                      \
  char  buff[32];                                                       \
  snprintf(buff, 32, "%-8s: %% 05.5lf %%%s.%%%s \n", name, fmt, fmt);     \
  printf(buff, x.to_float(), x.top(), x.bottom());                      \
 }                                               

#define TEST_EQ(x, y)  \
 if (x == y) {         \
  successes ++;        \
 } else {              \
  printf("FAIL.\n");   \
  errors ++;           \
 }                     

#define TEST_STREQ(x, y)  \
 if (strcmp(x, y) == 0) { \
  successes ++;           \
 } else {                 \
  printf("FAIL.\n");      \
 }                     

#define NL \
 printf("\n")

#define CONVERSIONS(x, y, z0, z1)               \
{                                               \
 fix_t a(fix_t::from_float(x));                 \
 fix_t b(y);                                    \
 fix_t c(z0, z1);                               \
                                                \
 PRINT("u", "a", a);                            \
 PRINT("u", "b", b);                            \
 PRINT("u", "c", c);                            \
                                                \
 TEST_EQ(a, b);                                 \
 TEST_EQ(b, c);                                 \
 TEST_EQ(a, c);                                 \
 TEST_EQ(x, a.to_float());                      \
 TEST_EQ(x, b.to_float());                      \
 TEST_EQ(x, c.to_float());                      \
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

template <typename fix_t, uint8_t pi_precis>
void test_fix_math_type() {
 size_t successes = 0;
 size_t errors    = 0;

 printf("Testing Q%un%u:\n\n", fix_t::CHARACTERISTIC, fix_t::MANTISSA);
 
 CONVERSIONS(1.0, fix_t::ONE, 1, 0);
 CONVERSIONS(0.5, fix_t::ONE >> 1, 0, 1 << (fix_t::MANTISSA - 1));
 CONVERSIONS(2.0, fix_t::ONE << 1, 0, 1 << (fix_t::MANTISSA + 1));

 if ((fix_t::MANTISSA % 2) == 1) {
  CONVERSIONS(-1.0, fix_t::ONE * -1, 1, 0);  
 }
 
 TEST_PI(pi_precis);
 
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
 
 test_fix_math_type<q8n8, 2>();
 test_fix_math_type<q7n8, 2>();
 test_fix_math_type<q16n16, 4>();
 test_fix_math_type<q15n16, 4>();
}
