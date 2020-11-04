#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
 class lowpass {

 public:

  typedef s0q15                                                io_t;

//  enum mode_t { LP, BP, HP };

 private:

  typedef u0q8                                                 control_frac_t;

 public:
  
//  typedef typename control_frac_t::value_type                  control_t;
  
 private:

  typedef int16_t                                              sample_t;
  typedef typename sample_type_traits<sample_t>::unsigned_type unsigned_sample_t;
  typedef typename sample_type_traits<sample_t>::mix_type      mix_t;
  typedef typename sample_type_traits<mix_t>::unsigned_type    unsigned_mix_t;

  static constexpr control_frac_t control_t_one = control_frac_t::ONE;

 private:
  static constexpr uint8_t FX_SHIFT = 8;
    
  control_frac_t    _q;
  control_frac_t    _freq;
  unsigned_sample_t _feedback;
  sample_t          _d0;
  sample_t          _o;
//  mode_t          _mode;
    
 public:
  lowpass() /* : _mode(LP) */ {}

  // inline mode_t mode() const {
  //  return _mode;
  // }

  inline control_frac_t freq() const {
   return _freq;
  }
    
  inline control_frac_t res() const {
   return _q;
  }

  // inline void mode(mode_t const & mode_) {
  //  _mode = mode_;
  // }
    
  inline void freq(control_frac_t const & freq_) {
   _freq     = freq_;

   auto tmp  = (
    (unsigned_mix_t(res().value)) *
    (control_t_one - _freq).value
   ) >> FX_SHIFT;
   
   _feedback = (res() + tmp).value;
  }

  inline void res(control_frac_t const & q_) {
   _q = q_;
  }

  inline io_t process(io_t const & in__) {
   char buff[64];
   
   //snprintf(buff, 64, "% d, ", freq()); Serial.print(buff);
   //snprintf(buff, 64, "% 9.9f, ", float(u0q8(freq()))); Serial.print(buff);

   //snprintf(buff, 64, "% d, ", res()); Serial.print(buff);
   //snprintf(buff, 64, "% 9.9f, ", float(u0q8(res()))); Serial.print(buff);
   
   int16_t in_ = in__.value;

   //snprintf(buff, 64, "% d,  ",  in_); Serial.print(buff);
   //snprintf(buff, 64, "% 9.9f, ", float(s0q15(in_))); Serial.print(buff);
   
   // D0 = D0 + FREQ * (IN - D0 + FB * (D0 - O));
   // O  = O  + FREQ * (D0 - O);
     
   sample_t hp = in_ - _d0;                          ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(in_))); Serial.print(buff);

   ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(_feedback))); Serial.print(buff);

   auto tmp1 = _d0 - _o;                             ////snprintf(buff, 64, "% 9.9fa, ", float(s0q15(tmp1))); Serial.print(buff);
   auto tmp2 = (_feedback * tmp1) >> FX_SHIFT;       ////snprintf(buff, 64, "% 9.9fb, ", float(s0q15(tmp2))); Serial.print(buff);
      
   _d0 += ((hp + tmp2) * freq().value) >> FX_SHIFT;        ////snprintf(buff, 64, "% 9.9fc, ", float(s0q15(_d0))); Serial.print(buff);
      
   sample_t bp = _d0 - _o;                           ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(bp))); Serial.print(buff);

   _o += (bp * freq().value) >> FX_SHIFT;                  ////snprintf(buff, 64, "% 9.9f, ", float(s0q15(_o))); Serial.print(buff);

   // if      (_mode == HP)
   //  return io_t(hp);
   // else if (_mode == BP)
   //  return io_t(bp);

   io_t out(_o);

   // //snprintf(buff, 64, "% d,  ",  out.value); Serial.print(buff);
   // //snprintf(buff, 64, "% 9.9f ", float(out)); Serial.print(buff); Serial.println(); 
   // Serial.println();

   return out;
  }
 };
}

#endif /* LOWPASS_H_ */
