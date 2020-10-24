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
    // printf("F1: % 05.5lf \n", F1);
   }

   void set_q() {
    Q1 = 1 / Q;
    // printf("Q1: % 05.5lf \n", Q1);
   }
   
   sat_q0n15 process(sat_q0n15 input) {
//    printf("% 5.5lf, ", Q1)    ;

    printf("% 5.5lf, ", F1)    ;
    
    double I = input.to_float();
    printf("% 5.5lf, ", I)    ;
    
//    L = D2 + F1 * D1
//    H = I - L - Q1*D1
//    B = F1 * H + D1
//    N = H + L
//    D1 = B
//    D2 = L

    L  = D2 + F1 * D1         ;
    printf("% 5.5lf, ", L)    ;

    H  = I  - L  - Q1*D1      ;
    printf("% 5.5lf, ", H)    ;

    B  = F1 * H  + D1         ;
    printf("% 5.5lf, ", B)    ;
    
    N  = H  + L               ;
    printf("% 5.5lf, ", N)    ;

    D1 = B                    ;
    printf("% 5.5lf, ", D1)   ;
    
    D2 = L                    ;
    printf("% 5.5lf  ", D2)   ;
        
    return sat_q0n15::from_float(L);
   }
  };

  class fx_chamberlin {
  public:
   sat_q7n8 Q1, Q, F1, F, FS, D1, D2, L, H, B, N;
    
   fx_chamberlin() :
    Q1(0), Q(0), F1(0), F(0), FS(0), D1(0), D2(0), L(0), H(0), B(0), N(0) {
    Q.val  = 1.0;
    F.val  = 1000;
    FS.val = 44100;

    set_frequency();
    set_q();
   }

   void set_frequency() {
    auto pi2 = sat_q7n8::from_float(2.0 * M_PI);
    F1       = pi2;
    F1      *= F / FS;
    

    printf("F1: % 05.5lf \n", F1.to_float());
   }

   void set_q() {
    Q1 = sat_q7n8(sat_q7n8::ONE) / Q;
    // printf("Q1: % 05.5lf \n", Q1);
   }
   
   sat_q7n8 process(sat_q7n8 input) {
//    printf("% 5.5lf, ", Q1)    ;

    printf("% 5.5lf, ", F1)    ;
    
    sat_q7n8 I = input;
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
