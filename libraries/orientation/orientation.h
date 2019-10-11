#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <imumaths.h>
#include <Arduino.h>
// Possible vector values can be:
// - VECTOR_ACCELEROMETER - m/s^2
// - VECTOR_MAGNETOMETER  - uT
// - VECTOR_GYROSCOPE     - rad/s
// - VECTOR_EULER         - degrees
// - VECTOR_LINEARACCEL   - m/s^2
// - VECTOR_GRAVITY       - m/s^2
class orientation {
public:
	imu::Quaternion quaternion; //Gets quaternion orientation of sensor.
	imu::Vector<3> position = imu::Vector<3>(0, 0, 0);
	orientation() {};
	void setup();
	void loop();
	String serialize();
};