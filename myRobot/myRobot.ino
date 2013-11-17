/****************************************************
 * HelloRobot.ino: Initial Robot test sketch
 *
 ***************************************************/
 
#include <AFMotor.h>
#include <RobotMotor.h>
#include "robotDefines.h"

void setup() {
  Serial.begin(9600);
  
  // Open port while flashing. Needed for Leonardo only
  blinkNumber(8);
  
  Serial.println("Initializing the motors");
  motorBegin(MOTOR_LEFT);
  motorBegin(MOTOR_RIGHT);
  
  Serial.println("Initializing the sensors");
  
  irSensorBegin(); // Initialize sensors
  pinMode(LED_PIN, OUTPUT); // Enable the LED pin for output
  
  Serial.println("Waiting for a sensor to detect blocked reflection");
}

void loop() {
  if (counter == 5000) {
    printCurrentCalibrationLevels();
    counter = 0;
  } else {
    counter++;
  }
  // Call a function when reflection blocked on the left side
  if (lookForObstacle(OBST_LEFT_EDGE) == true) {
    calibrateRotationRate(DIR_LEFT, 360); // Calibrate CCW rotation
  }
  
  // Same as above for the right sensor
  if (lookForObstacle(OBST_RIGHT_EDGE) == true) {
    calibrateRotationRate(DIR_RIGHT, 360); // Calibrate CW rotation
  }
}

// Function to indicate numbers by flashing the built-in LED
void blinkNumber(byte number) {
  pinMode(LED_PIN, OUTPUT); // Enable the LED pin for output
  while (number--) {
    digitalWrite(LED_PIN, HIGH); delay(100);
    digitalWrite(LED_PIN, LOW);  delay(400);
  }
}

/*********************************************
 Code to look for obstacles
 *********************************************/

// Returns true if the given obstacle is detected
boolean lookForObstacle(int obstacle) {
  switch(obstacle) {
    case OBST_FRONT_EDGE:
      return irEdgeDetect(DIR_LEFT) || irEdgeDetect(DIR_RIGHT);
    case OBST_LEFT_EDGE:
      return irEdgeDetect(DIR_LEFT);
    case OBST_RIGHT_EDGE:
      return irEdgeDetect(DIR_RIGHT);
  }
  return false;
}

/*************************************************
 Functions to rotate the robot
 *************************************************/

// Return the time in milliseconds to turn the given
// angle at the given speed)
long rotationAngleToTime(int angle, int speed) {
  int fullRotationTime; // Time to rotate 360 degrees at given speed
  
  if (speed < MIN_SPEED) {
    return 0; // Ignore speeds slower than the first table entry
  }
  
  angle = abs(angle);
  
  if (speed >= 100) {
    fullRotationTime = rotationTime[NBR_SPEEDS - 1]; // Last entry
  } else {
    int index = (speed - MIN_SPEED) / SPEED_TABLE_INTERVAL;
    
    int t0 = rotationTime[index];
    int t1 = rotationTime[index + 1];
    fullRotationTime = map(speed,
                           speedTable[index],
                           speedTable[index + 1],
                           t0,
                           t1);
    // Serial.print(" full rotation time = ");
    // Serial.println(fullRotationTime);
  }
  long result = map(angle, 0, 360, 0, fullRotationTime);
  return result;
}

// Rotate the robot from MIN_SPEED to 100% increasing by
// SPEED_TABLE_INTERVAL
void calibrateRotationRate(int sensor, int angle) {
  Serial.print(locationString[sensor]);
  Serial.println(" calibration");
  
  for (int speed = MIN_SPEED; speed <= 100; speed += SPEED_TABLE_INTERVAL) {
    delay(1000);
    blinkNumber(speed/10);
    
    if (sensor == DIR_LEFT) {
      // Rotate left
      motorReverse(MOTOR_LEFT, speed);
      motorForward(MOTOR_RIGHT, speed);
    } else if (sensor == DIR_RIGHT) {
      // Rotate right
      motorForward(MOTOR_LEFT, speed);
      motorReverse(MOTOR_RIGHT, speed);
    } else {
      Serial.println("Invalid sensor");
    }
    
    int time = rotationAngleToTime(angle, speed);
    
    Serial.print(locationString[sensor]);
    Serial.print(": rotate ");
    Serial.print(angle);
    Serial.print(" degrees at speed ");
    Serial.print(speed);
    Serial.print(" for ");
    Serial.print(time);
    Serial.println("ms");
    
    delay(time);
    motorStop(MOTOR_LEFT);
    motorStop(MOTOR_RIGHT);
    delay(2000); // Two second delay between speeds
  }
}


