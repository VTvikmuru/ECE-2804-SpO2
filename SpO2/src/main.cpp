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

#define TFT_DC 9
#define TFT_CS 10
#define MUX_OUTPUT_PIN A0
#define LED1 2
#define LED2 3

//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
SensorReader sensor(A0, 205);
//DisplayHandler handler(&sensor.maxArrayLength, &sensor.waveformArray);
DisplayHandler handler(&sensor.waveformArray[0], &sensor.maxArrayLength, &sensor.lastWritten, 6);

//Intitialize functions for multiplexer implementation 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensor.activateLED(LED1);     // activate LED1 initially
  sensor.selectSignalPath(0);   // Select signal path 0

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

  handler.drawData(dataDisplay::line, ILI9341_TFTWIDTH, 2*ILI9341_TFTHEIGHT/3, 0, 0, "");
  handler.drawData(dataDisplay::text, 0, 2, 35, 20, String(sensor.getFreqSec()) + "Hz,\n   " + String((int)(sensor.getFreqSec() * 60)) + "Bpm");
  handler.drawData(dataDisplay::line, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);  
   
    // Read sensor value
    sensor.readSensorValue();

    sensor.deactivateLED(LED2); // Deactivate LED2
    sensor.activateLED(LED1);   // Activate LED1
    sensor.selectSignalPath(0);     // Select path 0
}

