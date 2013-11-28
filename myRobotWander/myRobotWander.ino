
/**********************************************************
 myRobotWander.ino
 
 Robot wanders using forward scanning for obstacle avoidance.
 ***********************************************************/
#include <AFMotor.h>
#include <RobotMotor.h>

#include "robotDefines.h"

void setup() {
  Serial.begin(9600);
  blinkNumber(8);
  
  lookBegin();
  moveBegin();
  moveSetSpeed(MIN_SPEED + 30);
  
  Serial.println("Ready");
}

void loop() {
  moveForward();
  roam(); // Look around
}


