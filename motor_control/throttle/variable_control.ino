#include "variable_control.h"

VariableThrottle::VariableThrottle(const int &pin) : Throttle(pin) {}

void VariableThrottle::compute_motor_value()
{
    /*
   * Reads the throttle input from analog signal,
   * Returns 0~100
   */
    int throttleReading = get_raw_value();
    // Throttle cutoff threshold
    if (throttleReading < minVoltage * 100)
    {
        m_motor_value = 0;
    }
    else if (throttleReading < maxVoltage * 100)
    {
        m_motor_value = map(throttleReading, minVoltage * 100, maxVoltage * 100, 0, 100);
    }
    else
    {
        m_motor_value = 100;
    }
}
