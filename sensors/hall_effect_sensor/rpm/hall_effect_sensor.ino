#include "hall_effect_sensor.h"


HallEffectSensor::HallEffectSensor(int pin = 2) : Sensor(pin)
{
    init_sensor(pin);
}

void Sensor::init_sensor(const int pin)
{
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(pin), interruptFunc, RISING);
    delay(1000); // Gather data to average.
}

void HallEffectSensor::interruptFunc()
{
    PeriodBetweenPulses = micros() - LastTimeWeMeasured;
    LastTimeWeMeasured = micros();

    if (PulseCounter >= AmountOfReadings) // If counter for amount of readings reach the set limit:
    {
        PeriodAverage = PeriodSum / AmountOfReadings;
        // Reset pulse counter and sum
        PulseCounter = 1;
        PeriodSum = PeriodBetweenPulses;

        // Change the amount of readings we use depending on the period
        // (High RPM -> More readings to average, Low RPM -> Less readings to be responsive)
        int RemapedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);
        RemapedAmountOfReadings = constrain(RemapedAmountOfReadings, 1, 10);
        AmountOfReadings = RemapedAmountOfReadings; // Updates amount
    }
    else
    {
        PulseCounter++;
        PeriodSum = PeriodSum + PeriodBetweenPulses; // Add the periods so later we can average.
    }
}

void HallEffectSensor::loop()
{
    LastTimeCycleMeasure = LastTimeWeMeasured;
    CurrentMicros = micros();

    // CurrentMicros should always be higher than LastTimeWeMeasured, but in rare occasions that's not true, reset LastTimeWeMeasured.
    if (CurrentMicros < LastTimeCycleMeasure)
    {
        LastTimeCycleMeasure = CurrentMicros;
    }

    // Calculate the frequency:
    FrequencyRaw = 10000000000 / PeriodAverage; // Frequency * 10^4 (preserve 4 decimals)

    // Detect if pulses stopped or frequency is too low, so we can show 0 Frequency:
    if (PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra)
    {                               // If the pulses are too far apart that we reached the timeout for zero:
        FrequencyRaw = 0;           // Set frequency as 0.
        ZeroDebouncingExtra = 2000; // Change the threshold a little so it doesn't bounce.
    }
    else
    {
        ZeroDebouncingExtra = 0; // Reset the threshold to the normal value so it doesn't bounce.
    }

    FrequencyReal = FrequencyRaw / 10000; 

    // Calculate the RPM:
    RPM = FrequencyRaw / PulsesPerRevolution * 60; // Frequency divided by amount of pulses per revolution multiply by
                                                   // 60 seconds to get minutes.
    RPM = RPM / 10000;                             // Remove the decimals.

    // Smoothing RPM:
    total = total - readings[readIndex]; // Advance to the next position in the array.
    readings[readIndex] = RPM;           // Takes the value that we are going to smooth.
    total = total + readings[readIndex]; // Add the reading to the total.
    readIndex = readIndex + 1;           // Advance to the next position in the array.

    if (readIndex >= SMOOTHING_NUM) // If we're at the end of the array:
    {
        readIndex = 0; // Reset array index.
    }

    // Calculate the average:
    average = total / SMOOTHING_NUM; // The average value it's the smoothed result.

    Serial.print("Period: ");
    Serial.print(PeriodBetweenPulses);
    Serial.print("\tReadings: ");
    Serial.print(AmountOfReadings);
    Serial.print("\tFrequency: ");
    Serial.print(FrequencyReal);
    Serial.print("\tRPM: ");
    Serial.print(RPM);
    Serial.print("\tTachometer: ");
    Serial.println(average);
}