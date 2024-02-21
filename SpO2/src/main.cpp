#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include <Arduino.h>
#include <DisplayHandler.h>
#include <SensorReader.h>

#define TFT_DC 9
#define TFT_CS 10
// TFT_LED = 6
// SensorIn = A0

//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
SensorReader sensor(A0, 500);
//DisplayHandler handler(&sensor.maxArrayLength, &sensor.waveformArray);
DisplayHandler handler(&sensor.waveformArray[0], &sensor.maxArrayLength, &sensor.lastWritten, 6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  handler.handlerBegin();
  
  handler.setDisplayBrightness(150);
  handler.drawTest();
}

void loop() {

  // Sensor must be read and its value stored constantly
  sensor.readSensorValue();
  // Draws the read sensor value to serial monitor as graph
  //sensor.drawSensorValue();
  //sensor.drawPeriodInfo();

  //sensor.drawArrayInfo();

  handler.drawData(dataDisplay::line, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
}
