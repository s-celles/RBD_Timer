// Arduino RBD Timer Library v1.0.4 - Manage many timed events.
// https://github.com/alextaujenis/RBD_Timer
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer

namespace RBD {
  void Timer::setTimeout(unsigned long value) {
    if(value > 0) { _timeout = value; }
  }

  void Timer::setHertz(int value) {
    if(value > 0 && value < 1001) {
      _timeout = (unsigned long)(1000 / value);
    }
  }

  void Timer::restart() {
    _waypoint         = millis();
    _active           = true;
    _has_been_active  = false;
    _has_been_expired = false;
  }

  bool Timer::isActive() {
    return _timeout > getValue() && _active;
  }

  bool Timer::isExpired() {
    return _timeout <= getValue() || !_active;
  }

  bool Timer::onRestart() {
    if(isActive()) { return false; }
    restart();
    return true;
  }

  bool Timer::onActive() {
    if(isActive()) {
      if(!_has_been_active) { return _has_been_active = true; }
      return false;
    }
    return _has_been_active = false;
  }

  bool Timer::onExpired() {
    if(isExpired()) {
      if(!_has_been_expired) { return _has_been_expired = true; }
      return false;
    }
    return _has_been_expired = false;
  }

  unsigned long Timer::getValue() {
    return millis() - _waypoint;
  }

  unsigned long Timer::getInverseValue() {
    return _timeout - getValue();
  }

  int Timer::getPercentValue() {
    return getValue() / float(_timeout) * 100;
  }

  int Timer::getInversePercentValue() {
    return 100 - getPercentValue();
  }
}