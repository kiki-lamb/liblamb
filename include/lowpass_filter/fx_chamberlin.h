#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

#include <cmath>

namespace lamb {
  class fx_chamberlin {
  public:
   typedef sat_q15n16 qtype;
   
   qtype Q1, Q, F1, F, FS, D1, D2, L, H, B, N;
    
   fx_chamberlin() :
    Q1(0), Q(0), F1(0), F(0), FS(0), D1(0), D2(0), L(0), H(0), B(0), N(0) {
    Q  = qtype::from_float(1.0);
    F  = qtype(1000,0);
    FS = qtype(44100);

    set_frequency();
    set_q();
   }

   void set_frequency() {
    F1 = qtype::from_float(2.0) * qtype::from_float(M_PI) * F / FS;

    // printf("F1: % 05.5lf \n", F1);
   }

   void set_q() {
    Q1 = qtype::from_float(1) / Q;

    // printf("Q1: % 05.5lf \n", Q1);
   }

//    L = D2 + F1 * D1
//    H = I - L - Q1*D1
//    B = F1 * H + D1
//    N = H + L
//    D1 = B
//    D2 = L

   sat_q0n15 process(sat_q0n15 input) {
//    double I = input.to_float();
//    
//    printf("% 5.5lf, ", I)    ;
//    printf("% 5.5lf, ", F1)   ;        
//    printf("% 5.5lf, ", Q1)   ;
//        
//    L  = D2 + F1 * D1         ;
//    printf("% 5.5lf, ", L)    ;
//
//    H  = I  - L  - Q1*D1      ;
//    printf("% 5.5lf, ", H)    ;
//
//    B  = F1 * H  + D1         ;
//    printf("% 5.5lf, ", B)    ;
//    
//    N  = H  + L               ;
//    printf("% 5.5lf, ", N)    ;
//
//    D1 = B                    ;
//    printf("% 5.5lf, ", D1)   ;
//    
//    D2 = L                    ;
//    printf("% 5.5lf  ", D2)   ;
//        
//    return sat_q0n15::from_float(L);
    
    return sat_q0n15::from_float(0.0);
   }
  };
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */
