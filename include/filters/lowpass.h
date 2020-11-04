#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
 class lowpass {

  static constexpr u0q8 q8_one = u0q8::ONE;

  static constexpr uint8_t FX_SHIFT = 8;
    
  u0q8    _q;
  u0q8    _freq;
  u0q16   _feedback;
  s0q15   _d0;
  s0q15   _o;
  mode_t  _mode;
    
 public:

  inline mode_t mode() const {
   return _mode;
  }

  inline u0q8 freq() const {
   return _freq;
  }
    
  inline u0q8 res() const {
   return _q;
  }

  inline void mode(mode_t const & mode_) {
   _mode = mode_;
  }
    
  inline void freq(u0q8 const & freq_) {
   _freq     = freq_;

   u0q8 tmp  = res() * (q8_one - _freq);

   Serial.println(tmp.value);
   
   _feedback.value  = res().value;
   _feedback       += tmp.value;

   // char buff[64];
   // snprintf(buff, 64, "%d, %d, %d ", res().value, tmp, _feedback.value);
   // Serial.println(buff);
  }

  inline void res(u0q8 const & q_) {
   _q = q_;
  }

  inline s0q15 process(s0q15 const & in__) {
   char buff[64];
   
   //snprintf(buff, 64, "% d, ", freq()); Serial.print(buff);
   //snprintf(buff, 64, "% 9.9f, ", float(u0q8(freq()))); Serial.print(buff);

   //snprintf(buff, 64, "% d, ", res()); Serial.print(buff);
   //snprintf(buff, 64, "% 9.9f, ", float(u0q8(res()))); Serial.print(buff);
   
   //snprintf(buff, 64, "% d,  ",  in_); Serial.print(buff);
   //snprintf(buff, 64, "% 9.9f, ", float(s0q15(in_))); Serial.print(buff);
   
   // D0 = D0 + FREQ * (IN - D0 + FB * (D0 - O));
   // O  = O  + FREQ * (D0 - O);
     
   int16_t hp = in_ - _d0.value;                          ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(in_))); Serial.print(buff);

   ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(_feedback))); Serial.print(buff);

   auto tmp1 = _d0 - _o.value;                             ////snprintf(buff, 64, "% 9.9fa, ", float(s0q15(tmp1))); Serial.print(buff);
   auto tmp2 = (_feedback.value * tmp1.value) >> FX_SHIFT;       ////snprintf(buff, 64, "% 9.9fb, ", float(s0q15(tmp2))); Serial.print(buff);
      
   _d0 += ((hp + tmp2) * freq().value) >> FX_SHIFT;        ////snprintf(buff, 64, "% 9.9fc, ", float(s0q15(_d0))); Serial.print(buff);
      
   int16_t bp = (_d0 - _o).value;                           ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(bp))); Serial.print(buff);

   _o += (bp * freq().value) >> FX_SHIFT;                  ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(_o))); Serial.print(buff);

   // if      (_mode == HP)
   //  return s0q15(hp);
   // else if (_mode == BP)
   //  return s0q15(bp);

   s0q15 out(_o);

   // //snprintf(buff, 64, "% d,  ",  out.value); Serial.print(buff);
   // //snprintf(buff, 64, "% 9.9f ", float(out)); Serial.print(buff); Serial.println(); 
   // Serial.println();

   return out;
  }
 };
}

#endif /* LOWPASS_H_ */
