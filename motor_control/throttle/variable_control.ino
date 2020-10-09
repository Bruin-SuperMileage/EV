#include "variable_control.h"

VariableThrottle::VariableThrottle(const int &pin):Throttle(pin){}

void VariableThrottle::compute_motor_value() {
  /*
   * Reads the throttle input from analog signal,
   * Returns 0~1023
   */
  read_sensor_value();
  int throttleReading = get_raw_value();
  // Throttle cutoff threshold
  if (throttleReading < minVoltage * 1023) {
      m_motor_value = 0;
  } 
  else if (throttleReading < maxVoltage * 1023) {
      m_motor_value = map(throttleReading, minVoltage * 1023, maxVoltage * 1023, 0, 1023);
  } 
  else {
      m_motor_value =  1023;
  }
}
