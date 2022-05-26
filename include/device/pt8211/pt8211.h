#ifndef LAMBOS_DEV_PT8211_H
#define LAMBOS_DEV_PT8211_H

#include "SPI.h"
#include <Arduino.h>

namespace lamb {
 namespace device {
  class pt8211 : public sample_sink<s0q15> {
  public:
   inline pt8211(unsigned int ws_pin_) :
    _spi(nullptr),
    _ws_pin(ws_pin_) {}      
      
   inline void setup(SPIClass & spi_) {
    _spi = &spi_;
      
    _spi->setBitOrder(MSBFIRST);
    _spi->setDataMode(SPI_MODE0);
    _spi->setClockDivider(SPI_CLOCK_DIV2);
      
    pinMode(_ws_pin, OUTPUT);
   }
     
   inline void write_mono(s0q15 const & sample) {
    _lData   = sample.value;

    _hData   = sample.value;
    _hData >>= 8;
        
    digitalWrite(_ws_pin, LOW);

    _spi->transfer(_hData);
    _spi->transfer(_lData);
        
    digitalWrite(_ws_pin, HIGH);
   }

  protected:
   inline virtual void impl_sink(s0q15 const & val) {
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
