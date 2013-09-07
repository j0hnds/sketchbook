#include <Servo.h> // Include Servo library

// Create the servo object 
Servo vertical; // Vertical servo
int servoV = 90; // Stand vertical servo

// LDR pin connections
// name = analog_pin;
int ldrUpLeft = 0;
int ldrDownLeft = 2;

void setup() {
  vertical.attach(9);
}

void loop() {
  // Read the light values from the LDR's
  int leftUp = analogRead(ldrUpLeft);
  int leftDown = analogRead(ldrDownLeft);
  
  // We don't have any pot's connected at the moment, so
  // we'll just have to wing the value...
  int dtime = 20;
  int tolerance = 20;
  
  // Determine the difference between the up/down LDR's
  int delta = leftUp - leftDown;
  
  // Only do something if the difference exceeds the tolerance value
  if (abs(delta) > tolerance) {
    if (leftUp > leftDown) {
      servoV++;
      if (servoV > 180) {
        servoV = 180;
      }
    } else {
      servoV--;
      if (servoV < 0) {
        servoV = 0;
      }
    }
    vertical.write(servoV);
  }
  
  delay(dtime);
}
