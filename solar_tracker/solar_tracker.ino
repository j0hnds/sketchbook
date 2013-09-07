
#include <Servo.h> // Include the Servo Library

// Create the Servo objects. These guys control the
// actual physical servos. The values for the servos
// will start at 90 and range between 0 and 180

Servo vertical;
int verticalValue = 90; // Initial value of 90

Servo horizontal;
int horizontalValue = 90; // Initial value of 90

// Set up the initial pin connections for the LDRs
// name = analogpin
int ldrLT = 0; // LDR top left
int ldrRT = 1; // LDR top right (I think this should be left down)
int ldrLD = 2; // LDR down left (I think this should be right top)
int ldrRD = 3; // LDR down right

// Set up the digital pin assignments
int horizontalServoPin = 9;
int verticalServoPin = 10;

// Set up some values for the delay time and tolerance;
// Change these values to suit your taste
int delayTime = 100;
int tolerance = 20;

void setup() {
  Serial.begin(9600);
  
  // Set up the Servo connections 
  horizontal.attach(horizontalServoPin);
  vertical.attach(verticalServoPin);
}

int determineNextValue(int currentValue, int diffValue) {
  if (diffValue > 0) {
    currentValue++;
  } else {
    currentValue--;
  }
  
  // Clamp the value between 0 and 180
  if (currentValue > 180) {
    currentValue = 180;
  } else if (currentValue < 0) {
    currentValue = 0;
  }
  
  return currentValue;
}

void loop() {
  // Read the current values of the LDRs
  int vLT = analogRead(ldrLT); // Top Left
  int vRT = analogRead(ldrRT); // Top Right
  int vLD = analogRead(ldrLD); // Down Left
  int vRD = analogRead(ldrRD); // Down Right
  
  Serial.print("vLT = "); Serial.println(vLT);
  Serial.print("vRT = "); Serial.println(vRT);
  Serial.print("vLD = "); Serial.println(vLD);
  Serial.print("vRD = "); Serial.println(vRD);
  
  // Calculate the average values for the four "sides"
  int avgTop = (vLT + vRT) / 2;
  int avgDown = (vLD + vRD) / 2;
  int avgLeft = (vLT + vLD) / 2;
  int avgRight = (vRT + vRD) / 2;
  
  
  // Determine the difference between the averages
  int diffVertical = avgDown - avgTop;
  // int diffVertical = avgTop - avgDown;
  int diffHorizontal = avgLeft - avgRight;
  
  Serial.print("diffVertical = "); Serial.println(diffVertical);
  Serial.print("diffHorizontal = "); Serial.println(diffHorizontal);
  
  if (abs(diffVertical) > tolerance) {
    // The difference is greater than the tolerance. We can
    // go ahead and move the vertical servo
    verticalValue = determineNextValue(verticalValue, diffVertical);
    vertical.write(verticalValue);
  }
  
  if (abs(diffHorizontal) > tolerance) {
    // The difference is greater than the tolerance. We can
    // go ahead and move the horizontal servo
    horizontalValue = determineNextValue(horizontalValue, diffHorizontal);
    horizontal.write(horizontalValue);
  }
  Serial.print("verticalValue = "); Serial.println(verticalValue);
  Serial.print("horizontalValue = "); Serial.println(horizontalValue);
  
  delay(delayTime);
}
