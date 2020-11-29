#pragma once
#include "cartesian_sensor.h"

class Accelerometer: public Cartesian_Sensor
{
public:
    Accelerometer(const int &pin);
    values.val1.name="MaX:";
    values.val1.name="MaY:";
    values.val1.name="MaZ:";
    void read_sensor_value();
};
