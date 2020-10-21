
#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out
// g++ -std=gnu++14 -DNO_ARDUINO test.cpp && ./a.out

using namespace lamb;

typedef signed_frac<0,7> l_test_t;
typedef signed_frac<0,7> r_test_t;

#define BASE 1

int main() {
  printf("l ONE is %d.\n", l_test_t::ONE);
  printf("l MAX is %d.\n", l_test_t::MAX);
  printf("l MIN is %d.\n", l_test_t::MIN);
  printf("r ONE is %d.\n", r_test_t::ONE);
  printf("r MAX is %d.\n", r_test_t::MAX);
  printf("l MIN is %d.\n", l_test_t::MIN);
  
  for (  l_test_t::big_type x = l_test_t::MIN; x <= l_test_t::MAX; x += BASE) {
    printf("[%d]\n", x);
    
    for (  r_test_t::big_type y = r_test_t::MIN; y <= r_test_t::MAX; y += BASE) {    
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

  return 0;
}


