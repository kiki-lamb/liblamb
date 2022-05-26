#ifndef KL_MAPLE_TIMER_H
#define KL_MAPLE_TIMER_H

namespace lamb {
 namespace device {
  namespace maple_timer {    
   inline uint32_t get_frequency(uint32_t const & prescale) {
    return F_CPU/(prescale*2);
   }
    
   inline uint32_t prescale_from_frequency(uint32_t frequency) {
    return F_CPU/frequency/2;
   }
    
   inline void setup(HardwareTimer & timer, uint32_t const & hz, void(*func)(), bool resume = true) {
    timer.pause();
    timer.setPrescaleFactor(prescale_from_frequency(hz));
    timer.setOverflow(1);
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 0);
    timer.attachCompare1Interrupt(func);
    timer.refresh();
      
    if (resume)
     timer.resume();
   }
  }
 }
}
#endif
