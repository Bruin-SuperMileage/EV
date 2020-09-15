#include "base_throttle.h"

Throttle::Throttle(const int &pin)
{
    m_sensor_pin = pin;
    m_raw_value = 0;
    m_motor_value = 0;
}

void Throttle::read_sensor_value()
{
    m_raw_value = analogRead(m_sensor_pin);
}

int Throttle::get_raw_value() const
{
    return m_raw_value;
}

int Throttle::get_motor_value() const
{
    return m_motor_value;
}
