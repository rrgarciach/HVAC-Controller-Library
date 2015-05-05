#ifndef ScoutGroup_h
#define ScoutGroup_h

#include "Arduino.h"
#include "HvacScout.h"
#include "SoftwareSerial.h"

class ScoutGroup
{
	public:
        // constructor:
		ScoutGroup(String strName);

        // setters:
		void updateState(HvacScout* scouts[], int arraySize);
		void setName(String name);
		void setTemperature(uint8_t value);
		void setMaxTemperature(uint8_t value);
		void setPower(bool newState);
		void triggerPower(bool newState, HvacScout* scouts[], int arraySize);
		void setAutomatic(bool newState);
		void setQuiet(bool newState);
		void setDelayTime(int seconds);
		void changeDelayTime(int seconds, HvacScout* scouts[], int arraySize);
        // getters:
		String getName();
		uint8_t getTemperature();
		uint8_t getMaxTemperature();
		bool getPower();
		bool getAutomatic();
		bool getQuiet();
		uint16_t getDelayTime();
		String groupToJson(int groupId);
	protected:
        // attributes:
        String name;
        uint8_t count;
		uint8_t temperature;
        uint8_t maxTemperature;
		bool power;
        bool automatic;
        bool quiet;
        uint32_t delayTime;
};

#endif