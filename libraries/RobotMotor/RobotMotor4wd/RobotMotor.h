/*******************************************************
    RobotMotor.h
    low level motor driver interface
	
    Copyright Michael Margolis May 8 2012
********************************************************/

/* if you have the 4WD chassis, change the line:
     #define CHASSIS_2WD 
   to:
     #define CHASSIS_4WD
 */

#define CHASSIS_4WD // change suffix from 2WD to 4WD if using the 4WD chassis

// defines for left and right motors
const int MOTOR_LEFT  = 0;
const int MOTOR_RIGHT = 1;

extern const int MIN_SPEED;
extern int speedTable[];
extern int rotationTime[];
extern const int SPEED_TABLE_INTERVAL;
extern const int NBR_SPEEDS;

void motorBegin(int motor); 

// speed range is 0 to 100 percent
void motorSetSpeed(int motor, int speed);

void motorForward(int motor, int speed);

void motorReverse(int motor, int speed);

void motorStop(int motor);

void motorBrake(int motor);