#include "current_sensor.h"

CurrentSensor::CurrentSensor(const int &pin)
  : Sensor(&pin)
{
}

void CurrentSensor::read_sensor_value()
{
    m_raw_value = analogRead(m_sensor_pin);
    m_sensor_value = (m_raw_value - 511) * 110;
}
