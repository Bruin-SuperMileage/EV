#include "accelerometer.h"
#include <SPI.h>
// https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library/archive/master.zip
#include <SparkFunLSM9DS1.h>

LSM9DS1 accelerometer;

Accelerometer::Accelerometer(const int &pin): Cartesian_Sensor(&pin) {}

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
  m_raw_x = accelerometer.ax;
  m_raw_y = accelerometer.ay;
  m_raw_z = accelerometer.az;
  
  m_sensor_x = accelerometer.calcAccel(m_raw_x);
  m_sensor_y = accelerometer.calcAccel(m_raw_y);
  m_sensor_z = accelerometer.calcAccel(m_raw_z);
  
  m_raw_value = compute_magnitude(m_raw_x, m_raw_y, m_raw_z);
  m_sensor_value = compute_magnitude(m_sensor_x, m_sensor_y, m_sensor_z);
}
