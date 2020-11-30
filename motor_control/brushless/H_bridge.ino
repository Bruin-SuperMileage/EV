// think when the motor is at stop position because our implementations won't work when it is at stop position
// maybe a good idea to use initMotor

#include "ramping.h"
// ===================================================
// FUNCTION DECLARATIONS =============================
// ===================================================
void changeState_1();
void changeState_2();
void changeState_3();

// ===================================================
// VARIABLE DECLARATIONS =============================
// ===================================================
int outHighPins[3] = {10, 6, 4};
int shutPins[3]    = {9, 5, 3};
int hallPins[3]    = {0,1,2};
int throttlePin    = A0;

bool hallStates[3];
void (*stateChange[])() = {changeState_1, changeState_2, changeState_3};
byte spdToWrite;

Ramping* ramp;
bool rampingOption = true; // true for Linear, false for PD

// these need to be changed to appropriate values
byte Kp = -1, Kd = -1; // determine the values and signs by thorough calculations or testings
byte RAMP_SPD = 1; // can be changed but I think it can be 1 as the loop iterates really fast
// RAMP_SPD can also be decimal values and change type to short(?) and types of member variables in class definitions

// ===================================================
// SETUP FUNCTION ====================================
// ===================================================
void setup() {
  for(int j = 0; j < 3; j++){
    pinMode(shutPins[j], OUTPUT);
    pinMode(outHighPins[j], OUTPUT);
    pinMode(hallPins[j], INPUT);
    analogWrite(shutPins[j], 0);

    hallStates[j] = digitalRead(hallPins[j]);
    attachInterrupt(digitalPinToInterrupt(hallPins[j]), stateChange[j], CHANGE);
  }  
  pinMode(throttlePin, INPUT);
  
  initMotor();
//  Serial.begin(9600);
  if(rampingOption){
    ramp = new Linear(RAMP_SPD);
//    Serial.print("Linear Ramping Testing with RAMP_SPD: ");
//    Serial.println(RAMP_SPD);
  } 
  else{
    ramp = PD(Kp, Kd);
//    Serial.print("PD Ramping Testing with Kp: ");
//    Serial.print(Kp);
//    Serial.print(", Kd: ");
//    Serial.println(Kd);
  }
}
// ===================================================
// LOOP FUNCTION =====================================
// ===================================================
void loop() {  
  int throttleRead = analogRead(throttlePin);

  // shut down motor if throttle is low
  if(throttleRead < 100){ // this number is at which the motor doesn't operate because of the vehicle's weight
    for(int i = 0; i < 3; i++){
      analogWrite(outHighPins[i], 0);
      digitalWrite(shutPins[i], HIGH);
    }
//    Serial.println("Motor Shut Down");
    return;
  }

  spdToWrite = ramp->newSpd(throttleRead); // set new speed to write to motor
}
// ===================================================
// FUNCTION DEFINITIONS ==============================
// ===================================================
// DESC: this initializes outHighPins and shutPins 
//       as changeState functions don't write all pins (not necessary) in each function call
void initMotor(){
  byte hallIndex = 4 * (byte)hallStates[0] + 2 * (byte)hallStates[1] + (byte)hallStates[2] - 1;

  int powerToWrite[6][3] = {
  {2,0,1}, // hallReadings 001
  {0,1,2}, // hallReadings 010
  {0,2,1}, // hallReadings 011
  {1,2,0}, // hallReadings 100
  {1,0,2}, // hallReadings 101
  {2,1,0}  // hallReadings 110
  };

  for(int i = 0; i < 3; i++){
   if(powerToWrite[hallIndex][i] == 0){
     analogWrite(outHighPins[i], 0);
     digitalWrite(shutPins[i], HIGH);
   }
   else if(powerToWrite[hallIndex][i] == 1){
     analogWrite(outHighPins[i], 0);
     digitalWrite(shutPins[i], HIGH);
   }
   else if(powerToWrite[hallIndex][i] == 2){
    digitalWrite(shutPins[i], LOW);
   }
  }
}

// DESC: this function is called when hallState[0] changes
//       this function writes corresponding outHighPins and shutPins that are required to change
void changeState_1(){
  if(hallStates[0])
    analogWrite(outHighPins[0], 0);
  else
    analogWrite(outHighPins[0], spdToWrite);
  digitalWrite(shutPins[0], HIGH);
  digitalWrite(shutPins[2], LOW);
  hallStates[0] != hallStates[0];
}

// DESC: this function is called when hallState[1] changes
//       this function writes corresponding outHighPins and shutPins that are required to change
void changeState_2(){
  if(hallStates[1])
    analogWrite(outHighPins[1], 0);
  else
    analogWrite(outHighPins[1], spdToWrite);
  digitalWrite(shutPins[0], LOW);
  digitalWrite(shutPins[1], HIGH);
  hallStates[1] != hallStates[1];
}

// DESC: this function is called when hallState[2] changes
//       this function writes corresponding outHighPins and shutPins that are required to change
void changeState_3(){
  if(hallStates[2])
    analogWrite(outHighPins[2], 0);
  else
    analogWrite(outHighPins[2], spdToWrite);
  digitalWrite(shutPins[1], LOW);
  digitalWrite(shutPins[2], HIGH);
  hallStates[2] != hallStates[2];
}
