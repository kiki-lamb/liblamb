#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out

using namespace lamb;

typedef signed_frac<0,7> test_t;

int main() {
//  for (  size_t x = (((size_t)test_t::ONE)); x < (((size_t)test_t::MAX)); x++) {
  for (  int16_t x = -128; x < (((int16_t)test_t::MAX)); x++) {
    printf("[%d]\n", x);
    
//    for (size_t y = 2; y < (((size_t)test_t::MAX)); y++) {
    for (int16_t y = -128; y < (((int16_t)test_t::MAX)); y++) {
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
        printf("Try %d * %d: = %d \n", x, y, fz.val);
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
}


