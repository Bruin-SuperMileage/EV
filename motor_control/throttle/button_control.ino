#include "button_control.h"

ButtonThrottle::ButtonThrottle(const int &pin, int timeToFull) : Throttle(pin, true)
{
  this->m_timeToFull = timeToFull;
  m_isPressed = false;
}

int ButtonThrottle::mappingFunction(int time_pressed, m_map_type mapType)
{
  if (mapType == LINEAR)
  {
    return std::min(time_pressed / m_timeToFull, 1) * 100;
  }
  if (mapType == EXPONENTIAL)
  {
  }
  if (mapType == LOGARITHMIC)
  {
  }
}

/*
   * Reads the throttle input from analog signal,
   * Returns 0~100
   */
void ButtonThrottle::compute_motor_value()
{
  if (get_raw_value() == 1)
  {
    if (!m_isPressed)
    {
      m_pressStart = millis();
    }
    int timePressed = millis() - m_pressStart;
    //using a linear mapping function(for now)
    m_motor_value = mappingFunction(timePressed, LINEAR);
  }
  else
  {
    m_isPressed = false;
    m_motor_value = 0;
  }
}
