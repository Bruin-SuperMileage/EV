#include "base_throttle.h"

Throttle::Throttle(const int &pin, bool digital)
{
    m_sensor_pin = pin;
    pinMode(m_sensor_pin, INPUT);
    m_raw_value = 0;
    m_motor_value = 0;
    m_digital_read = digital;
}

void Throttle::read_sensor_value()
{
    if (m_digital_read)
        m_raw_value = digitalRead(m_sensor_pin);
    else
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
