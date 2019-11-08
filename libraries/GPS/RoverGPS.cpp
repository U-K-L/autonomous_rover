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

	// approximately every 2 seconds or so, print out the current stats
	if (millis() - timer > 2000) {
		timer = millis(); // reset the timer
		if (gps.fix) {
			serialize();
			//position.x() = gps.latitude;
			//position.y() = gps.longitude;
			speed = gps.speed;
		}

		calculateBearing(position.x(), position.y(), destination.x(), destination.y()); //Recalculates every 2 seconds.
	}

	
}

double RoverGPS::calculateBearing(double latStart, double lonStart, double latDest, double lonDest) {
	latStart = latStart * (PI / 180);
	latDest = latDest * (PI / 180);
	lonStart = lonStart * (PI / 180);
	lonDest = lonDest * (PI / 180);
	double y = sinf(lonDest - lonStart)*cosf(latDest);
	double x = cosf(latStart)*sinf(latDest) - sinf(latStart)*cosf(latDest)*cosf(lonDest-lonStart);
	double bear = atan2(y, x)*(180 / PI);
	bearing = fmodf((360 + bear), 360.00); //ensures that degree is between 0 and 360 just like heading.
	return bearing;
}

void RoverGPS::serialize() {
	String value = (String)"GPS_ROVER " + String(gps.latitude, 8) + "," + String(gps.longitude, 8);
	Serial.println(value);
}