#ifndef SensorReader_h
#define SensorReader_h

#include <Arduino.h>

class SensorReader {
private:
    int pin;
    boolean dynamic;
    int threshold;

public:
    SensorReader(int pin);
    SensorReader(int pin, boolean dynamic);
    SensorReader(int pin, int threshold);
    ~SensorReader();

// Reads sensor value 
 int readSensorValue();
}; 

#endif
