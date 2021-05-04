//NOTE: CODE TAKEN FROM: https://www.youtube.com/watch?v=u2uJMJWsfsg

#include "hall_effect_sensor.h"


HallEffectSensor::HallEffectSensor(const int &pin)
  : Sensor(&pin)
{
  attachInterrupt(digitalPinToInterrupt(2), Pulse_Event, RISING);  
  delay(1000);
}

void HallEffectSensor::read_sensor_value()
{
  LastTimeCycleMeasure = LastTimeWeMeasured;  
  CurrentMicros = micros();  

  if(CurrentMicros < LastTimeCycleMeasure)
  {
    LastTimeCycleMeasure = CurrentMicros;
  }

  // Calculate the frequency:
  FrequencyRaw = 10000000000 / PeriodAverage; 

  // Detect if pulses stopped or frequency is too low, so we can show 0 Frequency:
  if(PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra)
  {  
    FrequencyRaw = 0;  
    ZeroDebouncingExtra = 2000;  // Change the threshold a little so it doesn't bounce.
  }
  else
  {
    ZeroDebouncingExtra = 0;  // Reset the threshold to the normal value so it doesn't bounce.
  }

  FrequencyReal = FrequencyRaw / 10000;  

  RPM = FrequencyRaw / PulsesPerRevolution * 60; 
  RPM = RPM / 10000; 

  // Smoothing RPM:
  total = total - readings[readIndex];  
  readings[readIndex] = RPM;  
  total = total + readings[readIndex];  
  readIndex = readIndex + 1; 

  if (readIndex >= numReadings)  
  {
    readIndex = 0;  
  }
  
  average = total / numReadings;  // The average value it's the smoothed result.
}


double HallEffectSensor::get_sensor_value(){
  return RPM;
}

void Pulse_Event()  // The interrupt runs this to calculate the period between pulses:
{

  PeriodBetweenPulses = micros() - LastTimeWeMeasured; 

  LastTimeWeMeasured = micros();  

  if(PulseCounter >= AmountOfReadings)  
  {
    PeriodAverage = PeriodSum / AmountOfReadings; 
    PulseCounter = 1; 
    PeriodSum = PeriodBetweenPulses;  

    int RemapedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);  
    RemapedAmountOfReadings = constrain(RemapedAmountOfReadings, 1, 10); 
    AmountOfReadings = RemapedAmountOfReadings;  
  }
  else
  {
    PulseCounter++;  
    PeriodSum = PeriodSum + PeriodBetweenPulses; 
  }
} 
