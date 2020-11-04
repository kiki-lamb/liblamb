#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
 class lowpass {

 public:

  typedef s0q15                                                io_t;

  enum mode_t { LP, BP, HP };

  typedef u0q32                                                  freq_t;
  typedef u0q32                                                  res_t;

 // public:
  
 //  typedef typename control_frac_t::value_type                  control_t;
  
 private:

  typedef int16_t                                              sample_t;
  typedef typename sample_type_traits<sample_t>::unsigned_type unsigned_sample_t;
  typedef typename sample_type_traits<sample_t>::mix_type      mix_t;
  typedef typename sample_type_traits<mix_t>::unsigned_type    unsigned_mix_t;

  static constexpr freq_t freq_t_one = freq_t::ONE;
  static constexpr res_t  res_t_one  = res_t::ONE;

 private:
  res_t             _q;
  freq_t            _freq;
  res_t             _feedback;
  sample_t          _d0;
  sample_t          _o;
  mode_t            _mode;
    
 public:
  lowpass() : _mode(LP) {}

  inline mode_t mode() const {
   return _mode;
  }

  inline freq_t freq() const {
   return _freq;
  }
    
  inline res_t q() const {
   return _q;
  }

  inline void mode(mode_t const & mode_) {
   _mode = mode_;
  }
    
  inline void freq(freq_t const & freq_) {
   _freq     = freq_;
   res_t tmp = q() * (freq_t_one - _freq);
   _feedback = q() + tmp;
  }

  inline void q(res_t const & q_) {
   _q = q_;
  }

  inline io_t process(io_t const & in__) {
   int16_t in_ = in__.value;
     
   // D0 = D0 + FREQ * (IN - D0 + FB * (D0 - O));
   // O  = O  + FREQ * (D0 - O);
     
   sample_t hp   = in_ - _d0;     
   res_t    tmp  = _feedback * (_d0 - _o);
   _d0          += ((tmp + hp) * freq()).value;
   sample_t bp   = _d0 - _o;
   _o           += (freq() * bp).value;

   if      (_mode == HP)
    return io_t(hp);
   else if (_mode == BP)
    return io_t(bp);
      
   return io_t(_o);
  }
 };
}

#endif /* LOWPASS_H_ */
