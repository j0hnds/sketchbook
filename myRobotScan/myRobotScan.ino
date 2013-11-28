// -*- c -*-
/************************************************************
 myRobotScan.ino

 Robot wanders turning his 'head' to find obstacles.
************************************************************/
#include <AFMotor.h>
#include <RobotMotor.h>

#include "robotDefines.h"

void setup() {
  Serial.begin(9600);
  blinkNumber(8);

  lookBegin(); 
  moveBegin();  
  moveSetSpeed(MIN_SPEED + 10) ;   // Run at 10% above minimum speed
  softServoWrite(90, 2000);        // center the servo 

  Serial.println("Ready");
}

void loop() {
  moveForward();
  roam();  // look around 
}
