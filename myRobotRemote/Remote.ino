// -*- c -*-
/************************************************************
 robot remote commands
************************************************************/

#include <IRremote.h>                // IR remote control library

IRrecv irrecv(irReceivePin);

decode_results results;

// IR remote keycodes:

// Command constants 

const char MOVE_FORWARD = 'f'; // move forward
const char MOVE_BACK    = 'b'; // move backward
const char MOVE_LEFT    = 'l'; // move left
const char MOVE_RIGHT   = 'r'; // move right 
const char PIVOT_CCW    = 'C'; // rotate 90 degrees CCW
const char PIVOT_CW     = 'c'; // rotate 90 degrees CW
const char PIVOT        = 'p'; // rotation angle (minus rotates CCW)
const char HALT         = 'h'; // stop

// not used in this example
const char MOVE_SPEED        = 's'; 
const char MOVE_SLOWER       = 'v'; // reduce speed 
const char MOVE_FASTER       = '^'; // increase speed 

// IR remote keycodes:replace this with codes for your remote
// These are the codes from the Gray RCA remote
const long IR_MOVE_FORWARD = 50190375;
const long IR_MOVE_BACK    = 50198535;
const long IR_MOVE_LEFT    = 50165895;
const long IR_MOVE_RIGHT   = 50157735;
const long IR_PIVOT_CW     = 50149575;
const long IR_PIVOT_CCW    = 50194455;
const long IR_HALT         = 50137335;
// See text for procedure for obtaining codes.
/* const long IR_MOVE_FORWARD = 1064; */
/* const long IR_MOVE_BACK    = 3112; */
/* const long IR_MOVE_LEFT    = 1128; */
/* const long IR_MOVE_RIGHT   = 2152; */
/* const long IR_PIVOT_CW     = 136; */
/* const long IR_PIVOT_CCW    = 1160; */
/* const long IR_HALT         = 2216; */

int commandState = MOV_STOP;    // what robot is told to do

void remoteBegin(byte irPin) {
  irrecv.enableIRIn(); // Start the receiver
}

void remoteService() {
  if (irrecv.decode(&results)) {
    if (results.decode_type != UNKNOWN) {
      //Serial.println(results.value); // uncomment to see raw result
      convertIrToCommand(results.value);
    }
    irrecv.resume(); // Receive the next value
  }  

  // additional support for serial commands
  if(Serial.available() ) {
    int cmd = Serial.read();
    processCommand(cmd);   
  }  
}

void convertIrToCommand(long value) {
  {
    switch(value) {
    case  IR_MOVE_LEFT    :  processCommand(MOVE_LEFT);    break;
    case  IR_MOVE_RIGHT   :  processCommand(MOVE_RIGHT);   break;
    case  IR_MOVE_FORWARD :  processCommand(MOVE_FORWARD); break;
    case  IR_MOVE_BACK    :  processCommand(MOVE_BACK);    break;
    case  IR_PIVOT_CCW    :  processCommand(PIVOT_CCW);    break;
    case  IR_PIVOT_CW     :  processCommand(PIVOT_CW);     break;
    case  IR_HALT         :  processCommand(HALT);         break;
//    case  IR_SLOWER       :  processCommand(SLOWER);       break;
//    case  IR_FASTER       :  processCommand(FASTER);       break;
    }  
  }
} 
 
void changeCmdState(int newState) {
  if(newState != commandState) {
    Serial.print("Changing Cmd state from "); Serial.print( states[commandState]);
    Serial.print(" to "); Serial.println(states[newState]);
    commandState = newState;
  } 
}

void processCommand(int cmd) {
  int val = 0;
  if( cmd == MOVE_SPEED) {
    val =  Serial.parseInt();
  } else if( cmd == PIVOT) {
    val =  Serial.parseInt();
  }
  processCommand(cmd, val);
}

void processCommand(int cmd, int val) {
  byte speed;

  //Serial.write(cmd); // uncomment to echo
  switch(cmd) { 
  case MOVE_LEFT    : changeCmdState(MOV_LEFT);    moveLeft();      break;
  case MOVE_RIGHT   : changeCmdState(MOV_RIGHT);   moveRight();     break;
  case MOVE_FORWARD : changeCmdState(MOV_FORWARD); moveForward();   break;
  case MOVE_BACK    : changeCmdState(MOV_BACK);    moveBackward();  break;
  case PIVOT_CCW    : changeCmdState(MOV_ROTATE);  moveRotate(-90); break;
  case PIVOT_CW     : changeCmdState(MOV_ROTATE);  moveRotate(90);  break;
  case PIVOT        : changeCmdState(MOV_ROTATE);  moveRotate(val); break; 
  case HALT         : changeCmdState(MOV_STOP);    moveStop();      break;
  case MOVE_SPEED   : speed = val;    moveSetSpeed(speed);         break;
//   case SLOWER       : moveSlower(speedIncrement);                  break;
//   case FASTER       : moveFaster(speedIncrement);                  break;
  case '\r' : case '\n': break; // ignore cr and lf
  default :  Serial.print('['); Serial.write(cmd); Serial.println("] Ignored");  break;
  }    
}
