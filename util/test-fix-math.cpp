#include "../include/lamb.h"

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-fix-math.cpp && .\a.exe

using namespace lamb;

#define PRINT(fmt, name, x)                                             \
 {                                                                      \
  char  buff[32];                                                       \
  snprintf(buff, 32, "%s: %% 05.5lf %%%s.%%%s \n", name, fmt, fmt);     \
  printf(buff, x.to_float(), x.top(), x.bottom());                      \
 }                                               

#define TEST_EQ(x, y) \
  successes += x == y;

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
}                                               \
                                                \
NL; 




template <typename fix_t>
void test_fix_math_type(size_t & successes, size_t & failures) {

 CONVERSIONS(1.0, fix_t::ONE, 1, 0);
 CONVERSIONS(0.5, fix_t::ONE >> 1, 0, 1 << (fix_t::MANTISSA - 1));
 CONVERSIONS(2.0, fix_t::ONE << 1, 0, 1 << (fix_t::MANTISSA + 1));
}

int main() {
 size_t successes = 0;
 size_t errors    = 0;
 
 test_fix_math_type<q8n8>(successes, errors);
 
 printf("\nPassed: %u / %u \n", successes, successes + errors);
}
