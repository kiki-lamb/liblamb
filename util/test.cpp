
#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out
// g++ -std=gnu++14 -DNO_ARDUINO test.cpp && ./a.out

// Multiply tests:
//
// L/R     u0,8   u0,16  u0,32  u16,16  s0,7  s0,15  s0,31  s7,8  s15,16
// u0,8    Yes
// u0,16   Yes
// u0,32   Yes
// u8,8
// u16,16
// s0,7
// s0,15
// s0,31
// s7,8
// s15,16

using namespace lamb;

typedef unsigned_frac<0,32>  l_test_t;
typedef unsigned_frac<0,8>   r_test_t;

#define L_BASE ((l_test_t::MAX >> (sizeof(l_test_t::type) >> 1) >> 5) + 1)
#define R_BASE ((r_test_t::MAX >> (sizeof(r_test_t::type) >> 1) >> 5) + 1)

int main() {
  printf("THIS   is %u.\n", UINT32_MAX);
  printf("l BASE is %u.\n", L_BASE);
  printf("l ONE  is %u.\n", l_test_t::ONE);
  printf("l MAX  is %u.\n", l_test_t::MAX);
  printf("l MIN  is %u.\n", l_test_t::MIN);
  printf("r BASE is %u.\n", R_BASE);
  printf("r ONE  is %u.\n", r_test_t::ONE);
  printf("r MAX  is %u.\n", r_test_t::MAX);
  printf("r MIN  is %u.\n", r_test_t::MIN);
  
  for (  l_test_t::big_type x = l_test_t::MIN; x <= l_test_t::MAX; x += L_BASE) {
    printf("[%lld]\n", x);
    
    for (  r_test_t::big_type y = r_test_t::MIN; y <= r_test_t::MAX; y += R_BASE) {    
      l_test_t fx(x);
      r_test_t fy(y);
      
      {
        l_test_t fz = fx * fy;
        printf("Try %lld * %d: = %u \n", x, y, fz.val);
        fflush(stdout);
      }

      // {
      //   test_t fz = fx + fy;
      //   printf("Try %d + %d: = %d \n", x, y, fz.val);
      //   fflush(stdout);
      // }

      // {
      //   test_t fz = fx - fy;
      //   printf("Try %d - %d: = %d \n", x, y, fz.val);
      //   fflush(stdout);
      // }
      
      // if (y == 0) {
      //   continue;
      // }
      // else {
      //   test_t fz = fx / fy;
      //   printf("Try %d / %d: = %d \n", x, y, fz.val);
      //   fflush(stdout);
      // }
    }
  }

  printf("Done.\n");

  return 0;
}


