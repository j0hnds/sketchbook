// -*- c -*-
// This sketch is to read from the galvanized
// nail moisture meter and light the LED with the
// output. We will be writing the output of the 
// A0 pin (moisture meter) to the LED (D1)
// 
// See the schematic in the sketchbook for how
// to wire this up.

const int LED = 9;
const int METER = 0; // Analog pin 0

int val = 0; // The value to be read from the meter

void setup() {
  Serial.begin(9600); // Set up the serial line for 9600 baud
  
  pinMode(LED, OUTPUT); // Set up LED for writing
  // pinMode(METER, INPUT); // This is automatic
}

void loop() {
  val = analogRead(METER);
  
  Serial.println(val);
  
  analogWrite(LED, val / 4);
  
  delay(100); // Wait a bit
}
