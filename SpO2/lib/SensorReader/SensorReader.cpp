#include <SensorReader.h>

SensorReader::SensorReader(int pin) : dynamic(false), threshold(0) {
    // Check if pin number is valid
    if (pin < A0 || pin > A5) {
        // If invalid pin number, A0
        Serial.println("Invalid pin number, default pin A0.");
        pin = A0;
    } else {
        pin = pin;
    }
}

SensorReader::SensorReader(int pin, boolean dynamic) : dynamic(dynamic), threshold(0) {
    // Check if pin number is valid 
    if (pin < A0 || pin > A5) {
        // If invalid pin number, A0
        Serial.println("Invalid pin number, default pin A0.");
        pin = A0;
    } else {
        pin = pin;
    }
}

SensorReader::SensorReader(int pin, int threshold) : dynamic(false), threshold(threshold) {
    // Check if pin number is valid 
    if (pin < A0 || pin > A5) {
        // If invalid pin number, A0
        Serial.println("Invalid pin number, default pin A0.");
        pin = A0;
    } else {
        pin = pin;
    }
}

SensorReader::~SensorReader() 
{

}

// Perform analog read
int SensorReader::getSensorValue() 
{
    return sensorValue;
}

void SensorReader::readSensorValue()
{
    sensorValue = analogRead(inPin);
}

void SensorReader::drawSensorValue()
{   
    int graphx = sensorValue / 10;

    Serial.print((millis())/1000);

    for (int i = 1; i < graphx; i++)
    {
        Serial.print(' ');
    }

    if (graphx > lastGraphx)
    {
        Serial.println('\\');
    }else{
        if (graphx < lastGraphx)
        {
            Serial.println('/');
        }
        else{
            Serial.println('|');
        }
    }
    
    lastGraphx = graphx;
}