#ifndef LOWPASS_LAMB_H_
#define LOWPASS_LAMB_H_

#define FX_SHIFT 8
#define SHIFTED_1 ((uint8_t) 255)

namespace lamb {
  class lowpass_filter
  {
  private:
    uint8_t q;
    uint8_t f;
    uint32_t fb;
    int32_t buf0;
    int32_t buf1;

  public:
    lowpass_filter() : fb(0), buf0(0), buf1(0) {}

    /** Set the cut off frequency,
        @param cutoff use the range 0-255 to represent 0-8192 Hz (AUDIO_RATE/2).
        Be careful of distortion at the lower end, especially with high resonance.
    */
    void set_f(uint8_t cutoff)
      {
        f = cutoff;
        fb = q+ucfxmul(q, SHIFTED_1 - cutoff);
      }


    /** Set the resonance. If you hear unwanted distortion, back off the resonance.
        @param resonance in the range 0-255, with 255 being most resonant.
    */
    void set_q(uint8_t resonance)
      {
        q = resonance;
      }

    int16_t process(int16_t in)
      {
        buf0+=fxmul(((in - buf0) + fxmul(fb, buf0-buf1)), f);
        buf1+=ifxmul(buf0-buf1, f); // could overflow if input changes fast
        return buf1;
      }

  private:
    static uint32_t ucfxmul(uint8_t a, uint8_t b)
      {
        return (((uint32_t)a*b)>>FX_SHIFT);
      }

    static int32_t ifxmul(int32_t a, uint8_t b)
      {
        return ((a*b)>>FX_SHIFT);
      }

    static int32_t fxmul(int32_t a, int32_t b)
      {
        return ((a*b)>>FX_SHIFT);
      }
  };
}

#endif /* LOWPASS_H_ */
