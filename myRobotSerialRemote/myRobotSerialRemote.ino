// -*- c -*-
/******************************************************************************
 myRobotSerialRemote.ino

 Robot sketch with serial remote commands
******************************************************************************/

#include <AFMotor.h>       // adafruit motor shield library
#include "RobotMotor.h"    // 2wd or 4wd motor library

#include "robotDefines.h"  // global defines

// Setup runs at startup and is used configure pins and init system variables
void setup() {
  Serial.begin(9600);    
  while(!Serial);  // only needed for leonardo
  
  moveBegin();  
  moveSetSpeed(MIN_SPEED + 10) ;  // Run at 10% above minimum speed     
}

void loop() {
  remoteService(); // wait for serial commands
}

/**
   function to check if robot can continue moving when taking evasive action
   returns true if robot is not blocked when moving to avoid obstacles
   this 'placeholder' version always returns true
*/
boolean isPathClear() {
  return true; 
}
