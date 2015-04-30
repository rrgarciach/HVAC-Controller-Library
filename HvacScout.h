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
        void end();
		void ping();
		void resetPing();
        // setters:
		void setName(String name);
		void setGroupId(int8_t value);
		void setTemperature(uint8_t value);
		void setMaxTemperature(uint8_t value);
		void setPower(bool newState);
		void triggerPower(bool newState);
		void setHumidity(uint8_t value);
		void setAutomatic(bool newState);
		void setQuiet(bool newState);
		void setDelayTime(int seconds);
		void changeDelayTime(int seconds);
        // getters:
		String getName();
		bool getStatus();
		int8_t getGroupId();
		uint8_t getTemperature();
		uint8_t getMaxTemperature();
		uint8_t getHumidity();
		bool getPower();
		bool getAutomatic();
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
        bool status;
        int pingCount;
        int8_t groupId;
        uint8_t temperature;
        uint8_t maxTemperature;
        uint8_t humidity;
        bool power;
        bool automatic;
        bool quiet;
        uint32_t delayTime;
};

#endif