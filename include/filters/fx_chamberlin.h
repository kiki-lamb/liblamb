#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

////////////////////////////////////////////////////////////////////////////////

namespace lamb {

////////////////////////////////////////////////////////////////////////////////

 class fx_chamberlin {

////////////////////////////////////////////////////////////////////////////////

 public:
  //----------------------------------------------------------------------------
  typedef u17q15s hz_type;
  static constexpr
  hz_type         PI2 = hz_type::from_double(2*M_PI);
  //----------------------------------------------------------------------------
  hz_type         FS;
  hz_type         F0;
  hz_type         F1;
  //----------------------------------------------------------------------------
  typedef u16q16s q0_type;
  q0_type         Q0; 
  //----------------------------------------------------------------------------
  typedef u2q30s  q1_type;
  q1_type         Q1;
  //----------------------------------------------------------------------------
  typedef s0q15s  external_type;
  //----------------------------------------------------------------------------
  typedef s2q29s  internal_type;
  internal_type   L;
  internal_type   H;
  internal_type   B;
  internal_type   N;
  internal_type   D0;
  internal_type   D1;
  //----------------------------------------------------------------------------
  
////////////////////////////////////////////////////////////////////////////////

 public:
  
  constexpr
  fx_chamberlin() :
   FS(44100, 0),
   F0(1000, 0),
   F1(0), 
   Q0(1, 0),
   Q1(0),
   L(0),
   H(0),
   B(0),
   N(0),
   D0(0),
   D1(0) {
    f(F0);
    q(Q0);
   }

////////////////////////////////////////////////////////////////////////////////

  static inline constexpr
  external_type externalize(internal_type const & intern) {
   external_type ret(intern >> 2);
   
   printf("% 9.9lf  ", double(ret));

   return ret;
  }
  
////////////////////////////////////////////////////////////////////////////////

  constexpr
  hz_type::type f() {
   return F0.characteristic();
  }

  constexpr
  void f(hz_type::type const & x) {
   f(hz_type(x & 0xffffff, 0));
  }

 private:
  
  constexpr
  void f(hz_type const & x) {
   // printf("\nFRQ:% 13.05lf \n", double(x));
   F0  = x;
   F1  = F0 / FS;
   // printf("PI2:% 13.05lf \n", double(PI2));
   F1 *= PI2;
   // printf("PML:% 13.05lf \n", double(F1));
   // printf("\n");
  }

////////////////////////////////////////////////////////////////////////////////

 public:
  
  constexpr
  q0_type q() const {
   return Q0;
  }

  constexpr
  void q(double const & x) {
   q(q0_type::from_double(x >= 0.5 ? x : 0.5));
   }

  constexpr
  void q(q0_type const & x) {
   // printf("\nQ:  % 13.05lf \n", double(x));

   constexpr q1_type one(1,0);
   
   Q0.val = x.val;
   Q1 = one / Q0;

   // printf("\n");
  }

////////////////////////////////////////////////////////////////////////////////
  
  constexpr
  uint32_t fs() {
   return FS.characteristic();
  }

  constexpr
  void fs(uint32_t const & x) {
   FS = hz_type(x, 0);
   f(F0);
  }

////////////////////////////////////////////////////////////////////////////////
  
  constexpr
  external_type l() const {
   return externalize(L);
  }


  constexpr
  external_type h() const {
   return externalize(H);
  }


  constexpr
  external_type b() const {
   return externalize(B);
  }


  constexpr
  external_type n() const {
   return externalize(N);
  }

////////////////////////////////////////////////////////////////////////////////

  //----------------------------------------------------------------------------
  //  L = F1 * D0*D1
  //  H = I - L - Q1*D0
  //  B = F1 * H + D0
  //  N = H + L
  //  D0 = B
  //  D1 = L
  //----------------------------------------------------------------------------

  constexpr
  external_type process(external_type I_) {
   internal_type I(I_)                ;  

   printf("% 6.9lf, ", double(F1))  ;        
   printf("% 6.9lf, ", double(Q1))  ;
   
   L  = D1     + D0 * F1            ;    printf("% 9.9lf, ", double(L)) ;
   H  = I  - L - D0 * Q1            ;    printf("% 9.9lf, ", double(H)) ;
   B  = D0     + H  * F1            ;    printf("% 9.9lf, ", double(B)) ;
   N  = H      + L                  ;    printf("% 9.9lf, ", double(N)) ;
   D0 = B                           ;    printf("% 9.9lf, ", double(D0));
   D1 = L                           ;    printf("% 9.9lf, ", double(D1));

   printf("% 9.9lf, ", double(L));

   return externalize(L);
  }

////////////////////////////////////////////////////////////////////////////////
  
 };

////////////////////////////////////////////////////////////////////////////////
 
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */

