#ifndef GLOBAL_H
#define GLOBAL_H
const int NUM_PINS = 3;
const int NEUTRAL_THROTTLE = 100;
const int MAX_THROTTLE = 1023;
const byte MAX_SPD = 255;
const byte MIN_SPD = 0;

const bool rampingOption = true; // true for Linear, false for PD
const byte Kp = -1, Kd = -1; 
const byte RAMP_SPD = 1;

byte spdToWrite;

const int powerToWrite[6][3] = {
  {2,0,1}, // hallReadings 001
  {0,1,2}, // hallReadings 010
  {0,2,1}, // hallReadings 011
  {1,2,0}, // hallReadings 100
  {1,0,2}, // hallReadings 101
  {2,1,0}  // hallReadings 110
};

struct MotorControl{
  MotorControl(){ timeMark = millis();  }

  bool hallSensor[3];

  const int outHighPins[3] = {10, 6, 4};
  const int outLowPins[3]  = {9, 5, 3};
  const int hallPins[3]    = {0,1,2};
  const int throttlePin    = A0;
  
  bool changing_state = false;
  bool interrupting = false;

  long timeMark = millis();
  const long maxWaitTime = 1500;

  void initSensors(){
    for(int i = 0; i < NUM_PINS; i++)
      hallSensor[i] = digitalRead(hallPins[i]);
  }

  bool isMotorStopped(){  return millis() - timeMark >= maxWaitTime;  }

  void rotateMotor(){
    byte index = 4 * (byte)hallSensor[0] + 2 * (byte)hallSensor[1] + (byte)hallSensor[2] - 1;

    for(int i = 0; i < NUM_PINS; i++){
      if(powerToWrite[index][i] == 0){
        analogWrite(outHighPins[i], 0);
        digitalWrite(outLowPins[i], HIGH);
      }
      else if(powerToWrite[index][i] == 1){
        analogWrite(outHighPins[i], spdToWrite);
        digitalWrite(outLowPins[i], LOW);
      }
      else{
        digitalWrite(outHighPins[i], LOW);
        digitalWrite(outLowPins[i], LOW);
      }
    }
  }
};

void changeState(MotorControl* s, int index){
  if (s->changing_state) // triggered if interrupt function is called during other function
    s->interrupting = true;
    
  if(s->hallSensor[index]){
    analogWrite(s->outHighPins[index], 0);
    digitalWrite(s->outLowPins[index], HIGH);
  }
  else{
    analogWrite(s->outHighPins[index], spdToWrite);
    digitalWrite(s->outLowPins[index], LOW);
  }

  if(index == 0)
    digitalWrite(s->outLowPins[2], LOW);
  else
    digitalWrite(s->outLowPins[index - 1], LOW);

  s->hallSensor[index] = !s->hallSensor[index];

  s->timeMark = millis();
}
#endif 
