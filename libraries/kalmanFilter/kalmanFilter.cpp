#include "kalmanFilter.h"

void kalmanFilter::setup() {
	roverGPS.setup();
	orient.setup();
	calibrate();
}

void kalmanFilter::loop() {
	orient.loop();
	roverGPS.loop();
	orient.serialize();
	//debug();
}

void kalmanFilter::calibrate() {
	int i = 0;
	for (; i < 1000; i++) {
		orient.calibrate();
		roverGPS.loop();

		averageCalibration.x() += orient.acceleration.x();
		averageCalibration.y() += orient.acceleration.y();
		averageCalibration.z() += orient.acceleration.z();
		delay(60);
	}
	averageCalibration = averageCalibration*(1.0 / i);
}

void kalmanFilter::debug() {
	//Prints the GPS data. Absolute position.
	Serial.println(" GPS DATA ");
	Serial.println(roverGPS.position.x());
	Serial.println(roverGPS.position.y());
	Serial.println("GPS SPEED: ");
	Serial.println(roverGPS.speed);
	//Prints the accelerometer data.
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

}