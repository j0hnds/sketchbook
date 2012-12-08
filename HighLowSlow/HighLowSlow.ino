const int LED = 9; // The pin for the LED

int i = 0; // We'll use this to count up and down

void setup() {
  pinMode(LED, OUTPUT); // Tell arduino LED is an output
}

void loop() {
  for (i=0; i<255; i++) {
    analogWrite(LED, i); // set the LED brightness
    delay(10); // Wait 10ms because analogWrite is instantaneous
  }
  
  for (i=255; i > 0; i--) {
    analogWrite(LED, i);
    delay(10);
  }
}
