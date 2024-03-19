#ifndef LEDHandler_h
#define LEDHandler_h

#include <Arduino.h>

#define CD405xB_A 5 // Control pin A 
#define CD405xB_B 6 // Control pin B 
#define CD405xB_C 7 // Control pin C 

#define LED1_PIN 2
#define LED2_PIN 3

class LEDHandler {
public:
    LEDHandler(); // Constructor
    void LED1_on(); // Turns on LED1
    void LED2_on(); // Turns on LED2
    void LED1_off(); // Turns off LED1
    void LED2_off(); // Turns off LED2
    void setMuxChannel(uint8_t channel); // Set the channel for the multiplexer
};

LEDHandler::LEDHandler() {
    pinMode(CD405xB_A, OUTPUT);
    pinMode(CD405xB_B, OUTPUT);
    pinMode(CD405xB_C, OUTPUT);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    digitalWrite(CD405xB_A, LOW);
    digitalWrite(CD405xB_B, LOW);
    digitalWrite(CD405xB_C, LOW);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
}

void LEDHandler::setMuxChannel(uint8_t channel) {
    digitalWrite(CD405xB_A, (channel & 0x01) ? HIGH : LOW);
    digitalWrite(CD405xB_B, (channel & 0x02) ? HIGH : LOW);
    digitalWrite(CD405xB_C, (channel & 0x04) ? HIGH : LOW);
}

void LEDHandler::LED1_on() {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW); // only LED1 is on
}

void LEDHandler::LED2_on() {
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED1_PIN, LOW); // only LED2 is on
}

void LEDHandler::LED1_off() {
    digitalWrite(LED1_PIN, LOW); // Turn LED1 off
}

void LEDHandler::LED2_off() {
    digitalWrite(LED2_PIN, LOW); // Turn LED2 off
}

#endif