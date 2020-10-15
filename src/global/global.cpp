#include <Arduino.h>
#include "../../include/global/global.h"

int __free_mem()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

int lamb::free_mem() {
	return __free_mem();
}

void lamb::print_bits_8(uint8_t const & t0) {
  {
    for(uint16_t mask = 0x80; mask; mask >>= 1) {
      if (mask & t0) {
        Serial.print('1'); Serial.flush();
      }
      else {
        Serial.print('0'); Serial.flush();
      }
    }
  }
}

void lamb::print_bits_16(uint16_t const & t0) {
  {
    for(uint16_t mask = 0x8000; mask; mask >>= 1) {
      if (mask & t0) {
        Serial.print('1'); Serial.flush();
      }
      else {
        Serial.print('0'); Serial.flush();
      }
    }
  }
}

void lamb::print_bits_32(uint32_t const & t0) {
  {
    for(uint32_t mask = 0x80000000; mask; mask >>= 1) {
      if (mask & t0) {
        Serial.print('1'); Serial.flush();
      }
      else {
        Serial.print('0'); Serial.flush();
      }
    }
  }
}

uint16_t lamb::flip_bytes(uint16_t const & value) {
  uint8_t a = value >> 8;
  uint8_t b = value &  0xff;
  
  return (((uint16_t)b) << 8) | a; 
}
