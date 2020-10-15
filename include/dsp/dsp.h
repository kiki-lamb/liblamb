#ifndef LAMB_DSP
#define LAMB_DSP

namespace lamb {
  
////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type, typename output_type = input_type>
  class identity : public lamb::SampleProcessor<input_type, output_type> {
  public:
    inline virtual ~identity() {};

    inline identity(lamb::sample_source<input_type> * in = NULL) {
      this->connect(in);
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
  class ConvertToUnsigned : public lamb::SampleProcessor<input_type, typename lamb::sample_type_traits<input_type>::unsigned_type> {
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
  class convert_to_signed : public lamb::SampleProcessor<input_type, typename lamb::sample_type_traits<input_type>::signed_type> {
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
