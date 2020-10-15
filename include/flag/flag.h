#ifndef LAMBOS_FLAG_H
#define LAMBOS_FLAG_H

namespace lamb {
  class flag {
  private:
    bool value;

  public:
    explicit flag(bool _value = false);
    
    void set();

    bool consume();
    
    void unset();
  };
}  
#endif
