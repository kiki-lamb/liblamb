#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

namespace lamb {
  class fx_chamberlin {
  public:
   typedef q15n16s sqint;
   typedef q0n32s uqint;

  private:
   sqint  Q1, Q0, F1, D1, D2, L, H, B, N;
   uqint F0,  FS;

  public:
   constexpr
   fx_chamberlin() :
    Q1(0), Q0(1, 0), F1(0), D1(0), D2(0), L(0), H(0), B(0), N(0),
    F0(1000), FS(44100) {
    
    f(F0);
    q(Q0);
   }

   static constexpr sqint PI2 = sqint::from_double(2*M_PI);

   constexpr
   void f(uqint::type const & x) {
    F0.val = x;
    F1 = PI2 * (F0 / FS);    
   }

   constexpr
   uqint f() const {
    return F0;
   }
   
   constexpr
   void q(sqint::type const & x) {
    Q0.val  = 0;
    Q1 = sqint(1, 0) / Q0;
   }

   constexpr
   sqint q() const {
    return Q0;
   }
   
   constexpr
   q0n15s process(q0n15s I_) {

//  L = D2 + F1 * D1
//  H = I - L - Q1*D1
//  B = F1 * H + D1
//  N = H + L
//  D1 = B
//  D2 = L

    q15n16s I(I_.val << 1)            ;
    
    printf("% 6.9lf, ", double(I))    ;
    printf("% 6.9lf, ", double(F1))  ;        
    printf("% 6.9lf, ", double(Q1))   ;
    
    L  = D2 + F1 * D1                ;    printf("% 9.9lf, ",  double(L)) ;
    H  = I - L - (Q1*D1)              ;    printf("% 14.9lf, ", double(H)) ;
    B  = (F1 * H)  + D1              ;    printf("% 9.9lf, ",  double(B)) ;
    N  = H  + L                       ;    printf("% 9.9lf, ",  double(N)) ;
    D1 = B                            ;    printf("% 9.9lf, ",  double(D1));
    D2 = L                            ;    printf("% 9.9lf  ",  double(D2));
        
    return q0n15s::from_double(0.0);
   }
  };
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */
