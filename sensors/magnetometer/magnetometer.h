#pragma once
#include "cartesian_sensor.h"

class Magnetometer: public Cartesian_Sensor
{
public:
    Magnetometer(const int &pin);

    void read_sensor_value();
};
