#include "orientation.h"
#include "RoverGPS.h"

class kalmanFilter {
	public:
		imu::Vector<2> stateTrans = imu::Vector<2>(0, 0); //State transition matrix. Matrix that holds our initial and desired state. Position/Velocity.

		orientation orient;
		RoverGPS roverGPS;

		void loop();
		void setup();
		void debug();
};