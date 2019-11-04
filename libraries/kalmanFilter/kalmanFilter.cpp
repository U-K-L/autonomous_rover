#include "kalmanFilter.h"

void kalmanFilter::setup() {
	roverGPS.setup();
	orient.setup();
	//orient.callibrateCompass(); //Turned off for now!!!
	calibrate();
}

void kalmanFilter::loop() {
	orient.loop();
	roverGPS.loop();
	//orient.serialize();
	debug();
}

void kalmanFilter::calibrate() {
	int i = 0;
	for (; i < 250; i++) {
		orient.calibrate();
		roverGPS.loop();

		averageCalibration.x() += abs(orient.acceleration.x());
		averageCalibration.y() += abs(orient.acceleration.y());
		averageCalibration.z() += abs(orient.acceleration.z());
		delay(20);
	}
	averageCalibration = averageCalibration*(1.0 / i);
	orient.xf = 0;
	orient.yf = 0;
	orient.zf = 0;
	orient.averageCalibration.x() = averageCalibration.x();
	orient.averageCalibration.y() = averageCalibration.y();
	orient.averageCalibration.z() = averageCalibration.z();
}

void kalmanFilter::debug() {
	//Prints the GPS data. Absolute position.
	Serial.println(orient.heading);
	Serial.println(orient.incline);
	Serial.println(" GPS DATA ");
	Serial.println(roverGPS.position.x());
	Serial.println(roverGPS.position.y());
	Serial.println("GPS SPEED: ");
	Serial.println(roverGPS.speed);
	//Prints the accelerometer data.
	/*
	Serial.println(" POSITION DATA ");
	Serial.println(orient.position.x());
	Serial.println(orient.position.y());
	Serial.println(orient.position.z());
	//Prints the orentation data
	Serial.println(" ORIENTATION DATA ");
	Serial.println(orient.quaternion.x());
	Serial.println(orient.quaternion.y());
	Serial.println(orient.quaternion.z());
	// RAW ACCELERATION
	Serial.println(" ACCELERATION DATA ");
	Serial.println(String(averageCalibration.x(), 6));
	Serial.println(String(averageCalibration.y(), 6));
	Serial.println(String(averageCalibration.z(), 6));
	*/
}