long lastTime = 0;

const int voltagePin = A5;
const float VOLTAGE_CALIB = 0.969;
const int PRINT_SPEED = 500;

const int numReadings = 30;
float readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average

float currentValue = 0;

float convertedValue = 0;

float throttle = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(voltagePin, INPUT);
}

void loop()
{   
 throttle = analogRead(A4); //RAW THROTTLE READING
 throttle = map(throttle, 240, 760, 0, 100); //CONVERT TO PERCENTAGE
 
 currentValue = analogRead(A6); //Raw data reading

 convertedValue = (currentValue - 511) * 110;
 delay(10); 
 
  if (millis() - lastTime > PRINT_SPEED)
  {
    lastTime = millis(); 
    currentValue = analogRead(A6);

    int voltage_raw = analogRead(voltagePin);
    float voltage = 5*VOLTAGE_CALIB*(voltage_raw/0.091)/1023;
    Serial.print("Cur: ");
    Serial.println(convertedValue);
    Serial.print("Vlt: ");
    Serial.println(voltage);
    Serial.print("Thr: ");
    Serial.println(throttle);
  }
}
