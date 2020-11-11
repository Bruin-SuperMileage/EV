#pragma once
#include "base_sensor.h"

class Thermometer: public Sensor
{
public:
	Thermometer(const int &pin);

	void read_sensor_value();
};
