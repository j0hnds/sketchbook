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
const char *states[] = { "MoveLeft", "MoveRight", "MoveForward", "MoveBack", "MoveRotate", "MoveStop" };

// Obstacles constants
const int OBST_NONE       = 0; // No obstacle detected
const int OBST_LEFT_EDGE  = 1; // Left edge detected
const int OBST_RIGHT_EDGE = 2; // Right edge detected
const int OBST_FRONT_EDGE = 3; // Edge detected both right/left
const int OBST_FRONT      = 4; // Obstacle in front
const int OBST_REAR       = 5; // Obstacle behind.

const int LED_PIN = 13;
int counter = 0;

enum {
  MOV_LEFT, MOV_RIGHT, MOV_FORWARD, MOV_BACK, MOV_ROTATE, MOV_STOP
};
/*********** End of Global Defines *********************/
