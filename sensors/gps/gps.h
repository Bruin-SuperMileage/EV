#pragma once
#include "base_sensor.h"

class GPS: public Sensor
{
public:
	GPS(const int &pin);

	void read_sensor_value();

	long get_latitude() const;
	long get_longitude() const;
	long get_speed() const;
	
	list_of_values[0].name="Rpm:";
	list_of_values[1].name="Thr:";
	list_of_values[2].name="Spd:";
	
protected:
	long m_latitude;
	long m_longitude;
	long m_speed;
};
