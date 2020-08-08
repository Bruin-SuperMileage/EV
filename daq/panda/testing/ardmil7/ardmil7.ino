//Constants:
const int potPin = A5; //pin A5 to read analog input

//Variables:
int value; //save analog value

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT); // Potentiometer pin
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  value = analogRead(potPin);          //Read and save analog value from potentiometer
  value = map(value, 0, 1023, 0, 255); //Map value 0-1023 to 0-255 (PWM)
  Serial.print("Pot:");
  Serial.print(value);
  delay(100);                          //Small delay
  
  // printing out data values
  Serial.print("Lat:");
  Serial.print(911);
  Serial.print("Lng:");
  Serial.print(912);
  
  Serial.print("Cur:");
  Serial.print(913);
  Serial.print("Pwr:");
  Serial.print(914);
  Serial.print("Vlt:");
  Serial.print(915);
  
  Serial.print("GyX:");
  Serial.print(916);
  Serial.print("GyY:");
  Serial.print(917);
  Serial.print("GyZ:");
  Serial.print(918);
  
  Serial.print("Hea:");
  Serial.print(919);
  Serial.print("Pit:");
  Serial.print(910);
  Serial.print("Rol:");
  Serial.print(911);
  
  Serial.print("Alt:");
  Serial.print(912);
  Serial.print("Tem:");
  Serial.print(913); 
  
  Serial.print("Rpm:");
  Serial.print(914);
  Serial.print("Thr:");
  Serial.print(915);
  Serial.print("Spd:");
  Serial.print(916);

  Serial.print("AcX:");
  Serial.print(917);
  Serial.print("AcY:");
  Serial.print(918);
  Serial.print("AcZ:");
  Serial.print(919);

  Serial.print("MaX:");
  Serial.print(920);
  Serial.print("MaY:");
  Serial.print(921);
  Serial.print("MaZ:");
  Serial.println(922);
}
