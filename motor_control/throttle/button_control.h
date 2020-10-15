#ifndef BUTTON_CONTROL
#define BUTTON_CONTROL

#include "base_throttle.h"
#include <string>

class ButtonThrottle : public Throttle
{
private:
    int m_timeToFull;
    bool m_isPressed;
    int m_pressStart;
    enum m_map_type
    {
        LINEAR,
        LOGARITHMIC,
        EXPONENTIAL
    };

public:
    ButtonThrottle(const int &pin, int timeToFull = 5);
    void compute_motor_value();
    int mappingFunction(int val, m_map_type mapType);
};

#endif
