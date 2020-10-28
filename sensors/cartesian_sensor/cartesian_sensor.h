#pragma once
#include "base_sensor.h"

struct Cartesian_Coordinates {
	double x;
	double y;
	double z;
};

class Cartesian_Sensor: public Sensor
{
public:
    Cartesian_Sensor(const int &pin);

    virtual void read_sensor_value() = 0; // sensor-specific implementation

    double compute_magnitude(double x, double y, double z);

    Cartesian_Coordinates get_raw_coordinates();
    Cartesian_Coordinates get_sensor_coordinates();

protected:
	Cartesian_Coordinates m_raw;
	Cartesian_Coordinates m_sensor;
};
