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

    // Write to storage array to store waveform information
    waveformArray[arrayIndex] = sensorValue;
    lastWritten = arrayIndex;
    arrayIndex++;
    if (arrayIndex >= maxWaveformStorageLength)
    {
        arrayIndex = 0;
    }
    
    
    if (previousState == LOW)
    {
        if (sensorValue > threshold)
        {
            previousState = HIGH;
            if (!firstHigh)
            {   
                firstHigh = true;
                last_threshold_time = millis();
            }else{
                period = millis() - last_threshold_time;
                verifyBeat();
                firstHigh = false;
            } 
        }
    }else{
        if (sensorValue < threshold)
        {
            previousState = LOW;
        }
    }
}

void SensorReader::verifyBeat()
{
    if(period <= 20 || period > 1400)
    {
        return;
    }
    if (verifyCall < 9)
    {
        periodarr[verifyCall] = period;
        verifyCall++;
    }else{
        periodarr[9] = period;
        verifyCall = 0;
    }
}

int SensorReader::getPeriodAvg()
{   
    int sum = 0;

    for (int i = 0; i < 10; i++)
    {
        sum = sum + periodarr[i];
    }
    sum = sum/10;
    return (sum);
}

int SensorReader::getPeriod()
{
    return period;
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

void SensorReader::drawPeriodInfo()
{
    Serial.print(" Period: ");
    Serial.print(period);

    Serial.print(" Sensor: ");
    Serial.println(sensorValue);

    if (arrayfull == true)
    {
        Serial.print(" Period Average: ");
        Serial.print(getPeriodAvg());
        Serial.print(" Average Frequency: ");
        Serial.println(getFreqSec());
    }
    else{
        arrayfull = true;
        for (int i = 0; i < 10; i++)
        {
            if (periodarr[i] == 0)
            {
                arrayfull = false;
            }   
        }    
    }
}

float SensorReader::getFreqSec()
{
    //int avg = getPeriodAvg();
    return (1000*(1/((float)getPeriodAvg())));
}

void SensorReader::drawArrayInfo()
{
    Serial.println("Values Start:");
    for (int i = 0; i < maxArrayLength; i++)
    {
        Serial.println(waveformArray[i]);
    }  
    Serial.println("Values END\n"); 
}
//void SensorReader::getFrequency()