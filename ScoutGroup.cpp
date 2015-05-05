#include "Arduino.h"
#include "HvacScout.h"
#include "ScoutGroup.h"
#include <SoftwareSerial.h>

// constructor:
ScoutGroup::ScoutGroup(String name)
{
    this->count = 0;
    this->name = name;
    this->temperature = 0;
    this->maxTemperature = 25;
    this->power = false;
    this->automatic = false;
    this->quiet = false;
    this->delayTime = 900000; // 15 minutes by default.
}
void ScoutGroup::updateState(HvacScout* scouts[], int arraySize)
{
	uint8_t aveTemp = 0;
	for (int i = 0 ; i < arraySize ; i++) {
		// If slot is NOT NULL:
		if (scouts[i] != NULL) {
			this->count++;
		}
		// get temperature:
		aveTemp += scouts[i]->getTemperature();
	}
	aveTemp /= this->count;
	this->setTemperature(aveTemp);
}
// setters:
void ScoutGroup::setName(String name)
{
    this->name = name;
}
void ScoutGroup::setTemperature(uint8_t value)
{
    this->temperature = value;
}
void ScoutGroup::setMaxTemperature(uint8_t value)
{
    this->maxTemperature = value;
}
void ScoutGroup::setPower(bool newState)
{
	this->power = newState;
}
void ScoutGroup::triggerPower(bool newState, HvacScout* scouts[], int arraySize)
{
	for (int i = 0 ; i < arraySize ; i++) {
		// If slot is NOT NULL:
		if (scouts[i] != NULL) {
			if (newState == true) {
				scouts[i]->serial->println(F("turnOn;"));
//				if ( readResultFromSerial(F("OK"),';') ) {
//					this->power = true;
//					Serial.println("OK;");
//				}
			} else {
				scouts[i]->serial->println(F("turnOff;"));
//				if ( readResultFromSerial(F("OK"),';') ) {
//					this->power = false;
//					Serial.println("OK;");
//				}
			}
		}
	}
}
void ScoutGroup::setAutomatic(bool newState)
{
    this->automatic = newState;
}
void ScoutGroup::setQuiet(bool newState)
{
    this->quiet = newState;
}
void ScoutGroup::setDelayTime(int seconds)
{
	this->delayTime = seconds;
	this->delayTime *= 1000;
}
void ScoutGroup::changeDelayTime(int seconds, HvacScout* scouts[], int arraySize)
{
	for (int i = 0 ; i < arraySize ; i++) {
		// If slot is NOT NULL:
		if (scouts[i] != NULL) {
			scouts[i]->serial->print(F("changeDelayTime:"));
			scouts[i]->serial->print(seconds);
			scouts[i]->serial->println(";");
			this->setDelayTime(seconds);
		}
	}
}
// getters:
String ScoutGroup::getName()
{
    return this->name;
}
uint8_t ScoutGroup::getTemperature()
{
    return this->temperature;
}
uint8_t ScoutGroup::getMaxTemperature()
{
    return this->maxTemperature;
}
bool ScoutGroup::getPower()
{
    return this->power;
}
bool ScoutGroup::getAutomatic()
{
    return this->automatic;
}
bool ScoutGroup::getQuiet()
{
    return this->quiet;
}
uint16_t ScoutGroup::getDelayTime()
{
    int seconds = this->delayTime / 1000;
    return ( seconds );
}
String ScoutGroup::groupToJson(int groupId) {
	String jsonObj;
	jsonObj += F("{");
	jsonObj += F("\"id\":");
	jsonObj += groupId;
	jsonObj += F(",");
	jsonObj += F("\"name\":\"");
	jsonObj += this->getName();
	jsonObj += F("\",");
	jsonObj += F("\"temperature\":");
	jsonObj += this->getTemperature();
	jsonObj += F(",");
	jsonObj += F("\"maxTemperature\":");
	jsonObj += this->getMaxTemperature();
	jsonObj += F(",");
	jsonObj += F("\"power\":");
	jsonObj += this->getPower();
	jsonObj += F(",");
	jsonObj += F("\"automatic\":");
	jsonObj += this->getAutomatic();
	jsonObj += F(",");
	jsonObj += F("\"quiet\":");
	jsonObj += this->getQuiet();
	jsonObj += F(",");
	jsonObj += F("\"delayTime\":");
	jsonObj += this->getDelayTime();
	jsonObj += F("}");
	return jsonObj;
}
