#include <Wire.h> //Needed for I2C to GPS

int hall_sensor = 3;
float t1 = 0;
float t2 = 0;
float t_tot = 0;
long rpm = 0;

void time1()
{
  t1 = millis();
}

#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS
SFE_UBLOX_GPS myGPS;

long lastTime = 0;

void setup()
{
  Serial.begin(9600);
  
  Wire.begin();

  if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  pinMode(hall_sensor,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hall_sensor), time1, FALLING);
}

void loop()
{
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); 
    
    long latitude = myGPS.getLatitude();
    long longitude = myGPS.getLongitude();
    long speed = myGPS.getGroundSpeed();

    t_tot = t1 - t2;
    t2 = t1;
    
    if (((1/t_tot)*1000*60) < 1000000)
    {
      rpm = ((1/t_tot)*1000*60);
    }
    
    Serial.print("Lat: ");
    Serial.println(latitude);
    Serial.print("Lng: ");
    Serial.println(longitude);
    Serial.print("Spd: ");
    Serial.println(speed/1000); 
    Serial.print("Rpm: ");
    Serial.println(rpm);

  }
}
