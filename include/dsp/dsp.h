#ifndef LAMB_DSP
#define LAMB_DSP

namespace lamb {
  
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
  
  // template <
  //   typename input_type,
  //   uint8_t  downshift,
  //   typename output_type = input_type
  //   >
  // class amplify : public lamb::sample_processor<input_type, output_type> {
  // public:
  //   uint16_t amplitude;
    
  //   virtual ~amplify() = default;

  //   inline amplify(lamb::sample_source<input_type> * in = NULL) {
  //     this->connect(in);
  //   }

  //   inline output_type process(input_type const & input) {
  //     typename sample_type_traits<input_type>::mix_type tmp = input;

  //     tmp *= amplitude;
  //     tmp >>= downshift;

  //     return tmp;
  //   }
  // };


////////////////////////////////////////////////////////////////////////////////

  template <
    typename input_type,
    typename amplitude_type = input_type
    >
  input_type amplify(
    input_type const & input,
    amplitude_type const & ampl,
    uint8_t const & shift = sizeof(amplitude_type) << 3
  ) {
    typename sample_type_traits<input_type>::mix_type tmp = input;

    tmp         *=  ampl;
    tmp        >>= shift;

    return tmp;
  }

////////////////////////////////////////////////////////////////////////////////

  template <typename t>
  typename sample_type_traits<typename t::value_type>::mix_type
  mix(
    t ** sources_,
    size_t const & count) {

    typename sample_type_traits<typename t::value_type>::mix_type tmp_mix = 0;

    tmp_mix = sample_type_traits<decltype(tmp_mix)>::silence;
    
    for (size_t ix = 0; ix < count; ix++) {
      sample_source<int16_t> * s = sources_[ix];
      
      tmp_mix += s->read();
    }
    
    return tmp_mix;
  }

////////////////////////////////////////////////////////////////////////////////
  
  // This should be replaced.
  template <typename input_type>
  class mix_6 : public lamb::sample_source<input_type> {
  public:
    identity<input_type> input0;
    identity<input_type> input1;
    identity<input_type> input2;
    identity<input_type> input3;
    identity<input_type> input4;
    identity<input_type> input5;

    inline virtual ~mix_6() = default;

    inline virtual input_type read() {
      typename sample_type_traits<input_type>::mix_type mix = 0;

      input_type tmp;

      tmp = input0.read();
      mix += tmp;

      tmp = input1.read();
      mix += tmp;

      tmp = input2.read();
      mix += tmp;

      tmp = input3.read();
      mix += tmp;

      tmp = input4.read();
      mix += tmp;
      
      tmp = input5.read();
      mix += tmp;

      const int8_t shift = sizeof(mix) - sizeof(input_type) - 1;

      if (shift > 0) {
        mix >>= shift;
      }
      
      return mix;
    }
  };

////////////////////////////////////////////////////////////////////////////////
  
  // This should be a template...
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

  template <typename input_type>
  class ConvertToUnsigned : public lamb::sample_processor<input_type, typename lamb::sample_type_traits<input_type>::unsigned_type> {
  public:
    inline virtual ~ConvertToUnsigned() {};

    inline ConvertToUnsigned(lamb::sample_source<input_type> * in) {
      this->connect(in);
    }

    inline virtual typename lamb::sample_type_traits<input_type>::unsigned_type process(input_type v) {
      return lamb::sample_type_traits<input_type>::to_uint8_t(v);
    }
  };

/////////////////////////////////////////////////////////////////////////////////

  template <typename input_type>
  class convert_to_signed : public lamb::sample_processor<input_type, typename lamb::sample_type_traits<input_type>::signed_type> {
  public:
    inline virtual ~convert_to_signed() {};

    inline convert_to_signed(lamb::sample_source<input_type> * in) {
      connect(in);
    }

    inline virtual typename lamb::sample_type_traits<input_type>::unsigned_type process(input_type v) {
      return lamb::sample_type_traits<input_type>::to_int8_t(v);
    }
  };
};

#endif


/* Local Variables:  */
/* fill-column: 100  */
/* End:              */
