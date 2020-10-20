#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out

using namespace lamb;

typedef unsigned_frac<0,16> test_t;

int main() {
  for (  size_t x = 0; x < (((size_t)test_t::ONE)); x++) {
    printf("[%u]\n", x);
    
    for (size_t y = 0; y < (((size_t)test_t::ONE)); y++) {
      test_t fx(x);
      test_t fy(y);
     
      {
        test_t fz = fx + fy;
        // printf("Try %zu + %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }

      {
        test_t fz = fx - fy;
        // printf("Try %zu - %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }
      
      {
        test_t fz = fx * fy;
        // printf("Try %zu * %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }

      if (y == 0) {
        continue; // don't div by 0
      }
      else {
        test_t fz = fx / fy;
        // printf("Try %zu / %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }
    }
  }

  printf("Done.\n");
}


