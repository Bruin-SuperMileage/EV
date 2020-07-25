/*
50A Current Sensor(AC/DC)(SKU:SEN0098) Sample Code
This code shows you how to get raw datas from the sensor through Arduino and convert the raw datas to the value of the current according to the datasheet;
Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing) is used to make the outputting current value more reliable;
Created 27 December 2011
By Barry Machine 
www.dfrobot.com
Version:0.2
*/


const int numReadings = 30;
float readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average
int currentPin = A7;              //pin A7

float currentValue = 0;

void setup()
{
  //analogReference(INTERNAL);
  Serial.begin(57600);
  //pinMode(currentPin, INPUT);
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;       
}
void loop()
{   currentValue = analogRead(currentPin);
    Serial.println(currentValue);
    /*total= total - readings[index];          
    readings[index] = analogRead(currentPin); //Raw data reading
    //readings[index] = (readings[index]-510)*5/1024/0.04-0.04;//Data processing:510-raw data from analogRead when the input is 0; 5-5v; the first 0.04-0.04V/A(sensitivity); the second 0.04-offset val;
    total= total + readings[index];
    index = index + 1;                    
    if (index >= numReadings)              
      index = 0;                           
    average = total/numReadings;   //Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing)    
    currentValue= average;
    Serial.println(currentValue);*/
    delay(1000);
}
