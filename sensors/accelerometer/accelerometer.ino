#include "accelerometer.h"
#include <math.h>
#include <SPI.h>
// https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library/archive/master.zip
#include <SparkFunLSM9DS1.h>

LSM9DS1 accelerometer;

Accelerometer::Accelerometer(const int &pin) : Sensor(&pin) {}

void Accelerometer::read_sensor_value() {
  // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  if (accelerometer.begin() == false) {
    Serial.println("Failed to communicate with LSM9DS1.");
  } else if (accelerometer.accelAvailable()) {
    accelerometer.readAccel();
  }
  
  // Now we can use the ax, ay, and az variables as we please.
  // Either use them as raw ADC values, or calculated in g's.
  raw_value = sqrt(pow(accelerometer.ax, 2) + pow(accelerometer.ay, 2) + pow(accelerometer.az, 2));
  m_raw_value = raw_value;
  sensor_value = sqrt(pow(accelerometer.calcAccel(accelerometer.ax), 2) + pow(accelerometer.calcAccel(accelerometer.ay), 2) + pow(accelerometer.calcAccel(accelerometer.az), 2));
  m_sensor_value = sensor_value;
}
