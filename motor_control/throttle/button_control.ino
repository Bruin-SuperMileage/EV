#include "button_control.h"

ButtonThrottle::ButtonThrottle(const int &pin, int timeToFull) : Throttle(pin, true)
{
  this->m_timeToFull = timeToFull;
  m_isPressed = false;
}

int ButtonThrottle::mappingFunction(int time_pressed, m_map_type mapType)
{
  if(m_isPressed == true)
  {
if (mapType == LINEAR)
  {
    m_speedOfCar = std::min((double)time_pressed / (double)m_timeToFull, 1.0) * m_maxValue;
    return m_speedOfCar;
  }
  if (mapType == POWER)
  {
    if (time_pressed <= m_timeToFull)
    {
      m_speedOfCar = std::pow((double)time_pressed / (double)m_timeToFull, 2) * m_maxValue;
      return m_speedOfCar; // This function uses m_timeToFull to create a dependency on what time we pick and creates an exponential to the power of the 2 with the ratio
    }
    else
    {
      m_speedOfCar = m_maxValue;
      return m_speedOfCar;
    }
  }
  if (mapType == EXPONENTIAL)
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
      if (std::exp(ratio) <= m_maxValue)
      {
        m_speedOfCar = std::exp(ratio);
        return m_speedOfCar; //This function has no reliance on m_timeToFull, it simply follows an e exponential curve up til maximum value. Takes about 5.5 seconds to reach max speed(assuming 255 is the value we set)
      }
    }
    else
    {
      m_speedOfCar = m_maxValue;
      return m_speedOfCar;
    }
  }
  }
}

int mappingFunctionDeceleration(int time_NotPressed)
{
   if(m_isPressed == false)
  {
    if(m_speedOfCar ==0)
    {
      return m_speedOfCar;
    }
  if(time_NotPressed >= 1)
  {
    double seconds_conversion = time_notPressed/1000;
    m_speedOfCar = m_speedOfCar/seconds_conversion;
  }
  m_speedOfCar = m_speedOfCar/(double)time_NotPressed;
  return m_speedOfCar;
  }
  return m_speedOfCar;
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
