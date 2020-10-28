#pragma once
#include "cartesian_sensor.h"

class Gyroscope: public Cartesian_Sensor
{
public:
    Gyroscope(const int &pin);

    void read_sensor_value();
};
