#pragma once
#include "base_sensor.h"

class Accelerometer: public Sensor
{
public:
    Accelerometer(const int &pin);

    void read_sensor_value();
};
