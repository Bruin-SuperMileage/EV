#include <Wire.h>
#include <SPI.h>

#include "accelerometer.h"
#include "altimeter.h"
#include "gps.h"
#include "gyroscope.h"

void setup() {
  accelerometer myAccelerometer = new accelerometer;
  altimeter myAltimeter = new altimeter;
  gps myGps = new gps;
  gyroscope myGyroscope = new gyroscope;
}

void loop() {
  
}
