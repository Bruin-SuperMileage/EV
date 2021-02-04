int ButtonThrottle::mappingFunction(int time_pressed, m_map_type mapType)
{
  if(m_isPressed == true)
  {
if (mapType == LINEAR)
  {
    return std::min((double)time_pressed / (double)m_timeToFull, 1.0) * m_maxValue;
  }
  if (mapType == POWER)
  {
    if (time_pressed <= m_timeToFull)
    {
      return std::pow((double)time_pressed / (double)m_timeToFull, 2) * m_maxValue; // This function uses m_timeToFull to create a dependency on what time we pick and creates an exponential to the power of the 2 with the ratio
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
      double temp_time_pressed = time_pressed;
      double ratio = 0;
      ratio = temp_time_pressed / 1000;
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
}
