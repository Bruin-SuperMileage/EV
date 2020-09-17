#include <Firmata.h>

int ledPin = 13;
int EP = 9;

int sum = 0;
int clock = 0;
int avg = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(EP, INPUT);
  Serial.begin(9600);
  Serial.println("Vibration Data");
}

long TP_init() {
  delay(10);
  long measurement = pulseIn(EP, HIGH);
  return measurement;
}


void loop() {
  // put your main code here, to run repeatedly:
    while (clock < 1000)
    {
        long measurement = TP_init();
        delay(40);


        digitalWrite(ledPin, HIGH);
    
        sum += measurement;
        clock += 50;
    }

    avg = sum / 20;
    Serial.println("Average after 1 sec: " + avg);

    sum = 0;
    clock = 0;
}
