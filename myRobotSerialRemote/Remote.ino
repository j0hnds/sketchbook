// -*- c -*-
/************************************************************
 robot remote commands

 This version is for serial commands
************************************************************/

// Command constants 

const char MOVE_FORWARD = 'f'; // move forward
const char MOVE_BACK    = 'b'; // move backward
const char MOVE_LEFT    = 'l'; // move left
const char MOVE_RIGHT   = 'r'; // move right 
const char PIVOT_CCW    = 'C'; // rotate 90 degrees CCW
const char PIVOT_CW     = 'c'; // rotate 90 degrees CW
const char PIVOT        = 'p'; // rotation angle (minus rotates CCW)
const char HALT         = 'h'; // stop moving

// not used in this example
const char MOVE_SPEED        = 's'; 
const char MOVE_SLOWER       = 'v'; // reduce speed 
const char MOVE_FASTER       = '^'; // increase speed 

int commandState = MOV_STOP;    // what robot is told to do

void remoteService() {
  if (Serial.available() ) {
    int cmd = Serial.read();
    processCommand(cmd);   
  }  
}

void changeCmdState(int newState) {
  if (newState != commandState) {
    Serial.print("Changing Cmd state from "); Serial.print( states[commandState]);
    Serial.print(" to "); Serial.println(states[newState]);
    commandState = newState;
  } 
}

void processCommand(int cmd) {
  int val = 0;
  if (cmd == PIVOT || cmd == SPEED) {
    val =  Serial.parseInt();
  }
  processCommand(cmd, val);
}

void processCommand(int cmd, int val) {
  byte speed;
  Serial.write(cmd); // echo

  switch(cmd) { 
  case MOVE_LEFT: 
    changeCmdState(MOV_LEFT);    
    moveLeft();      
    break;

  case MOVE_RIGHT: 
    changeCmdState(MOV_RIGHT);   
    moveRight();     
    break;

  case MOVE_FORWARD: 
    changeCmdState(MOV_FORWARD); 
    moveForward();
    break;

  case MOVE_BACK: 
    changeCmdState(MOV_BACK);    
    moveBackward();  
    break;

  case PIVOT_CCW: 
    changeCmdState(MOV_ROTATE);  
    moveRotate(-90); 
    break;

  case PIVOT_CW: 
    changeCmdState(MOV_ROTATE);  
    moveRotate(90);  
    break;

  case PIVOT: 
    changeCmdState(MOV_ROTATE);  
    moveRotate(val); 
    break; 

  case HALT: 
    changeCmdState(MOV_STOP);    
    moveStop();      
    break;

  case SPEED: 
    speed = val;             
    moveSetSpeed(speed); 
    break;
  }    
}
