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
