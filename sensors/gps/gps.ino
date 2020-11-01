#include "gps.h"
#include <SPI.h>
#include <SparkFun_Ublox_Arduino_Library.h>

SFE_UBLOX_GPS gps;

GPS::GPS(const int &pin): Sensor(pin) {
  m_latitude = 0;
  m_longitude = 0;
  m_speed = 0;
}

void GPS::read_sensor_value() {
  if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    return;
  }

  m_latitude = gps.getLatitude();
  m_longitude = gps.getLongitude();
  m_speed = gps.getGroundSpeed();
}

long GPS::get_latitude() {
  return m_latitude;
}

long GPS::get_longitude() {
  return m_longitude;
}

long GPS::get_speed() {
  return m_speed;
}
