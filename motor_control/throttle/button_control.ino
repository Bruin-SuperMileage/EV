#include "button_control.h"

ButtonThrottle::ButtonThrottle(const int &pin, int timeToFull): Throttle(pin, true){
    this->m_timeToFull = timeToFull;
    m_isPressed = false;
}

int ButtonThrottle::mappingFunction(int val, m_map_type mapType){
  if(mapType = linear){
    return std::min(val/m_timeToFull, 1) * 1023;
  }
  if(mapType = exponential){
  }
  if(mapType = logarithmic){
  }
}

/*
   * Reads the throttle input from analog signal,
   * Returns 0~1023
   */
void ButtonThrottle::compute_motor_value() {
    read_sensor_value();
    if(get_raw_value() == 1){
      if(!m_isPressed){
        m_pressStart = millis();
      }
      int timePressed = millis() - m_pressStart;
      //using a linear mapping function(for now)
      m_motor_value =  mappingFunction(timePressed, linear);
    }
    else{
      m_isPressed = false;
      m_motor_value = 0;
    }
}