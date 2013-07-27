#include "DHT.h"

#define DHTPIN 2 // The arduino pin we're connected to

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  // Serial.println("DHT11 Test!");
  
  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds.
  // Sensor readings may also be up to 2 seconds 'old'
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // Check if return values are valid, if they are NaN
  // (not a number), then something went wrong
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print(h);
    Serial.print(",");
    Serial.println(t);
    // Serial.print("Humidity: ");
    // Serial.print(h);
    // Serial.print(" %\t");
    // Serial.print("Temperature: ");
    // Serial.print(t);
    // Serial.println(" *C");
  }
}
