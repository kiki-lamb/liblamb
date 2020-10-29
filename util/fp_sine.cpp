#include "../include/lamb.h"

using namespace lamb;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_sine.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

////////////////////////////////////////////////////////////////////////////////

/// @param x   angle (with 2^15 units/circle)
/// @return     Sine value (Q12)

typedef s0q31   in_type;
typedef s1q14   out_type;
typedef s17q14  mid_type;

out_type qsin(in_type const & x_)
{
 mid_type x(x_.value >> 1);
 
 constexpr uint8_t  shift_1 = mid_type::CHARACTERISTIC;
 constexpr uint8_t  shift_2 = mid_type::CHARACTERISTIC + 1;
 constexpr mid_type pi      = mid_type::constants::pi;
 constexpr mid_type two     { 2,         0                 };
 constexpr mid_type one     { 1,         0                 };
 constexpr mid_type half    ( one     >> 1                 );
 constexpr mid_type quarter ( half    >> 1                 );
 constexpr mid_type B       = two      - pi / mid_type(4, 0);
 constexpr mid_type C       = one      - pi / mid_type(4, 0);
 mid_type           carry   = x       << shift_1;
 x                          = x        - half;
 x                          = x       << shift_2;
 x                          = x       >> shift_2;
 x                          = x        * x;
 x                          = x       << 2;
 mid_type           y       = x        * C;
 y                          = B        - y;
 x                          = x        * y;
 x                          = x       >> 2;
 y                          = quarter  - x;

 return out_type(carry.value >= 0 ? y : -y);
}

////////////////////////////////////////////////////////////////////////////////

int main() {
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

 return 0;
 printf("MAX: % 05.5lf %d \n", double(max), max.value); 
 printf("MIN: % 05.5lf %d \n", double(min), min.value);
}
