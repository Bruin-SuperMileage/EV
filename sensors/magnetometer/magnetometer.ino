#include "magnetometer.h"
#include <SPI.h>
// https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library/archive/master.zip
#include <SparkFunLSM9DS1.h>

LSM9DS1 magnetometer;

Magnetometer::Magnetometer(const int &pin): Cartesian_Sensor(pin) {}

void Magnetometer::read_sensor_value() {
  // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  if (magnetometer.begin() == false) {
    Serial.println("Failed to communicate with LSM9DS1.");
    return;
  } else if (magnetometer.magAvailable()) {
    magnetometer.readMag();
  }
  
  // Now we can use the mx, my, and mz variables as we please.
  // Either use them as raw ADC values, or calculated in Gauss.
  m_raw.x = magnetometer.mx;
  m_raw.y = magnetometer.my;
  m_raw.z = magnetometer.mz;
  
  m_sensor.x = magnetometer.calcMag(m_raw.x);
  m_sensor.y = magnetometer.calcMag(m_raw.y);
  m_sensor.z = magnetometer.calcMag(m_raw.z);
  
  m_raw_value = compute_magnitude(m_raw.x, m_raw.y, m_raw.z);
  m_sensor_value = compute_magnitude(m_sensor.x, m_sensor.y, m_sensor.z);
}
