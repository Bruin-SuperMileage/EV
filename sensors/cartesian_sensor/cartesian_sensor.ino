#include "cartesian_sensor.h"
#include <math.h>

Cartesian_Sensor::Cartesian_Sensor(const int &pin): Sensor(&pin) {
  m_raw_x = 0, m_raw_y = 0, m_raw_z = 0;
  m_sensor_x = 0, m_sensor_y = 0, m_sensor_z = 0;
}

double Cartesian_Sensor::compute_magnitude(double x, double y, double z) {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double Cartesian_Sensor::get_raw_x() {
  return m_raw_x;
}

double Cartesian_Sensor::get_raw_y() {
  return m_raw_y;
}

double Cartesian_Sensor::get_raw_z() {
  return m_raw_z;
}

double Cartesian_Sensor::get_sensor_x() {
  return m_sensor_x;
}

double Cartesian_Sensor::get_sensor_y() {
  return m_sensor_y;
}

double Cartesian_Sensor::get_sensor_z() {
  return m_sensor_z;
}
