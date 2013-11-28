// -*- c -*-
/****************************
 IR reflectance sensor code   
****************************/

// this version only has left and right sensors
const byte NBR_SENSORS = 2;

// analog pins for sensors
const byte IR_SENSOR[NBR_SENSORS] = { 0, 1 }; 

int irSensorAmbient[NBR_SENSORS]; // sensor value with no reflection
int irSensorReflect[NBR_SENSORS]; // value considered detecting an object
int irSensorEdge[NBR_SENSORS];    // value considered detecting an edge

boolean isDetected[NBR_SENSORS] = { false, false }; // set true if object detected

const int irReflectThreshold = 10; // % level below ambient to trigger reflection
const int irEdgeThreshold    = 90; // % level above ambient to trigger edge

void irSensorBegin() {
  for (int sensor = 0; sensor < NBR_SENSORS; sensor++) {
    irSensorCalibrate(sensor);
  }
}

/**
  Calibrate for ambient light 
*/
void irSensorCalibrate(byte sensor) {
  int ambient = analogRead(IR_SENSOR[sensor]); // get ambient level
  irSensorAmbient[sensor] = ambient; 

  // precalculate the levels for object and edge detection  
  irSensorReflect[sensor] = (ambient * (long)(100 - irReflectThreshold)) / 100;
  irSensorEdge[sensor]    = (ambient * (long)(100 + irEdgeThreshold)) / 100; 
}

/**
  Returns true if an object reflection detected on the given sensor
  the sensor parameter is the index into the sensor array
*/
boolean irSensorDetect(int sensor) {
  boolean result = false; // default value

  int value = analogRead(IR_SENSOR[sensor]); // get IR light level

  if (value <= irSensorReflect[sensor]) {
    // Object detected (lower value means more reflection)
    result = true; 
    if (! isDetected[sensor]) { 
      // Only print on initial detection
      Serial.print(locationString[sensor]);         
      Serial.println(" object detected");
    }
  }

  isDetected[sensor] = result; 
  return result;
}

boolean irEdgeDetect(int sensor) {
  boolean result = false; // default value

  int value = analogRead(IR_SENSOR[sensor]); // get IR light level

  if (value >= irSensorEdge[sensor]) {
    // edge detected (higher value means less reflection)
    result = true; 
    if (isDetected[sensor] == false) { 
      // only print on initial detection
      Serial.print(locationString[sensor]);         
      Serial.println(" edge detected");
    }
  }

  isDetected[sensor] = result; 
  return result;
}
