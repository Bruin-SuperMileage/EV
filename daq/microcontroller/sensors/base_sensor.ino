#include "base_sensor.h"

Sensor::Sensor(const int &pin)
{
    m_sensor_pin = pin;
    pinMode(m_sensor_pin, INPUT);
    m_raw_value = 0;
    m_sensor_value = 0;
}

double Sensor::get_raw_value() const
{
    return m_raw_value;
}

double Sensor::get_sensor_value() const
{
    return m_sensor_value;
}
