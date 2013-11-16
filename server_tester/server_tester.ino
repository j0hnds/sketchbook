/*
 * Test sketch for a servo. What we want to do is to have the 
 * servo go to 0 position when the switch is open (unpushed)
 * and to go to 180 position when the switch is closed (pushed).
 *
 * The circuit is as follows:
 *
 * One pole of switch to a 10k resistor to 5V.
 * The other pole of switch to ground.
 * The point between the 10k and first pole of switch to pin 7
 *
 * The Yellow wire of the servo to pin 9
 * The Brown wire of the servo to GND
 * The Red wire of the servo to 5V
 *
 * That's it.
 */
#include <Servo.h>

Servo servo;
//int servoValue = 90; // Initial value of servo

int ledPin = 13; 
int inPin = 7; // Test pin for the switch
int servoPin = 9; // The signal pin for the servo.
int val = 0; // Pin 7 status
int prevVal = 0; // Previous value of Pin 7
int state=0; // State of button press

void setup() {
  servo.attach(servoPin); // The servo signal pin is on pin 9
  pinMode(ledPin, OUTPUT); // Declare the LED as output
  pinMode(inPin, INPUT); // Declare the pushbutton as input
}

void loop() {
  val = digitalRead(inPin);  // Read the input value
  
  // Check if there was a transition
  if ((val == HIGH) && (prevVal == LOW)) {
    state = 1 - state;
    delay(10); // Wait 10ms for debounce of the switch
  }
  
  prevVal = val; // Val is now old, let's store it
  
  if (state == 1) { // Check if the input is HIGH (button released)
    digitalWrite(ledPin, LOW); // turn LED OFF
    servo.write(0);
  } else {
    digitalWrite(ledPin, HIGH); // turn the LED ON
    servo.write(180);
  }
  
  // Slow the loop down a bit; wait 200ms
  delay(200);
}
