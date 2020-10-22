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
    sat_q0n15  out1, out2, out3, out4;
    sat_q0n15  in1,  in2,  in3,  in4;
    
  public:
    moog_filter() :
     freq(sat_q0n16::MAX),
     q(0),
     out1(0), out2(0), out3(0), out4(0),
     in1(0), in2(0), in3(0), in4(0) {}
      
   static constexpr sat_q8n8   _1_0      = sat_q8n8(sat_q8n8::ONE);
   static constexpr sat_q8n8   _1_16     = sat_q8n8 ::from_float(1.16);
   static constexpr sat_q0n16  _0_15     = sat_q0n16::from_float(0.15);
   static constexpr sat_q0n16  _0_35013  = sat_q0n16::from_float(0.35013);
   static constexpr sat_q0n16  _0_3      = sat_q0n16::from_float(0.3);

//   double f = freq * 1.16;
//   double fb = q * (1.0 - 0.15 * f * f);
//   input -= out4 * fb;
//   input *= 0.35013 * (f*f)*(f*f);

   sat_q0n15 process(sat_q0n15 input) {
    printf("i: %f \n",      input.to_float());
    printf("1.16 = %lf \n", _1_16.to_float());
    printf("freq: %f \n",   freq.to_float());    

    sat_q8n8 f   = _1_16 * freq;
    printf( "f: %f \n", f.to_float());

    sat_q8n8 ff  = f * f;
    printf( "ff: %f \n", ff.to_float());

    sat_q8n8 ffff   = ff * ff;
    printf( "ffff: %f \n", ffff.to_float());

    sat_q8n8 fb_coeff = _1_0 - (ffff * _0_15);    
    printf( "fb_coeff: %f \n", ffff.to_float());

    sat_q2n14 fb = q * fb_coeff;
    printf( "fb: %f \n", fb.to_float());

    input -= out4 * fb;
    printf("i': %f \n", input.to_float());

    input *= ffff * _0_35013;
    printf("i'': %f \n", input.to_float());
            
    sat_q8n8 inv_f = _1_0 - f;
    printf("inv_f: %f \n", inv_f.to_float());

    {
//   out1 = input + 0.3 * in1 + (1 - f) * out1; // Pole 1
//   in1  = input;

     sat_q0n15 inv_fp = in1 + out1 * inv_f;
     printf("inv_fp: %f \n", inv_fp.to_float());
     
     sat_q0n15 inv_fpp = inv_fp * _0_3;
     printf("inv_fpp: %f \n", inv_fpp.to_float());
     
     out1 = input + inv_fpp;
     printf("out1: %f \n", out1.to_float());
     
     in1  = input;
     printf("in1: %f \n", in1.to_float());
    }

    {
//   out2 = out1 + 0.3 * in2 + (1 - f) * out2;  // Pole 2
//   in2  = out1;

     sat_q0n15 inv_fp = in2 + out2 * inv_f;
     printf("inv_fp: %f \n", inv_fp.to_float());
     
     sat_q0n15 inv_fpp = inv_fp * _0_3;
     printf("inv_fpp: %f \n", inv_fpp.to_float());
     
     out2 = out1 + inv_fpp;    
     printf("out2: %f \n", out2.to_float());

     in2  = out1;
     printf("in2: %f \n", in1.to_float());
    }

    {
     //   out3 = out2 + 0.3 * in3 + (1 - f) * out3;  // Pole 3
     //   in3  = out2;

     sat_q0n15 inv_fp = in3 + out3 * inv_f;
     printf("inv_fp: %f \n", inv_fp.to_float());
     
     sat_q0n15 inv_fpp = inv_fp * _0_3;
     printf("inv_fpp: %f \n", inv_fpp.to_float());
     
     out3 = out2 + inv_fpp;    
     printf("out3: %f \n", out3.to_float());

     in3  = out2;
     printf("in3: %f \n", in1.to_float());
    }

    {
    //   out4 = out3 + 0.3 * in4 + (1 - f) * out4;  // Pole 4
    //   in4  = out3;

     sat_q0n15 inv_fp = in4 + out4 * inv_f;
     printf("inv_fp: %f \n", inv_fp.to_float());
     
     sat_q0n15 inv_fpp = inv_fp * _0_3;
     printf("inv_fpp: %f \n", inv_fpp.to_float());
     
     out4 = out3 + inv_fpp;    
     printf("out4: %f \n", out3.to_float());

     in4  = out3;
     printf("in4: %f \n", in1.to_float());
    }

    return out4;
   }
  };
}

#endif /* MOOG_H_ */
