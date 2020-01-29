#include "orientation.h"
#include "RoverGPS.h"
#include "Arduino.h"

class kalmanFilter {
	public:
		imu::Vector<2> stateTrans = imu::Vector<2>(0, 0); //State transition matrix. Matrix that holds our initial and desired state. Position/Velocity.
		imu::Vector<3> averageCalibration = imu::Vector<3>(0, 0, 0);

		double tolerance = 1.0;
		orientation orient;
		RoverGPS roverGPS;

		void loop();
		void setup();
		void debug();
		void calibrate();
};