#ifndef LAMBOS_TASK_H
#define LAMBOS_TASK_H

#include <inttypes.h>

namespace lamb {
  class task {
    static char last_id;
  private:
    void describe() const;
  public:
    unsigned long    last_ran;
    unsigned long    interval;
    volatile  bool * flag;
    char             id;
    void             (*work)() = 0;
    bool             operator()(unsigned long now);
    task(void(*work)(), unsigned long interval, volatile bool * flag = 0);
    task(void(*work)(), volatile bool * flag, unsigned long interval = 0);
    task(void(*work)());
  };
}

#endif
