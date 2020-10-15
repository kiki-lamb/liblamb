#ifndef LAMB_SAMPLE_TYPE_INTERFACES
#define LAMB_SAMPLE_TYPE_INTERFACES

namespace lamb {

////////////////////////////////////////////////////////////////////////////////
// SampleSource
////////////////////////////////////////////////////////////////////////////////
  
  template <typename output_type_> 
    class SampleSource { 
  public:
    typedef output_type_ output_type;
    typedef lamb::sample_type_traits<output_type> traits;

    virtual ~SampleSource() {};
    virtual output_type read() = 0;
  };

////////////////////////////////////////////////////////////////////////////////
// SampleReceiver
////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type_>
    class SampleReceiver {
  public:
    typedef input_type_ input_type;
  
    SampleSource<input_type> * _source;
      
    virtual ~SampleReceiver() {};

    virtual inline SampleSource<input_type> * source() {
      return _source;
    }
    virtual inline void connect(SampleSource<input_type> * source_ = NULL) {
      _source = source_;
    } 
  };

////////////////////////////////////////////////////////////////////////////////
// SampleProcessor : public SampleSource<output_type_>
////////////////////////////////////////////////////////////////////////////////
  
  template <typename input_type_, typename output_type_ = input_type_ > 
    class SampleProcessor :
    public SampleSource<output_type_>,
    public SampleReceiver<input_type_> { 
  public:
  typedef input_type_ input_type;
  typedef output_type_ output_type;
  
  virtual inline ~SampleProcessor() {};
  
  virtual inline output_type read() {
    return process(SampleReceiver<input_type_>::_source->read());
  }

  protected:
  virtual inline output_type process(input_type in) {
    return in;
  }
  };

// ////////////////////////////////////////////////////////////////////////////////
// // FunctionSampleSource : public SampleSource<output_type_>
// ////////////////////////////////////////////////////////////////////////////////
//   
//   template <typename output_type_>
//     class FunctionSampleSource : public SampleSource<output_type_> {
//   public:
//     typedef output_type_ (*func_type)();
//     func_type func;
//   FunctionSampleSource(func_type f) : func(f) {};
//     virtual inline ~FunctionSampleSource() {};  
//       virtual inline output_type_ read() {
//       return (*func)();
//     }
//   };
// 
// // ////////////////////////////////////////////////////////////////////////////////
// // FunctionSampleReceiver : public SampleReceiver<input_type_>
// ////////////////////////////////////////////////////////////////////////////////
//   
//   template <typename input_type_>
//     class FunctionSampleReceiver : public SampleReceiver<input_type_> {
//   public:
//     inline ~FunctionSampleReceiver() {};
//     typedef bool (*func_type)(input_type_);  
//     func_type func;
//     inline FunctionSampleReceiver(func_type f, SampleSource<input_type_> * source = NULL) : func(f) {
//       connect(source);
//     }
//     virtual inline bool sink() {
//       return (*func)(SampleReceiver<input_type_>::read());
//     }
//   };
// 
// ////////////////////////////////////////////////////////////////////////////////
// // FunctionSampleProcessor : public SampleProcessor<input_type_, output_type_>
// ////////////////////////////////////////////////////////////////////////////////
//   
//   template <typename input_type_, typename output_type_ = input_type_ > 
//     class FunctionSampleProcessor : public SampleProcessor<input_type_, output_type_> {
//   public:
//   typedef output_type_ (*func_type)(input_type_);
//   
//   func_type func;
//   
//   inline FunctionSampleProcessor(func_type f, SampleSource<input_type_> * source = NULL) : func(f) {
//     connect(source);
//   };
//   
//   virtual inline ~FunctionSampleProcessor() {};
//   
//   virtual inline output_type_ process(input_type_ v) {
//     return (*func)(v);
//   }
//   };
// 
//
  
////////////////////////////////////////////////////////////////////////////////
// Triggerable
////////////////////////////////////////////////////////////////////////////////
  
  class Triggerable {
  public:
    virtual void trigger() = 0;
    virtual ~Triggerable() {};
  };

////////////////////////////////////////////////////////////////////////////////
};
#endif
