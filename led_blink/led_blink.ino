const int LED = 13; // LED connected to digital pin 13

void setup() {
  pinMode(LED, OUTPUT); // Sets the digital pin as output
}

void loop () {
  digitalWrite(LED, HIGH); // Turns the LED on
  delay(3000); // Waits for 2 seconds
  digitalWrite(LED, LOW); // Turns the LED off
  delay(1000);
}
