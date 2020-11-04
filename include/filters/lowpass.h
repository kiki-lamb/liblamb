#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

//////////////////////////////////////////////////////////////////////////////////////////

namespace lamb {

 /////////////////////////////////////////////////////////////////////////////////////////

 template <typename internal_t = s0q31, typename external_t = s0q15>
 // tested with s0q15 and s0q31
 class lowpass {

  //--------------------------------------------------------------------------------------
  
  static constexpr u0q16 q8_one = u0q16::ONE;

  //--------------------------------------------------------------------------------------

  enum mode_t { mode_lp, mode_hp, mode_bp };
  
  //--------------------------------------------------------------------------------------

  u0q16      _res;
  u0q16      _freq;
  u0q16      _feedback;
  internal_t _d0;
  internal_t _lp;
  internal_t _hp;
  internal_t _bp;
  mode_t     _mode;

 /////////////////////////////////////////////////////////////////////////////////////////
  
 public:

  //--------------------------------------------------------------------------------------
  
  inline mode_t mode()             const { return _mode;                  }
  inline u0q16 freq()              const { return _freq;                  }
  inline u0q16 res()               const { return _res;                   }
  inline external_t lp()           const { return external_t(_lp);        }
  inline external_t bp()           const { return external_t(_bp);        }
  inline external_t hp()           const { return external_t(_hp);        }

  //--------------------------------------------------------------------------------------

  inline void mode(mode_t const & mode_) { _mode = mode_;                 }
  inline void res (u0q16  const & res_ ) { _res = res_;                   }
  inline void freq(u0q16  const & freq_) {
   // Serial.print("Filter: ");
   // Serial.print(freq_.value);
   // Serial.println();
   
   _freq            = freq_;
   _feedback        = _res;
   _feedback      >>= 8;
   _feedback       += (_res * (q8_one - _freq)) >> 8;
  }

  inline external_t process(external_t const & in) {
   if (_freq.value < 160) {
    _hp.value >>= 1;
    _bp.value >>= 1;
    _lp.value >>= 1;
    _d0.value >>= 1;
   }
   else {   
    _hp  = in   - _d0;
    _d0 += (_hp + ((_d0 - _lp) * u8q8(_feedback.value))) * _freq;
    _bp  = _d0  - _lp;
    _lp += _bp  * _freq;
   }
   
   if      (_mode == mode_hp)
    return _hp;
   else if (_mode == mode_bp)
    return _bp;

   return _lp;
  }

 /////////////////////////////////////////////////////////////////////////////////////////
  
 };
}

//////////////////////////////////////////////////////////////////////////////////////////

#endif /* LOWPASS_H_ */
