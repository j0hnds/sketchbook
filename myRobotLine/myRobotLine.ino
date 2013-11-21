/************************************************************
 myRobotLine.ino
 
 Robot sketch to following lines
 ************************************************************/
#include <AFMotor.h>
#include <RobotMotor.h>
#include "robotDefines.h"

int speed = MIN_SPEED - 10; // Speed when moving in a straight line

void setup() {
  Serial.begin(9600);
  blinkNumber(8);
  
  lookBegin();
  moveBegin();
  lineSenseBegin();
  
  Serial.println("Ready");
}

void loop() {
  int drift = lineSense();
  lineFollow(drift, speed);
}

/***********************************************************
 Line Sensor code
***********************************************************/
int damping = 1; // 1 is most sensitive, range 1 to 1023

void lineSenseBegin() {
  // Nothing yet
}

// returns drift - 0 if over line, minus value if left, plus if right
int lineSense() {
  int leftVal = analogRead(SENSE_IR_LEFT);
  int centerVal = analogRead(SENSE_IR_CENTER);
  int rightVal = analogRead(SENSE_IR_RIGHT);
  
  int leftSense = centerVal - leftVal;
  int rightSense = rightVal - centerVal;
  
  int drift = rightVal - leftVal;
  
  Serial.print("L,C,R=");
  Serial.print(leftVal);
  Serial.print(",");
  Serial.print(centerVal);
  Serial.print(",");
  Serial.println(rightVal);
  
  Serial.print("LS,RS=");
  Serial.print(leftSense);
  Serial.print(",");
  Serial.println(rightSense);
  
  Serial.print("Drift=");
  Serial.println(drift);
  
  return drift;
}

int lineFollow(int drift, int speed) {
  int leftSpeed = constrain(speed - (drift / damping), 0, 100);
  int rightSpeed = constrain(speed + (drift / damping), 0, 100);
  
  motorForward(MOTOR_LEFT, rightSpeed);
  motorForward(MOTOR_RIGHT, leftSpeed);
}
