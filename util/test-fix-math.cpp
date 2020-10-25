#include "../include/lamb.h"

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test-fix-math.cpp && .\a.exe

using namespace lamb;

#define PRINT(name, x) \
 printf("%s: % 05.5lf %u.%u \n", name, x.to_float(), x.top(), x.bottom());

#define TEST_EQ(x, y) \
  successes += x == y;

#define NL \
 printf("\n")

template <typename fix_t>
void test_fix_math_type(size_t & successes, size_t & failures) {

 {
  fix_t a(fix_t::from_float(1.0));
  fix_t b(fix_t::ONE);
  fix_t c(1, 0);

  PRINT("a", a);
  PRINT("b", b);
  PRINT("c", c);

  TEST_EQ(a, b);
  TEST_EQ(b, c);
  TEST_EQ(a, c);
  TEST_EQ(1.0, a.to_float());
  TEST_EQ(1.0, b.to_float());
  TEST_EQ(1.0, c.to_float());
 }

 NL;
 
 {
  fix_t a(fix_t::from_float(0.5));
  fix_t b(fix_t::ONE >> 1);
  fix_t c(0, 1 << (fix_t::MANTISSA - 1));
  
  PRINT("a", a);
  PRINT("b", b);
  PRINT("c", c);

  TEST_EQ(a, b);
  TEST_EQ(b, c);
  TEST_EQ(a, c);
  TEST_EQ(1.0, a.to_float());
  TEST_EQ(1.0, b.to_float());
  TEST_EQ(1.0, c.to_float());

 } 

 NL;
 
 {
  fix_t a(fix_t::from_float(2.0));
  fix_t b(fix_t::ONE << 1);
  fix_t c(0, 1 << (fix_t::MANTISSA + 1));
  
  PRINT("a", a);
  PRINT("b", b);
  PRINT("c", c);
  
  TEST_EQ(a, b);
  TEST_EQ(b, c);
  TEST_EQ(a, c);
  TEST_EQ(1.0, a.to_float());
  TEST_EQ(1.0, b.to_float());
  TEST_EQ(1.0, c.to_float());

 } 
}

int main() {
 size_t successes = 0;
 size_t errors    = 0;
 
 test_fix_math_type<q8n8>(successes, errors);
 
 printf("\nPassed: %u / %u \n", successes, successes + errors);
}
