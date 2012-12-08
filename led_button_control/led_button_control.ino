// LED is on when button is down. Have to hold
// the button down to keep the light on.

const int LED = 13; // The pin for the LED
const int BUTTON = 7; // The input pin where the pushbutton is connected

int val = 0; // val will be used to store the state of the input pin

void setup() {
  pinMode(LED, OUTPUT); // Tell arduino LED is an output
  pinMode(BUTTON, INPUT); // and BUTTON is an input
}

void loop() {
  val = digitalRead(BUTTON); // read input value and store it
  
  // check whether the input is HIGH (button pressed)
  if (val == HIGH) {
    digitalWrite(LED, HIGH); // Turn the LED on
  } else {
    digitalWrite(LED, LOW); // LED off
  }
}
