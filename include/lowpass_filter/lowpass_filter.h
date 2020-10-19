#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
  template <typename sample_t_>
  class lowpass_filter {
  public:
    typedef sample_t_                                            sample_t;
    typedef typename sample_type_traits<sample_t>::unsigned_type unsigned_sample_t;
    typedef typename sample_type_traits<sample_t>::mix_type      mix_t;
    typedef typename sample_type_traits<mix_t>::unsigned_type    unsigned_mix_t;


    typedef typename unsigned_frac<0, (
      sizeof(
        typename sample_type_traits<sample_t>::unmixed_type
      ) << 3)>::type                                            control_t;

  private:
    static const uint8_t FX_SHIFT = sizeof(control_t) << 3;
    
    control_t  _q;
    control_t  _freq;
    unsigned_sample_t  _feedback;
    sample_t    _buf0;
    sample_t    _buf1;

  public:
    control_t freq() const {
      return _freq;
    }
    
    control_t q() const {
      return _q;
    }
    
    void freq(control_t const & freq_) {
      _freq     = freq_;
      _feedback = q() + us_fxmul_cXc(q(), 255 - _freq);
    }

    void q(control_t const & q_) {
      _q = q_;
    }

    sample_t process(sample_t const & in_) {
      _buf0 += m_fxmul_mXs(
        (in_ - _buf0) + m_fxmul_mXs(_feedback, _buf0 - _buf1),
        freq()
      );
      
      _buf1 += s_fxmul_sXc(
        _buf0 - _buf1,
        freq()
      ); 
      
      return _buf1;
    }

  private:
    static unsigned_sample_t us_fxmul_cXc(control_t const & a, control_t const & b) {
      return ((unsigned_mix_t)a * b) >> FX_SHIFT;
    }
    
    static sample_t s_fxmul_sXc(sample_t const & a, control_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
    
    static mix_t m_fxmul_mXs(mix_t const & a, sample_t const & b) {
      return (a * b) >> FX_SHIFT; // FX_SHIFT less than size of input!
    }
  };
}

#endif /* LOWPASS_H_ */
