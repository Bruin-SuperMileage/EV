void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // printing out data values
  Serial.print("Alt:");
  Serial.print(-1);
  Serial.print("Tem:");
  Serial.print(-1); 
  Serial.print("Lat:");
  Serial.print(-1);
  Serial.print("Lng:");
  Serial.print(-1);
  Serial.print("Spd:");
  Serial.print(-1);
  Serial.print("Rpm:");
  Serial.println(-1);
}
