#include "thermometer.h"
#include <SPI.h>
// https://github.com/sparkfun/MPL3115A2_Breakout/tree/V_H1.1_L1.2.0/Libraries/Arduino
#include <SparkFunMPL3115A2.h>

MPL3115A2 thermometer;

Thermometer::Thermometer(const int &pin): Sensor(pin) {
  thermometer.begin();
  thermometer.setModeAltimeter();
  // recommended setup from sample code
  thermometer.setOversampleRate(7); // Set Oversample to the recommended 128
  thermometer.enableEventFlags(); // Enable all three pressure and temp even  
}

void Thermometer::read_sensor_value() {
  // readTemp() - ºC
  // readTempF() - ºF
  m_raw_value = thermometer.readTempF();
  m_sensor_value = thermometer.readTempF();
}
