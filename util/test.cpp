#include "../include/lamb.h"

#include <iostream>

using namespace std;

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out
// g++ -std=gnu++14 -DNO_ARDUINO test.cpp && ./a.out

// Multiply tests:
//
// L/R     u0,8   u0,16  u0,32  u8,8  u16,16  s0,7  s0,15  s0,31  s7,8  s15,16
// u0,8    Yes    Yes    Yes    EXCL  EXCL    OMIT  OMIT   OMIT   EXCL  EXCL
// u0,16   Yes    Yes    Yes    EXCL  EXCL    OMIT  OMIT   OMIT   EXCL  EXCL
// u0,32   Yes    Yes    Yes    EXCL  EXCL    OMIT  OMIT   OMIT   EXCL  EXCL
// u8,8    Yes    Yes    Yes    ?     ?       OMIT  OMIT   OMIT   EXCL  EXCL
// u16,16  Yes    Yes    Yes    ?     ?       OMIT  OMIT   OMIT   EXCL  EXCL
// s0,7    Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,15   Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,31   Yes    Yes    Yes    EXCL  EXCL    Yes
// s7,8    
// s15,16  

using namespace lamb;

typedef signed_frac<0,31>      l_test_t;
typedef signed_frac<0,15>      r_test_t;

#define L_BASE ((l_test_t::MAX >> (sizeof(l_test_t::type) >> 1) >> 3) + 1)
#define R_BASE ((r_test_t::MAX >> (sizeof(r_test_t::type) >> 1) >> 4) + 1)

int main() {
  printf("THIS   is %u.\n", UINT32_MAX);
  printf("l BASE is %u.\n", L_BASE);
  printf("l ONE  is %d.\n", l_test_t::ONE);
  printf("l MAX  is %d.\n", l_test_t::MAX);
  printf("l MIN  is %d.\n", l_test_t::MIN);
  printf("r BASE is %d.\n", R_BASE);
  printf("r ONE  is %d.\n", r_test_t::ONE);
  printf("r MAX  is %d.\n", r_test_t::MAX);
  printf("r MIN  is %d.\n", r_test_t::MIN);
  
  for (  l_test_t::big_type x = l_test_t::MIN; x <= l_test_t::MAX; x += L_BASE) {
    for (  r_test_t::big_type y = r_test_t::MIN; y <= r_test_t::MAX; y += R_BASE) {    
      l_test_t fx(x);
      r_test_t fy(y);
      
      {
        l_test_t fz = fx * fy;
//        printf("Try %d * %llu: = %d \n", x, y, fz.val);

        cout << "Try " << x << " * " << y << ": ";
        printf("%d\n", fz.val);
        
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


