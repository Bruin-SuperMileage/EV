#include "variable_control.h"

VariableThrottle::VariableThrottle(const int &pin):Throttle(pin){}

int VariableThrottle::compute_motor_value() {
  /*
   * Reads the throttle input from analog signal,
   * Returns 0~1023
   */
  int throttleReading = analogRead(get_pin());
  // Throttle cutoff threshold
  if (throttleReading < minVoltage * 1023) {
    return 0;
  } else if (throttleReading < maxVoltage * 1023) {
    return map(throttleReading, minVoltage * 1023, maxVoltage * 1023, 0, 1023);
  } else {
    return 1023;
  }
}