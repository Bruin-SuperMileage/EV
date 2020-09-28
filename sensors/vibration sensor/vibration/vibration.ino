#include <Firmata.h>

int ledPin = 13;
int EP = 9;


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

  long measurement = TP_init();
  delay(50);
  Serial.print("measurement = ");
  Serial.println(measurement);

  if (measurement > 1000) {
    digitalWrite(ledPin, HIGH);
  }

  else {
    digitalWrite(ledPin, LOW);
  }
}
