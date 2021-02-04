#include "ramping.h"
#include "GLOBAL.h"

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

  if(throttleRead <= NEUTRAL_THROTTLE){
    for(int i = 0; i < NUM_PINS; i++){
      analogWrite(Motor.outHighPins[i], 0);
      digitalWrite(Motor.outLowPins[i], HIGH);
    }
    return;
  }

  if(Motor.isMotorStopped()){
    Motor.changing_state = true; // shows that our initmotor function is in the middle of being called
    Motor.rotateMotor();
    Motor.changing_state = false;

    if (Motor.interrupting) { // if the interrupt is called within the initMotor function then call the function again
      Motor.rotateMotor();
      Motor.interrupting = false;
    }
  }
    
  spdToWrite = ramp->newSpd(throttleRead, millis());
}

void changeState_1(){ changeState(&Motor, 0);  }
void changeState_2(){ changeState(&Motor, 1);  }
void changeState_3(){ changeState(&Motor, 2);  }
