#ifndef LAMB_SAMPLE_TYPE_INTERFACES
#define LAMB_SAMPLE_TYPE_INTERFACES

#include "../sample_type_traits/sample_type_traits.h"

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// sample_source
////////////////////////////////////////////////////////////////////////////////
  
  template <typename output_type_> 
  class sample_source { 
  public:
    typedef output_type_ output_type;
    typedef lamb::sample_type_traits<output_type> traits;

    virtual ~sample_source() {};
    virtual output_type read() = 0;
  };

////////////////////////////////////////////////////////////////////////////////
// sample_sink
////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type_>
  class sample_sink {
  public:
    typedef input_type_ input_type;
  
    sample_source<input_type> * _source;
      
    virtual ~sample_sink() {};

    virtual inline sample_source<input_type> * source() {
      return _source;
    }
    virtual inline void connect(sample_source<input_type> * source_ = NULL) {
      _source = source_;
    } 
  };

////////////////////////////////////////////////////////////////////////////////
// sample_processor : public sample_source<output_type_>
////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type_, typename output_type_ = input_type_ > 
  class sample_processor :
    public sample_source<output_type_>,
    public sample_sink<input_type_> { 
  public:
    typedef input_type_ input_type;
    typedef output_type_ output_type;
  
    virtual inline ~sample_processor() {};
  
    virtual inline output_type read() {
      return process(sample_sink<input_type_>::_source->read());
    }

  protected:
    virtual inline output_type process(input_type in) {
      return in;
    }
  };

  ////////////////////////////////////////////////////////////////////////////////
  // function_sample_source : public sample_source<output_type_>
  ////////////////////////////////////////////////////////////////////////////////
   
  template <typename output_type_>
  class function_sample_source : public sample_source<output_type_> {
  public:
    typedef output_type_ (*func_type)();
    func_type func;
    function_sample_source(func_type f) : func(f) {};
    virtual inline ~function_sample_source() {};  
    virtual inline output_type_ read() {
      return (*func)();
    }
  };
 
  // ////////////////////////////////////////////////////////////////////////////////
  // function_sample_sink : public sample_sink<input_type_>
  ////////////////////////////////////////////////////////////////////////////////
   
  template <typename input_type_>
  class function_sample_sink : public sample_sink<input_type_> {
  public:
    inline ~function_sample_sink() {};
    typedef bool (*func_type)(input_type_);  
    func_type func;
    inline function_sample_sink(func_type f, sample_source<input_type_> * source = NULL) : func(f) {
      connect(source);
    }
    virtual inline bool sink() {
      return (*func)(sample_sink<input_type_>::read());
    }
  };
 
  ////////////////////////////////////////////////////////////////////////////////
  // function_sample_processor : public sample_processor<input_type_, output_type_>
  ////////////////////////////////////////////////////////////////////////////////
   
  template <typename input_type_, typename output_type_ = input_type_ > 
  class function_sample_processor : public sample_processor<input_type_, output_type_> {
  public:
    typedef output_type_ (*func_type)(input_type_);
   
    func_type func;
   
    inline function_sample_processor(func_type f, sample_source<input_type_> * source = NULL) : func(f) {
      connect(source);
    };
   
    virtual inline ~function_sample_processor() {};
   
    virtual inline output_type_ process(input_type_ v) {
      return (*func)(v);
    }
  };

////////////////////////////////////////////////////////////////////////////////
// Triggerable
////////////////////////////////////////////////////////////////////////////////
  
  class triggerable {
  public:
    virtual void trigger() = 0;
    virtual ~triggerable() {};
  };

////////////////////////////////////////////////////////////////////////////////
};
#endif
