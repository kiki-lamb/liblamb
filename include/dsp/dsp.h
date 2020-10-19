#ifndef LAMB_DSP
#define LAMB_DSP

namespace lamb {
  
#define MIX(out_, sources_, count_) \
  { for (size_t ix = 0; ix < count_; ix ++) { out_ += sources_[ix]->play(); } }

#define AMPLIFY(out_, amplitude_, shift_) \
  { out_ *= amplitude_; out_ >>= shift_; }

////////////////////////////////////////////////////////////////////////////////

  template <
    uint8_t shift,
    typename in_out_type,
    typename amplitude_type = uint12_t
    >
  inline __attribute__((always_inline))
  void amplify(
    amplitude_type const & ampl,
    in_out_type & in_out
  ) {
    in_out  *=  ampl;
    in_out >>= shift;
  }

////////////////////////////////////////////////////////////////////////////////

  template <
    typename t,
    typename amplitude_type = typename t::output_type
    >
  class amplifier :
    public sample_source<typename t::output_type> {
  private:
    t * _source;

  public:
    amplitude_type amplitude;
    uint8_t shift;
    
  public:
    explicit amplifier(
      t * source_,
      amplitude_type const & amplitude_,
      uint8_t const & shift_
    ) :
    _source(source_),
    amplitude(amplitude_),
    shift(shift_) {}

    virtual ~amplifier() = default;
    
    virtual
    typename t::output_type
    read() {
      return amplify(_source->read(), amplitude, shift);
    }
  };
  
////////////////////////////////////////////////////////////////////////////////

  template <typename t>
  inline __attribute__((always_inline))
  void mix(
    t ** sources_,
    size_t const & count,
    typename sample_type_traits<typename t::output_value_type>::mix_type & out
  ) {
    for (size_t ix = 0; ix < count; ix++) {
      out += sources_[ix]->read();
    }
  }

////////////////////////////////////////////////////////////////////////////////

//  template <typename t>
//  class mixer :
//    public sample_source<typename t::output_type> {
//  private:
//    t **  _sources;
//    size_t  _count;
//    
//  public:
//    mixer(t ** sources_, size_t count_) :
//    _sources(sources_),
//    _count(count_) {}
//
//    virtual ~mixer() = default;
//    
//    virtual
//    typename t::output_type
//    read() {
//      return mix(_sources, _count);
//    }
//  };

////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type, typename output_type = input_type>
  class identity : public lamb::sample_processor<input_type, output_type> {
  public:
    virtual ~identity() = default;

    inline identity(lamb::sample_source<input_type> * in = NULL) {
      this->connect(in);
    }
  };

////////////////////////////////////////////////////////////////////////////////
  
  // Deprecated, get rid of this crappy class.
  template <typename input_type>
  class unity_mix : public lamb::sample_source<input_type> {
  public:
    identity<input_type> input1;
    identity<input_type> input2;

    inline virtual ~unity_mix() {}; 

    inline unity_mix(sample_source<input_type> * in1, sample_source<input_type> * in2) {
      input1.connect(in1);
      input2.connect(in2);
    }

    inline virtual input_type read() {
      uint16_t tmp = 0;
      tmp += input1.read();
      tmp += input2.read();
      return tmp / 2;
    }
  };

////////////////////////////////////////////////////////////////////////////////

}  

#endif


/* Local Variables:  */
/* fill-column: 120  */
/* End:              */
