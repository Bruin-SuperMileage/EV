#include "base_throttle.h"

Throttle::Throttle()
{
    lastMotorWrite = 0;
}


void Throttle::run(){
    setup();
    loop();
}

void Throttle::setup() {
  // Initialisation of ESC
  ESC.attach(ESCOutput, minPulseWidth, maxPulseWidth);
}

void Throttle::writeToESC(int input_pin) { 
  ESC.write(map(input_pin, 0, 1023, 0, 180));
}

int Throttle::readThrottle() {
  /*
   * Reads the throttle input from analog signal,
   * Returns 0~1023
   */
  int throttleReading = analogRead(throttleIn);
  int throttleMin = throttleMinVoltage * 1023; 
  int throttleMax = throttleMaxVoltage * 1023;
  // Throttle cutoff threshold
  if (throttleReading < throttleMin) {
    return 0;
  } else if (throttleReading < throttleMax) {
    return map(throttleReading, throttleMin, throttleMax, 0, 1023);
  } else {
    return 1023;
  }
}

void Throttle::throttleRamping(int throttleValue) {
  for (int i = lastMotorWrite; i <= throttleValue; i++) {
    writeToESC(i);
    // Serial.println(i);
    delay(map(i, 0, 1023, 30, 1));
  }
}

void Throttle::read_sensor_value()
{
    m_raw_value = analogRead(throttleIn);
}

int Throttle::get_raw_value() const
{
    return m_raw_value;
}

int Throttle::get_motor_value() const
{
    return m_motor_value;
}

void Throttle::loop() {
  // Standard Arduino has 10-bit output
  int throttleRead = readThrottle();

  if (throttleRead > lastMotorWrite) {
    throttleRamping(throttleRead);
  } else {
    writeToESC(throttleRead);
  }
  lastMotorWrite = throttleRead;
}
