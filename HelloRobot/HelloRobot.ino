/****************************************************
 * HelloRobot.ino: Initial Robot test sketch
 *
 ***************************************************/
 
#include <AFMotor.h>
#include <RobotMotor.h>

/*********** Global Defines ******************/
// Defines to identify sensors
const int SENSE_IR_LEFT   = 0;
const int SENSE_IR_RIGHT  = 1;
const int SENSE_IR_CENTER = 2;

// Defines for directions
const int DIR_LEFT   = 0;
const int DIR_RIGHT  = 1;
const int DIR_CENTER = 2;

// Debug labels
const char *locationString[] = { "Left", "Right", "Center" };

// Obstacles constants
const int OBST_NONE       = 0; // No obstacle detected
const int OBST_LEFT_EDGE  = 1; // Left edge detected
const int OBST_RIGHT_EDGE = 2; // Right edge detected
const int OBST_FRONT_EDGE = 3; // Edge detected both right/left

const int LED_PIN = 13;
int counter = 0;
/*********** End of Global Defines *********************/

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

/*************************************************
 IR Reflectance Sensor code
 ************************************************/
 
 const byte NBR_SENSORS = 2; // This version only has left/right
 const byte IR_SENSOR[NBR_SENSORS] = { 0, 1 }; // Analog pins for sensors
 
 int irSensorAmbient[NBR_SENSORS]; // sensor value with no reflection
 int irSensorReflect[NBR_SENSORS]; // value considered detecting an object
 int irSensorEdge[NBR_SENSORS];    // value considered detecting an edge
 boolean isDetected[NBR_SENSORS] = { false, false }; // True if detected
 
 const int irReflectThreshold = 10; // % level below ambient to trigger reflection
 const int irEdgeThreshold    = 90; // % level above ambient to trigger edge
 
 void irSensorBegin() {
   for (int sensor = 0; sensor < NBR_SENSORS; sensor++) {
     irSensorCalibrate(sensor);
   }
 }
 
 // Calibrate thresholds for ambient light
 void irSensorCalibrate(byte sensor) {
   int ambient = analogRead(IR_SENSOR[sensor]); // Get ambient level
   irSensorAmbient[sensor] = ambient;
   
   // Precalculate the levels for object and edge detection
   irSensorReflect[sensor] = (ambient * (long)(100 - irReflectThreshold)) / 100;
   irSensorEdge[sensor]    = (ambient * (long)(100 + irEdgeThreshold)) / 100;
 }
 
 void printCurrentCalibrationLevels() {
   for (int sensor = 0; sensor < NBR_SENSORS; sensor++) {
     Serial.print(locationString[sensor]);
     Serial.print(" ambient = ");
     Serial.print(irSensorAmbient[sensor]);
     Serial.print(" reflect = ");
     Serial.print(irSensorReflect[sensor]);
     Serial.print(" edge = ");
     Serial.println(irSensorEdge[sensor]);
   }
 }
 
 // Returns true if an object reflection detected on the given sensor
 boolean irSensorDetect(int sensor) {
   boolean result = false; // Default value
   int value = analogRead(IR_SENSOR[sensor]); // Get the light level
   if (value <= irSensorReflect[sensor]) {
     result = true; // object detected (lower value means more reflection)
     if (isDetected[sensor] == false) { // Only print on initial detection
       Serial.print(locationString[sensor]);
       Serial.println(" object detected");
     }
   }
   isDetected[sensor] = result;
   return result;
 }
 
 boolean irEdgeDetect(int sensor) {
   boolean result = false; // default value
   int value = analogRead(IR_SENSOR[sensor]); // Get the light level
   if (counter == 4000) {
     Serial.print(locationString[sensor]);
     Serial.print(" current level = ");
     Serial.print(value);
     Serial.print(" >= ");
     Serial.println(irSensorEdge[sensor]);
   }
   if (value >= irSensorEdge[sensor]) {
     result = true; // Edge detected (higher value means less reflected)
     if (isDetected[sensor] == false) { // only print on initial detection
       Serial.print(locationString[sensor]);
       Serial.println(" edge detected");
     }
   }
   isDetected[sensor] = result;
   return result;
 }
