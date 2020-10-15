#ifndef LAMBOS_FUNCTIONS_H
#define LAMBOS_FUNCTIONS_H

namespace lamb {
  template <void(*FUNC)(), uint32_t RATE> bool periodically(uint32_t const & now) {
    static uint32_t last = 0;

    if ((now - RATE) > last) {
      (*FUNC)();
      last = now;
      return true;
    }
    return false;
  }

  template <bool(*FUNC)(), uint32_t RATE> bool periodically(uint32_t const & now) {
    static uint32_t last = 0;

    if (((now - RATE) > last) && (*FUNC)()) {
      last = now;
      return true;
    }
    return false;
  }

  inline bool if_flagged(volatile bool & flag, void (*func)()) {
    if (flag) {
      flag = false;
      (*func)();
      return true;
    }
    return false;
  }
}

#endif
