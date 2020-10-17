#include "cartesian_sensor.h"
#include <math.h>

Cartesian_Sensor::Cartesian_Sensor(const int &pin): Sensor(&pin) {}

double Cartesian_Sensor::compute_magnitude(double x, double y, double z) {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
