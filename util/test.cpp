#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out

using namespace lamb;

typedef signed_frac<15,16> test_t;

#define BASE 16

int main() {
  printf("ONE is %d.\n", test_t::ONE);
  printf("MAX is %d.\n", test_t::MAX);
  
  for (  int64_t x = -BASE; x <= (((int32_t)test_t::MAX)); x+= BASE) {
    printf("[%lld]\n", x);
    
    for (int64_t y = -BASE; y <= (((int32_t)test_t::MAX)); y+= BASE) {
      test_t fx(x);
      test_t fy(y);
     
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
        test_t fz = fx * fy;
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


