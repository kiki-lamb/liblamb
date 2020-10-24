#ifndef MOOG_LAMB_H_
#define MOOG_LAMB_H_

// in[x] and out[x] are member variables, init to 0.0 the controls:
// 
// freq = cutoff, nearly linear [0,1] -> [0, fs/2]
// q = resonance [0, 4] -> [no resonance, self-oscillation]
// 
// code:
// double MoogVCF::run(double input, double freq, double q){

namespace lamb {
  class moog_filter {
  private:
    sat_q0n16  freq;     
    sat_q2n14  q;    
   sat_q0n15  out1;
   sat_q0n15  in1;
    
  public:
    moog_filter() :
     freq(sat_q0n16::MAX),
     q(0),
     out1(0),
     in1(0) {}
      
   static constexpr sat_q8n8  _1_0       = sat_q8n8(sat_q8n8::ONE);
   static constexpr sat_q8n8  _1_16      = sat_q8n8::from_float(1.16);
   static constexpr sat_q8n8  _0_15      = sat_q8n8::from_float(0.15);
   static constexpr sat_q8n8  _0_35013   = sat_q8n8::from_float(0.35013);
   static constexpr sat_q8n8  _0_3       = sat_q8n8::from_float(0.3);

//   double f = freq * 1.16;
//   double fb = q * (1.0 - 0.15 * f * f);
//   input -= out4 * fb;
//   input *= 0.35013 * (f*f)*(f*f);

   sat_q0n15 process(sat_q0n15 input) {
    printf("% 04.3f, ",      input.to_float());

    sat_q8n8 f   = _1_16 * freq;
//    printf("% 04.3f, ", f.to_float());
    
    sat_q8n8 ff  = f * f;
//    printf("% 04.3f, ", ff.to_float());
    
    sat_q8n8 ffff   = ff * ff;
    printf("% 04.3f, ", ffff.to_float());

    sat_q8n8 fb_coeff = _1_0 - (ffff * _0_15);    
    printf("% 04.3f, ", fb_coeff.to_float());
    
    sat_q2n14 fb = q * fb_coeff;
    printf("% 04.3f, ", fb.to_float());
    
    sat_q0n15 sub = out1 * fb;
    printf("% 04.3f, ", sub.to_float());
    
    input -= sub;
    printf("% 04.3f, ", sub.to_float());

    sat_q8n8 mul = ffff * _0_35013;
    printf("% 04.3f, ", mul.to_float());
    
    input *= mul;
    printf("% 04.3f, ", input.to_float());
            
    sat_q8n8 inv_f = _1_0 - f;

    {
     sat_q0n15 inv_fp = in1 + out1 * inv_f;
     printf("% 04.3f, ", inv_fp.to_float());
     
     sat_q0n15 inv_fpp = inv_fp * _0_3;
     printf("% 04.3f, ", inv_fpp.to_float());
     
     out1 = input + inv_fpp;
     printf("% 04.3f, ", out1.to_float());
     
     in1  = input;
     printf("% 04.3f, ", in1.to_float());
    }

    return out1;
   }
  };
}

#endif /* MOOG_LAMB_H_ */
