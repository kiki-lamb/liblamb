#include "../include/lamb.h"

////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_sine.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

////////////////////////////////////////////////////////////////////////////////

void pprint_bits_32(uint32_t const & t0) {
  {
    for(uint32_t mask = 0x80000000; mask; mask >>= 1) {
      if (mask & t0) {
#ifdef LAMB_NO_ARDUINO
       printf("1");
#else
       Serial.print('1'); Serial.flush();
#endif
      }
      else {
#ifdef LAMB_NO_ARDUINO
       printf("0");
#else
       Serial.print('0'); Serial.flush();
#endif
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

/// @param x   angle (with 2^15 units/circle)
/// @return     Sine value (Q12)

typedef s0q31   in_type;
typedef s0q15   out_type;
typedef s17q14  mid_type;

out_type qsin(in_type const & x_)
{
 constexpr uint8_t  q_shift { mid_type::CHARACTERISTIC             };
 constexpr mid_type pi      { mid_type::constants::pi              };
 constexpr mid_type four    { 4,         0                         };
 constexpr mid_type two     { four    >> 1                         };
 constexpr mid_type one     { two     >> 1                         };
 constexpr mid_type half    { one     >> 1                         };
 constexpr mid_type quarter { half    >> 1                         };
 constexpr mid_type B       { two      - pi / mid_type(4, 0)       };
 constexpr mid_type C       { one      - pi / mid_type(4, 0)       };
 //-----------------------------------------------------------------------------
 mid_type           x       { x_      << q_shift - 1               }; 
 mid_type           carry   { x       << q_shift                   };
 //-----------------------------------------------------------------------------
 x                          = x        - half                       ;
 x                          = x       << q_shift + 1                ;
 x                          = x       >> q_shift + 1                ;
 x                          = x        * x                          ;
 x                          = x       << 2                          ;
  //-----------------------------------------------------------------------------
 mid_type           y       { x        * C                          };
 //-----------------------------------------------------------------------------
 y                          = B        - y                          ;
 x                          = x        * y                          ;
 y                          = one      - x                          ;
 //-----------------------------------------------------------------------------
 return out_type(carry.value >= 0 ? y : -y);
}

////////////////////////////////////////////////////////////////////////////////

int main() {

// for (uint8_t ix = 1; ix < 64; ix++)
//  printf("%d: %u \n", ix, size_fit_bits(ix));
 
 out_type  last(0);
 out_type  min(0);
 out_type  max(0);
 
 for (
  int32_t ix = 0;
  ix < 65535;
  ix++
 ) {
  last = qsin(s0q31(ix));

  // printf("%d, % 05.5lf \n", last, last / 4096.0);
  printf("% 05.5lf \n", double(last));

  if (last > max)
   max = last;

  if (last < min)
   min = last;
  }

// return 0;
 printf("MAX: % 05.5lf %d \n", double(max), max.value); 
 printf("MIN: % 05.5lf %d \n", double(min), min.value);
}
