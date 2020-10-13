#ifndef VARIABLE_CONTROL
#define VARIABLE_CONTROL

#include "base_throttle.h"

const double minVoltage = 0.8;
const double maxVoltage = 4.2;

class VariableThrottle : public Throttle
{
public:
    VariableThrottle(const int &pin);
    void compute_motor_value();
};

#endif
