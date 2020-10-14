#include "variable_control.h"

VariableThrottle::VariableThrottle(const int &pin) : Throttle(pin) {}

void VariableThrottle::compute_motor_value()
{
    /*
   * Reads the throttle input from analog signal,
   * Returns 0~100
   */
    // Throttle cutoff threshold
    if (m_raw_value < minVoltage * 100)
    {
        m_motor_value = 0;
    }
    else if (m_raw_value < maxVoltage * 100)
    {
        m_motor_value = map(m_raw_value, minVoltage * 100, maxVoltage * 100, 0, 100);
    }
    else
    {
        m_motor_value = 100;
    }
}
