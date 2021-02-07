
#ifndef HALLEFFECTSENSOR_H
#define HALLEFFECTSENSOR_H

#include "../base_sensor/base_sensor.h"

#define SMOOTHING_NUM 2

class HallEffectSensor : public Sensor
{
public:
    HallEffectSensor(int pin);
    virtual void init_sensor(const int pin);
    virtual double readSensorValue();
    void loop();

    double get_raw_value() const; // should only be used to debug
    double get_sensor_value() const;

protected:
    virtual void interruptFunc();

private:
    const byte PulsesPerRevolution = 2;

    // Max time interval between pulses before showing 0 (microseconds)
    // High response time: 100000, For reading low RPM : 300000
    const unsigned long ZeroTimeout = 200000;

    // Calibration for smoothing RPM. Higher means more smoothing. 1 = no smoothing.

    volatile unsigned long LastTimeWeMeasured;
    volatile unsigned long PeriodBetweenPulses = ZeroTimeout + 1000; // Stores the period between pulses in microseconds. Stores a large number to show 0 initially.
    volatile unsigned long PeriodAverage = ZeroTimeout + 1000;
    unsigned long FrequencyRaw;    // Calculated frequency, based on the period. This has a lot of extra decimals without the decimal point.
    unsigned long FrequencyReal;   // Frequency without decimals.
    unsigned long RPM;             // Raw RPM without any processing.
    unsigned int PulseCounter = 1; // Counts the amount of pulse readings we took so we can average multiple pulses before calculating the period.

    unsigned long PeriodSum; // Stores the summation of all the periods to do the average.

    // Stores the last time we measure a pulse in that cycle. (Not changed by interrupt function)
    unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;
    unsigned long CurrentMicros = micros();

    // Amount of readings to gather before update.
    unsigned int AmountOfReadings = 1;

    unsigned int ZeroDebouncingExtra; // Debouncing reduces the "bouncing" around the threshold and 0.

    // Variables for smoothing tachometer:
    unsigned long readings[SMOOTHING_NUM]; // The input.
    unsigned long readIndex;               // The index of the current reading.
    unsigned long total;                   // The running total.
    unsigned long average;                 // The RPM value after applying the smoothing.

}

#endif
