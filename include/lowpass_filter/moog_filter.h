#ifndef MOOG_LAMB_H_
#define MOOG_LAMB_H_

namespace lamb {
  class moog_filter {
  public:
    typedef int16_t  out_t;   // int16_t
    typedef q15n16_t int_t;   // int32_t
    typedef q0n31_t  uint_t;   // uint32_t
    typedef uint64_t ubig_t;
    typedef int64_t big_t;
    
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
       _q = q_ << 4;
       //_q = 0b00010000'00000000;
    }

    void freq(int_t const & freq_) {
       _freq = freq_ << 4;
      //_freq = 0xffff;
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

    static const int_t _1_pt_16     = 0x0001'28f5;
    static const int_t _1_pt_0      = 0x0001'0000;
    static const int_t _big_1_pt_0  = 0xffff'ffff;
    static const int_t _0_pt_15     = 0x0000'2666;
    static const int_t _0_pt_35013  = 0x0000'59a2;
    static const int_t _0_pt_3      = 0x0000'4ccc;

    static const int_t ssfxmul(int_t const & x, int_t const & y, uint8_t const & shift = 16) {
      return (((big_t)x) * y) >> shift;
    }

    static const uint_t uufxmul(uint_t const & x, uint_t const & y, uint8_t const & shift = 16) {
      return (((ubig_t)x) * y) >> shift;
    }

    out_t process(out_t input) {
      // Serial.print("f");
      // Serial.print(_freq);

      // Serial.print(" q");
      // Serial.print(_q);

      // Serial.print(" i");
      // Serial.print(input);

      int_t f      = ssfxmul(_freq, _1_pt_16, 16);
//      // Serial.print(" f");
//      // Serial.print(f);
      
      int_t f_2    = ssfxmul(f, f, 16);
//     // Serial.print(" f2=");
//      // Serial.print(f_2);
  
      int_t f_2_2  = ssfxmul(f_2, f_2, 16);
//      // Serial.print(" f2_2=");
//      // Serial.print(f_2_2);

      int_t s     = ssfxmul(_0_pt_15, f_2, 16);
      // Serial.print(" s");
      // Serial.print(s);

      int_t p     = _1_pt_0 - s;
      // Serial.print(" p");
      // Serial.print(p);
  
      int_t fb     = ssfxmul(_q, p, 14); // downshift 14 for max q = almost 4.
      // Serial.print(" fb");
      // Serial.print(fb);

      // Serial.print(" |");
      
      input -= ssfxmul(out1, fb);
      
      // Serial.print(" i");
      // Serial.print(input);
      
      input = ssfxmul(input, ssfxmul(_0_pt_35013, f_2_2, 15));
      // Serial.print(" >i");
      // Serial.print(input);
            
      out1      = input + ssfxmul(_0_pt_3, in1, 15) + ssfxmul((_1_pt_0 - f), out1, 16);
      // Serial.print(" o1=");
      // Serial.print(out1     );
    
      in1       = input;
      // Serial.print(" i1=");
      // Serial.print(in1      );
    
      out2      = out1 + ssfxmul(_0_pt_3, in2, 15) + ssfxmul((_1_pt_0 - f), out2, 16);
      // Serial.print(" o2=");
      // Serial.print(out2     );
       
      in2       = out1;
      // Serial.print(" i2=");
      // Serial.print(in2      );
       
      out3      = out2 + ssfxmul(_0_pt_3, in3, 15) + ssfxmul((_1_pt_0 - f), out3, 16);
      // Serial.print(" o3=");
      // Serial.print(out3     );
       
      in3       = out2;
      // Serial.print(" i3=");
      // Serial.print(in3      );
      
      out4      = out3 + ssfxmul(_0_pt_3, in4, 15) + ssfxmul((_1_pt_0 - f), out4, 16);
      // Serial.print(" o4=");
      // Serial.print(out4     );
      
      in4       = out3;
      // Serial.print(" i4=");
      // Serial.print(in4      );

      // Serial.print(" ret=");
      // Serial.print(out4 / 2);

      // Serial.println();
      
      return out4 / 2;
      
    }
  };
}

#endif /* MOOG_H_ */
