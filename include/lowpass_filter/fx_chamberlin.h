#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

#include <cmath>

namespace lamb {
  class fx_chamberlin {
  public:
   typedef sat_q15n16 qtype;
   typedef sat_q0n32 pqtype;
   
   qtype  Q1, Q, F1, D1, D2, L, H, B, N;
   pqtype F,  FS;
   
   fx_chamberlin() :
    Q1(0), Q(0), F1(0), F(0), FS(0), D1(0), D2(0), L(0), H(0), B(0), N(0) {
    Q  = qtype::from_float(1.0);
    F  = pqtype(1000 );
    FS = pqtype(44100);

    set_frequency();
    set_q();
   }

   void set_frequency() {
//    printf("F.val   => %llu \n",     F.val);
//    printf("F.valf  => % 05.5lf \n", F.to_float());
//    printf("FS.val  => %llu \n",     FS.val);
//    printf("FS.valf => % 05.5lf \n", FS.to_float());

//    printf("F_FS   => % 05.5lf %lu\n", F_FS.to_float(), F_FS.val);
    static const qtype PI2(qtype::from_float(2*M_PI));

//    printf("2M_PI   => % 05.5lf\n", F1.to_float());
    
//    printf("FF1: % 05.5lf %u\n", F1, F1.val);

    F1 = PI2 * (F / FS);
    
//    printf("FF2: % 05.5lf %u\n", F1, F1.val);
   }

   void set_q() {
    Q1 = qtype(1,0) / Q;

    //printf("Q1: % 05.5lf \n", Q1);
   }

//    L = D2 + F1 * D1
//    H = I - L - Q1*D1
//    B = F1 * H + D1
//    N = H + L
//    D1 = B
//    D2 = L

   sat_q0n15 process(sat_q0n15 I_) {
    sat_q15n16 I(I_. val << 1);
    
    printf("% 5.5lf, ", I.to_float())    ;
    printf("% 5.5lf, ", F1.to_float())   ;        
    printf("% 5.5lf, ", Q1.to_float())   ;
        
    L  = D2 + F1 * D1         ;
    printf("% 5.5lf, ", L.to_float())    ;

    H  = qtype(I)  - L  - Q1*D1      ;
    printf("% 5.5lf, ", H.to_float())    ;

    B  = F1 * H  + D1         ;
    printf("% 5.5lf, ", B.to_float())    ;
    
    N  = H  + L               ;
    printf("% 5.5lf, ", N.to_float())    ;

    D1 = B                    ;
    printf("% 5.5lf, ", D1.to_float())   ;
    
    D2 = L                    ;
    printf("% 5.5lf  ", D2.to_float())   ;
        
    return sat_q0n15::from_float(0.0);
   }
  };
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */
