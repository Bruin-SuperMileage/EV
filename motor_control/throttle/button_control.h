#ifndef BUTTON_CONTROL
#define BUTTON_CONTROL

#include "base_throttle.h"
#include <string>
//#include <math.h>

class ButtonThrottle: public Throttle{
    public:
    ButtonThrottle(const int &pin, int timeToFull = 5);
    virtual int compute_motor_value() override;
    int mappingFunction(int val, std::string mapType);//mapType is either "linear", "logarithmic", or "exponential"

    private:
    int timeToFull;//the amount of time the button must be pressed for throttle to run at full power
    bool isPressed;
    int pressStart;
};

#endif