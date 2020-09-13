void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // printing out data values
  Serial.print("Lat:");
  Serial.print(11);
  Serial.print("Lng:");
  Serial.print(12);
  
  Serial.print("Cur:");
  Serial.print(13);
  Serial.print("Pwr:");
  Serial.print(14);
  Serial.print("Vlt:");
  Serial.print(15);
  
  Serial.print("GyX:");
  Serial.print(16);
  Serial.print("GyY:");
  Serial.print(17);
  Serial.print("GyZ:");
  Serial.print(18);
  
  Serial.print("Hea:");
  Serial.print(19);
  Serial.print("Pit:");
  Serial.print(10);
  Serial.print("Rol:");
  Serial.print(11);
  
  Serial.print("Alt:");
  Serial.print(12);
  Serial.print("Tem:");
  Serial.print(13); 
  
  Serial.print("Rpm:");
  Serial.print(14);
  Serial.print("Thr:");
  Serial.print(15);
  Serial.print("Spd:");
  Serial.print(16);

  Serial.print("AcX:");
  Serial.print(17);
  Serial.print("AcY:");
  Serial.print(18);
  Serial.print("AcZ:");
  Serial.print(19);

  Serial.print("MaX:");
  Serial.print(20);
  Serial.print("MaY:");
  Serial.print(21);
  Serial.print("MaZ:");
  Serial.println(22);
}
