#include <Arduino.h>
#include <SensorReader.h>

// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

SensorReader sensor(A0);

void loop() {
  // Sensor must be read and its value stored constantly
  sensor.readSensorValue();
  // Draws the read sensor value to serial monitor as graph
  sensor.drawSensorValue();
}

// put function definitions here:
