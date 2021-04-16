#ifndef TWOWHEELSPEED_H
#define TWOWHEELSPEED_H

//Arbitrary values for now
#define KP 0.05
#define KD 0.05

void twoWheelSpeed(double wheelRatio, int throttleRead, int* leftPWM, int* rightPWM, byte currRightSpeed, byte currLeftSpeed, byte* prevError, bool leftFast, Ramp* ramp)
{
    byte currFastSpeed;
    byte currSlowSpeed;
    byte fastSpeedToWrite;
    int slowSpeedToWrite;
    byte error;
    
    if(leftFast)
    {
        currFastSpeed = currLeftSpeed;
        currSlowSpeed = currRightSpeed;
        
        fastSpeedToWrite = *leftPWM;
        slowSpeedToWrite = *rightPWM;
    }
    else
    {
        currFastSpeed = currRightSpeed;
        currSlowSpeed = currLeftSpeed;
        
        fastSpeedToWrite = *rightPWM;
        slowSpeedToWrite = *leftPWM;
    }
    
    //use ramping to get desired fast wheel speed
    fastSpeedToWrite = ramp->newSpd(throttleRead, millis());
    
    //calculate desired slow wheel speed based on ratio and fast wheel speed
    //use PD to adjust slow wheel speed
    error = currSlowSpeed - currFastSpeed * wheelRatio;
    slowSpeedToWrite += KP*error + KD*(error - *prevError);
    slowSpeedToWrite = max(0, min(slowSpeedToWrite, 255));
    
    *prevError = error;
    
    //update PWM values
    if(leftFast)
    {
        *leftPWM = fastSpeedToWrite;
        *rightPWM = slowSpeedToWrite;
    }
    else
    {
        *rightPWM = fastSpeedToWrite;
        *leftPWM = slowSpeedToWrite;
    }
}

#endif
