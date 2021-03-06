#ifndef LAMB_FX_CHAMBERLIN_H_
#define LAMB_FX_CHAMBERLIN_H_

////////////////////////////////////////////////////////////////////////////////

namespace lamb {

////////////////////////////////////////////////////////////////////////////////

 class fx_chamberlin {

////////////////////////////////////////////////////////////////////////////////

 public:
  //----------------------------------------------------------------------------
  typedef u17q15  hz_type;
  //----------------------------------------------------------------------------
  static constexpr
  hz_type         PI2 = hz_type::from_float(2*M_PI);
  //----------------------------------------------------------------------------
  hz_type         FS;
  hz_type         F0;
  hz_type         F1;
  //----------------------------------------------------------------------------
  typedef u16q16  q0_type;
  //----------------------------------------------------------------------------
  q0_type         Q0; 
  //----------------------------------------------------------------------------
  typedef u2q30   q1_type;
  //----------------------------------------------------------------------------
  q1_type         Q1;
  //----------------------------------------------------------------------------
  typedef s0q15   external_type;
  //----------------------------------------------------------------------------
  typedef s3q28   internal_type;
  internal_type   L;
  internal_type   H;
  internal_type   B;
  internal_type   N;
  internal_type   Z0;
  internal_type   Z1;
  //----------------------------------------------------------------------------
  
  //////////////////////////////////////////////////////////////////////////////

  constexpr
  fx_chamberlin() :
   FS(48000, 0),
   F0(1000, 0),
   F1(0), 
   Q0(1, 0),
   Q1(0),
   L(0),
   H(0),
   B(0),
   N(0),
   Z0(0),
   Z1(0) {
    freq(F0);
    res(Q0);
   }

  //////////////////////////////////////////////////////////////////////////////

  static inline constexpr
  external_type externalize(internal_type const & intern) {
   external_type ret((external_type)(intern >> 2));
   
   //printf("% 9.9f  ", float(ret));

   return ret;
  }
  
  //////////////////////////////////////////////////////////////////////////////

  constexpr
  hz_type::value_type freq() {
   return F0.value; // .characteristic();
  }
  
  //----------------------------------------------------------------------------
  
  // constexpr
  // void freq(hz_type::value_type const & x) {
  //  freq(hz_type(x & 0xffffff, 0));
  // }

  //----------------------------------------------------------------------------

  
  constexpr
  void freq(hz_type const & x) {
   F0  = x;
   F1  = F0 / FS;
   F1 *= PI2;
  }

  //////////////////////////////////////////////////////////////////////////////
  
  constexpr
  q0_type res() const {
   return Q0;
  }

  //----------------------------------------------------------------------------

  constexpr
  void res(q0_type x) {
   if (x.value == 0)
    x.value = 1;
   
   Q0.value = x.value;
   Q1       = q1_type::ONE / Q0;

//   //printf("% 12ld, % 12ld \n", float(q0_type(x)), float(Q0));
  }

  //////////////////////////////////////////////////////////////////////////////
  
  constexpr
  uint32_t fs() {
   return FS.value; // characteristic();
  }

  //----------------------------------------------------------------------------

  constexpr
  void fs(uint32_t const & x) {
   FS = hz_type(x, 0);
   freq(F0);
  }

  //////////////////////////////////////////////////////////////////////////////
  
  constexpr
  external_type l() const {
   return externalize(L);
  }

  //----------------------------------------------------------------------------
  
  constexpr
  external_type h() const {
   return externalize(H);
  }

  //----------------------------------------------------------------------------
  
  constexpr
  external_type b() const {
   return externalize(B);
  }

  //----------------------------------------------------------------------------

  constexpr
  external_type n() const {
   return externalize(N);
  }

  //////////////////////////////////////////////////////////////////////////////

  //----------------------------------------------------------------------------
  // L = F1 * Z0*Z1
  // H = I - L - Q1*Z0
  // B = F1 * H + Z0
  // N = H + L
  // Z0 = B
  // Z1 = L
  //----------------------------------------------------------------------------

  // constexpr
  // external_type::value_type process(external_type::value_type I_) {
  //  return process(external_type(I_)).value;
  // }

  //----------------------------------------------------------------------------

  constexpr
  external_type process(external_type I_) {
   internal_type I(I_)              ;

   //printf("% 6.9f, ", float(F1))  ;        
   //printf("% 6.9f, ", float(Q1))  ;
   
   L  = Z1     + Z0 * F1            ;    //printf("% 9.9f, ", float(L)) ;
   H  = I  - L - Z0 * Q1            ;    //printf("% 9.9f, ", float(H)) ;
   B  = Z0     + H  * F1            ;    //printf("% 9.9f, ", float(B)) ;
   N  = H      + L                  ;    //printf("% 9.9f, ", float(N)) ;
   Z0 = B                           ;    //printf("% 9.9f, ", float(Z0));
   Z1 = L                           ;    //printf("% 9.9f, ", float(Z1));

   //printf("% 9.9f, ", float(L));

   auto t = externalize(L);
   
   return t;
  }

////////////////////////////////////////////////////////////////////////////////
  
 };

////////////////////////////////////////////////////////////////////////////////
 
}

#endif /* LAMB_FX_CHAMBERLIN_H_ */


