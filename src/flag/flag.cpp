#include "../../include/flag/flag.h"
#include "Arduino.h"

void lamb::flag::set() {
  _value = true;
}

void lamb::flag::unset() {
  _value = false;
}

lamb::flag::flag(bool value_) :
  _value(value_) {
};

bool lamb::flag::consume() {
  if (_value) {
    _value = false;
    
    return true;
  }

  return false;
}

