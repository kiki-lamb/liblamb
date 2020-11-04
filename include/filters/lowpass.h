#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

//////////////////////////////////////////////////////////////////////////////////////////

namespace lamb {

 /////////////////////////////////////////////////////////////////////////////////////////

 class lowpass {

  //--------------------------------------------------------------------------------------
  
  static constexpr u0q8 q8_one = u0q16::ONE;

  //--------------------------------------------------------------------------------------

  enum mode_t { mode_lp, mode_hp, mode_bp };
  
  //--------------------------------------------------------------------------------------

  u0q16   _res;
  u0q16   _freq;
  u0q16   _feedback;
  s0q15   _d0;
  s0q15   _lp;
  s0q15   _hp;
  s0q15   _bp;
  mode_t  _mode;

 /////////////////////////////////////////////////////////////////////////////////////////
  
 public:

  //--------------------------------------------------------------------------------------
  
  inline mode_t mode()             const { return _mode;                  }
  inline u0q16 freq()              const { return _freq;                  }
  inline u0q16 res()               const { return _res;                   }
  inline s0q15 lp()                const { return _lp;                    }
  inline s0q15 bp()                const { return _bp;                    }
  inline s0q15 hp()                const { return _hp;                    }

  //--------------------------------------------------------------------------------------

  inline void mode(mode_t const & mode_) { _mode = mode_;                 }
  inline void res (u0q16  const & res_ ) { _res = res_;                   }
  inline void freq(u0q16  const & freq_) {
   _freq            = freq_;
   _feedback        = _res;
   _feedback      >>= 8;
   _feedback       += (_res * (q8_one - _freq)) >> 8;
  }

 /////////////////////////////////////////////////////////////////////////////////////////
  
 public:

  //--------------------------------------------------------------------------------------
  
  inline s0q15 process(s0q15 const & in) {
   _hp  = in   - _d0;
   _d0 += (_hp + ((_d0 - _lp) * u8q8(_feedback.value))) * _freq;
   _bp  = _d0  - _lp;
   _lp += _bp  * _freq;

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
