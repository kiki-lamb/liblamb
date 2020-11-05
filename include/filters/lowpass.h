#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

//////////////////////////////////////////////////////////////////////////////////////////

namespace lamb {

 /////////////////////////////////////////////////////////////////////////////////////////

 template <typename internal_t = s0q31, typename external_t = s0q15, bool use_limits = true>
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
  
#define ACCESSOR(type, name, member)                            \
  inline type       name()         const { return type(member); }

  ACCESSOR(mode_t,     mode, _mode);
  ACCESSOR(u0q16,      freq, _freq);
  ACCESSOR(u0q16,      res,  _res);
  ACCESSOR(external_t, lp,   _lp);
  ACCESSOR(external_t, bp,   _bp);
  ACCESSOR(external_t, hp,   _hp);

#undef ACCESSOR
    
  //--------------------------------------------------------------------------------------

  inline void mode(mode_t const & x) { _mode = x; }
  inline void res (u0q16  const & x) { _res.value = min(62000L, res_.value); }
  inline void freq(u0q16  const & x) {

   if constexpr(use_limits) {
    static constexpr size_t   limits_count            = 4;
    
    static constexpr uint16_t limits[limits_count][2] = {
     { 300, 58000 },
     { 500, 59000 },
     { 700, 60000 },
     { 900, 61000 },
    };
    
    if (freq_ <= limits[limits_count - 1][0]) {    
     for (size_t ix = 0; ix < limits_count; ix++) {
      if ((freq_ < limits[ix][0]) && (_res > limits[ix][1])) {
       _res.value = limits[ix][1];

       Serial.print("Clamp ");
       Serial.print(ix);
       Serial.println();
      
       break;
      }
     }
    }
   }
   
   //  if      ((freq_ < 300) && (_res > 62000)) {
   //   _res.value = 62000;
   //  }
   //  else if ((freq_ < 400) && (_res > 64000)) {
   //   _res.value = 64000;
   //  }
   //  else if  ((freq_ < 520) && (_res > 64250)) {
   //   _res.value = 64500;
   //  }
   // }

   Serial.print("Filter: ");
   Serial.print(freq_.value);
   Serial.print(" Res: ");
   Serial.print(_res.value);
   Serial.println();
   
   _freq            = freq_;
   _feedback        = _res;
   _feedback      >>= 8;
   _feedback       += (_res * (q8_one - _freq)) >> 8;
  }

  //--------------------------------------------------------------------------------------

  inline external_t process(external_t const & in) {
   if constexpr(use_limits) {
    if (_freq.value < 100) {
     _hp.value -= 2;
     _bp.value -= 2;
     _lp.value -= 2;
     _d0.value -= 2;
    }
   }
   
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
