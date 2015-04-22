#ifndef HvacScout_h
#define HvacScout_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class HvacScout
{
	public:
        // constructor:
		HvacScout(String strName, uint8_t pinRx, uint8_t pinTx, uint8_t pinKey, uint8_t vcc);
        void startSPP();
        void start();
        // setters:
		void setName(String name);
		void setTemperature(uint8_t value);
		void setPower(bool newState);
		void setQuiet(bool newState);
		void setDelayTime(int seconds);
        // getters:
		String getName();
		uint8_t getTemperature();
		bool getPower();
		bool getQuiet();
		uint16_t getDelayTime();
        // attributes:
        SoftwareSerial* serial;
	protected:
        // methods:
        bool readResultFromSerial(String expected, char terminator);
        // attributes:
        uint8_t pinKey;
        uint8_t vcc;
        String name;
        uint8_t temperature;
        bool power;
        bool quiet;
        uint32_t delayTime;
};

#endif