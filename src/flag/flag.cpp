#include "../../include/flag/flag.h"
#include "Arduino.h"

void lamb::flag::set() {
  value = true;
}

void lamb::flag::unset() {
  value = false;
}

lamb::flag::flag(bool _value) :
  value(_value) {
};

bool lamb::flag::consume() {
  if (value) {
    value = false;
    
    return true;
  }
  return false;
}

