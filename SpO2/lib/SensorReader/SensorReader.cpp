#include <SensorReader.h>

SensorReader::SensorReader(int pin) : pin(pin), dynamic(false), threshold(0) {
    // Check if pin number is valid
    if (pin < 0 || pin > 13) {
        // If invalid pin number
        Serial.println("Invalid pin number!");
    
    }
    // Initialize analog write with the pin
    analogWrite(this->pin, pin); 
}

SensorReader::SensorReader(int pin, boolean dynamic) : pin(pin), dynamic(dynamic), threshold(0) {
    // Check if pin number is valid 
    if (pin < 0 || pin > 13) {
        // if invalid pin number
        Serial.println("Invalid pin number!");
    }
    // Initialize analog write with the pin
    analogWrite(this->pin, pin); 
}

SensorReader::SensorReader(int pin, int threshold) : pin(pin), dynamic(false), threshold(threshold) {
    // Initialize analog write with the pin
    analogWrite(this->pin, pin); 
}

SensorReader::~SensorReader() {
    
}

