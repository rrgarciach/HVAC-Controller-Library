#include "Arduino.h"
#include "HvacScout.h"
#include <SoftwareSerial.h>

// constructor:
HvacScout::HvacScout(String name, uint8_t pinRx, uint8_t pinTx, uint8_t pinKey, uint8_t vcc)
{
	// slave Bluetooth socket to communicate with Scout device:
    // For HC-05 Bluetooth module's TX goes to arduino's TX (in this case, pin 3).
    this->serial = new SoftwareSerial(pinRx,pinTx);
    this->pinKey = pinKey;
    this->vcc = vcc;
    pinMode(this->pinKey, OUTPUT);
    pinMode(this->vcc, OUTPUT);
    this->name = name;
    this->temperature = 0;
    this->power = false;
    this->quiet = false;
    this->delayTime = 900000; // 15 minutes by default.
}
void HvacScout::startSPP()
{
    this->serial->begin(38400);
    Serial.println(F("Starting SPP"));
    digitalWrite(this->vcc, LOW);
    digitalWrite(this->pinKey, HIGH);
    digitalWrite(this->vcc, HIGH);
    delay(500);
    this->serial->println("AT");
    delay(500);
    this->serial->println("AT+INIT");
    delay(500);
    digitalWrite(this->vcc, LOW);
    delay(500);
    digitalWrite(this->pinKey, LOW);
    digitalWrite(this->vcc, HIGH);
    this->serial->end();
}
void HvacScout::start()
{
    Serial.println(F("Starting Serial"));
    this->serial->begin(9600);
}
bool HvacScout::readResultFromSerial(String expected, char terminator)
{
    if ( this->serial->available() ) {
        String message;
        char c;
        while ( this->serial->available() ) {
            c = this->serial->read();
            if (c == terminator) break;
            message += c;
        }
        if (message == expected) {
            return true;
        }
        return false;
    }
}
// setters:
void HvacScout::setName(String name)
{
    this->name = name;
}
void HvacScout::setTemperature(uint8_t value)
{
    this->temperature = value;
}
void HvacScout::setPower(bool newState)
{
    if (newState == true) {
        this->serial->println("turn_on;");
        if ( readResultFromSerial("OK",';') ) this->power = true;
    } else {
        this->serial->println("turn_off;");
        if ( readResultFromSerial("OK",';') ) this->power = false;
    }
}
void HvacScout::setQuiet(bool newState)
{
    this->quiet = newState;
}
void HvacScout::setDelayTime(int seconds)
{
    this->delayTime = seconds;
    this->delayTime *= 1000;
}
// getters:
String HvacScout::getName()
{
    return this->name;
}
uint8_t HvacScout::getTemperature()
{
    return this->temperature;
}
bool HvacScout::getPower()
{
    return this->power;
}
bool HvacScout::getQuiet()
{
    return this->quiet;
}
uint16_t HvacScout::getDelayTime()
{
    int seconds = this->delayTime / 1000;
    return ( seconds );
}
