// -*- c -*-
/******************************************************************************
 myRobotRemote.ino

 Robot sketch with remote commands
 Note: if motors don't turn, check that irRemoteInt.h uses Timer1, not Timer2
******************************************************************************/

#include <AFMotor.h>       // adafruit motor shield library
#include "RobotMotor.h"    // 2wd or 4wd motor library

#include "robotDefines.h"  // global defines

const byte irReceivePin = A3; // analog pin 3

/**
   Setup runs at startup and is used configure pins and init system variables.
*/
void setup() {
  Serial.begin(9600);  
  blinkNumber(8); // open port while flashing. Needed for Leonardo only  
  
  lookBegin();  
  moveBegin(); 
  remoteBegin(irReceivePin);  // added Remote tab
 
  moveSetSpeed(MIN_SPEED + 10) ;  // Run at 10% above minimum speed   
  Serial.println("Ready");    
}

void loop() {
  remoteService();
}
