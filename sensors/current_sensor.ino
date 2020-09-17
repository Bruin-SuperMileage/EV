#include "current_sensor.h"

Current_Sensor::Current_Sensor(const int &pin)
  : Sensor(&pin)
{
}

void Current_Sensor::read_sensor_value()
{
    m_raw_value = analogRead(m_sensor_pin);
    m_sensor_value = (m_raw_value - 511) * 110;
}
