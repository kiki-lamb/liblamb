#ifndef LAMB_CHAMBERLIN_H_
#define LAMB_CHAMBERLIN_H_

#include <cmath>

namespace lamb {
  class chamberlin {
  public:
   double Q1, Q, F1, F, FS, D1, D2, L, H, B, N;
    
   chamberlin() :
    Q1(0), Q(0), F1(0), F(0), FS(0), D1(0), D2(0), L(0), H(0), B(0), N(0) {
    Q  = 1.0;
    F  = 1000;
    FS = 44100;

    set_frequency();
    set_q();
   }

   void set_frequency() {
    F1 = 2.0 * M_PI * F / FS;
    // printf("F1: % 05.3lf \n", F1);
   }

   void set_q() {
    Q1 = 1 / Q;
    // printf("Q1: % 05.3lf \n", Q1);
   }

//    L = D2 + F1 * D1
//    H = I - L - Q1*D1
//    B = F1 * H + D1
//    N = H + L
//    D1 = B
//    D2 = L

   q0n15s process(q0n15s I) {
    double If = double(I)     ;
    
    printf("% 5.3lf, ", If)   ;
    printf("% 5.3lf, ", F1)   ;        
    printf("% 5.3lf, ", Q1)   ;
        
    L  = D2 + F1 * D1         ;
    printf("% 5.3lf, ", L)    ;

    H  = I  - L  - Q1*D1      ;
    printf("% 5.3lf, ", H)    ;

    B  = F1 * H  + D1         ;
    printf("% 5.3lf, ", B)    ;
    
    N  = H  + L               ;
    printf("% 5.3lf, ", N)    ;

    D1 = B                    ;
    printf("% 5.3lf, ", D1)   ;
    
    D2 = L                    ;
    printf("% 5.3lf,  ", D2)  ;
        
    return q0n15s::from_double(L);
   }
  };
}

#endif /* LAMB_CHAMBERLIN_H_ */