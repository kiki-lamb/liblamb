#include "../include/lamb.h"

// g++ -std=gnu++14 -DNO_ARDUINO test.cpp && ./a.out

using namespace lamb;

int main() {
  for (size_t x = 0; x < 256; x++) {
    for (size_t y = 0; y < 256; y++) {
      unsigned_frac<0,8> fx(x);
      unsigned_frac<0,8> fy(y);
     
      {
        unsigned_frac<0,8> fz = fx + fy;
        printf("Try %zu + %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }

      {
        unsigned_frac<0,8> fz = fx - fy;
        printf("Try %zu - %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }
      
      {
        unsigned_frac<0,8> fz = fx * fy;
        printf("Try %zu * %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }

      if (y == 0) {
        continue; // don't div by 0
      }
      else {
        unsigned_frac<0,8> fz = fx / fy;
        printf("Try %zu / %zu: = %u \n", x, y, fz.val);
        fflush(stdout);
      }
       

    }
  }
}


