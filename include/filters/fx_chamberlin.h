#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

////////////////////////////////////////////////////////////////////////////////

namespace lamb {

////////////////////////////////////////////////////////////////////////////////

 class fx_chamberlin {

////////////////////////////////////////////////////////////////////////////////

 public:

 public:
  q24n8s  F0;
  q8n24s  F1;

  q16n16s Q0; 
  q2n30s  Q1;

  q7n24s L;
  q7n24s H;
  q7n24s B;
  q7n24s N;

  q7n24s D0;
  q7n24s D1;

  q24n8s FS;
   
  static constexpr q8n24s PI2 = q8n24s::from_double(2*M_PI);

////////////////////////////////////////////////////////////////////////////////

 public:
  
  constexpr
  fx_chamberlin() :
   F0(1000, 0),
   F1(0), 
   Q0(1, 0),
   Q1(0),
   L(0),
   H(0),
   B(0),
   N(0),
   D0(0),
   D1(0),
   FS(44100, 0) {
    
    f(F0);
    q(Q0);
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  q24n8s::type f() {
   return F0.characteristic();
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void f(q24n8s::type const & x) {
   f(q24n8s(x & 0xffffff, 0));
  }

////////////////////////////////////////////////////////////////////////////////

 private:
  
  constexpr
  void f(q24n8s const & x) {
   F0  = x;
   F1  = q8n24s((F0 / FS).val << 16);
   F1 *= PI2;
  }

////////////////////////////////////////////////////////////////////////////////

 public:
  
  constexpr
  q16n16s q() {
   return Q0;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void q(double const & x) {
   q(q16n16s::from_double(x >= 0.5 ? x : 0.5));
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void q(q16n16s const & x) {
   Q0.val = x.val;
   Q1 = q2n30s(1,0) / Q0;
  }

////////////////////////////////////////////////////////////////////////////////
  
 public:

  constexpr
  uint32_t fs() {
   return FS.characteristic();
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void fs(uint32_t const & x) {
   FS = q24n8s(x, 0);
   f(F0);
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

   q7n24s I(((q7n24s::type)I_.val) << 9);
    
   printf("% 6.9lf, ", double(I))    ;
   printf("% 6.9lf, ", double(F1))   ;        
   printf("% 6.9lf, ", double(Q1))   ;
   
   L  = D1 + D0 * F1                 ;    printf("% 9.9lf, ",  double(L)) ;
   H  = I - L - (D0 * Q1)            ;    printf("% 14.9lf, ", double(H)) ;
   B  = (H * F1)  + D0               ;    printf("% 9.9lf, ",  double(B)) ;
   N  = H  + L                       ;    printf("% 9.9lf, ",  double(N)) ;
   D0 = B                            ;    printf("% 9.9lf, ",  double(D0));
   D1 = L                            ;    printf("% 9.9lf,  ", double(D1));

   printf("% 9.9lf, ",  double(L)) ;

   q0n15s r = q0n15s(L.val >> 11);
   
   printf("% 9.9lf  ", double(r));
   
   return r;
  }
  
////////////////////////////////////////////////////////////////////////////////
  
 };

////////////////////////////////////////////////////////////////////////////////
 
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */
