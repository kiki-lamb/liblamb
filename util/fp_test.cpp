#include "../include/lamb.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

// g++ -std=gnu++17 -DLAMB_NO_ARDUINO fp_test.cpp && .\a.exe

////////////////////////////////////////////////////////////////////////////////

int main() {
 // pi:      51471  3.14154 
 // one:     16384  1.00000 
 // one:     16384  1.00000 
 // two:     32768  2.00000 
 // half:     8192  0.50000 
 // B:       19901  1.21466 
 // C:        3517  0.21466

 // 3.14159265359
 // printf("MPI:           % 010.10lf \n", M_PI);
 // printf("pi:   % 8d % 010.10lf \n", s17q14::PI.value,         float(s17q14::PI));
 // printf("dec:  % 8d % 010.10lf \n", s17q14::PI - s17q14(3,0), float(s17q14::PI - s17q14(3,0)));
 // printf("pi+1: % 8d % 010.10lf \n", s17q14::PI.value + 1,     float(s17q14::PI + 1));
 // printf("pi-1: % 8d % 010.10lf \n", s17q14::PI.value - 1,     float(s17q14::PI - 1));
 // printf("x:    % 8d % 010.10lf \n", float(s17q14::ffrom_float(1.5)));
 // printf("x:    % 8d % 010.10lf \n", float(s15q16::ffrom_float(1.5)));
 printf("x:    % 10.10lf \n", float(s15q16::ffrom_float(1.5).scaled_add(s17q14::ffrom_float(1.5))));
 printf("x:    % 10.10lf \n", float(s15q16::ffrom_float(1.5) + s17q14::ffrom_float(1.5)));
}
