/***** Global Defines ****/ 

// defines for locations of sensors
enum {
  SENSE_IR_LEFT,
  SENSE_IR_RIGHT,
  SENSE_IR_CENTER
};
/* const int SENSE_IR_LEFT  = 0; */
/* const int SENSE_IR_RIGHT = 1; */
/* const int SENSE_IR_CENTER = 2; */

// defines for directions
enum {
  DIR_LEFT,
  DIR_RIGHT,
  DIR_CENTER 
};

/* const int DIR_LEFT   = 0; */
/* const int DIR_RIGHT  = 1; */
/* const int DIR_CENTER = 2; */
    
const char* locationString[] = { // labels for debug
  "Left", 
  "Right", 
  "Center"}; 
// see http://arduino.cc/en/Reference/String for more on character string arrays

// obstacles constants 
enum {
  OBST_NONE,        // no obstacle detected
  OBST_LEFT_EDGE,   // left edge detected 
  OBST_RIGHT_EDGE,  // right edge detected
  OBST_FRONT_EDGE,  // edge detect at both left & right sensors
  OBST_FRONT,       // obstacle in front
  OBST_REAR         // obstacle behind 
};
/* const int OBST_NONE       = 0;  // no obstacle detected */
/* const int OBST_LEFT_EDGE  = 1;  // left edge detected  */
/* const int OBST_RIGHT_EDGE = 2;  // right edge detected */
/* const int OBST_FRONT_EDGE = 3;  // edge detect at both left & right sensors */
/* const int OBST_FRONT      = 4;  // obstacle in front */
/* const int OBST_REAR       = 5;  // obstacle behind  */
const char* obstacles[] = { // Debug labels
  "None", 
  "Left Edge",
  "Right Edge", 
  "Front Edge", 
  "Front",
  "Rear"
};

const int LED_PIN = 13;

/// move states:
enum {
  MOV_LEFT, 
  MOV_RIGHT, 
  MOV_FORWARD, 
  MOV_BACK, 
  MOV_ROTATE, 
  MOV_STOP
};

const char* states[] = { // Debug Labels
  "Left", 
  "Right", 
  "Forward", 
  "Back", 
  "Rotate", 
  "Stop"
};

/**** End of Global Defines ****************/
