#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

namespace lamb {
  template <typename input_t_>
  class lowpass_filter {
  public:
    typedef input_t_                                            input_t;
    typedef typename sample_type_traits<input_t>::unsigned_type uinput_t;
    typedef typename sample_type_traits<input_t>::mix_type      mix_t;
    typedef typename sample_type_traits<mix_t>::unsigned_type   umix_t;


    typedef typename unsigned_frac<0, (
      sizeof(
        typename sample_type_traits<input_t>::unmixed_type
      ) << 3)>::type                                            ucontrol_t;

  private:
    static const uint8_t FX_SHIFT = sizeof(ucontrol_t) << 3;
    
    ucontrol_t  _q;
    ucontrol_t  _freq;
    uinput_t  _feedback;
    input_t    _buf0;
    input_t    _buf1;

  public:
    ucontrol_t freq() const {
      return _freq;
    }
    
    ucontrol_t q() const {
      return _q;
    }
    
    void freq(ucontrol_t const & freq_) {
      _freq     = freq_;
      _feedback = q() + ui_fxmul_ucXuc(q(), 255 - _freq);
    }

    void q(ucontrol_t const & q_) {
      _q = q_;
    }

    input_t process(input_t const & in_) {
      _buf0 += m_fxmul_mXi(
        (in_ - _buf0) + m_fxmul_mXi(_feedback, _buf0 - _buf1),
        freq()
      );
      
      _buf1 += i_fxmul_iXuc(
        _buf0 - _buf1,
        freq()
      ); 
      
      return _buf1;
    }

  private:
    static uinput_t ui_fxmul_ucXuc(ucontrol_t const & a, ucontrol_t const & b) {
      return ((umix_t)a * b) >> FX_SHIFT;
    }
    
    static input_t i_fxmul_iXuc(input_t const & a, ucontrol_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
    
    static mix_t m_fxmul_mXi(mix_t const & a, input_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
  };
}

#endif /* LOWPASS_H_ */
