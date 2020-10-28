#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

////////////////////////////////////////////////////////////////////////////////

namespace lamb {

////////////////////////////////////////////////////////////////////////////////

 class fx_chamberlin {

////////////////////////////////////////////////////////////////////////////////

 public:
  typedef s2q29s output_type;
//  typedef u32q0s fs_type;
  typedef u28q4s fs_type;
  
  u24q8s  F0;
  u8q24s  F1;

  u16q16s Q0; 
  u2q30s  Q1;

  output_type  L;
  output_type  H;
  output_type  B;
  output_type  N;

  output_type  D0;
  output_type  D1;

  fs_type  FS;

  static constexpr uint8_t OUT_SHIFT = 1;
  static constexpr u8q24s  PI2 = u8q24s::from_double(2*M_PI);

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

   u24q8s tmp = F0 / FS;
   
   F1  = u8q24s(tmp);
   F1 *= PI2;
  }

////////////////////////////////////////////////////////////////////////////////

 public:
  
  constexpr
  u16q16s q() const {
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
   FS = fs_type(x, 0);
   f(F0);
  }

////////////////////////////////////////////////////////////////////////////////
  
  constexpr
  s0q15s l() const {
   return s0q15s(L >> OUT_SHIFT);   
  }


  constexpr
  s0q15s h() const {
   return s0q15s(H >> OUT_SHIFT);   
  }


  constexpr
  s0q15s b() const {
   return s0q15s(B >> OUT_SHIFT);   
  }


  constexpr
  s0q15s n() const {
   return s0q15s(N >> OUT_SHIFT);   
  }

////////////////////////////////////////////////////////////////////////////////

  constexpr
  output_type process(s0q15s I_) {

//  L = F1 * D0*D1
//  H = I - L - Q1*D0
//  B = F1 * H + D0
//  N = H + L
//  D0 = B
//  D1 = L

   output_type I(I_);
   
   printf("% 6.9lf, ", double(F1))   ;        
   printf("% 6.9lf, ", double(Q1))   ;
   
   L  = D1      + D0 * F1            ;    printf("% 9.9lf, ",  double(L)) ;
   H  = I  - L  - D0 * Q1            ;    printf("% 14.9lf, ", double(H)) ;
   B  = D0      + H  * F1            ;    printf("% 9.9lf, ",  double(B)) ;
   N  = H       + L                  ;    printf("% 9.9lf, ",  double(N)) ;
   D0 = B                            ;    printf("% 9.9lf, ",  double(D0));
   D1 = L                            ;    printf("% 9.9lf,  ", double(D1));

   return L;
   
//   auto x(L);
//   x >>= OUT_SHIFT;
   
//   s0q15s r   = s0q15s(x);
//   
//   printf("% 9.9lf  ", double(r));
  }
  
////////////////////////////////////////////////////////////////////////////////
  
 };

////////////////////////////////////////////////////////////////////////////////
 
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */

