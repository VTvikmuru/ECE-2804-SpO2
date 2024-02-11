#include <SensorReader.h>

SensorReader::SensorReader(int pin) : inPin(pin), dynamic(false), threshold(0) {
    // Check if pin number is valid
    if (pin < 0 || pin > 13) {
        // If invalid pin number
        Serial.println("Invalid pin number!");
    }
}

SensorReader::SensorReader(int pin, boolean dynamic) : inPin(pin), dynamic(dynamic), threshold(0) 
{
    // Check if pin number is valid 
    if (pin < 0 || pin > 13) {
        // if invalid pin number
        Serial.println("Invalid pin number!");
    }
}

SensorReader::SensorReader(int pin, int threshold) : inPin(pin), dynamic(false), threshold(threshold)
{

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