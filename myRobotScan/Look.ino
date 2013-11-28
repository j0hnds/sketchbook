// -*- c -*-
/**********************
 code to look for obstacles
**********************/

// servo defines
const int sweepServoPin  = 9;   // pin connected to servo
const int servoDelay     = 500; // time in ms for servo to move

const int MIN_DISTANCE   = 18;   // robot stops when object is nearer (in inches)
const int CLEAR_DISTANCE = 30;  // distance in inches considered attracive to move
const int MAX_DISTANCE   = 150; // the maximum range of the distance sensor

// servo angles             left, right, center 
const int servoAngles[] = {  150,  30,   90 };

const byte pingPin = 10; // digital pin 10

void lookBegin() {
  irSensorBegin();    // initialize sensors 

  softServoAttach(sweepServoPin);  /// attaches the servo pin to the servo object 
}

/**
   Returns true if the given obstacle is detected
*/
boolean sensesObstacle(int obstacle) {
  switch(obstacle) {
  case  OBST_FRONT_EDGE: 
    return irEdgeDetect(DIR_LEFT) && irEdgeDetect(DIR_RIGHT); 
  case  OBST_LEFT_EDGE:  
    return irEdgeDetect(DIR_LEFT); 
  case  OBST_RIGHT_EDGE: 
    return irEdgeDetect(DIR_RIGHT); 
  case  OBST_FRONT:     
    return lookAt(servoAngles[DIR_CENTER]) <= MIN_DISTANCE;      
  }
  return false; 
}

/**
   Returns the distance of objects at the given angle
*/
int lookAt(int angle) {
  // wait for servo to get into position
  softServoWrite(angle, servoDelay ); 

  int distance, samples;
  long cume;
  distance = samples = cume = 0;

  // Take 4 samples of the distance to average later...
  for (int i=0; i < 4; i++) {  
    distance = pingGetDistance(pingPin);
    if (distance > 0) {
      samples++;
      cume += distance;
    }
  }

  if (samples > 0) {
    distance = cume / samples;
  } else {
    distance = 0;  
  }

  if (angle != servoAngles[DIR_CENTER]) {
    // Print only if looking right/left
    Serial.print("looking at dir "); 
    Serial.print(angle), Serial.print(" distance= "); 
    Serial.println(distance); 
    
    // Re-center the servo
    softServoWrite(servoAngles[DIR_CENTER], servoDelay/2);    
  } 

  return distance;   
}

/**
   Function to check if robot can continue moving in current direction 
   returns true if robot is not blocked moving in current direction.
   This version only tests for obstacles in front.
*/
boolean isPathClear() {
  boolean isClear = true; // default return value if no obstacles

  if (moveGetState() == MOV_FORWARD) {
    isClear = ! sensesObstacle(OBST_FRONT);
  }
  return isClear; 
}

/**
   Look for and avoid obstacles using servo to scan .
*/
void roam() {
  int distance = lookAt(servoAngles[DIR_CENTER]);

  if (distance == 0) { 

    // no sensor
    moveStop();
    Serial.println("No front sensor");
    return;  // No point in continuing...

  } else if (distance <= MIN_DISTANCE) {
    // Need to stop and look around to see if 
    // there is a clear path
    moveStop();

    int leftDistance  = lookAt(servoAngles[DIR_LEFT]);
    if (leftDistance > CLEAR_DISTANCE)  {

      // Appears to be clear on the left...
      moveRotate(-90);

    } else {

      // Not clear on the left; check to the right...
      delay(500);
      int rightDistance = lookAt(servoAngles[DIR_RIGHT]);
      if (rightDistance > CLEAR_DISTANCE) {

	// It's clear to the right. Let's go there...
        moveRotate(90);   

      } else {

	// Hmm, not clear to the right or the left...
	// What is the maximum clearance?
        distance = max( leftDistance, rightDistance);

        if (distance < CLEAR_DISTANCE / 2) {
	  
	  // If the maximum clearance we have is less than have
	  // the acceptable clearance, move backwards for
	  // one second, then turn around and go the other direction
          timedMove(MOV_BACK, 1000); // back up for one second  
          moveRotate(-180); // turn around

        } else {

	  // The maximum clearance was more than half the acceptable
	  // clearance. Go right or left depending on which had the
	  // most clearance
          if (leftDistance > rightDistance) {
            moveRotate(-90);
          } else {
            moveRotate(90);   
	  }

        }                  
      } 
    }
  }   
}

/**
   the following is based on loop code from myRobotEdge
   robot checks for edge and moves to avoid
*/
void avoidEdge() {
   if (sensesObstacle(OBST_FRONT_EDGE)) {

     Serial.println("left and right sensors detected edge");
     timedMove(MOV_BACK, 300);
     moveRotate(120);
     while (sensesObstacle(OBST_FRONT_EDGE)) {
       moveStop(); // stop motors if still over cliff
     }

   } else if (sensesObstacle(OBST_LEFT_EDGE)) {

     Serial.println("left sensor detected edge");
     timedMove(MOV_BACK, 100);
     moveRotate(30);

   } else if (sensesObstacle(OBST_RIGHT_EDGE)) {

     Serial.println("right sensor detected edge");
     timedMove(MOV_BACK, 100);
     moveRotate(-30); 

   }
}
