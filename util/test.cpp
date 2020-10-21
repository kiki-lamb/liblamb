
#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out
// g++ -std=gnu++14 -DNO_ARDUINO test.cpp && ./a.out

using namespace lamb;

typedef signed_frac<0,15>   l_test_t;
typedef unsigned_frac<0,16> r_test_t;

#define BASE 1

int main() {
  printf("l ONE is %d.\n", l_test_t::ONE);
  printf("l MAX is %d.\n", l_test_t::MAX);
  printf("r ONE is %d.\n", r_test_t::ONE);
  printf("r MAX is %d.\n", r_test_t::MAX);
  
  for (  int64_t x = -128; x <= (((int16_t)l_test_t::MAX)); x+= BASE) {
    printf("[%lld]\n", x);
    
    for (int64_t y = 0; y <= (((uint16_t)r_test_t::MAX)); y+= BASE) {
      l_test_t fx(x);
      r_test_t fy(y);
      
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
      
      {
        l_test_t fz = fx * fy;
        printf("Try %lld * %lld: = %d \n", x, y, fz.val);
        fflush(stdout);
      }

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


