#include "RoverGPS.h"
void RoverGPS::setup() {
	gps = Adafruit_GPS(&GPSSerial);
	gps.begin(9600);
	gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	gps.sendCommand(PGCMD_ANTENNA);
	delay(1000);
}

void RoverGPS::loop() {

	// read data from the GPS in the 'main loop'
	gps.read();
	// if you want to debug, this is a good time to do it!
	// if a sentence is received, we can check the checksum, parse it...
	if (gps.newNMEAreceived()) {
		// a tricky thing here is if we print the NMEA sentence, or data
		// we end up not listening and catching other sentences!
		// so be very wary if using OUTPUT_ALLDATA and trying to print out data
		gps.lastNMEA(); // this also sets the newNMEAreceived() flag to false
		if (!gps.parse(gps.lastNMEA())) // this also sets the newNMEAreceived() flag to false
			return; // we can fail to parse a sentence in which case we should just wait for another
	}
	// if millis() or timer wraps around, we'll just reset it
	if (timer > millis()) timer = millis();

	// approximately every 1 seconds or so, print out the current stats
	if (millis() - timer > 1000) {
		timer = millis(); // reset the timer
		if (gps.fix) {

			position.x() = gps.longitudeDegrees;//gps.latitude;
			position.y() = gps.latitudeDegrees;//gps.longitude;
			speed = gps.speed;
		}

		calculateBearing(position.x(), position.y(), destination.x(), destination.y()); //Recalculates every 1 seconds.
	}

	
}

double RoverGPS::calculateBearing(double latStart, double lonStart, double latDest, double lonDest) {
	latStart = toRadians(latStart);
	latDest = toRadians(latDest);
	lonStart = toRadians(lonStart);
	lonDest = toRadians(lonDest);
	double y = sin(lonDest - lonStart)*cos(latDest);
	double x = cos(latStart)*sin(latDest) - sin(latStart)*cos(latDest)*cos(lonDest-lonStart);
	double bear = toDegrees(atan2(y, x));
	bearing = fmodf((360 + bear), 360.00); //ensures that degree is between 0 and 360 just like heading.
	return bearing;
}

//Calculates using haversine formula.
double RoverGPS::calculateDistance(double latStart, double lonStart, double latDest, double lonDest) {


	latStart = toRadians(latStart);
	lonStart = toRadians(lonStart);

	latDest = toRadians(latDest);
	lonDest = toRadians(lonDest);

	double phiStart = latStart;
	double phiDest = latDest;

	double deltaLat = (latDest - latStart);
	double deltaLon = (lonDest - lonStart);


	double alpha = sin(deltaLat / 2)*sin(deltaLat / 2)+
				   
				   cos(phiStart)*cos(phiDest)*
				   
				   sin(deltaLon / 2)*sin(deltaLon / 2);

	double c = 2 * atan2(sqrt(alpha), sqrt(1-alpha));
	distance = (EarthRadius * c)*1000;
	return distance;
}

void RoverGPS::serialize() {
	String value = (String)"GPS_ROVER" + String(position.y(), 8) + "," + String(position.x(), 8);
	Serial.println(value);
	Serial.print("GPS_SPEED");
	Serial.println(speed);
}