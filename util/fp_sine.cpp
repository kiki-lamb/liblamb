#include "../include/lamb.h"

using namespace lamb;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_sine.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

////////////////////////////////////////////////////////////////////////////////

/// @param x   angle (with 2^15 units/circle)
/// @return     Sine value (Q12)

typedef s0q31   in_type;
typedef s1q14   out_type;

out_type qsin(in_type const & x_)
{
 int32_t x(x_.value >> 1);
 int32_t c;
 int32_t y;
 
 constexpr int32_t shift_qcirc = 13;
 constexpr int32_t shift_out   = 12;
 constexpr s17q14  B           = s17q14(2, 0) - s17q14::constants::pi / s17q14(4, 0);
 constexpr s17q14  C           = s17q14(1, 0) - s17q14::constants::pi / s17q14(4, 0);
 constexpr s17q14  one         { 1, 0     };
 constexpr s17q14  half        ( one >> 1 );
 
 c  = x                 << (30 - shift_qcirc      );  // Semi-circle info into carry.
 x -= half.value;
 x  = x                 << (31 - shift_qcirc      );  // Mask with PI
 x  = x                 >> (31 - shift_qcirc      ); 
 x  = x * x             >> (2  * shift_qcirc  - 14);  // x=x^2 To Q14
 y  = B.value            - (x  * C.value     >> 14);  // B - x^2 * C
 y  = (1 << shift_out)   - (x  * y           >> 16);  // A - x^2*(B-x^2*C)
 
 return out_type(c>=0 ? y : -y);
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
