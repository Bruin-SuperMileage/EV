#include "Button.h"

Button::Button(int ft = 5):Throttle(){
    isPressed = false;
    fullThrottle = ft;
}

int Button::mappingFunction(int f, int s){
  //linear
  if(0){
    return min(s/fullThrottle, 1) * 1023;
  }
  //exponential
  if(1){
  }
  //logarithmic
  if(2){
  }
}

int Button::readThrottle() {
  /*
   * Reads the throttle input from analog signal,
   * Returns 0~1023
   */
    if(throttleIn == HIGH){
      if(!isPressed){
        pressStart = millis();
      }
      int timePressed = millis() - pressStart;
      //using a linear mapping function(for now)
      return mappingFunction(0, timePressed);
    }
    else{
      isPressed = false;
      return 0;
    }
}

