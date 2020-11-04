#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
 class lowpass {

 public:

  typedef s0q15                                                io_t;
  typedef u0q8                                                 control_frac_t;

  enum mode_t { LP, BP, HP };
  
 private:

  typedef int16_t                                              sample_t;
  typedef typename sample_type_traits<sample_t>::unsigned_type unsigned_sample_t;
  typedef typename sample_type_traits<sample_t>::mix_type      mix_t;
  typedef typename sample_type_traits<mix_t>::unsigned_type    unsigned_mix_t;
  typedef typename control_frac_t::value_type                  control_t;

  static const control_t control_t_one = control_frac_t::ONE.value;

 private:
  static const uint8_t FX_SHIFT = sizeof(control_t) << 3;
    
  control_t         _q;
  control_t         _freq;
  unsigned_sample_t _feedback;
  sample_t          _d0;
  sample_t          _o;
  mode_t            _mode;
    
 public:
  lowpass() : _mode(LP) {}

  inline mode_t mode() const {
   return _mode;
  }

  inline control_t freq() const {
   return _freq;
  }
    
  inline control_t q() const {
   return _q;
  }

  inline void mode(mode_t const & mode_) {
   _mode = mode_;
  }
    
  inline void freq(control_t const & freq_) {
   _freq     = freq_;
   auto tmp  = ((unsigned_mix_t(q())) * (control_t_one - _freq)) >> FX_SHIFT;
   _feedback = q() + tmp;
  }

  inline void q(control_t const & q_) {
   _q = q_;
  }

  inline io_t process(io_t const & in__) {
   int16_t in_ = in__.value;
     
   // D0 = D0 + FREQ * (IN - D0 + FB * (D0 - O));
   // O  = O  + FREQ * (D0 - O);
     
   sample_t hp = in_ - _d0;
     
   auto tmp = (_feedback * (_d0 - _o)) >> FX_SHIFT;
      
   _d0 += ((hp + tmp) * freq()) >> FX_SHIFT;
      
   sample_t bp = _d0 - _o;

   _o += (bp * freq()) >> FX_SHIFT;

   if      (_mode == HP)
    return io_t(hp);
   else if (_mode == BP)
    return io_t(bp);
      
   return io_t(_o);
  }
 };
}

#endif /* LOWPASS_H_ */
