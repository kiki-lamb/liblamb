#include <Arduino.h>

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <lamb.h>

typedef lamb::interp_table_osc<int8_t, int16_t, 4> osc_t;
//typedef lamb::table_osc<int8_t> osc_t;
osc_t osc_8bit(lamb::Tables::sin256_int8_t::data,  256);

__attribute__((flatten))
void loop() {
    volatile register osc_t::output_value_type sample; 

      unsigned long start = micros();

      size_t ix = 0;
      do {
          sample = osc_8bit.read();
      } while (ix++ != 10000);
      
      unsigned long const & delta = micros()-start;
      Serial.println(delta);
}

void setup() {
  Serial.begin(57600);    
  osc_8bit._phincr =  1L<<23;
}


