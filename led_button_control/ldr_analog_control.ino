const int LED = 13

int val = 0;

void setup() {
  pinMode(LED, OUTPUT);
  
  // Analog pins are auto-INPUT
}

void loop() {
  val = analogRead(0); 
  
  digitalWrite(LED, HIGH);
  
  delay(val);
  
  digitalWrite(LED, LOW);
  
  delay(val);
}
