#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

////////////////////////////////////////////////////////////////////////////////

namespace lamb {

////////////////////////////////////////////////////////////////////////////////

 class fx_chamberlin {

////////////////////////////////////////////////////////////////////////////////

 public:

 public:
  u24q8s  F0;
  u8q24s  F1;

  u16q16s Q0; 
  u2q30s  Q1;

  s7q24s  L;
  s7q24s  H;
  s7q24s  B;
  s7q24s  N;

  s7q24s  D0;
  s7q24s  D1;

  u24q8s  FS;
   
  static constexpr u8q24s PI2 = u8q24s::from_double(2*M_PI);

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
  u24q8s::type f() {
   return F0.characteristic();
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void f(u24q8s::type const & x) {
   f(u24q8s(x & 0xffffff, 0));
  }

////////////////////////////////////////////////////////////////////////////////

 private:
  
  constexpr
  void f(u24q8s const & x) {
   F0  = x;
   F1  = u8q24s(F0 / FS);
   F1 *= PI2;
  }

////////////////////////////////////////////////////////////////////////////////

 public:
  
  constexpr
  u16q16s q() {
   return Q0;
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void q(double const & x) {
   q(u16q16s::from_double(x >= 0.5 ? x : 0.5));
   }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  void q(u16q16s const & x) {
   Q0.val = x.val;
   Q1 = u2q30s(1,0) / Q0;
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
   FS = u24q8s(x, 0);
   f(F0);
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  s0q15s l() const {
   return s0q15s(L >> 4);   
  }


  constexpr
  s0q15s h() const {
   return s0q15s(H >> 4);   
  }


  constexpr
  s0q15s b() const {
   return s0q15s(B >> 4);   
  }


  constexpr
  s0q15s n() const {
   return s0q15s(N >> 4);   
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  s0q15s process(s0q15s I_) {

//  L = F1 * D0*D1
//  H = I - L - Q1*D0
//  B = F1 * H + D0
//  N = H + L
//  D0 = B
//  D1 = L

   s7q24s I(I_);
    
   printf("% 6.9lf, ", double(I))    ;
   printf("% 6.9lf, ", double(F1))   ;        
   printf("% 6.9lf, ", double(Q1))   ;
   
   L  = D1      + D0 * F1            ;    printf("% 9.9lf, ",  double(L)) ;
   H  = I  - L  - D0 * Q1            ;    printf("% 14.9lf, ", double(H)) ;
   B  = D0      + H  * F1            ;    printf("% 9.9lf, ",  double(B)) ;
   N  = H       + L                  ;    printf("% 9.9lf, ",  double(N)) ;
   D0 = B                            ;    printf("% 9.9lf, ",  double(D0));
   D1 = L                            ;    printf("% 9.9lf,  ", double(D1));

   printf("% 9.9lf, ",  double(L)) ;

   s0q15s r   = s0q15s(L >> 2);
   
   printf("% 9.9lf  ", double(r));

   return r;
  }
  
////////////////////////////////////////////////////////////////////////////////
  
 };

////////////////////////////////////////////////////////////////////////////////
 
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */
