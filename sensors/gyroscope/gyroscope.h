#pragma once
#include "cartesian_sensor.h"

class Gyroscope: public Cartesian_Sensor
{
public:
    Gyroscope(const int &pin);
    list_of_values[0].val1.name="Hea:";
    list_of_values[1].name="Pit:";
    list_of_values[2].name="Rol:";
    void read_sensor_value();
};
