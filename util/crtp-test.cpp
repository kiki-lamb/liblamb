#include "../include/lamb.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

// g++ -DLAMB_NO_ARDUINO crtp-test.cpp && .\a.exe

////////////////////////////////////////////////////////////////////////////////

using namespace lamb;

////////////////////////////////////////////////////////////////////////////////

// P double  Direct.
// P      t  Direct.
// _      =  Default.
// P      ~  Direct.
// P      +  Direct.
// P      -  Direct.
// P      *  Direct.
// P      /  Direct.
// -      %  No.
// P     u~  Direct.
// P     <<  Direct.
// P     >>  Direct.
// P      >  Direct.
// P      <  Direct
// P     ==  Direct.
// P     u-  *
// C     !=  ==
// C     >=  >,  ==
// C     <=  >,  ==
// C     ++  +,  =
// C     --  +,  =
// C     +=  +,  =
// C     -=  -,  =
// C     /=  /,  =
// -     %=  %,  =
// C     *=  *,  =
// C    <<=  <<, =
// C    >>=  >>, =
// P     u+  No.

////////////////////////////////////////////////////////////////////////////////

int main() {
 typedef mathematized<q<15, 16>> t;

 t x(t::PI);
 t y(t::from_double(0.5));

 printf("=> % 5.6lf \n", double(x / y));

// t z({0,128});

 q<8,8> zz ({1, 128});
  
 printf("=> % 5.5lf \n", double(zz));

 mathematized<q<8,8>> yy ({1, 128});
  
 printf("=> % 5.5lf \n", double(yy));
}
