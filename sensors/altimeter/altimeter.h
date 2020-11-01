#pragma once
#include "base_sensor.h"

class Altimeter: public Sensor
{
public:
	Altimeter(const int &pin);

	void read_sensor_value();
};
