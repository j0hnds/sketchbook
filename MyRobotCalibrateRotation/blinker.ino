// Function to indicate numbers by flashing the built-in LED
void blinkNumber(byte number) {
  pinMode(LED_PIN, OUTPUT); // Enable the LED pin for output
  while (number--) {
    digitalWrite(LED_PIN, HIGH); delay(100);
    digitalWrite(LED_PIN, LOW);  delay(400);
  }
}
