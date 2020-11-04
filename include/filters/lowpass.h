#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
 class lowpass {

  static constexpr u0q8 q8_one = u0q8::ONE;

  static constexpr uint8_t FX_SHIFT = 8;

  enum mode_t { mode_lp, mode_hp, mode_bp };
  
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

   u0q16 tmp((res() * (q8_one - _freq)).value);

   _feedback.value  = res().value; //.value;
   _feedback       += tmp;

   // char buff[64];
   // snprintf(buff, 64, "%d, %d, %d ", res().value, tmp.value, _feedback.value);
   // Serial.println(buff);
  }

  inline void res(u0q8 const & q_) {
   _q = q_;
  }

  inline s0q15 process(s0q15 const & in) {
   char buff[64];   

   s0q15 hp     = (in       - _d0                   );
   s0q15 tmp1   = (_d0      - _o.value              );                             
   s0q15 tmp2   = (tmp1     * u8q8(_feedback.value ));
   s0q15 tmp3   = (hp       + tmp2                  );
   _d0         += (tmp3     * freq()                );
   s0q15 bp     = (_d0      - _o                    );
   _o          += (bp       * freq()                );

   // if      (_mode == HP)
   //  return s0q15(hp);
   // else if (_mode == BP)
   //  return s0q15(bp);

   return _o;
  }
 };
}

#endif /* LOWPASS_H_ */
