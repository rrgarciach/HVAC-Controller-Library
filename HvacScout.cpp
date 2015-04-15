#include "Arduino.h"
#include "HvacScout.h"
#include <SoftwareSerial.h>

HvacScout::HvacScout(String name, uint8_t pinRx, uint8_t pinTx)
{
	// slave Bluetooth socket to communicate with Scout device:
    // For HC-05 Bluetooth module's TX goes to arduino's TX (in this case, pin 3).
    this->btSerial = new SoftwareSerial(pinRx,pinTx);
    this->name = name;
    this->temperature = 0;
    this->power = false;
    this->quiet = false;
    this->delayTime = 900000; // 15 minutes
}
// settings:
void HvacScout::setPower(bool newState)
{
    this->power = newState;
}
void HvacScout::setDelayTime(uint16_t seconds)
{
    this->delayTime = (seconds * 1000);
}
// getters:
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
    return (this->delayTime / 1000);
}
