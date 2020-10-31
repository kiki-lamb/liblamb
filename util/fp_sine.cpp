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


namespace math {
 typedef   s17q14   mid_type;

 constexpr mid_type operator ""_mid(long double const x) {
  return mid_type::from_double(x);
 }
 
 template <typename out_type>
 out_type qsin(s0q31 const & x_)
  {
   //-----------------------------------------------------------------------------
   constexpr uint8_t  q_shift { mid_type::FRAC                   };
   constexpr mid_type pi      { mid_type::PI                     };
   constexpr mid_type two     { 2.0_mid                          };
   constexpr mid_type one     { 1.0_mid                          };
   constexpr mid_type half    { 0.5_mid                          };
   constexpr mid_type B       { two        - pi / 4.0_mid        };
   constexpr mid_type C       { one        - pi / 4.0_mid        };

   printf("% 8d, ", x_);
      
   //--------------------------------------------------------------
   mid_type           x       { x_.value >> 1                    }; printf("% 8d, ", x);  
   mid_type           cry     { x         << q_shift             }; printf("% 8d, ", cry);
   //--------------------------------------------------------------                      
   x                          = x          - half                 ; printf("% 13d, ", x);  
   x                          = x         << q_shift + 1          ; printf("% 13d, ", x);  
   x                          = x         >> q_shift + 1          ; printf("% 13d, ", x);  
   x                          = x          * x                    ; printf("% 13d, ", x);  
   x                          = x         << 2                    ; printf("% 13d, ", x);  
   //--------------------------------------------------------------                      
   mid_type           y       { x          * C                   }; printf("% 13d, ", y);  
   //--------------------------------------------------------------                      
   y                          = B          - y                    ; printf("% 13d, ", y);  
   y                          = y          * x                    ; printf("% 13d, ", y);  
   y                          = one        - y                    ; printf("% 13d, ", y);  
   y                          = cry.value >= 0 ? y : -y           ; printf("% 13d, ", y);  
   //--------------------------------------------------------------
   return                       out_type(y)                       ;
  }
};
 
////////////////////////////////////////////////////////////////////////////////

int main() {
 typedef s0q31 out_type;
 
 out_type  last(0);
 out_type  min(0);
 out_type  max(0);
 
 for (
  uint64_t ix = 0;
  ix < 65536;
  ix++
 ) {
  last = math::qsin<s0q31>(s0q31(ix));

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
