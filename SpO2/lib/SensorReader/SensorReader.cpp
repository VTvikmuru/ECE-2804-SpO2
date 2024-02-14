#include <SensorReader.h>

SensorReader::SensorReader(int pin) : dynamic(false), threshold(0) {
    // Check if pin number is valid
    if (pin < A0 || pin > A5) {
        // If invalid pin number, A0
        Serial.println("Invalid pin number, default pin A0.");
        this->pin = A0;
    } else {
        this->pin = pin;
    }
}

SensorReader::SensorReader(int pin, boolean dynamic) : dynamic(dynamic), threshold(0) {
    // Check if pin number is valid 
    if (pin < A0 || pin > A5) {
        // If invalid pin number, A0
        Serial.println("Invalid pin number, default pin A0.");
        this->pin = A0;
    } else {
        this->pin = pin;
    }
}

SensorReader::SensorReader(int pin, int threshold) : dynamic(false), threshold(threshold) {
    // Check if pin number is valid 
    if (pin < A0 || pin > A5) {
        // If invalid pin number, A0
        Serial.println("Invalid pin number, default pin A0.");
        this->pin = A0;
    } else {
        this->pin = pin;
    }
}

SensorReader::~SensorReader() {
    // Destructor 
}

// Performs analog read
int SensorReader::readSensorValue() {
    return analogRead(pin);
}