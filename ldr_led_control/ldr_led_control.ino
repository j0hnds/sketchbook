const int SENSOR = 0;

int val = 0;

void setup() {
  Serial.begin(9600);
  // Analog pins are auto-INPUT
}

void loop() {
  val = analogRead(SENSOR); 
  
  Serial.print(val);
  
  delay(100);
  
}
