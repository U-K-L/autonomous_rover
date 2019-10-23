#include "kalmanFilter.h"

void kalmanFilter::setup() {
	roverGPS.setup();
	orient.setup();
}

void kalmanFilter::loop() {
	orient.loop();
	roverGPS.loop();
	debug();
}

void kalmanFilter::debug() {
	//Prints the GPS data. Absolute position.
	Serial.println(" GPS DATA ");
	Serial.println(gps.position.x);
	Serial.println(gps.position.y);
	Serial.println("GPS SPEED: ");
	Serial.print(roverGPS.speed)
	//Prints the accelerometer data.
	Serial.println(" POSITION DATA ");
	Serial.println(orient.position.x);
	Serial.println(orient.position.y);
	Serial.println(orient.position.z);
	//Prints the orentation data
	Serial.println(" ORIENTATION DATA ");
	Serial.println(orient.quaternion.x);
	Serial.println(orient.quaternion.y);
	Serial.println(orient.quaternion.z);
}