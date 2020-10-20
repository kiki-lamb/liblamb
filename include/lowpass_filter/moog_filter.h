#ifndef MOOG_LAMB_H_
#define MOOG_LAMB_H_

namespace lamb {
  class moog_filter {
  public:
    typedef int16_t  out_t;   // int16_t
    typedef q15n16_t int_t;   // int32_t
    typedef uint64_t big_t;
    
  private:
    int_t        _freq;     
    int_t        _q;    
    int_t        out1, out2, out3, out4;
    int_t        in1,  in2,  in3,  in4;
    
  public:
    int_t q() const {
      return _q;
    }

    int_t freq() const {
      return _freq;
    }
    
    void q(int_t const & q_) {
      _q = q_;
    }

    void freq(int_t const & freq_) {
      _freq = freq_;
    }

    moog_filter() :
      _freq(0xffffffff),
      _q(0),
      out1(0), out2(0), out3(0), out4(0),
      in1(0), in2(0), in3(0), in4(0) {}
      
// in[x] and out[x] are member variables, init to 0.0 the controls:
// 
// freq = cutoff, nearly linear [0,1] -> [0, fs/2]
// q = qonance [0, 4] -> [no resonance, self-oscillation]
// 
// code:
// double MoogVCF::run(double input, double freq, double q){
//   double f = freq * 1.16;
//   double fb = q * (1.0 - 0.15 * f * f);
//   input -= out4 * fb;
//   input *= 0.35013 * (f*f)*(f*f);
//   
//   out1 = input + 0.3 * in1 + (1 - f) * out1; // Pole 1
//   in1  = input;
//
//   out2 = out1 + 0.3 * in2 + (1 - f) * out2;  // Pole 2
//   in2  = out1;
//
//   out3 = out2 + 0.3 * in3 + (1 - f) * out3;  // Pole 3
//   in3  = out2;
//
//   out4 = out3 + 0.3 * in4 + (1 - f) * out4;  // Pole 4
//   in4  = out3;
//
//   return out4;
// }

    static const int_t _1_pt_16    = 0x1'28f5;
    static const int_t _1_pt_0     = 0x0'1000;
    static const int_t _0_pt_15    = 0x0'2666;
    static const int_t _0_pt_35013 = 0x0'59a2;
    static const int_t _0_pt_3     = 0x0'4ccc;

    static const int_t fxmul(int_t const & x, int_t const & y) {
      return ((((big_t)x) * y) >> 16);
    }
      
    out_t process(out_t input) {
      int_t f      = fxmul(_freq, _1_pt_16);
      int_t f_2    = fxmul(f, f);
      int_t f_2_2  = fxmul(f_2, f_2);  
      int_t fb     = fxmul(_q, _1_pt_0 - fxmul(_0_pt_15, f_2));

      input -= fxmul(out4, fb);
      input =  fxmul(input, fxmul(_0_pt_35013, f_2_2));      
        
      out1      = input + fxmul(_0_pt_3, in1) + fxmul((_1_pt_0 - f), out1);
      in1       = input;
      
      out2      = input + fxmul(_0_pt_3, in2) + fxmul((_1_pt_0 - f), out2);
      in2       = out1;

      out3      = input + fxmul(_0_pt_3, in3) + fxmul((_1_pt_0 - f), out3);
      in3       = out2;

      out4      = input + fxmul(_0_pt_3, in4) + fxmul((_1_pt_0 - f), out4);
      in4       = out3;
      
      return out4 / 2;
      
    }
  };
}

#endif /* MOOG_H_ */
