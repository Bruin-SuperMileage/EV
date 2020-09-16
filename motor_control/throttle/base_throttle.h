#ifndef BASE_THR_H
#define BASE_THR_H

//#include <Servo.h>
#define throttleIn 5   // Placeholders
#define ESCOutput 3
#define button 7

class Throttle
{
public:
    Throttle();

    void run();
    void setup();
    void loop();

    virtual void compute_motor_value() = 0; // this needs to be implemented differently for variable/button throttle
    void throttleRamping(int throttleValue);
    virtual int readThrottle();
    void writeToESC(int throttleRead); 
    void read_sensor_value();
    int get_raw_value() const; // should only be used to debug
    int get_motor_value() const;

private:
    int m_raw_value;
    int m_motor_value;
    int lastMotorWrite;
    const int minPulseWidth = 1000; // microseconds
    const int maxPulseWidth = 2000;
    const double throttleMinVoltage = 0.8;
    const double throttleMaxVoltage = 4.2;
};

#endif
