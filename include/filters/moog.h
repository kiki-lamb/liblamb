#ifndef MOOG_LAMB_H_
#define MOOG_LAMB_H_

// in[x] and out[x] are member variables, init to 0.0 the controls:
// 
// freq = cutoff, nearly linear [0,1] -> [0, fs/2]
// q = resonance [0, 4] -> [no resonance, self-oscillation]
// 
// code:
// double MoogVCF::run(double input, double freq, double q){

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/ NOT #included in lamb.h !!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


namespace lamb {
  class moog {
  public:
   q0n16s  freq;     
   q2n14s  q;    
   q0n15s  out1, out2;
   q0n15s  in1, in2;

   moog() :
    freq(q0n16s::from_double(0.65)),
    q(0),
    out1(0), out2(0),
    in1(0), in2(0) {}
      
   static constexpr q8n8s  _1_0       = q8n8s(q8n8s::ONE);
   static constexpr q8n8s  _1_16      = q8n8s::from_double(1.16);
   static constexpr q8n8s  _0_15      = q8n8s::from_double(0.15);
   static constexpr q8n8s  _0_35013   = q8n8s::from_double(0.35013);
   static constexpr q8n8s  _0_3       = q8n8s::from_double(0.3);

//   double f = freq * 1.16;
//   double fb = q * (1.0 - 0.15 * f * f);
//   input -= out4 * fb;
//   input *= 0.35013 * (f*f)*(f*f);

   q0n15s process(q0n15s input) {
    printf("% 04.3f, ",      double(input));

    q8n8s f         = _1_16 * freq;    
    printf("% 04.3f, ", double(f));

    q8n8s ff        = f * f;    
    printf("% 04.3f, ", double(ff));

    q8n8s ffff      = ff * ff;
    printf("% 04.3f, ", double(ffff));

    q8n8s fb_coeff  = _1_0 - (ffff * _0_15);    
    printf("% 04.3f, ", double(fb_coeff));
    
    q2n14s fb       = q * fb_coeff;
    printf("% 04.3f, ", double(fb));
    
    q0n15s sub      = out2 * fb;
    printf("% 04.3f, ", double(sub));
    
    input -= sub;
    printf("% 04.3f, ", double(sub));

    q8n8s mul       = ffff * _0_35013;
    printf("% 04.3f, ", double(mul));
    
    input *= mul;
    printf("% 04.3f, ", double(input));

    printf("% 04.3f, ", double(f));
    
    q8n8s inv_f     = _1_0 - f;
    printf("% 04.3f, ", double(inv_f));
    
    {
     printf("% 04.3f, ", double(out1));

     q0n15s part_in = in1 * _0_3;
     printf("% 04.3f, ", double(part_in));
     
     q0n15s part_out = out1 * inv_f;
     printf("% 04.3f, ", double(part_out));     
     
     out1 = input + part_in + part_out;     
     printf("% 04.3f, ", double(out1));
     
     in1  = input;
     printf("% 04.3f, ", double(in1));
    }

    {
     printf("% 04.3f, ", double(out1));

     q0n15s part_in = in2 * _0_3;
     printf("% 04.3f, ", double(part_in));
     
     q0n15s part_out = out2 * inv_f;
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
