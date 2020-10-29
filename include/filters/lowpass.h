#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
  template <typename sample_t_>
  class lowpass {
  public:
    typedef sample_t_                                            sample_t;
    typedef typename sample_type_traits<sample_t>::unsigned_type unsigned_sample_t;
    typedef typename sample_type_traits<sample_t>::mix_type      mix_t;
    typedef typename sample_type_traits<mix_t>::unsigned_type    unsigned_mix_t;

    typedef fixed<0, (
      sizeof(
        typename sample_type_traits<sample_t>::unmixed_type
      ) << 3), false>                                            control_frac_t;

    typedef typename control_frac_t::type                        control_t;

    static const control_t control_t_one = control_frac_t::ONE;

    enum mode_t { LP, BP, HP };

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

    mode_t mode() const {
      return _mode;
    }

    control_t freq() const {
      return _freq;
    }
    
    control_t q() const {
      return _q;
    }

    void mode(mode_t const & mode_) {
      _mode = mode_;
    }
    
    void freq(control_t const & freq_) {
      _freq     = freq_;
      _feedback = q() + us_fxmul_cXc(q(), control_t_one - _freq);
    }

    void q(control_t const & q_) {
      _q = q_;
    }

    sample_t process(sample_t const & in_) {
      // D0 = D0 + FREQ * (IN - D0 + FB * (D0 - O));
      // O  = O  + FREQ * (D0 - O);

      sample_t hp = in_ - _d0;
      
      _d0 += m_fxmul_mXs(
        hp + m_fxmul_mXs(_feedback, _d0 - _o),
        freq()
      );
      
      sample_t bp = _d0 - _o;

      _o += s_fxmul_sXc(
        bp,
        freq()
      ); 

      if      (_mode == HP)
        return hp;
      else if (_mode == BP)
        return bp;
      
      return _o;
    }

  private:
    static unsigned_sample_t us_fxmul_cXc(control_t const & a, control_t const & b) {
      return ((unsigned_mix_t)a * b) >> FX_SHIFT;
    }
    
    static sample_t s_fxmul_sXc(sample_t const & a, control_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
    
    static mix_t m_fxmul_mXs(mix_t const & a, sample_t const & b) {
      return (a * b) >> FX_SHIFT; // Note that FX_SHIFT is less than size of input!
    }
  };
}

#endif /* LOWPASS_H_ */
