#pragma once
#include "cartesian_sensor.h"

class Gyroscope: public Cartesian_Sensor
{
public:
    Gyroscope(const int &pin);
    values.val1.name="Hea:";
    values.val2.name="Pit:";
    values.val3.name="Rol:";
    void read_sensor_value();
};
