#include "accelerometer.h"
#include <SPI.h>
// https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library/archive/master.zip
#include <SparkFunLSM9DS1.h>

LSM9DS1 accelerometer;

Accelerometer::Accelerometer(const int &pin): Cartesian_Sensor(pin) {}

void Accelerometer::read_sensor_value() {
  // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  if (accelerometer.begin() == false) {
    Serial.println("Failed to communicate with LSM9DS1.");
    return;
  } else if (accelerometer.accelAvailable()) {
    accelerometer.readAccel();
  }
  
  // Now we can use the ax, ay, and az variables as we please.
  // Either use them as raw ADC values, or calculated in g's.
  m_raw.x = accelerometer.ax;
  m_raw.y = accelerometer.ay;
  m_raw.z = accelerometer.az;
  
  m_sensor.x = accelerometer.calcAccel(m_raw.x);
  m_sensor.y = accelerometer.calcAccel(m_raw.y);
  m_sensor.z = accelerometer.calcAccel(m_raw.z);
  
  m_raw_value = compute_magnitude(m_raw.x, m_raw.y, m_raw.z);
  m_sensor_value = compute_magnitude(m_sensor.x, m_sensor.y, m_sensor.z);
}
