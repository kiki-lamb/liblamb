#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

#define FX_SHIFT 8

namespace lamb {
  class lowpass_filter {
  private:
    uint8_t  _q;
    uint8_t  _freq;
    uint32_t _feedback;
    int32_t  _buf0;
    int32_t  _buf1;

  public:
    uint8_t freq() const {
      return _freq;
    }
    
    uint8_t q() const {
      return _q;
    }
    
    void freq(uint8_t const & freq_) {
      _freq     = freq_;
      _feedback = q() + ucfxmul(q(), 255 - _freq);
    }

    void q(uint8_t const & q_) {
      _q = q_;
    }

    int16_t process(int16_t const & in_) {
      _buf0 += fxmul(
        (in_ - _buf0) + fxmul(_feedback, _buf0 - _buf1),
        freq()
      );
      
      _buf1 += ifxmul(
        _buf0 - _buf1,
        freq()
      ); 
      
      return _buf1;
    }

  private:
    static uint32_t ucfxmul(uint8_t const & a, uint8_t const & b) {
      return ((uint32_t)a * b) >> FX_SHIFT;
    }
    
    static int32_t ifxmul(int32_t const & a, uint8_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
    
    static int32_t fxmul(int32_t const & a, int32_t const & b) {
      return (a * b) >> FX_SHIFT;
    }
  };
}

#endif /* LOWPASS_H_ */
