
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#ifdef __AVR__
#include <lamb.h>
#else
#define __DEBUG__
#include "../src/lamb.h"
#endif

typedef lamb::interp_table_osc<int8_t, int16_t, 4> osc_t;
osc_t osc_8bit(lamb::Tables::sin256_int8_t::data,  256);

#ifdef __AVR__
void loop() {}
void setup() {
  Serial.begin(115200);
  delay(2000);
#else
int main() {
#endif
  osc_8bit.set_phincr( 1L<<23 );
  
  for (size_t ix = 0; ix < 500; ix++) {
    osc_t::output_value_type const & sample = osc_8bit.read();

// #define __PRINT__
#ifdef __PRINT__
#ifdef __AVR__
    Serial.println(sample);
#else
     printf("%d\n", sample);
#endif
#endif
  }
}
