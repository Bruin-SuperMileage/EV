void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // printing out data values
  Serial.print("Lat:");
  Serial.println(-1);
  Serial.print("Lng:");
  Serial.println(-1);
  
  Serial.print("Cur:");
  Serial.println(-1);
  Serial.print("Pwr:");
  Serial.println(-1);
  Serial.print("Vlt:");
  Serial.println(-1);
  
  Serial.print("GyX:");
  Serial.println(-1);
  Serial.print("GyY:");
  Serial.println(-1);
  Serial.print("GyZ:");
  Serial.println(-1);
  
  Serial.print("Hea:");
  Serial.println(-1);
  Serial.print("Pit:");
  Serial.println(-1);
  Serial.print("Rol:");
  Serial.println(-1);
  
  Serial.print("Alt:");
  Serial.println(-1);
  Serial.print("Tem:");
  Serial.println(-1); 
  
  Serial.print("Rpm:");
  Serial.println(-1);
  Serial.print("Thr:");
  Serial.println(-1);
  Serial.print("Spd:");
  Serial.println(-1);

  Serial.print("AcX:");
  Serial.println(-1);
  Serial.print("AcY:");
  Serial.println(-1);
  Serial.print("AcZ:");
  Serial.println(-1);

  Serial.print("MaX:");
  Serial.println(-1);
  Serial.print("MaY:");
  Serial.println(-1);
  Serial.print("MaZ:");
  Serial.println(-1);
}
