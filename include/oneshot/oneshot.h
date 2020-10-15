#ifndef KL_ONESHOT_H
#define KL_ONESHOT_H

namespace lamb {
  template <typename T>
  class oneshot {
  public:
    typedef T output_value_type;
    
    const    output_value_type * data;
    volatile bool                trigger;
    bool                         state;
    uint16_t                     length;
    uint16_t                     index;
    uint16_t                     r_point;
    
    explicit oneshot(const output_value_type * data_, uint16_t length_) :
      data(data_),
      trigger(false),
      state(false),
      length(length_),
      index(0),
      r_point(length_-256) {}
    

    virtual output_value_type play(
      uint16_t const & index_,
      uint16_t const & incr_
    ) {
      if (trigger) {
        trigger = false;
        state   = true;
        index   = 0;
      }
      
      if (state && index_ > length)
        state = false;
      else if (! state)
        return 0;
      
      output_value_type audio = data[index_];
      
      index += incr_;
      
      return audio;
    } 
        
    virtual output_value_type play() {
      output_value_type audio = play(index, 1);
      
      if (index > r_point) {
        uint32_t         past_r = index - r_point;
        past_r                  = ~past_r;
        uint16_t const & mul    = audio * past_r;
        audio                   = mul >> 8;
      }
      
      return audio;
    }
  };

  class oneshot_plus : public oneshot<int16_t> {
  public:    
    explicit oneshot_plus(
      const typename oneshot<int16_t>::output_value_type * data_,
      uint16_t length_
    ) :
      oneshot<int16_t>(data_, length_),
      amplitude(255),
      phacc(0),
      phincr(0),
      accum(0) {
    }

    uint16_t amplitude;

    virtual int16_t get_index() {
      uint16_t phacc_msb = phacc >> 16;
      return  phacc_msb;
    }
    
    virtual int16_t play() {
      if (trigger) {
        trigger = false;
        state   = true;
        phacc   = 0;
      }
      
      if (state && get_index() > length) {
        state = false;
      }
      else if (! state) {
        return 0;
      }
      
      output_value_type audio = oneshot<int16_t>::data[get_index()];

      phacc += phincr;
      
      accum = amplitude * audio;
      accum >>= 8;
      
      return accum;
    }
    

    uint32_t phacc;
    uint32_t phincr;
    
  private:
    uint32_t accum;
  };
  
}
#endif
