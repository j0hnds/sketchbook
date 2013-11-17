#include <AFMotor.h>
#include <RobotMotor.h>

/*********************************************************
 MyRobotCalibrateTracking.ino
 ********************************************************/

const int TEST_SPEED = MIN_SPEED + 10; // Typical speed
const int differential = 5; // % faster left motor turns compared to right
const int LED_PIN = 13;

void setup() {
  Serial.begin(9600);
  
  blinkNumber(8);
  
  motorBegin(MOTOR_LEFT);
  motorBegin(MOTOR_RIGHT);
  
  calibrateDrift();
}

void loop() {
  // Do nothing...
}

void calibrateDrift() {
  motorForward(MOTOR_LEFT, TEST_SPEED - differential);
  motorForward(MOTOR_RIGHT, TEST_SPEED);
  
  delay(3000);
  
  motorStop(MOTOR_LEFT);
  motorStop(MOTOR_RIGHT);
}
