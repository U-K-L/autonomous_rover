#pragma once
#include <imumaths.h>
#include <Arduino.h>
#include <Adafruit_GPS.h>


#define GPSSerial Serial1
#define GPSECHO false

class RoverGPS {
public:
	Adafruit_GPS gps;
	imu::Vector<3> destination;
	uint32_t timer = millis();
	imu::Vector<2> position = imu::Vector<2>(0, 0);
	double speed;

	RoverGPS(){};
	void setup();
	void loop();
	void serialize();

};
