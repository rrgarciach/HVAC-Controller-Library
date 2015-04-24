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
    this->groupId = -1;
    this->temperature = 0;
    this->maxTemperature = 25;
    this->humidity = 0;
    this->power = false;
    this->automatic = false;
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
    this->serial->println(F("AT"));
    delay(500);
    this->serial->println(F("AT+INIT"));
    delay(500);
    digitalWrite(this->vcc, LOW);
    delay(500);
    digitalWrite(this->pinKey, LOW);
    digitalWrite(this->vcc, HIGH);
    this->serial->end();
}
void HvacScout::start()
{
    Serial.print(F("Starting Serial of "));
    Serial.println(this->getName());
    this->serial->begin(9600);
}
void HvacScout::end()
{
    Serial.print(F("Ending Serial of "));
    Serial.println(this->getName());
    this->serial->end();
}
bool HvacScout::readResultFromSerial(String expected, char terminator)
{
    if ( this->serial->available() ) {
        String message;
        char c;
        while ( this->serial->available() ) {
            c = this->serial->read();
			delay(50);
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
void HvacScout::setGroupId(int8_t value)
{
    this->groupId = value;
}
void HvacScout::setTemperature(uint8_t value)
{
    this->temperature = value;
}
void HvacScout::setMaxTemperature(uint8_t value)
{
    this->maxTemperature = value;
}
void HvacScout::setHumidity(uint8_t value)
{
    this->temperature = value;
}
void HvacScout::setPower(bool newState)
{
	this->power = newState;
}
void HvacScout::triggerPower(bool newState)
{
    if (newState == true) {
        this->serial->println(F("turnOn;"));
        if ( readResultFromSerial(F("OK"),';') ) {
			this->power = true;
			Serial.println("OK;");
		}
    } else {
        this->serial->println(F("turnOff;"));
        if ( readResultFromSerial(F("OK"),';') ) {
			this->power = false;
			Serial.println("OK;");
		}
    }
}
void HvacScout::setAutomatic(bool newState)
{
    this->automatic = newState;
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
void HvacScout::changeDelayTime(int seconds)
{
	this->serial->print(F("changeDelayTime:"));
	this->serial->print(seconds);
	this->serial->println(";");
	// I commented these lines due that te response is taking a lot of time
	// and this conditional is not receiving the answer at time failling into ERROR:0
//	if ( readResultFromSerial(F("OK"),';') ) {
//		Serial.println("OK;");
//	} else {
//		Serial.println("ERROR:0;");
//	}
}
// getters:
String HvacScout::getName()
{
    return this->name;
}
int8_t HvacScout::getGroupId()
{
	return this->groupId;
}
uint8_t HvacScout::getTemperature()
{
    return this->temperature;
}
uint8_t HvacScout::getMaxTemperature()
{
    return this->maxTemperature;
}
uint8_t HvacScout::getHumidity()
{
    return this->humidity;
}
bool HvacScout::getPower()
{
    return this->power;
}
bool HvacScout::getAutomatic()
{
    return this->automatic;
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
