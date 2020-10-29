#include "../include/lamb.h"

using namespace lamb;
using namespace std;

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_sine.cpp && .\a.exe > a.csv && sigrok-cli -I csv:column_formats="*a" -i a.csv -o x.sr

// A sine approximation via a third-order approx.
/// @param x    Angle (with 2^15 units/circle)
/// @return     Sine value (Q12)
int32_t isin_S3(int16_t x)
{
    // S(x) = x * ( (3<<p) - (x*x>>r) ) >> s
    // n : Q-pos for quarter circle             13
    // A : Q-pos for output                     12
    // p : Q-pos for parentheses intermediate   15
    // r = 2n-p                                 11
    // s = A-1-p-n                              17

 static const int qN = 13;
 static const int qA = 12;
 static const int qP = 15;
 static const int qR = 2 * 13 - qP;
 static const int qS = qN + qP +1 - qA;

 x = x << (30 - qN);          // shift to full int32_t range (Q13->Q30)
 
 if( (x ^ (x << 1)) < 0) {    // test for quadrant 1 or 2
  x = (1 << 31) - x;
 }
 
 x = x >> (30 - qN);
 
 return x * ( (3 << qP) - (x * x >> qR) ) >> qS;
}

////////////////////////////////////////////////////////////////////////////////

/// @param x   angle (with 2^15 units/circle)
/// @return     Sine value (Q12)
int32_t isin_S4(int32_t x)
{
    int c, x2, y;
    static const int qN = 13, qA = 12, B = 19900, C = 3516;

    c  = x << (30 - qN);              // Semi-circle info into carry.
    x -= 1 << qN;                 // sine -> cosine calc

    x  = x << (31 - qN);              // Mask with PI
    x  = x >> (31 - qN);              // Note: SIGNED shift! (to qN)
    x  = x * x >> (2 * qN-14);          // x =x^2 To Q14

    y  = B - (x * C >> 14);           // B - x^2 * C
    y  = (1 << qA) - (x * y >> 16);       // A - x^2 * (B-x^2 * C)

    return c >= 0 ? y : -y;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
 int32_t last = 0;
 
 for (
  int32_t ix = 0;
  ix <= 32768;
  ix++
 ) {
  last = isin_S4(ix);

   printf("% 05.5lf \n", last / 4096.0);
  
  }
}
