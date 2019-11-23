#include "kalmanFilter.h"

void kalmanFilter::setup() {
	roverGPS.setup();
	orient.setup();
	orient.callibrateCompass();
	calibrate();
}

void kalmanFilter::loop() {
	orient.loop();
	roverGPS.loop();
	//roverGPS.position.x() = 0;
	//roverGPS.position.y() = 0;
	roverGPS.destination.x() = 0;
	roverGPS.destination.y() = 0;

	roverGPS.calculateBearing(roverGPS.position.x(), roverGPS.position.y(),
							  roverGPS.destination.x(), roverGPS.destination.y() );

	roverGPS.calculateDistance(roverGPS.position.x(), roverGPS.position.y(),
								roverGPS.destination.x(), roverGPS.destination.y() );

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
	Serial.println(" GPS DATA ");
	Serial.println(roverGPS.position.x());
	Serial.println(roverGPS.position.y());
	Serial.println(" DESTINATION ");
	Serial.println(roverGPS.destination.x());
	Serial.println(roverGPS.destination.y());
	Serial.println(" DISTANCE ");
	Serial.println(String(roverGPS.distance, 8));
	Serial.println(" Bearing, Heading, Incline ");
	Serial.println(orient.heading);
	Serial.println(orient.incline);
	Serial.println(roverGPS.bearing);
	Serial.println("GPS SPEED: ");
	Serial.println(roverGPS.speed);
	//Prints the accelerometer data.
	Serial.println(" POSITION DATA ");
	Serial.println(orient.position.x());
	Serial.println(orient.position.y());
	Serial.println(orient.position.z());
}