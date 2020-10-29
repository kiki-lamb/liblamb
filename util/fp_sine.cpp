#include "../include/lamb.h"

using namespace lamb;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_sine.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

////////////////////////////////////////////////////////////////////////////////

/// @param x   angle (with 2^15 units/circle)
/// @return     Sine value (Q12)

// typedef s3q12 out_type;
typedef s0q15 out_type;

out_type qsin(s0q31 ph_ix_)
{
 int32_t ph_ix(ph_ix_);
 int32_t carry, x2, y;
 static const int32_t qN = 13, qA = 12, B = 19900, C = 3516;

 carry    = ph_ix     << (30     - qN          );  // Semi-circle info into carry.
 ph_ix   -= 1         << (qN                   );  // sine -> cosine calc
 ph_ix    = ph_ix     << (31     - qN          );  // Mask with PI
 ph_ix    = ph_ix     >> (31     - qN          );  // Note: SIGNED shift! (to qN)
 ph_ix    = ph_ix      * (ph_ix >> 2   * qN-14 );  // x =x^2 To Q14
 y        = B          - (ph_ix  * C  >> 14    );  // B - x^2 * C
 y        = (1 << qA)  - (ph_ix  * y  >> 16    );  // A - x^2 * (B-x^2 * C)
 
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

 printf("MAX: % 05.5lf %d \n", double(max), max.value); 
 printf("MIN: % 05.5lf %d \n", double(min), min.value);
}
