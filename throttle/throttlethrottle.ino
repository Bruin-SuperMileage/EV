/*
 * Code that converts a 0.8~4.2V output from throttle
 * to PWM signal that is sent to powertrain 
 * (Presumably their ESC or motor controller)
 * 
 * We are using the built-in Servo library because 
 * both a Servo and a brushless ESC uses the same
 * 50hz PWM signal. 
 * 
 * © 2020 SMV Electronics - BruinRacing
 */


#include <Servo.h>      // Servo library to generate PWM signal

#define throttleIn 5   // Placeholders
#define ESCOutput 3

const int minPulseWidth = 1000; // microseconds
const int maxPulseWidth = 2000;

Servo ESC;

void setup() {
  // Initialisation of ESC
  ESC.attach(ESCOutput, minPulseWidth, maxPulseWidth);
}

const double throttleMinVoltage = 0.8;
const double throttleMaxVoltage = 4.2;

int readThrottle() {
  /*
   * Reads the throttle input from analog signal,
   * Returns 0~1023
   */
  int throttleReading = analogRead(throttleIn);
  int throttleMin = throttleMinVoltage * 1023, throttleMax = throttleMaxVoltage * 1023;
  // Throttle cutoff threshold
  if (throttleReading < throttleMin) {
    return 0;
  } else if (throttleReading < throttleMax) {
    return map(throttleReading, throttleMin, throttleMax, 0, 1023);
  } else {
    return 1023;
  }
}

void writeToESC(int throttleRead) { 
  ESC.write(map(throttleRead, 0, 1023, 0, 180));
}

int lastMotorWrite = 0;

void throttleRamping(int throttleValue) {
  for (int i = lastMotorWrite; i <= throttleValue; i++) {
    writeToESC(i);
    // Serial.println(i);
    delay(map(i, 0, 1023, 30, 1));
  }
}