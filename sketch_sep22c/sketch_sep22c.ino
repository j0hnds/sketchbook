// Button click to turn light on, another click to turn it off

const int LED = 13; // The pin for the LED
const int BUTTON = 7; // The input pin where the pushbutton is connected

int val = 0; // val will be used to store the state of the input pin

int old_val = 0; // This variable stores the previous value of 'val'

int state = 0; // 0 = LED off while 1 = LED on

void setup() {
  pinMode(LED, OUTPUT); // Tell arduino LED is an output
  pinMode(BUTTON, INPUT); // and BUTTON is an input
}

void loop() {
  val = digitalRead(BUTTON); // Read input value and store it
  
  // Check if there was a transition
  if ((val == HIGH) && (old_val == LOW)) {
    state = 1 - state;
    delay(10); // Wait 10 ms for debounce of the switch
  }
  
  old_val = val; // Val is now old, let's store it
  
  if (state == 1) {
    digitalWrite(LED, HIGH); // Turn LED on
  } else {
    digitalWrite(LED, LOW); // Turn LED off
  }
}
