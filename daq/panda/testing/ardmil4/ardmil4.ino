void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // printing out data values
  Serial.print("Lat:");
  Serial.print(-1);
  Serial.print("Lng:");
  Serial.print(-1);
  
  Serial.print("Cur:");
  Serial.print(-1);
  Serial.print("Pwr:");
  Serial.print(-1);
  Serial.print("Vlt:");
  Serial.print(-1);
  
  Serial.print("GyX:");
  Serial.print(-1);
  Serial.print("GyY:");
  Serial.print(-1);
  Serial.print("GyZ:");
  Serial.print(-1);
  
  Serial.print("Hea:");
  Serial.print(-1);
  Serial.print("Pit:");
  Serial.print(-1);
  Serial.print("Rol:");
  Serial.print(-1);
  
  Serial.print("Alt:");
  Serial.print(-1);
  Serial.print("Tem:");
  Serial.print(-1); 
  
  Serial.print("Rpm:");
  Serial.print(-1);
  Serial.print("Thr:");
  Serial.print(-1);
  Serial.print("Spd:");
  Serial.print(-1);

  Serial.print("AcX:");
  Serial.print(-1);
  Serial.print("AcY:");
  Serial.print(-1);
  Serial.print("AcZ:");
  Serial.print(-1);

  Serial.print("MaX:");
  Serial.print(-1);
  Serial.print("MaY:");
  Serial.print(-1);
  Serial.print("MaZ:");
  Serial.println(-1);
}
