/***************************************************
 
 Class to help with using ILI9341 displays, with PWM controlled brightnes.
 Display uses SPI to communicate, and this class does not use the RST pin.


 Written by Vikram Muruganandam, 2024
****************************************************/

#ifndef DisplayHandler_h
#define DisplayHandler_h

#include <Arduino.h>

#define TFT_DC 9
#define TFT_CS 10

enum dataDisplay{
    graph = 1,
    line = 2,
};

class DisplayHandler
{
public:

    DisplayHandler(unsigned int * Array, unsigned int * arrayLength, unsigned int * arrayLastIndex, int displayPin);
    //DisplayHandler(int8_t CS, int8_t DC);
    ~DisplayHandler();

    void drawTest();
    void handlerBegin();
    void setDisplayBrightness(int brightness);
    void turnOnDisplay();
    void turnOffDisplay();
    void drawData(dataDisplay dataType, int drawWidth, int drawHeight);
    

private:
    int displayPin = 0;
    // The PWM voltage for analog write is 5V. 
    // This is HIGHER than its specification voltage.
    // However, the display will still work at higher values.
    unsigned int displayBrightness = 10; 

    Adafruit_ILI9341 tft =  Adafruit_ILI9341(TFT_CS, TFT_DC);
    // //Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

    unsigned int * dataArrayLength = nullptr;
    unsigned int * dataArray = nullptr;
    unsigned int * dataArrayUpdated = nullptr;

    void drawDataGraph(int drawWidth, int drawHeight);
    void drawDataLine(int drawWidth, int drawHeight);

};

DisplayHandler::DisplayHandler(unsigned int * Array, unsigned int * arrayLength, unsigned int * arrayIndex, int Pin)
{
    dataArray = Array;
    dataArrayLength = arrayLength;
    dataArrayUpdated = arrayIndex;
    displayPin = Pin;
}

void DisplayHandler::setDisplayBrightness(int Brightness)
{
    displayBrightness = Brightness;
    analogWrite(displayPin, displayBrightness);
}

void DisplayHandler::turnOnDisplay()
{
    analogWrite(displayPin, displayBrightness);
}

void DisplayHandler::turnOffDisplay()
{
    analogWrite(displayPin, LOW);
}

void DisplayHandler::handlerBegin()
{
    tft.begin();
    pinMode(displayPin, OUTPUT);
    analogWrite(displayPin, displayBrightness);
}

void DisplayHandler::drawTest()
{
    turnOffDisplay();
    tft.fillScreen(ILI9341_BLACK);
    yield();
    tft.drawCircle(ILI9341_TFTWIDTH/2, ILI9341_TFTHEIGHT/2, ILI9341_TFTWIDTH/5, ILI9341_RED);
    yield();
    tft.fillCircle(ILI9341_TFTWIDTH/2, ILI9341_TFTHEIGHT/2, (ILI9341_TFTWIDTH/5) - 1, ILI9341_WHITE);
    yield();
    tft.drawFastHLine((ILI9341_TFTWIDTH - (2*ILI9341_TFTWIDTH/5))/2, ILI9341_TFTHEIGHT/2, 2*ILI9341_TFTWIDTH/5 , ILI9341_GREEN);
    yield();
    tft.setCursor((ILI9341_TFTWIDTH/2), (ILI9341_TFTHEIGHT/2) + (ILI9341_TFTWIDTH/5 + 30));
    tft.println("Display POST.\n");
    turnOnDisplay();
    delay(3000);
    tft.println("Done.");
    turnOffDisplay();
    tft.fillScreen(ILI9341_BLACK);
    turnOnDisplay();
}

void DisplayHandler::drawData(dataDisplay dataType, int drawWidth, int drawHeight)
{
    if (dataType == dataDisplay::graph)
    {
        drawDataGraph(drawWidth, drawHeight);
    }
    if (dataType == dataDisplay::line)
    {
        drawDataLine(drawWidth, drawHeight);
    }
    
}

void DisplayHandler::drawDataGraph(int width, int height)
{
    //tft.fillScreen(ILI9341_BLACK);
    // auto width = ILI9341_TFTWIDTH;
    // auto height = ILI9341_TFTHEIGHT;

    int xOffset = 0;
    int yOffset = 0;
    int maxDatapoint = 1023;

    int barWidth = width / (*dataArrayLength);

    int l = (*dataArrayUpdated);
    //Serial.println(l);

        for (int i = 0; i < barWidth; i++)
        {
            //Serial.println("line 2");
            tft.drawFastVLine((barWidth*l)+i, 0, height, ILI9341_RED);
            tft.drawFastVLine((barWidth*l)+i+xOffset, yOffset, (int)(height*((float)(*(dataArray+l))/maxDatapoint)), ILI9341_GREEN);
            //Serial.println((barWidth*l)+i+xOffset);
           //tft.drawFastVLine((barWidth*l)+i, 0,ILI9341_TFTHEIGHT, ILI9341_GREEN);
        }
}

void DisplayHandler::drawDataLine(int width, int height)
{
    int xOffset = 0;
    int yOffset = 0;

    int maxDatapoint = 1023;

    int barWidth = width / (*dataArrayLength);

    int l = (*dataArrayUpdated);
    //Serial.println(l);

    for (int i = 0; i < barWidth; i++)
    {
        //Serial.println("line 2");
        tft.drawFastVLine((barWidth*l)+i, 0, height, ILI9341_RED);

        int drawHeight = (int)(height*((float)(*(dataArray+l))/maxDatapoint));
        //tft.drawFastVLine((barWidth*l)+i+xOffset, yOffset, (int)(height*((float)(*(dataArray+l))/maxDatapoint)), ILI9341_GREEN);
        tft.drawFastHLine((barWidth*l)+i+xOffset, drawHeight, barWidth, ILI9341_GREEN);
        tft.drawFastHLine((barWidth*l)+i+xOffset, drawHeight+1, barWidth, ILI9341_GREEN);
        tft.drawFastHLine((barWidth*l)+i+xOffset, drawHeight+2, barWidth, ILI9341_GREEN);
    }
}

DisplayHandler::~DisplayHandler()
{

}

#endif