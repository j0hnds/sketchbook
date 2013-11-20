/**********************************************************
 myRobotEdge.ino
 
 Robot sketch to move within area bordered by a non-reflective
 line.
 **********************************************************/
#include <AFMotor.h>
#include <RobotMotor.h>

#include "robotDefines.h"

void setup() {
  Serial.begin(9600);
  blinkNumber(8);
  
  lookBegin();
  moveBegin();
  
  Serial.println("Ready");
}

void loop() {
  if (counter == 5000) {
    // Do something...
    counter = 0;
  } else {
    counter++;
  }
  // Code for roaming around and avoiding obstacles
  if (lookForObstacle(OBST_FRONT_EDGE)) {
    Serial.println("both sensors detected edge");
    timedMove(MOV_BACK, 300);
    moveRotate(120);
    while (lookForObstacle(OBST_FRONT_EDGE)) {
      moveStop(); // Stop motors if still over cliff
    }
  } else if (lookForObstacle(OBST_LEFT_EDGE)) {
    Serial.println("left sensor detected edge");
    timedMove(MOV_BACK, 100);
    moveRotate(30);
  } else if (lookForObstacle(OBST_RIGHT_EDGE)) {
    Serial.println("right sensor detected edge");
    timedMove(MOV_BACK, 100);
    moveRotate(-30);
  } else {
    moveSetSpeed(MIN_SPEED);
    moveForward();
  }
}


