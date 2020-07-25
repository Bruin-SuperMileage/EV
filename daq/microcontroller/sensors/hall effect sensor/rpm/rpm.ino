int hall_sensor = 3;
float t1 = 0;
float t2 = 0;
float t_tot = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(hall_sensor,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hall_sensor), time1, FALLING);
}
void loop() {
  // put your main code here, to run repeatedly:
  t_tot = t1 - t2;
  t2 = t1;
  
  if (((1/t_tot)*1000*60) < 1000000)
  {
    Serial.println((1/t_tot)*1000*60);
  }
}
void time1()
{
  t1 = millis();
}
