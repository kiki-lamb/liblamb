#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
  template <typename input_t_>
  class lowpass_filter {
  public:
    typedef input_t_                                            input_t;
    typedef typename sample_type_traits<input_t>::mix_type      mix_t;
    typedef typename sample_type_traits<mix_t>::unsigned_type   umix_t;
    typedef typename sample_type_traits<input_t>::unsigned_type feedback_t;
    typedef typename unsigned_int<sizeof(
      typename sample_type_traits<input_t>::unmixed_type
    )>::type                                                    control_t;

  private:
    static const uint8_t FX_SHIFT = 8 * (sizeof(input_t) - sizeof(control_t));
    
    control_t  _q;
    control_t  _freq;
    feedback_t _feedback;
    input_t    _buf0;
    input_t    _buf1;

  public:
    control_t freq() const {
      return _freq;
    }
    
    control_t q() const {
      return _q;
    }
    
    void freq(control_t const & freq_) {
      _freq     = freq_;
      _feedback = q() + cc_fxmul(q(), 255 - _freq);
    }

    void q(control_t const & q_) {
      _q = q_;
    }

    input_t process(input_t const & in_) {
      _buf0 += mi_fxmul(
        (in_ - _buf0) + mi_fxmul(_feedback, _buf0 - _buf1),
        freq()
      );
      
      _buf1 += ic_fxmul(
        _buf0 - _buf1,
        freq()
      ); 
      
      return _buf1;
    }

  private:
    static feedback_t cc_fxmul(control_t const & a, control_t const & b) {
      return ((umix_t)a * b) >> FX_SHIFT;
    }
    
    static input_t ic_fxmul(input_t const & a, control_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
    
    static mix_t mi_fxmul(mix_t const & a, input_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
  };
}

#endif /* LOWPASS_H_ */
