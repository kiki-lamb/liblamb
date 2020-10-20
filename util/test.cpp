#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out

using namespace lamb;

typedef unsigned_frac<16,16> test_t;

int main() {
  for (  size_t x = (((size_t)test_t::ONE)); x < (((size_t)test_t::MAX)); x++) {
    printf("[%zu]\n", x);
    
    for (size_t y = 2; y < (((size_t)test_t::MAX)); y++) {
      test_t fx(x);
      test_t fy(y);
     
      {
        test_t fz = fx + fy;
        printf("Try %zu + %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }

      {
        test_t fz = fx - fy;
        printf("Try %zu - %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }
      
      {
        test_t fz = fx * fy;
        printf("Try %zu * %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }

      if (y == 0) {
        continue;
      }
      else {
        test_t fz = fx / fy;
        printf("Try %zu / %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }
    }
  }

  printf("Done.\n");
}


