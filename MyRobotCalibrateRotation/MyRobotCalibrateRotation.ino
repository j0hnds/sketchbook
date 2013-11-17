/************************************************************
 MyRobotCalibrateRotation.ino
 ***********************************************************/
#include <AFMotor.h>
#include <RobotMotor.h>

const int LED_PIN = 13;

void setup() {
  // Open port while flashing. Needed for Leonardo only
  blinkNumber(8);

  motorBegin(MOTOR_LEFT);
  motorBegin(MOTOR_RIGHT);
  
  calibrateSpeed();
}

void loop() {
  // Nothing to do; everything is done in calibrate speed.
}

void calibrateSpeed() {
  for (int speed = MIN_SPEED; speed <= 100; speed += 10) {
    
    // Rotate the robot left for 1 second
    motorReverse(MOTOR_LEFT,  speed);
    motorForward(MOTOR_RIGHT, speed);
    
    delay(1000); // Delay for 1 second
    
    motorStop(MOTOR_LEFT);
    motorStop(MOTOR_RIGHT);
    
    delay(5000); // Delay for 5
    
    // Rotate the robot right for 1 second
    motorReverse(MOTOR_RIGHT, speed);
    motorForward(MOTOR_LEFT,  speed);
    
    delay(1000); // Delay 1 second
    
    motorStop(MOTOR_LEFT);
    motorStop(MOTOR_RIGHT);
    
    delay(5000);
  }
}


