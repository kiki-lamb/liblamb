#ifndef LAMB_CHAMBERLIN_H_
#define LAMB_CHAMBERLIN_H_

#include <cmath>
#include <stdio.h>

namespace lamb {
  class fx_chamberlin {
  public:
   sat_q15n16 Q1, Q, F1, F, FS, D1, D2, L, H, B, N;
    
   fx_chamberlin() :
    Q1(0), Q(0), F1(0), F(1000,0), FS(44100,0), D1(0), D2(0), L(0), H(0), B(0), N(0) {
    Q.val  = 1.0;

    set_frequency();
    set_q();
   }

   void set_frequency() {
    printf("Set frequency to % 05.5lf %u... \n", F.to_float(), F.val);
    
    float fpi2 = 2.0 * M_PI;
    // printf("fpi2: % 05.5lf \n", fpi2);
    
    sat_q15n16 pi2 = sat_q15n16::from_float(fpi2);

    // printf("PI2: % 05.5lf \n", pi2.to_float()); fflush(stdout);

    sat_q15n16 f_div_fs(F / FS);

    // printf("f_div_fs: % 05.5lf %u \n", f_div_fs.to_float(), f_div_fs.val);
    
    F1       = pi2;
    F1      *= f_div_fs;
    

    printf("F1: % 05.5lf %u \n", F1.to_float(), F1.val);
   }

   void set_q() {
    Q1 = sat_q15n16(sat_q15n16::ONE) / Q;
   }
   
   sat_q15n16 process(sat_q15n16 input) {
//    printf("% 5.5lf, ", Q1)    ;

    printf("% 5.5lf, ", F1)    ;
    
    sat_q15n16 I = input;
    printf("% 5.5lf, ", I.to_float())    ;
    
//    L = D2 + F1 * D1
//    H = I - L - Q1*D1
//    B = F1 * H + D1
//    N = H + L
//    D1 = B
//    D2 = L

    L  = D2 + F1 * D1         ;
    printf("% 5.5lf, ", L.to_float())    ;

    H  = I  - L  - Q1*D1      ;
    printf("% 5.5lf, ", H.to_float())    ;

    B  = F1 * H  + D1         ;
    printf("% 5.5lf, ", B.to_float())    ;
    
    N  = H  + L               ;
    printf("% 5.5lf, ", N.to_float())    ;

    D1 = B                    ;
    printf("% 5.5lf, ", D1.to_float())   ;
    
    D2 = L                    ;
    printf("% 5.5lf  ", D2.to_float())   ;
        
    return L;
   }
  };
}

#endif /* LAMB_CHAMBERLIN_H_ */
