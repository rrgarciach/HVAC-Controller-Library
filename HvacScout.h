#ifndef HvacScout_h
#define HvacScout_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class HvacScout
{
	public:
        // constructor:
		HvacScout(String strName, uint8_t pinRx, uint8_t pinTx, uint8_t pinKey);
        // setters:
		void setPower(bool newState);
		void setDelayTime(uint16_t seconds);
        // getters:
		uint8_t getTemperature();
		bool getPower();
		bool getQuiet();
		uint16_t getDelayTime();
	private:
        SoftwareSerial* btSerial;
        uint8_t pinKey;
        String name;
        uint8_t temperature;
        bool power;
        bool quiet;
        uint16_t delayTime;
};

#endif