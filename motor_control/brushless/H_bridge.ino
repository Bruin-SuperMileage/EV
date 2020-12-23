#include "ramping.h"
#include "constants.h"

void changeState_1();
void changeState_2();
void changeState_3();
void (*stateChange[])() = {changeState_1, changeState_2, changeState_3};

MotorControl Motor;
Ramping* ramp;

void setup() {
  pinMode(Motor.throttlePin, INPUT);
  
  for(int i = 0; i < NUM_PINS; i++){
    pinMode(Motor.outLowPins[i], OUTPUT);
    pinMode(Motor.outHighPins[i], OUTPUT);
    pinMode(Motor.hallPins[i], INPUT);

    analogWrite(Motor.outHighPins[i], 0);
    digitalWrite(Motor.outLowPins[i], LOW);

    attachInterrupt(digitalPinToInterrupt(Motor.hallPins[i]), stateChange[i], CHANGE);
  }

  Motor.initSensors();
  
  if(rampingOption)
    ramp = new Linear;
  else
    ramp = new PD;
}

void loop() {
  int throttleRead = analogRead(Motor.throttlePin);

  // check analogWrite and digitalWrite for UCC277
  if(throttleRead <= NEUTRAL_THROTTLE){
    for(int i = 0; i < NUM_PINS; i++){
      analogWrite(Motor.outHighPins[i], 0);
      digitalWrite(Motor.outLowPins[i], HIGH);
    }
    return;
  }

  if(Motor.isMotorStopped())
    Motor.rotateMotor();
  
  spdToWrite = ramp->newSpd(throttleRead);
}

void changeState_1(){ changeState(Motor, 0);  }
void changeState_2(){ changeState(Motor, 1);  }
void changeState_3(){ changeState(Motor, 2);  }
