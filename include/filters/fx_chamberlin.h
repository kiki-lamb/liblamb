#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

////////////////////////////////////////////////////////////////////////////////

namespace lamb {

////////////////////////////////////////////////////////////////////////////////

 class fx_chamberlin {

////////////////////////////////////////////////////////////////////////////////

 public:

  typedef q15n16s sqint;
  typedef q0n32s uqint;
   
  sqint  Q1, Q0, FF1, D0, D1, L, H, B, N;
  uqint FF0;
  uint32_t  FS;
   
  static constexpr sqint PI2 = sqint::from_double(2*M_PI);

////////////////////////////////////////////////////////////////////////////////

  constexpr
  fx_chamberlin() :
    Q1(0), Q0(1, 0), FF1(0), D0(0), D1(0), L(0), H(0), B(0), N(0),
    FF0(1000), FS(44100) {
    
    set_frequency();
    set_q();
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void set_frequency() {
   FF1 = PI2 * (FF0 / uqint(FS));    
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void set_q() {
    Q1 = sqint(1,0) / Q0;
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  uqint frequency() {
   return FF0;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  sqint q() {
   return Q0;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  q0n15s process(q0n15s I_) {

//  L = D1 + F1 * D0
//  H = I - L - Q1*D0
//  B = F1 * H + D0
//  N = H + L
//  D0 = B
//  D1 = L

    q15n16s I(I_.val << 1)            ;
    
    printf("% 6.9lf, ", double(I))    ;
    printf("% 6.9lf, ", double(FF1))  ;        
    printf("% 6.9lf, ", double(Q1))   ;
    
    L  = D1 + FF1 * D0                ;    printf("% 9.9lf, ",  double(L)) ;
    H  = I - L - (Q1*D0)              ;    printf("% 14.9lf, ", double(H)) ;
    B  = (FF1 * H)  + D0              ;    printf("% 9.9lf, ",  double(B)) ;
    N  = H  + L                       ;    printf("% 9.9lf, ",  double(N)) ;
    D0 = B                            ;    printf("% 9.9lf, ",  double(D0));
    D1 = L                            ;    printf("% 9.9lf  ",  double(D1));
        
    return q0n15s::from_double(0.0);
   }

////////////////////////////////////////////////////////////////////////////////
  
 };

////////////////////////////////////////////////////////////////////////////////
 
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */
