#ifndef BASIC_LAMB_H_
#define BASIC_LAMB_H_

//////////////////////////////////////////////////////////////////////////////////////////

namespace lamb {

//////////////////////////////////////////////////////////////////////////////////////////

 namespace filters {

  /////////////////////////////////////////////////////////////////////////////////////////

  template <
   typename external_t          = s0q15,
   bool     use_limits          = true,
   typename internal_t          = s16p0q15
   >
  class basic {
   
   //--------------------------------------------------------------------------------------

  public:
   
   typedef u0q16 unsigned_internal_t;

   //--------------------------------------------------------------------------------------

  private:
   
   static constexpr u0q16 Q16_ONE     = u0q16::ONE;
   static constexpr u0q16 DEFAULT_RES = u0q16(63000L);

   //--------------------------------------------------------------------------------------

   enum mode_t { mode_lp, mode_hp, mode_bp };
  
   //--------------------------------------------------------------------------------------

#define ACCESSOR(store_type, cast_type, name)                           \
   private:                                                             \
   store_type (_ ## name);                                              \
                                                                        \
  public:                                                               \
  inline constexpr cast_type name() const { return cast_type(_ ## name);  }
  
   ACCESSOR(mode_t,                mode_t,     mode);
   ACCESSOR(unsigned_internal_t,   u0q16,      freq);
   ACCESSOR(unsigned_internal_t,   u0q16,      feedback);
   ACCESSOR(unsigned_internal_t,   u0q16,      res);
   ACCESSOR(internal_t,            external_t, d0);
   ACCESSOR(internal_t,            external_t, lp); 
   ACCESSOR(internal_t,            external_t, bp);
   ACCESSOR(internal_t,            external_t, hp);

#undef ACCESSOR

   //--------------------------------------------------------------------------------------

   inline constexpr basic() : _res(u0q16::MAX) {}
  
   //--------------------------------------------------------------------------------------
#define mmin(a,b) ((a)<(b)?(a):(b))
      inline constexpr void mode(mode_t const & x) { _mode = x; }
      inline constexpr void res (u0q16  const & x) { _res.value = mmin(DEFAULT_RES.value, x.value); }
#undef mmin
      inline constexpr void freq(u0q16  const & x) {
          // if (lamb_fixed_overflow) {
          //  _res -= 4;
          //  lamb_fixed_overflow = false;
          // }
   
          if constexpr(use_limits) {
              constexpr size_t   limits_count            = 7;
   
              constexpr uint16_t limits[limits_count][2] = {
                  { 600,  48500             }, // calib
                  { 900,  52000             }, // guessed
                  { 1200, 56000             }, // calib
                  { 1800, 57000             }, // guessed
                  { 2300, 58000             }, // calib
                  { 2800, 59750             }, // calib
                  { 3500, DEFAULT_RES.value }, // calib
              };
   
              if (x <= limits[limits_count - 1][0]) {    
                  for (size_t ix = 0; ix < limits_count; ix++) {
                      if ((x < limits[ix][0]) && (_res > limits[ix][1])) {
                          _res.value = limits[ix][1];

                          // Serial.print("Clamp ");
                          // Serial.print(ix);
                          // Serial.print(" ");
                          // Serial.println();
        
                          break;
                      }
                  }
              }
          }

          // Serial.print("Filter: ");
          // Serial.print(x.value);
          // Serial.print(" Res: ");
          // Serial.print(_res.value);
          // Serial.println();
   
          _freq            = x;
          _feedback        = _res;
          _feedback      >>= 8;
          _feedback       += (_res * (Q16_ONE - _freq)) >> 8;
      }

      //--------------------------------------------------------------------------------------

      inline constexpr
      external_t process(external_t const & in) {
          // if constexpr(use_limits) {
          //  if (_freq.value < 100) {
          //   _hp.value >>= 1;
          //   _bp.value >>= 1;
          //   _lp.value >>= 1;
          //   _d0.value >>= 1;
          //  }
          // }

          // if (false) {
          //  char buff[64];
    
          //  snprintf(
          //   buff, 64,
          //   "% 10.3f, ",
          //   float(_freq)
          //  );
          //  Serial.print(buff);
    
          //  snprintf(
          //   buff, 64,
          //   "% 10.3f, ",
          //   float(_feedback)
          //  );
          //  Serial.print(buff);

          //  snprintf(
          //   buff, 64,
          //   "% 10.3f, ",
          //   float(in)
          //  );
          //  Serial.print(buff);
    
          //  snprintf(
          //   buff, 64,
          //   "% 10.3f, ",
          //   float(_hp)
          //  );
          //  Serial.print(buff);
    
          //  snprintf(
          //   buff, 64,
          //   "% 10.3f, ",
          //   float(_d0)
          //  );
          //  Serial.print(buff);
    
          //  snprintf(
          //   buff, 64,
          //   "% 10.3f, ",
          //   float(_bp)
          //  );
          //  Serial.print(buff);
    
          //  snprintf(
          //   buff, 64,
          //   "% 10.3f, ",
          //   float(_lp)
          //  );
          //  Serial.print(buff);

          //  Serial.println();
          //  Serial.println();
          // }
    
          _hp  = in   - _d0;
          _d0 += (_hp + ((_d0 - _lp) * u8q8(_feedback.value))) * _freq;
          _bp  = _d0  - _lp;
          _lp += _bp  * _freq;
   
          // if      (_mode == mode_hp)
          //  return _hp;
          // else if (_mode == mode_bp)
          //  return _bp;

          return _lp;
      }

      /////////////////////////////////////////////////////////////////////////////////////////
  
  };
 }
}

//////////////////////////////////////////////////////////////////////////////////////////

#endif /* BASIC_H_ */
