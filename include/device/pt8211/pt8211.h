#ifndef LAMBOS_DEV_PT8211_H
#define LAMBOS_DEV_PT8211_H

#include "SPI.h"
#include <Arduino.h>
#include "../../sample_type_interfaces/sample_type_interfaces.h"

namespace lamb {
  namespace device {
    class pt8211 : public sample_sink<int16_t> {
    public:
      inline pt8211(unsigned int ws_pin_, SPIClass * spi_ = nullptr) :
        _spi(spi_),
        _ws_pin(ws_pin_) {}      
      
      inline void setup(SPIClass * spi_ = nullptr) {
        if (spi_ != nullptr)
          _spi = spi_;
        
        _spi->setBitOrder(MSBFIRST);
        _spi->setDataMode(SPI_MODE0);
        _spi->setClockDivider(SPI_CLOCK_DIV2);
        
        pinMode(_ws_pin, OUTPUT);
      }

      inline void write_mono(int16_t sample) {
        _lData   = sample;
        _hData   = sample;
        _hData >>= 8;
        
        digitalWrite(_ws_pin, LOW);
        SPI.transfer(_hData);
        SPI.transfer(_lData);
        
        digitalWrite(_ws_pin, HIGH);
      }

    protected:
      inline virtual void impl_sink(int16_t const & val) {
        write_mono(val);
      }
      
    private:
      SPIClass *   _spi;
      uint16_t     _hData;
      uint16_t     _lData;
      unsigned int _ws_pin;      
    };
  }
}

#endif
