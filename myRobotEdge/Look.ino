/***************************************************
 Code to look for obstacles
 ***************************************************/
 
void lookBegin() {
  irSensorBegin(); // Initialize sensors
};

// returns true if the given obstacle is detected
boolean lookForObstacle(int obstacle) {
  switch (obstacle) {
    case OBST_FRONT_EDGE:
      return irEdgeDetect(SENSE_IR_LEFT) && irEdgeDetect(SENSE_IR_RIGHT);
    case OBST_LEFT_EDGE:
      return irEdgeDetect(SENSE_IR_LEFT);
    case OBST_RIGHT_EDGE:
      return irEdgeDetect(SENSE_IR_RIGHT);
  }
  return false;
}

// function to check if robot can continue moving when taking
// evasive action. Returns true if robot is not blocked when
// moving to avoid obstacles.
// This placeholder version always returns true
boolean checkMovement() {
  return true;
}
