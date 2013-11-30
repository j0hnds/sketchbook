// -*- c -*-
/******************************************************************************
 LED starts flashing when voltage drops below warning level.
 
 Mark space ratio increases from 10% to 50% as voltage decreases from warning
 to critical.
 
 Robot shuts down when battery level below critical and LED flashes SOS.
 ******************************************************************************/
 
// Thresholds are cell millivolts times number of cells.
const int batteryFull     = 1500 * 5;
const int batteryWarning  = 1100 * 5;
const int batteryCritical = 1000 * 5;

int batteryMonitorPin;      // Analog pin to monitor
int chargerDetectPin = -1;  // Pin goes open circuit when charger connected, default is no pin
int blinkPin;               // LED pin to flash

void batteryBegin(int monitorPin, int ledPin) {
  batteryMonitorPin = monitorPin;
  blinkPin = ledPin;
  pinMode(blinkPin, OUTPUT);
}

/**
   Version for charger detection.
 */
void batteryBegin(int monitorPin, int ledPin, int chargerPin) {
  batteryBegin(monitorPin, ledPin);
  chargerDetectPin = chargerPin;
  pinMode(chargerDetectPin, INPUT_PULLUP); // Connect pull-up resistor
}

void batteryCheck() {
  int mv = batteryMv(batteryMonitorPin); // Get battery level in millivolts
  Serial.print("mv = ");
  Serial.print(mv);
  if (chargerDetectPin >= 0 && digitalRead(chargerDetectPin) == HIGH) {
    // Got here if charger detect is enabled and charger is plugged in
    while (digitalRead(chargerDetectPin) == HIGH) {
      // While charger is plugged in
      moveStop();
      mv = batteryMv(batteryMonitorPin);
      Serial.print(", charger detected, voltage = ");
      int percent = map(mv, batteryCritical, batteryFull, 50, 100);
      percent = constrain(percent, 0, 100);
      Serial.println(percent);
      flash(percent, blinkPin);
    }
  } else {
    if (mv < batteryCritical) {
      Serial.println("Critical");
      // Shut down the robot
      moveStop();
      while (1) {
        flashCritical(blinkPin);
        // Check if the charger is plugged in 
        if (chargerDetectPin >= 0 && digitalRead(chargerDetectPin) == HIGH) {
          return; // Exit if charging
        }
        delay(5000); // Wait 5 seconds
      }
    } else if (mv < batteryWarning) {
      int percent = map(mv, batteryCritical, batteryWarning, 10, 50);
      flash(percent, blinkPin);
    }
  }
  delay(1000);
  Serial.println();
}

/**
   Return the voltage on the given pin in millivolts.
   See text for voltage divider resistor values
 */
int batteryMv(int pin) {
#if defined(__AVR_ATmega32U4__) // Is this a Leonardo board?
  const long INTERNAL_REFERENCE_MV = 2560; // Leo reference is 2.56 volts
#else
  const long INTERNAL_REFERENCE_MV = 1100; // ATmega328 is 1.1 volts
#endif
  const float R1 = 18.0; // Voltage divider values
  const float R2 = 2.2;
  const float DIVISOR = R2 / (R1 + R2);
  
  analogReference(INTERNAL); // Set reference to internal (1.1V)
  analogRead(pin); // Allow the ADC to settle
  delay(10);
  
  int value = 0;
  for (int i=0; i < 8; i++) {
      value = value + analogRead(pin);
  }
  value = value / 8; // Get the average of 8 readings
  int mv = map(value, 0, 1023, 0, INTERNAL_REFERENCE_MV / DIVISOR);
  
  analogReference(DEFAULT); // Set the reference back to default (Vcc)
  analogRead(pin);  // Just to let the ADC settle ready for next reading
  delay(10); // Allow reference to stabilise
  
  return mv;
}

/**
   Flashes SOS in morse code.
 */
void flashCritical(int pin) {
  for (int i = 0; i < 3; i++) {
    flash(20, pin);
  }
  for (int i = 0; i < 3; i++) {
    flash(60, pin);
  }
  for (int i = 0; i < 3; i++) {
    flash(20, pin);
  }
}

/**
   Percent is the percent of on time time (duty cycle)
 */
void flash(int percent, int pin) {
  Serial.print(", flash percent = ");
  Serial.println(percent);
  const int duration = 1000;
  // Blink the LED
  digitalWrite(pin, HIGH);
  int onTime = map(percent, 0, 100, 0, duration);
  delay(onTime);
  digitalWrite(pin, LOW);
  delay(duration - onTime);
}
