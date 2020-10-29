#include "../include/lamb.h"

using namespace lamb;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_sine.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

////////////////////////////////////////////////////////////////////////////////

/// @param x   angle (with 2^15 units/circle)
/// @return     Sine value (Q12)

typedef s0q15 out_type;

out_type qsin(s0q31 ph_ix_)
{
 int32_t ph_ix(ph_ix_);
 int32_t carry;
 int32_t x2, y;
 
 constexpr int32_t shift_quad  = 13;
 constexpr int32_t shift_out   = 12; 
 constexpr s17q14 B            = s17q14(2, 0) - (s17q14::constants::pi >> 2);
 constexpr s17q14 C            = s17q14(1, 0) - (s17q14::constants::pi >> 2);

 carry  = ph_ix           << (30     - shift_quad                );// Semi-circ carry.

 ph_ix -= s17q14(1, 0).value;                                      // sine -> cosine calc

 ph_ix  = ph_ix           << (31     - shift_quad                );// Mask with PI
 ph_ix  = ph_ix           >> (31     - shift_quad                );  
 ph_ix  = ph_ix            * (ph_ix >> 2         * shift_quad-14 );// x =x^2 To Q14
 y      = B.value          - (ph_ix  * C.value  >> 14            );// B - x^2 * C
 y      = (1 << shift_out) - (ph_ix  * y        >> 16            );// A - x^2 * (B-x^2 * C)
 
 if (carry < 0) {
  y = -y;
 }
 
 return out_type(y);
}

////////////////////////////////////////////////////////////////////////////////

int main() {
 out_type  last(0);
 out_type  min(0);
 out_type  max(0);
 
 for (
  int32_t ix = 0;
  ix <= 32768;
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

 printf("MAX:  % 05.5lf %d \n", double(max), max.value); 
 printf("MIN:  % 05.5lf %d \n", double(min), min.value);
 printf("PI:   % 05.5lf %d \n", double(s17q14::constants::pi), s17q14::constants::pi.value);
 printf(
  "PI/4: % 05.5lf %d \n",
  double(s17q14::constants::pi >> 2),
  (s17q14::constants::pi >> 2).value
 );
 printf(
  "?:    % 05.5lf %d \n",
  double(s17q14(3516)),
  s17q14(3516)
 );
}
