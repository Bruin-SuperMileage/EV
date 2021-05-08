#include <math.h>

void setup() {
  // put your setup code here, to run once;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly;
  Serial.print("Lat;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Lng;");
  Serial.print(rand() % 90 + 10);

  Serial.print(";Cur;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Pwr;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Vlt;");
  Serial.print(rand() % 90 + 10);
 
  Serial.print(";GyX;");
  Serial.print(rand() % 90 + 10);;
  Serial.print(";GyY;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";GyZ;");
  Serial.print(rand() % 90 + 10);

  Serial.print(";Hea;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Pit;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Rol;");
  Serial.print(rand() % 90 + 10);

  Serial.print(";Alt;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Tem;");
  Serial.print(rand() % 90 + 10); 

  Serial.print(";Rpm;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Thr;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";Spd;");
  Serial.print(rand() % 90 + 10);

  Serial.print(";AcX;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";AcY;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";AcZ;");
  Serial.print(rand() % 90 + 10);

  Serial.print(";MaX;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";MaY;");
  Serial.print(rand() % 90 + 10);
  Serial.print(";MaZ;");
  Serial.println(rand() % 90 + 10);
  
}
