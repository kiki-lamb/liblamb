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
  s0q15   _lp;
  s0q15   _hp;
  s0q15   _bp;
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

  inline s0q15 lp() const {
   return _lp;
  }

  inline s0q15 bp() const {
   return _bp;
  }

  inline s0q15 hp() const {
   return _hp;
  }

  inline void mode(mode_t const & mode_) {
   _mode = mode_;
  }

  inline void freq(u0q16 const & freq_) {
   freq(u0q8(freq_.value >> 4));
  }
  
  inline void res(u0q16 const & q_) {
   res(u0q8(q_.value >> 4));
  }

 private:
  
  inline void freq(u0q8 const & freq_) {
   _freq            = freq_;
   _feedback.value  = res().value;
   _feedback       += (res() * (q8_one - _freq)).value;
  }
  
  inline void res(u0q8 const & q_) {
   _q = q_;
  }

 public:
  
  inline s0q15 process(s0q15 const & in) {
   _hp  = in   - _d0;
   _d0 += (_hp + ((_d0 - _lp) * u8q8(_feedback.value))) * freq();
   _bp  = _d0  - _lp;
   _lp += _bp  * freq();

   if      (_mode == mode_hp)
    return _hp;
   else if (_mode == mode_bp)
    return _bp;

   return _lp;
  }
 };
}

#endif /* LOWPASS_H_ */
