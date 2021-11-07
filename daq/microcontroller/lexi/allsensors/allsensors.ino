#include <Wire.h>
#include <SPI.h>
#include "libraries/SparkFunMPL3115A2.h"
#include "libraries/SparkFunLSM9DS1.h"
#include "libraries/SparkFun_Ublox_Arduino_Library.h"

/*
#include <SparkFunMPL3115A2.h>
#include <SparkFunLSM9DS1.h>
#include <SparkFun_Ublox_Arduino_Library.h>
*/

MPL3115A2 myPressure;
LSM9DS1 imu;
SFE_UBLOX_GPS myGPS;

///////////////////////
// Example I2C Setup //
///////////////////////
// SDO_XM and SDO_G are both pulled high, so our addresses are:
// #define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW
// #define LSM9DS1_AG 0x6B // Would be 0x6A if SDO_AG is LOW

////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 10 // 10 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. Calculate
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

//Function definitions
void printGyro();
void printAccel();
void printMag();
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);

int hall_sensor = 3;
float t1 = 0;
float t2 = 0;
float t_tot = 0;
long rpm = 0;

void time1()
{
  t1 = millis();
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x60);        // Join i2c bus
  Wire.begin(0x6A);        // Join i2c bus
  Wire.begin(0x6B);        // Join i2c bus
  Wire.begin(0x42);        // Join i2c bus
  Serial.begin(9600);  // Start serial for output

  if (imu.begin() == false) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are.");
    while (1);
  }
    if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  pinMode(hall_sensor,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hall_sensor), time1, FALLING);

  myPressure.begin(); // Get sensor online

  //Configure the sensor
  myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
  //myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa

  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
}

void loop() {
  // put your main code here, to run repeatedly:

  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
  {
    // To read from the gyroscope,  first call the
    // readGyro() function. When it exits, it'll update the
    // gx, gy, and gz variables with the most current data.
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    // To read from the accelerometer, first call the
    // readAccel() function. When it exits, it'll update the
    // ax, ay, and az variables with the most current data.
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    // To read from the magnetometer, first call the
    // readMag() function. When it exits, it'll update the
    // mx, my, and mz variables with the most current data.
    imu.readMag();
  }

   long latitude = myGPS.getLatitude();
   long longitude = myGPS.getLongitude();
   long speed = myGPS.getGroundSpeed();


    t_tot = t1 - t2;
    t2 = t1;
    
    if (((1/t_tot)*1000*60) < 1000000)
    {
      rpm = ((1/t_tot)*1000*60);
    }
    
  if ((lastPrint + PRINT_SPEED) < millis())
  {
    //float altitude = myPressure.readAltitude();
    //Serial.print("Altitude(m):");
    //Serial.print(altitude, 2);
  
    float altitude = myPressure.readAltitudeFt();
    Serial.print("Alt: "); //Altitude(ft)
    Serial.println(altitude, 2);
  
    //float pressure = myPressure.readPressure();
    //Serial.print("Pressure(Pa):");
    //Serial.print(pressure, 2);
  
    //float temperature = myPressure.readTemp();
    //Serial.print(" Temp(c):");
    //Serial.print(temperature, 2);
  
    float temperature = myPressure.readTempF();
    Serial.print("Tem: "); //Temp(f)
    Serial.println(temperature, 2);
    
    printGyro();  // Print "G: gx, gy, gz"
    printAccel(); // Print "A: ax, ay, az"
    printMag();   // Print "M: mx, my, mz"
    // Print the heading and orientation for fun!
    // Call print attitude. The LSM9DS1's mag x and y
    // axes are opposite to the accelerometer, so my, mx are
    // substituted for each other.
    printAttitude(imu.ax, imu.ay, imu.az,
                  -imu.my, -imu.mx, imu.mz);

    long latitude = myGPS.getLatitude();
    long longitude = myGPS.getLongitude();
    long speed = myGPS.getGroundSpeed();


    
    Serial.print("Lat: ");
    Serial.println(latitude);
    Serial.print("Lng: ");
    Serial.println(longitude);
    Serial.print("Spd: ");
    Serial.println(speed/1000); 
    Serial.print("Rpm: ");
    Serial.println(rpm);


    lastPrint = millis(); // Update lastPrint time
  }
}

void printGyro()
{
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
//  Serial.print("Gyr: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.
  Serial.print("GyX: ");
  Serial.println(imu.calcGyro(imu.gx), 2);
  Serial.print("GyY: ");
  Serial.println(imu.calcGyro(imu.gy), 2);
  Serial.print("GyZ: ");
  Serial.println(imu.calcGyro(imu.gz), 2);
//  Serial.println(" deg/s");
#elif defined PRINT_RAW
  Serial.print("GyX: ");
  Serial.println(imu.gx);
  Serial.print("GyY: ");
  Serial.println(imu.gy);
  Serial.print("GyZ: ");
  Serial.println(imu.gz);
#endif
}

void printAccel()
{
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
//  Serial.print("Acc: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
  Serial.print("AcX: ");
  Serial.println(imu.calcAccel(imu.ax), 2);
  Serial.print("AcY: ");
  Serial.println(imu.calcAccel(imu.ay), 2);
  Serial.print("AcZ: ");
  Serial.println(imu.calcAccel(imu.az), 2);
//  Serial.println(" g");
#elif defined PRINT_RAW
  Serial.print("AcX: ");
  Serial.println(imu.ax);
  Serial.print("AcY: ");
  Serial.println(imu.ay);
  Serial.print("AcZ: ");
  Serial.println(imu.az);
#endif

}

void printMag()
{
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
//  Serial.print("Mag: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcMag helper function to convert a raw ADC value to
  // Gauss. Give the function the value that you want to convert.
  Serial.print("MaX: ");
  Serial.println(imu.calcMag(imu.mx), 2);
  Serial.print("MaY: ");
  Serial.println(imu.calcMag(imu.my), 2);
  Serial.print("MaZ: ");
  Serial.println(imu.calcMag(imu.mz), 2);
//  Serial.println(" gauss");
#elif defined PRINT_RAW
  Serial.print("MaX: ");
  Serial.println(imu.mx);
  Serial.print("MaY: ");
  Serial.println(imu.my);
  Serial.print("MaZ: ");
  Serial.println(imu.mz);
#endif
}

// Calculate pitch, roll, and heading.
// Pitch/roll calculations take from this app note:
// http://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf?fpsp=1
// Heading calculations taken from this app note:
// http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/Magnetic__Literature_Application_notes-documents/AN203_Compass_Heading_Using_Magnetometers.pdf
void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
{
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));

  float heading;
  if (my == 0)
    heading = (mx < 0) ? PI : 0;
  else
    heading = atan2(mx, my);

  heading -= DECLINATION * PI / 180;

  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);

  // Convert everything from radians to degrees:
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;

  Serial.print("Pit: "); //Pitch
  Serial.println(pitch, 2);
  Serial.print("Rol: "); //Roll
  Serial.println(roll, 2);
  Serial.print("Hea: "); //Heading
  Serial.println(heading, 2);
}
