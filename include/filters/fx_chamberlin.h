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

 public:
  sqint Q0;
  uqint F0;
  
 private:
  sqint  Q1, F1, D0, D1, L, H, B, N;
  uint32_t  FS;
   
  static constexpr sqint PI2 = sqint::from_double(2*M_PI);

////////////////////////////////////////////////////////////////////////////////

 public:
  
  constexpr
  fx_chamberlin() :
    Q1(0), Q0(1, 0), F1(0), D0(0), D1(0), L(0), H(0), B(0), N(0),
    F0(1000), FS(44100) {
    
    f(F0);
    q(F1);
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  uint32_t fs() {
   return FS;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void fs(uint32_t const & x) {
   FS = x;
   f(F0);
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  uqint f() {
   return F0;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void f(uqint::type const & x) {
   F0.val = x;
   F1 = PI2 * (F0 / uqint(FS));    
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  sqint q() {
   return Q0;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void q(double const & x) {
   sqint(sqint::from_double(x));
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void q(sqint::type const & x) {
   Q0.val = x;
   Q1 = sqint(1,0) / Q0;
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void q(sqint const & x) {
   q(x.val);
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
    printf("% 6.9lf, ", double(F1))  ;        
    printf("% 6.9lf, ", double(Q1))   ;
    
    L  = D1 + F1 * D0                ;    printf("% 9.9lf, ",  double(L)) ;
    H  = I - L - (Q1*D0)              ;    printf("% 14.9lf, ", double(H)) ;
    B  = (F1 * H)  + D0              ;    printf("% 9.9lf, ",  double(B)) ;
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
