#ifndef MOOG_LAMB_H_
#define MOOG_LAMB_H_


namespace lamb {
  class moog_filter {
  private:
    sat_q0n16  freq;     
    sat_q2n14  q;    
    sat_q0n15  out1, out2, out3, out4;
    sat_q0n15  in1,  in2,  in3,  in4;
    
  public:
    moog_filter() :
     freq(sat_q0n16::ONE),
     q(0),
     out1(0), out2(0), out3(0), out4(0),
     in1(0), in2(0), in3(0), in4(0) {}
      
   static constexpr sat_q8n8   _1_pt_0      = sat_q8n8(sat_q8n8::ONE);
   static constexpr sat_q8n8   _1_pt_16     = sat_q8n8 ::from_float(1.16);
   static constexpr sat_q0n16  _0_pt_15     = sat_q0n16::from_float(0.15);
   static constexpr sat_q0n16  _0_pt_35013  = sat_q0n16::from_float(0.35013);
   static constexpr sat_q0n16  _0_pt_3      = sat_q0n16::from_float(0.3);

   
// in[x] and out[x] are member variables, init to 0.0 the controls:
// 
// freq = cutoff, nearly linear [0,1] -> [0, fs/2]
// q = resonance [0, 4] -> [no resonance, self-oscillation]
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

   sat_q0n15 process(sat_q0n15 input) {
    
    
    return out4;
   }
  };
}

#endif /* MOOG_H_ */
