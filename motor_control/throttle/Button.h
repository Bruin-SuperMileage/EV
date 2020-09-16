#ifndef BUTTON_THROTTLE
#define BUTTON_THROTTLE

#include "base_throttle.h"

class Button: public Throttle{
    public:
    Button(int ft);
    virtual int readThrottle();
    int mappingFunction(int f, int s);
    private:
    int fullThrottle;//the amount of time the button must be pressed to bring the motor to full capacity
    bool isPressed;
    int pressStart;
};






#endif