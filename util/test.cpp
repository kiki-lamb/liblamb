#include "../include/lamb.h"

using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO test.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

using namespace lamb;

typedef q8n8    l_test_t;
typedef q0n8    r_test_t;

#define L_BASE ((l_test_t::MAX >> (sizeof(l_test_t::type) >> 1) >> 4) + 1)
#define R_BASE ((r_test_t::MAX >> (sizeof(r_test_t::type) >> 1) >> 4) + 1)

int main() {
 moog_filter mf;

 sat_q0n15 acc(q0n15::MIN);

 sat_q8n8  mul = sat_q8n8::from_float(0.605);
 sat_q0n15 inp = sat_q0n15::from_float(-0.992);

 printf("m=> % 04.3f \n", mul.to_float());
 printf("i=> % 04.3f \n", inp.to_float()); 
 printf("*=> % 04.3f \n", (inp * mul).to_float());
 
 printf("input,   ffff,   fbc,    fb,     sub,    inpp,   mul,    inppp,  inv_fp, inv_fpp,out1,   in1\n");
 for(size_t ix = 0; ix < 200L; ix ++) {
  acc += 256;

  // printf("%ld\n", acc.val);
  
  auto x = mf.process(acc);

  printf("\n");
 }
}

// void test() {
//  printf("l BASE is %u.\n", L_BASE);
//  printf("l ONE  is %u.\n", l_test_t::ONE);
//  printf("l MAX  is %u.\n", l_test_t::MAX);
//  printf("l MIN  is %u.\n", l_test_t::MIN);
//  printf("r BASE is %u.\n", R_BASE);
//  printf("r ONE  is %u.\n", r_test_t::ONE);
//  printf("r MAX  is %u.\n", r_test_t::MAX);
//  printf("r MIN  is %u.\n", r_test_t::MIN);
// 
//  for (    l_test_t::big_type x = l_test_t::MIN; x <= l_test_t::MAX; x += L_BASE) {
//   for (  r_test_t::big_type y = r_test_t::MIN; y <= r_test_t::MAX; y += R_BASE) {    
//    l_test_t fx(x);
//    r_test_t fy(y);
// 
//    {
//     l_test_t fz = fx * fy;
// 
//     cout << "Try " << x << " * " << y << ": ";
//     printf("%u\n", fz.val);
//         
//     fflush(stdout);
//    }
/// 
//    // {
//    //   test_t fz = fx + fy;
//    //   printf("Try %d + %d: = %d \n", x, y, fz.val);
//    //   fflush(stdout);
//    // }
// 
//    // {
//    //   test_t fz = fx - fy;
//    //   printf("Try %d - %d: = %d \n", x, y, fz.val);
//    //   fflush(stdout);
//    // }
//       
//    // if (y == 0) {
//    //   continue;
//    // }
//    // else {
//    //   test_t fz = fx / fy;
//    //   printf("Try %d / %d: = %d \n", x, y, fz.val);
//    //   fflush(stdout);
//    // }
//   }
//  }
// 
//  printf("Done.\n");
// }
// 
//
