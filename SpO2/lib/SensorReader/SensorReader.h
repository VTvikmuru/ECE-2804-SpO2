#ifndef SensorReader_h
#define SensorReader_h

#include <Arduino.h>

#define maxWaveformStorageLength 240
#define dataWriteInterval 4

#define MUX_SELECT_PIN0 5
#define MUX_SELECT_PIN1 6
#define MUX_SELECT_PIN2 7

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
    void drawArrayInfo();

    // Waveform data
    unsigned int lastWritten = 0;
    unsigned int waveformArray[maxWaveformStorageLength] = {0};
    unsigned int maxArrayLength = maxWaveformStorageLength;

    void activateLED(int ledpin);    //activates LED
    void deactivateLED(int ledpin);  //deactivates LED
    void selectSignalPath(int path); //selects signal path for mux

 private:

    int inPin;
    bool dynamic;
    int threshold;
    unsigned int arrayIndex = 0;
    int muxSelectPin;  //Initialize mux select pin

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

<<<<<<< Updated upstream
    int waveformWriteInterval = 0;
};
=======
    
    //unsigned int arrayLength = 0;
    
    void selectMuxInput(int input);   //Function to select input for mux
}; 
>>>>>>> Stashed changes

#endif