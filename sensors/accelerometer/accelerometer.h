#pragma once
#include "cartesian_sensor.h"

class Accelerometer: public Cartesian_Sensor
{
public:
    Accelerometer(const int &pin);
    list_of_values[0].name="MaX:";
    list_of_values[1].val1.name="MaY:";
    list_of_values[2].name="MaZ:";
    void read_sensor_value();
};
