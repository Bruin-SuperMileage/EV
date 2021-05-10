#include "button_control.h"

ButtonThrottle::ButtonThrottle(const int &pin, int timeToFull) : Throttle(pin, true)
{
  this->m_timeToFull = timeToFull;
  m_isPressed = false;
  m_maxValue = 255;
  m_speedOfCar = 0;
  m_delaySpeed = 1;
}

int ButtonThrottle::mappingFunction(int time_pressed, m_map_type mapType)
{
  if (mapType == LINEAR)
  {
    return std::min((time_pressed / m_timeToFull, 1.0) * m_maxValue;
  }
  if (mapType == POWER)
  {
    if (time_pressed <= m_timeToFull)
      {
        return std::pow(time_pressed / m_timeToFull, 2) * m_maxValue; // This function uses m_timeToFull to create a dependency on what time we pick and creates an exponential to the power of the 2 with the ratio
      }
      else
      {
        return m_maxValue;
      }
  }
  if (mapType == EXPONENTIAL)
  {
     if (time_pressed < m_timeToFull)
      {
        double ratio = 0;
        ratio = time_pressed / 1000;
        if (ratio == 0)
        {
          return 0;
        }
        if (std::exp(ratio) <= m_maxValue)
        {
          return std::exp(ratio); //This function has no reliance on m_timeToFull, it simply follows an e exponential curve up til maximum value. Takes about 5.5 seconds to reach max speed(assuming 255 is the value we set)
        }
      }
      else
      {
        return m_maxValue;
      }
  }
}

/*
   * Reads the throttle input from analog signal,
   * Returns 0~100
   */
                   
int ButtonThrottle::mappingFunctionDeceleration(int val)
{
    int timeNotPressed = millis() - m_UnpressStart;
    return val/(timeNotPressed*m_decelerationFactor);
    
}
                    
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
     if (m_motor_value !=0)
    {
    m_UnpressStart = millis();
    m_motor_value = mappingFunctionDeceleration(m_motor_value);
    }
  }
}
