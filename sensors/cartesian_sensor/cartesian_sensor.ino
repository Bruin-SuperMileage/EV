#include "cartesian_sensor.h"
#include <math.h>

Cartesian_Sensor::Cartesian_Sensor(const int &pin): Sensor(&pin) {
  m_raw_x = 0, m_raw_y = 0, m_raw_z = 0;
  m_sensor_x = 0, m_sensor_y = 0, m_sensor_z = 0;
}

double Cartesian_Sensor::compute_magnitude(double x, double y, double z) {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
