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
    return std::min((double)time_pressed / (double)m_timeToFull, 1.0) * 100;
  }
  if (mapType == EXPONENTIAL)
  {
    if (time_pressed <= m_timeToFull)
    {
      return std::pow((double)time_pressed / (double)m_timeToFull, 2) * 100; // This function uses m_timeToFull to create a dependency on what time we pick and creates an exponential to the power of the 2 with the ratio
    }
    else
    {
      return 100;
    }
  }
  if (mapType == LOGARITHMIC)
  {
    if (time_pressed < m_timeToFull)
    {
      double temp_time_pressed = time_pressed;
      double ratio = 0;
      ratio = temp_time_pressed / 1000;
      if (ratio == 0)
      {
        return 0;
      }
      if (std::exp(ratio) <= 100)
      {
        return std::exp(ratio); //This function has no reliance on m_timeToFull, it simply follows an e exponential curve up til 100. Takes about 4.6 seconds to reach max speed
      }
    }
    else
    {
      return 100;
    }
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
