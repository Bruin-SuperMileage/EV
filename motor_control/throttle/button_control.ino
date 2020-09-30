#include "button_control.h"

ButtonThrottle::ButtonThrottle(const int &pin, int timeToFull): Throttle(pin){
    this->timeToFull = timeToFull;
    isPressed = false;
}

int ButtonThrottle::mappingFunction(int val, std::string mapType){
  if(mapType == "linear"){
    return std::min(val/timeToFull, 1) * 1023;
  }
  if(mapType == "exponential"){
  }
  if(mapType == "logarithmic"){
  }
}

/*
   * Reads the throttle input from analog signal,
   * Returns 0~1023
   */
int ButtonThrottle::compute_motor_value() {
    if(digitalRead(this->get_pin()) == HIGH){
      if(!isPressed){
        pressStart = millis();
      }
      int timePressed = millis() - pressStart;
      //using a linear mapping function(for now)
      return mappingFunction(timePressed, "linear");
    }
    else{
      isPressed = false;
      return 0;
    }
}