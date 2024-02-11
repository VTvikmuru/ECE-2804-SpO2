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

 private:

    int inPin;
    bool dynamic;
    int threshold;
}; 

#endif
