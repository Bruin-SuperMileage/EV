//NOTE: CODE TAKEN FROM: https://www.youtube.com/watch?v=u2uJMJWsfsg

#ifndef HALL_EFFECT_SENSOR_H
#define HALL_EFFECT_SENSOR_H

class HallEffectSensor : public Sensor
{
public:
    HallEffectSensor(const int &pin);
    void read_sensor_value();
    double get_sensor_value();
private:
    void Pulse_Event();
    const byte PulsesPerRevolution = 2;  

    const unsigned long ZeroTimeout = 100000;  // For high response time, a good value would be 100000.
                                           // For reading very low RPM, a good value would be 300000.

    const byte numReadings = 2;  // Number of samples for smoothing. The higher, the more smoothing, but it's going to
                             // react slower to changes. 1 = no smoothing                      
    // Variables:
    volatile unsigned long LastTimeWeMeasured; 
    volatile unsigned long PeriodBetweenPulses = ZeroTimeout+1000;  
    volatile unsigned long PeriodAverage = ZeroTimeout+1000; 
    unsigned long FrequencyRaw;  
    unsigned long FrequencyReal;  // Frequency without decimals.
    unsigned long RPM;  
    unsigned int PulseCounter = 1;  

    unsigned long PeriodSum; 

    unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;  
    unsigned long CurrentMicros = micros(); 

    unsigned int AmountOfReadings = 1;

    unsigned int ZeroDebouncingExtra;  

    // Variables for smoothing tachometer:
    unsigned long readings[numReadings];  
    unsigned long readIndex;  
    unsigned long total;
    unsigned long average; 
};

#endif //HALL_EFFECT_SENSOR
