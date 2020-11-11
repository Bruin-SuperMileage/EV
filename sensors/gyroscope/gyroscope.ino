#include "gyroscope.h"
#include <SPI.h>
// https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library/archive/master.zip
#include <SparkFunLSM9DS1.h>

LSM9DS1 gyroscope;

Gyroscope::Gyroscope(const int &pin): Cartesian_Sensor(pin) {}

void Gyroscope::read_sensor_value() {
  // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  if (gyroscope.begin() == false) {
    Serial.println("Failed to communicate with LSM9DS1.");
    return;
  } else if (gyroscope.gyroAvailable()) {
    gyroscope.readGyro();
  }
  
  // Now we can use the gx, gy, and gz variables as we please.
  // Either use them as raw ADC values, or calculated in DPS.
  m_raw.x = gyroscope.gx;
  m_raw.y = gyroscope.gy;
  m_raw.z = gyroscope.gz;
  
  m_sensor.x = gyroscope.calcGyro(m_raw.x);
  m_sensor.y = gyroscope.calcGyro(m_raw.y);
  m_sensor.z = gyroscope.calcGyro(m_raw.z);
  
  m_raw_value = compute_magnitude(m_raw.x, m_raw.y, m_raw.z);
  m_sensor_value = compute_magnitude(m_sensor.x, m_sensor.y, m_sensor.z);
}
