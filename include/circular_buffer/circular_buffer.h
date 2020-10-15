#ifndef LAMBOS_CIRCULAR_BUFFER_H
#define LAMBOS_CIRCULAR_BUFFER_H

namespace lamb {
  template <class T>
  class circular_buffer {

  public:
    typedef T value_type;

  private:
    T buff[256];
    uint8_t         s_msb;
    uint8_t         e_msb;
    unsigned long   num_buffers_read;
    uint8_t         read_ix;
    uint8_t         write_ix;
  
  public:
    explicit circular_buffer(): read_ix(0),write_ix(0),s_msb(0),e_msb(0) {}
    
    bool writeable() {
      return write_ix == read_ix && e_msb != s_msb;
    }
    
    bool readable() {
      return write_ix == read_ix && e_msb == s_msb;
    }
    
    void write(T in) {
      buff[write_ix] = in;
      write_ix++;
      if (write_ix == 0) e_msb ^= 1;
    }
    
    T read() {
      T out = buff[read_ix];
      read_ix++;
      if (read_ix == 0) {
        s_msb ^= 1;
        num_buffers_read++;
      }
      return out;
    }
    
    uint8_t count() {
      return (num_buffers_read << 8) + read_ix;
    }
  };
}
#endif
