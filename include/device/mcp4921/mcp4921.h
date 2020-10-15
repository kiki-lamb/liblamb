#ifndef LAMBOS_DEV_MCP4921_H
#define LAMBOS_DEV_MCP4921_H

#include "SPI.h"

#include <Arduino.h>

namespace lamb {
  namespace device {
    class mcp4921 {
    private:
      byte config;
      int8_t shift;
#ifdef __AVR__
      volatile uint8_t* cs_pin_port;
#else // Assuming STM32F1...
      volatile uint32_t* cs_pin_port;
#endif
      uint16_t cs_pin_mask;

    public:
      explicit mcp4921(
        uint8_t cs_pin_,
        uint8_t data_width_ = 12,
        byte config_ = 0b01110000,
        bool init = true
      ) {
        config = config_;
        shift = data_width_ - 12;
        cs_pin_port = portOutputRegister(digitalPinToPort(cs_pin_));
        cs_pin_mask = digitalPinToBitMask(cs_pin_);

        if (init)
          pinMode(cs_pin_, OUTPUT);
      }

      inline void write(uint16_t data) __attribute__((always_inline)) {
        if (shift > 0)
          data >>= shift;
        else if (shift < 0)
          data <<= shift * -1;

        *cs_pin_port &= ~cs_pin_mask;
        SPI.transfer(config | (data>>8));
        SPI.transfer(data & 0x00ff);
        *cs_pin_port |= cs_pin_mask;
      }
    };
  }
}

#endif
