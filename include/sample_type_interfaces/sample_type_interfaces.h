#ifndef LAMB_SAMPLE_TYPE_INTERFACES
#define LAMB_SAMPLE_TYPE_INTERFACES

#include "../sample_type_traits/sample_type_traits.h"

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// sample_source
////////////////////////////////////////////////////////////////////////////////
  
  template <typename output_value_type_> 
  class sample_source { 
  public:
    typedef output_value_type_ output_value_type;
    typedef lamb::sample_type_traits<output_value_type> traits;

    virtual ~sample_source() = default;
    virtual output_value_type read() = 0;
  };

////////////////////////////////////////////////////////////////////////////////
// sample_receiver
////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type_>
  class sample_receiver {
  public:
    typedef input_type_ input_type;

  private:
    sample_source<input_type> * _source;
      
  public:
    virtual ~sample_receiver() = default;

    virtual inline sample_source<input_type> * source() {
      return _source;
    }

    virtual inline void connect(sample_source<input_type> * source_ = NULL) {
      _source = source_;
    } 
  };

////////////////////////////////////////////////////////////////////////////////
// sample_sink
////////////////////////////////////////////////////////////////////////////////
  
template <typename input_type_>
class sample_sink : public sample_receiver<input_type_> {
public:
  typedef input_type_ input_type;

  virtual ~sample_sink() = default;

  virtual void sink() {
    impl_sink(sample_receiver<input_type>::source()->read());
  }
  
protected:
  virtual void impl_sink(input_type const & val) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// sample_processor : public sample_source<output_value_type_>
//////////////////r//////////////////////////////////////////////////////////////
  
  template <typename input_type_, typename output_value_type_ = input_type_ > 
  class sample_processor :
    public sample_source<output_value_type_>,
    public sample_receiver<input_type_> { 
  public:
    typedef input_type_ input_type;
    typedef output_value_type_ output_value_type;
  
    virtual ~sample_processor() = default;
  
    virtual inline output_value_type read() {
      return process(sample_receiver<input_type>::source()->read());
    }

  protected:
    virtual inline output_value_type process(input_type const & in) {
      return in;
    }
  };

  ////////////////////////////////////////////////////////////////////////////////
  // function_sample_source : public sample_source<output_value_type_>
  ////////////////////////////////////////////////////////////////////////////////
   
  template <typename output_value_type_>
  class function_sample_source : public sample_source<output_value_type_> {
  public:
    typedef output_value_type_ (*func_type)();
    func_type func;
    function_sample_source(func_type f) : func(f) {};
    virtual ~function_sample_source() = default;
    virtual inline output_value_type_ read() {
      return (*func)();
    }
  };
 
  // ////////////////////////////////////////////////////////////////////////////////
  // function_sample_receiver : public sample_receiver<input_type_>
  ////////////////////////////////////////////////////////////////////////////////
   
  template <typename input_type_>
  class function_sample_receiver : public sample_receiver<input_type_> {
  public:
    ~function_sample_receiver() = default;
    typedef bool (*func_type)(input_type_);  
    func_type func;
    inline function_sample_receiver(func_type f, sample_source<input_type_> * source = NULL) : func(f) {
      connect(source);
    }
    virtual inline bool receiver() {
      return (*func)(sample_receiver<input_type_>::read());
    }
  };
 
  ////////////////////////////////////////////////////////////////////////////////
  // function_sample_processor : public sample_processor<input_type_, output_value_type_>
  ////////////////////////////////////////////////////////////////////////////////
   
  template <typename input_type_, typename output_value_type_ = input_type_ > 
  class function_sample_processor : public sample_processor<input_type_, output_value_type_> {
  public:
    typedef output_value_type_ (*func_type)(input_type_);
   
    func_type func;
   
    inline function_sample_processor(func_type f, sample_source<input_type_> * source = NULL) : func(f) {
      connect(source);
    };
   
    virtual ~function_sample_processor() = default;
   
    virtual inline output_value_type_ process(input_type_ v) {
      return (*func)(v);
    }
  };

////////////////////////////////////////////////////////////////////////////////
// Triggerable
////////////////////////////////////////////////////////////////////////////////
  
  class triggerable {
  public:
    virtual void trigger() = 0;
    virtual ~triggerable() = default;
  };

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
  
  class stoppable {
  public:
    virtual void stop() = 0;
    virtual ~stoppable() = default;
  };

////////////////////////////////////////////////////////////////////////////////

};

#endif
