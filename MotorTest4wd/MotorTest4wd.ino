/********************************************************
 * MotorTest4wd.ino
 *
 * Initial motor test for 4WD
 * robot rotates clockwise
 * (Left motors driven forward, right backward)
 */
const int LED_PIN = 13;
 
const int speed = 60; // Percent of maximum speed

#include <AFMotor.h> // adafruit motor shield library (modified)
AF_DCMotor Motor_Left_Front(4, MOTOR34_1KHZ);  // Motor 4
AF_DCMotor Motor_Right_Front(3, MOTOR34_1KHZ); // Motor 3
AF_DCMotor Motor_Left_Rear(1, MOTOR12_1KHZ);   // Motor 1
AF_DCMotor Motor_Right_Rear(2, MOTOR12_1KHZ);  // Motor 2

int pwm;

void setup() {
  Serial.begin(9600);
  
  // Open port while flashing, Needed for Leonardo only.
  blinkNumber(8);
  
  // Scale percent into pwm range (0-255)
  pwm = map(speed, 0, 100, 0, 255);
  Motor_Left_Front.setSpeed(pwm);
  Motor_Right_Front.setSpeed(pwm);
  Motor_Left_Rear.setSpeed(pwm);
  Motor_Right_Rear.setSpeed(pwm);
}

void loop() {
  Serial.println("rotate cw");
  
  Motor_Left_Front.run(FORWARD);
  Motor_Left_Rear.run(FORWARD);
  
  Motor_Right_Front.run(BACKWARD);
  Motor_Right_Rear.run(BACKWARD);
  
  delay(5000); // Run for 5 seconds
  
  Serial.println("stopped");
  
  Motor_Left_Front.run(RELEASE); // Stop the motors
  Motor_Right_Front.run(RELEASE);
  Motor_Left_Rear.run(RELEASE);
  Motor_Right_Rear.run(RELEASE);
  
  delay(5000); // Stop for 5 seconds
}

/**
 * Function to indicate numbers by flashing the built-in
 * LED
 */
void blinkNumber(byte number) {
  pinMode(LED_PIN, OUTPUT); // Enable the LED pin for output
  while (number--) {
    digitalWrite(LED_PIN, HIGH); delay(100);
    digitalWrite(LED_PIN, LOW);  delay(400);
  }
}
