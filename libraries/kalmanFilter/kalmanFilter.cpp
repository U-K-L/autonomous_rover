#include "kalmanFilter.h"

void kalmanFilter::setup() {
	//roverGPS.setup();
	orient.setup();
	//orient.callibrateCompass();
	calibrate();
}

void kalmanFilter::loop() {
	orient.loop();
	/*
	roverGPS.loop();
	roverGPS.destination.x() = 0;
	roverGPS.destination.y() = 0;
	//X is latitude.
	//Y is longitude.
	//Latitude is East/West.
	//Longitude is North/South.
	roverGPS.position.y() = 40.176335;
	roverGPS.position.x() =   -75.275412;
	
	roverGPS.destination.y() = 40.176548;
	roverGPS.destination.x() =  -75.276715;

	roverGPS.calculateBearing(roverGPS.position.x(), roverGPS.position.y(),
							  roverGPS.destination.x(), roverGPS.destination.y() );

	roverGPS.calculateDistance(roverGPS.position.x(), roverGPS.position.y(),
								roverGPS.destination.x(), roverGPS.destination.y() );

	//orient.serialize();
	debug();
	*/
	//orient.serialize();
	//Serial.println(orient.computeMagnitude());
}

void kalmanFilter::calibrate() {
	int i = 0;
	for (; i < 250; i++) {
		orient.calibrate();
		//roverGPS.loop();

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
	/*
	Serial.println(" GPS DATA ");
	Serial.println(roverGPS.position.x());
	Serial.println(roverGPS.position.y());
	Serial.println(" DESTINATION ");
	Serial.println(roverGPS.destination.x());
	Serial.println(roverGPS.destination.y());
	Serial.println(" DISTANCE ");
	Serial.println(String(roverGPS.distance, 8));
	Serial.println(" Bearing, Heading, Incline ");
	*/
	Serial.println(orient.heading);
	//Serial.println(orient.incline);
	Serial.println(roverGPS.bearing);
	//Serial.println("GPS SPEED: ");
	//Serial.println(roverGPS.speed);
	//Prints the accelerometer data.
	Serial.println(" POSITION DATA ");
	Serial.println(orient.position.x());
	Serial.println(orient.position.y());
	Serial.println(orient.position.z());
}