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
  public:
   sat_q0n16  freq;     
   sat_q2n14  q;    
   sat_q0n15  out1, out2;
   sat_q0n15  in1, in2;

   moog_filter() :
    freq(sat_q0n16::from_float(0.65)),
    q(0),
    out1(0), out2(0),
    in1(0), in2(0) {}
      
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
    printf("% 04.3f, ",      double(input));

    sat_q8n8 f         = _1_16 * freq;    
    printf("% 04.3f, ", double(f));

    sat_q8n8 ff        = f * f;    
    printf("% 04.3f, ", double(ff));

    sat_q8n8 ffff      = ff * ff;
    printf("% 04.3f, ", double(ffff));

    sat_q8n8 fb_coeff  = _1_0 - (ffff * _0_15);    
    printf("% 04.3f, ", double(fb_coeff));
    
    sat_q2n14 fb       = q * fb_coeff;
    printf("% 04.3f, ", double(fb));
    
    sat_q0n15 sub      = out2 * fb;
    printf("% 04.3f, ", double(sub));
    
    input -= sub;
    printf("% 04.3f, ", double(sub));

    sat_q8n8 mul       = ffff * _0_35013;
    printf("% 04.3f, ", double(mul));
    
    input *= mul;
    printf("% 04.3f, ", double(input));

    printf("% 04.3f, ", double(f));
    
    sat_q8n8 inv_f     = _1_0 - f;
    printf("% 04.3f, ", double(inv_f));
    
    {
     printf("% 04.3f, ", double(out1));

     sat_q0n15 part_in = in1 * _0_3;
     printf("% 04.3f, ", double(part_in));
     
     sat_q0n15 part_out = out1 * inv_f;
     printf("% 04.3f, ", double(part_out));     
     
     out1 = input + part_in + part_out;     
     printf("% 04.3f, ", double(out1));
     
     in1  = input;
     printf("% 04.3f, ", double(in1));
    }

    {
     printf("% 04.3f, ", double(out1));

     sat_q0n15 part_in = in2 * _0_3;
     printf("% 04.3f, ", double(part_in));
     
     sat_q0n15 part_out = out2 * inv_f;
     printf("% 04.3f, ", double(part_out));     
     
     out2 = out1 + part_in + part_out;     
     printf("% 04.3f, ", double(out1));
     
     in2  = out1;
     printf("% 04.3f, ", double(in1));
    }

    return out1;
   }
  };
}

#endif /* MOOG_LAMB_H_ */
