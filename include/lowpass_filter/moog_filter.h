#ifndef MOOG_LAMB_H_
#define MOOG_LAMB_H_

namespace lamb {
  class moog_filter {
  public:
    typedef q0n15                                                sample_t;
    typedef sample_type_traits<sample_t>                         sample_traits_t;
    typedef sample_traits_t::unsigned_type                       unsigned_sample_t;     // q0n16_t
    typedef sample_traits_t::mix_type                            mix_t;                 // q0n31_t
    typedef sample_type_traits<mix_t>                            mix_traits_t;
    typedef sample_type_traits<mix_t>::unsigned_type             unsigned_mix_traits_t;
    typedef unsigned_mix_traits_t::type                          unsigned_mix_t;        // q0n32_t

    typedef unsigned_frac<0, (
      sizeof(
        typename sample_type_traits<sample_t>::unmixed_type
      ) << 3)>                                                   control_traits_t;    

    typedef typename control_traits_t::type                      control_t;             // q0n8_t

    static const control_t control_t_one = control_traits_t::one;

  private:
    // static const uint8_t FX_SHIFT = sizeof(control_t) << 3;

    control_t          _freq; 
    
    unsigned_sample_t  _q_q04n8;
    
    sample_t           _out1, _out2, _out3, _out4;
    sample_t           _in1,  _in2,  _in3,  _in4;
    
  public:
//    moog_filter() {}

    unsigned_sample_t q() const {
      return _q_q04n8;
    }

    unsigned_sample_t freq() const {
      return _freq;
    }
    
    void q(unsigned_sample_t const & q_) {
      _q_q04n8 = q_;
    }

    void freq(unsigned_sample_t const & freq_) {
      _freq = freq_;
    }f

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
//   out2 = out1 + 0.3 * in2 + (1 - f) * out2;  // Pole 2
//   in2  = out1;
//   out3 = out2 + 0.3 * in3 + (1 - f) * out3;  // Pole 3
//   in3  = out2;
//   out4 = out3 + 0.3 * in4 + (1 - f) * out4;  // Pole 4
//   in4  = out3;
//   return out4;
// }

    static const q16n16 one_q16n16 = unsigned_frac<16, 16>::one;
        
    sample_t process(sample_t /* q0n15 */ const & in) { 
      q16n16 f                = 0x0001'28f6;                                   // approx 1.16
      f                      *= _freq;
      f                     >>= 8;                                             // 75725 for _freq = 255 (1). (_q = 2)

      q16n16 f_2             = ((uint64_t)f      * f       ) >> 16;            // 87498 

      q16n16 sub             = ((uint64_t)0x2666 * f_2     ) >> 16;            // 13124

      q16n16 fb              = one_q16n16 - sub;                               // 52412

      fb                     = ((uint64_t)fb     * q       ) >> 8;             // 104824

      in                    -= ((uint64_t)out4   * fb      ) >> 16;            // q0n15 * q16n16 = q31n16. 

      q16n16 f_2_f_2         = ((uint64_t)f_2    * f_2     ) >> 16;            // 167664

      static const
        q16n16 m             = 0x59a2;                                         // 0.35013;
      
      in                     = ((uint64_t)in     * m       ) >> 16;
      in                     = ((uint64_t)in     * f_2_f_2 ) >> 16;
      
      out1                   = input + (((uint64_t)0x4ccd * in1) >> 8);
      out1                  += (((uint64_t)(one_q16n16 - f)) * out1) >> 8;

      return out1;
    }

  private:
//    static unsigned_sample_t us_fxmul_cXc(control_t const & a, control_t const & b) {
//      return ((unsigned_mix_t)a * b) >> FX_SHIFT;
//    }
//    
//    static sample_t s_fxmul_sXc(sample_t const & a, control_t const & b) {
//      return (a * b) >> FX_SHIFT;
//    }
//    
//    static mix_t m_fxmul_mXs(mix_t const & a, sample_t const & b) {
//      return (a * b) >> FX_SHIFT; // Note that FX_SHIFT is less than size of input!
//    }
  };
}

#endif /* MOOG_H_ */
