#include <ramping.h>

int outHighPins[3] = { 10, 6, 4};
int outLowPins[3] = {9, 5, 3};
int inPins[3] = {0,1,2};
int throttlePin = A0;
bool pin1_state = 0;
bool pin2_state = 0;
bool pin3_state = 0;
int motor_speed = 0;
int speed_max = 0;
int interrupt_time = 0;

bool changing_state = false;
bool interrupting = false;

#define RAMP_SPEED 2;

void setup() {
 //For throttle controls
// Serial.begin(9600);
//  pinMode(A0, INPUT);
 
  for(int j = 0; j < 3; j++) {
    pinMode(outLowPins[j], OUTPUT);
    pinMode(outHighPins[j], OUTPUT);
//    pinMode(outLowPins[j], OUTPUT);
    pinMode(inPins[j], INPUT);
    analogWrite(outLowPins[j], 0);
  }
      bool pin1_state = digitalRead(inPins[0]);
      bool pin2_state = digitalRead(inPins[1]);
      bool pin3_state = digitalRead(inPins[2]);

      attachInterrupt(digitalPinToInterrupt(inPins[0]), State_Change_1, CHANGE); // initializes interrupt pin for every input
      attachInterrupt(digitalPinToInterrupt(inPins[1]), State_Change_2, CHANGE); // initializes interrupt pin for every input
      attachInterrupt(digitalPinToInterrupt(inPins[2]), State_Change_3, CHANGE); // initializes interrupt pin for every input
     
     
    pinMode(throttlePin, INPUT);

    initMotor();
      
    if(rampingOption)
      ramp = new Linear(RAMP_SPD);
    else
      ramp = new PD(Kp, Kd);
  
}


void loop() {

  int throttleRead = analogRead(throttlePin);
  
  if(analogRead(throttlePin) < 512){
    for(int i = 0; i < 3; i++){
      analogWrite(outHighPins[i], 0);
      digitalWrite(outLowPins[i], LOW);
    }
    return;
  }

   motor_speed = ramp->newSpd(throttleRead)

  

   if(millis() - interrupt_time > 1000){ // Only triggers if no interrupts have been triggered for 1000ms (Tire not rotating)
     changing_state = true; // shows that our initmotor function is in the middle of being called
     initMotor(); // Makes the motor move forward one rotation if car is at rest
     changing_state = false;

     if(interrupting){ // if the interrupt is called within the initMotor function then call the function again 
        initMotor();
        interrupting = false; 
     }
   }
   

   

}




// Could get rid of the read statements by writing three different codes that changes the value of "hall" based on which pin is the interrupt but not sure how much efficiency we'd really get out of that
void State_Change_1(){

      if(changing_state) // triggered if interrupt function is called during other function
         interrupting = true;

         
      if (pin1_state == 0){

        
        analogWrite(outHighPins[0], motor_speed);
        digitalWrite(outLowPins[0], LOW); 
        
        analogWrite(outHighPins[1], 0);
        digitalWrite(outLowPins[1], HIGH);
   
      }

      else{

        analogWrite(outHighPins[0], 0);
        digitalWrite(outLowPins[0], HIGH);

        analogWrite(outHighPins[1], motor_speed);
        digitalWrite(outLowPins[1], LOW);

      }
      
       analogWrite(outHighPins[2], 0);
       digitalWrite(outLowPins[2], LOW);

       pin1_state != pin1_state;
       interrupt_time = 0;
      
}



void State_Change_2(){
  
      if(changing_state) // triggered if interrupt function is called during other function
         interrupting = true;
         
      if (pin2_state == 0){

        analogWrite(outHighPins[1], motor_speed);
        digitalWrite(outLowPins[1], LOW);
        
        analogWrite(outHighPins[2], 0);
        digitalWrite(outLowPins[2], HIGH);
      }

      else{

        analogWrite(outHighPins[1], 0);
        digitalWrite(outLowPins[1], HIGH);

        analogWrite(outHighPins[2], motor_speed);
        digitalWrite(outLowPins[2], HIGH);
      }



      
       analogWrite(outHighPins[0], 0);
       digitalWrite(outLowPins[0], LOW);

       pin2_state != pin2_state;
       interrupt_time = 0;
      
}

void State_Change_3(){
  
       if(changing_state) // triggered if interrupt function is called during other function
         interrupting = true;
         
      if (pin3_state == 0){
        analogWrite(outHighPins[0], 0);
        digitalWrite(outLowPins[0], HIGH);

        analogWrite(outHighPins[2], motor_speed);
        digitalWrite(outLowPins[2], LOW);


      }

      else{
        analogWrite(outHighPins[0], motor_speed);
        digitalWrite(outLowPins[0], LOW);

        analogWrite(outHighPins[2], 0);
        digitalWrite(outLowPins[2], HIGH);

      }


        analogWrite(outHighPins[1], 0);
        digitalWrite(outLowPins[1], LOW);

       pin3_state != pin3_state;
       interrupt_time = 0;
      
}

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
  
   
