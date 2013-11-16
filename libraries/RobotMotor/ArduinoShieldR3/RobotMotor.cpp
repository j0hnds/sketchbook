/*******************************************************
    RobotMotor.cpp // Arduino Motor Shield R3 version
    low level motor driver for use with arduino Motor Shield

    Michael Margolis Sept 17 2012
********************************************************/

#include <Arduino.h>  
#include "RobotMotor.h"

const int differential = 0; // % faster left motor turns compared to right 

/****** motor pin defines *************/
// Pins connected to the motor driver. The PWM pins control the speed, and the
//  other pins are select forward and reverse

// Motor pins :              B, A
const byte M_PWM_PIN[2]   = {11,3};  // speed)
const byte M_DIR_PIN[2]   = {13,12}; // Dir
const byte M_BRAKE_PIN[2] = {8,9};   // brake
/* end of motor pin defines */

int  motorSpeed[2]  = {0,0}; // motor speed stored here (0-100%)

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
  pinMode(M_DIR_PIN[motor], OUTPUT);
  pinMode(M_BRAKE_PIN[motor], OUTPUT);
  motorStop(motor);
}

// speed range is 0 to 100
void motorSetSpeed(int motor, int speed)
{
   motorSpeed[motor] = speed;           // save the value
   speed = map(speed, 0,100, 0,255);    // scale to PWM range
   analogWrite(M_PWM_PIN[motor], speed);  // write the value   
}

void motorForward(int motor, int speed)
{
  digitalWrite(M_DIR_PIN[motor], HIGH);
  motorSetSpeed(motor, speed); 
}

void motorReverse(int motor, int speed)
{
  digitalWrite(M_DIR_PIN[motor], LOW);
  motorSetSpeed(motor, speed);  
}

void motorStop(int motor)
{
  analogWrite(M_PWM_PIN[motor], 0);
}

void motorBrake(int motor)
{
  analogWrite(M_PWM_PIN[motor], 0);
  digitalWrite(M_BRAKE_PIN[motor], HIGH);
}