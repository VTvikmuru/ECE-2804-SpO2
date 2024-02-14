#ifndef SensorReader_h
#define SensorReader_h

#include <Arduino.h>

class SensorReader {
public:
    // Constructors and Destructors
    SensorReader(int pin);
    SensorReader(int pin, boolean dynamic);
    SensorReader(int pin, int threshold);
    ~SensorReader();

    // Reads sensor value 
    int getSensorValue();
    int getPeriod();
    void readSensorValue();
    float getFreqSec();
    
    //debug
    void drawSensorValue();
    void drawPeriodInfo();

 private:

    int inPin;
    bool dynamic;
    int threshold;

    int sensorValue;

    // Debug
    int lastGraphx = 0;
    bool arrayfull = false;

    bool previousState = LOW;
    bool firstHigh = false;
    int last_threshold_time = 0;
    //int period[10] = {0};
    int period = 0;
    void verifyBeat();
    int getPeriodAvg();
    int verifyCall = 0;
    int periodarr[10];
}; 

#endif
