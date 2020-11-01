#include "altimeter.h"
#include <SPI.h>
// https://github.com/sparkfun/MPL3115A2_Breakout/tree/V_H1.1_L1.2.0/Libraries/Arduino
#include <SparkFunMPL3115A2.h>

MPL3115A2 altimeter;

Altimeter::Altimeter(const int &pin): Sensor(pin) {
  altimeter.begin();
  altimeter.setModeAltimeter();
  // recommended setup from sample code
  altimeter.setOversampleRate(7); // Set Oversample to the recommended 128
  altimeter.enableEventFlags(); // Enable all three pressure and temp even  
}

void Altimeter::read_sensor_value() {
  // readAltitude() - m
  // readAltitudeFt() - ft
  m_raw_value = altimeter.readAltitude();
  m_sensor_value = altimeter.readAltitude();
}
