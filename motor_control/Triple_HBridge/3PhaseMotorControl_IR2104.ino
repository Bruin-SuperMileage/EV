#include <ramping.h>

int outHighPins[3] = { 10, 6, 4};
int shutPins[3] = {9, 5, 3};
int inPins[3] = {0,1,2};
int throttlePin = A0;
bool pin1_state = 0;
bool pin2_state = 0;
bool pin3_state = 0;
int motor_speed = 0;
int speed_max = 0;

#define RAMP_SPEED 2;

void setup() {
 //For throttle controls
// Serial.begin(9600);
//  pinMode(A0, INPUT);
 
  for(int j = 0; j < 3; j++) {
    pinMode(shutPins[j], OUTPUT);
    pinMode(outHighPins[j], OUTPUT);
//    pinMode(outLowPins[j], OUTPUT);
    pinMode(inPins[j], INPUT);
    analogWrite(shutPins[j], 0);
  }
      bool pin1_state = digitalRead(inPins[0]);
      bool pin2_state = digitalRead(inPins[1]);
      bool pin3_state = digitalRead(inPins[2]);

      attachInterrupt(digitalPinToInterrupt(inPins[0]), State_Change_1, CHANGE); // initializes interrupt pin for every input
      attachInterrupt(digitalPinToInterrupt(inPins[1]), State_Change_2, CHANGE); // initializes interrupt pin for every input
      attachInterrupt(digitalPinToInterrupt(inPins[2]), State_Change_3, CHANGE); // initializes interrupt pin for every input
     
     
    pinMode(throttlePin, INPUT);
}


void loop() {

  if(analogRead(throttlePin) < 512){
    for(int i = 0; i < 3; i++){
      analogWrite(outHighPins[i], 0);
      digitalWrite(shutPins[i], HIGH);
    }
  }

  else{
     desired_speed = map(analogRead(throttlePin), 512, 1023, 0, 255); // Reads in speed from throttle
  
     if (motor_speed != speed_max){ // Only changes speed if we aren't already at desired speed
        if(motor_speed < speed_max){
          motor_speed += RAMP_SPEED; // If desired speed is above current speed then ramp up speed
        }  
        
        else{
        motor_speed -= RAMP_SPEED; // If desired speed is below current speed then ramp down
        }
        
     }
   }
    return;
}
  
//  for testing throttle. Didn't go too well but the code is still there
//  byte pwr = map(analogRead(A0), 1, 1023, 0, 255);
//  if(pwr < 128)
//    pwr = 0;
//  else
//    pwr = 255;

// Could get rid of the read statements by writing three different codes that changes the value of "hall" based on which pin is the interrupt but not sure how much efficiency we'd really get out of that
void State_Change_1(){

      if (pin1_state == 0){
        analogWrite(outHighPins[1], 0);
        digitalWrite(shutPins[1], HIGH);

        analogWrite(outHighPins[0], motor_speed);
        digitalWrite(shutPins[0], HIGH);

        digitalWrite(shutPins[2], LOW);
      }

      else{

        analogWrite(outHighPins[0], 0);
        digitalWrite(shutPins[0], HIGH);

        analogWrite(outHighPins[1], motor_speed);
        digitalWrite(shutPins[1], HIGH);

        digitalWrite(shutPins[2], LOW);
      }

       pin1_state != pin1_state;
      
}


void State_Change_2(){

      if (pin2_state == 0){
        analogWrite(outHighPins[2], 0);
        digitalWrite(shutPins[2], HIGH);

        analogWrite(outHighPins[1], motor_speed);
        digitalWrite(shutPins[1], HIGH);

        digitalWrite(shutPins[0], LOW);
      }

      else{

        analogWrite(outHighPins[1], 0);
        digitalWrite(shutPins[1], HIGH);

        analogWrite(outHighPins[2], motor_speed);
        digitalWrite(shutPins[2], HIGH);

        digitalWrite(shutPins[0], LOW);
      }

       pin2_state != pin2_state;
      
}

void State_Change_3(){

      if (pin2_state == 0){
        analogWrite(outHighPins[0], 0);
        digitalWrite(shutPins[0], HIGH);

        analogWrite(outHighPins[2], motor_speed);
        digitalWrite(shutPins[2], HIGH);

        digitalWrite(shutPins[1], LOW);
      }

      else{

        analogWrite(outHighPins[2], 0);
        digitalWrite(shutPins[2], HIGH);

        analogWrite(outHighPins[0], motor_speed);
        digitalWrite(shutPins[0], HIGH);

        digitalWrite(shutPins[1], LOW);
      }

       pin3_state != pin3_state;
      
}


  
   
