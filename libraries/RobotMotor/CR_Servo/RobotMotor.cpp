/*******************************************************
    RobotMotor.cpp // continuous rotation servo version
	
    low level motor driver for use with continuous rotation servos and 2WD robot

    Copyright Michael Margolis May 8 2012
********************************************************/

#include <Arduino.h>  
#include <Servo.h>
#include "RobotMotor.h"

Servo myservo[2];               // create instances for two servos

const int MAX_ANGLE    = 60;    // number of degrees that motor driven at max speed
const int servoPins[2] = {7,8}; // digital pins connected to servos:(left,right)

                              // change sign to reverse direction of the motor 
int motorSense[2] = {1,-1};     // 1 increases angle for forward, -1 decreaes 

int motorStopAngle[2] = {90,90}; // inc or dec so motor stops when motorStop is called 

int motorSpeed[2] = {0,0};      // left and right motor speeds stored here (0-100%)

// tables hold time in ms to rotate robot 360 degrees at various speeds 
// this enables conversion of rotation angle into timed motor movement 
// The speeds are percent of max speed
// Note: low cost motors do not have enough torque at low speeds so
// the robot will not move below this value 
// Interpolation is used to get a time for any speed from MIN_SPEED to 100%

const int MIN_SPEED = 40; // first table entry is 40% speed
const int SPEED_TABLE_INTERVAL = 10; // each table entry is 10% faster speed
const int NBR_SPEEDS =  1 + (100 - MIN_SPEED)/ SPEED_TABLE_INTERVAL;
 
int speedTable[NBR_SPEEDS]  =  {40,     50,   60,   70,   80,   90,  100}; // speeds  
int rotationTime[NBR_SPEEDS] = {5500, 3300, 2400, 2000, 1750, 1550, 1150}; // time 

void motorBegin(int motor)
{
   myservo[motor].attach(servoPins[motor]);
}

// speed range is 0 to 100
void motorSetSpeed(int motor, int speed)
{
   motorSpeed[motor] = speed;           // save the value
}

void motorForward(int motor, int speed)
{
  motorSetSpeed(motor, speed); 
  int stopAngle = motorStopAngle[motor];
  int maxSpeedAngle =  stopAngle + (MAX_ANGLE *  motorSense[motor]); 
  int angle = map(speed, 0,100, stopAngle, maxSpeedAngle);   
  myservo[motor].write(angle);
}

void motorReverse(int motor, int speed)
{
  motorSetSpeed(motor, speed); 
  int stopAngle = motorStopAngle[motor];
  int maxSpeedAngle =  stopAngle - (MAX_ANGLE *  motorSense[motor]); 
  int angle = map(speed, 0,100, stopAngle, maxSpeedAngle);   
  myservo[motor].write(angle);  
}

void motorStop(int motor)
{
  myservo[motor].write(motorStopAngle[motor]);
}

void motorBrake(int motor)
{
  myservo[motor].write(motorStopAngle[motor]);
}