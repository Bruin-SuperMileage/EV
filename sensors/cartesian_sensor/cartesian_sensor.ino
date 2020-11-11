#include "cartesian_sensor.h"
#include <math.h>

Cartesian_Sensor::Cartesian_Sensor(const int &pin): Sensor(pin) {
  m_raw.x = 0, m_raw.y = 0, m_raw.z = 0;
  m_sensor.x = 0, m_sensor.y = 0, m_sensor.z = 0;
}

double Cartesian_Sensor::compute_magnitude(double x, double y, double z) {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Cartesian_Coordinates Cartesian_Sensor::get_raw_coordinates() {
  return m_raw;
}

Cartesian_Coordinates Cartesian_Sensor::get_sensor_coordinates() {
  return m_sensor;
}
