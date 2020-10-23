#pragma once
#include "base_sensor.h"

class Cartesian_Sensor: public Sensor
{
public:
    Cartesian_Sensor(const int &pin);

    virtual void read_sensor_value() = 0; // sensor-specific implementation

    double compute_magnitude(double x, double y, double z);

    double get_raw_x() const;
    double get_raw_y() const;
    double get_raw_z() const;

    double get_sensor_x() const;
    double get_sensor_y() const;
    double get_sensor_z() const;

protected:
	double m_raw_x;
	double m_raw_y;
	double m_raw_z;

	double m_sensor_x;
	double m_sensor_y;
	double m_sensor_z;
};
