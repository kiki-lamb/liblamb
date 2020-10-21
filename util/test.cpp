#include "../include/lamb.h"

#include <iostream>

using namespace std;

// g++ -std=gnu++14 -DNO_ARDUINO -DLAMB_FP_SATURATE test.cpp && ./a.out
// g++ -std=gnu++14 -DNO_ARDUINO test.cpp && ./a.out

// Multiply tests:
//
// L/R     u0,8   u0,16  u0,32  u8,8  u16,16  s0,7  s0,15  s0,31  s7,8  s15,16
// u0,8    Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u0,16   Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u0,32   Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u8,8    Yes    Yes    Yes    ?     ?       EXCL  EXCL   EXCL   EXCL  EXCL
// u16,16  Yes    Yes    Yes    ?     ?       EXCL  EXCL   EXCL   EXCL  EXCL
// s0,7    Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,15   Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,31   Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s7,8    
// s15,16  

// Multiply tests #2:
//
// L/R     u0,8   u0,16  u0,32  u8,8  u16,16  s0,7  s0,15  s0,31  s7,8  s15,16
// u0,8    Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u0,16   Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u0,32   Yes    Yes    Yes    EXCL  EXCL    EXCL  EXCL   EXCL   EXCL  EXCL
// u8,8    Redo   Redo   Redo   ?     ?       EXCL  EXCL   EXCL   EXCL  EXCL
// u16,16  Redo   Redo   Redo   ?     ?       EXCL  EXCL   EXCL   EXCL  EXCL
// s0,7    Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,15   Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s0,31   Yes    Yes    Yes    EXCL  EXCL    Yes   Yes    Yes    EXCL  EXCL
// s7,8    Redo   Redo   Redo   ?     ?       Redo  Redo   Redo   EXCL  EXL
// s15,16  Redo   Redo   Redo   ?     ?       Redo  Redo   Redo   EXCL  EXCL

using namespace lamb;

typedef q0n7  l_test_t;
typedef q0n8  r_test_t;

#define L_BASE ((l_test_t::MAX >> (sizeof(l_test_t::type) >> 1) >> 4) + 1)
#define R_BASE ((r_test_t::MAX >> (sizeof(r_test_t::type) >> 1) >> 4) + 1)

int main() {
  sat_q0n8  x(0x40);

  sat_q0n16 z(x);

  printf("Conv: %d\n", z.val);

  q0n8  y(0x80);
  
  printf("Add: %d\n", (x + y).val);

  x += unsigned_frac<0,8,false>(0x10);

  printf("Add2: %d\n", (x + y).val);
  
  printf("l BASE is %u.\n", L_BASE);
  printf("l ONE  is %d.\n", l_test_t::ONE);
  printf("l MAX  is %d.\n", l_test_t::MAX);
  printf("l MIN  is %d.\n", l_test_t::MIN);
  printf("r BASE is %u.\n", R_BASE);
  printf("r ONE  is %u.\n", r_test_t::ONE);
  printf("r MAX  is %u.\n", r_test_t::MAX);
  printf("r MIN  is %u.\n", r_test_t::MIN);

  return 0;
  
  for (    l_test_t::big_type x = l_test_t::MIN; x <= l_test_t::MAX; x += L_BASE) {
    for (  r_test_t::big_type y = r_test_t::MIN; y <= r_test_t::MAX; y += R_BASE) {    
      l_test_t fx(x);
      r_test_t fy(y);
      
      {
        l_test_t fz = fx * fy;
//        printf("Try %d * %lld: = %u \n", x, y, fz.val);

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


