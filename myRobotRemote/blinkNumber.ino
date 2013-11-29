// -*- c -*-
/************************************************************
This module is used to blink a number of times
************************************************************/

/**
   Function to indicate numbers by flashing the built-in LED
*/
void blinkNumber(byte number) {
  pinMode(LED_PIN, OUTPUT); // enable the LED pin for output

  while (number--) {
    digitalWrite(LED_PIN, HIGH); 
    delay(100);
    digitalWrite(LED_PIN, LOW); 
    delay(400);
  }

}
