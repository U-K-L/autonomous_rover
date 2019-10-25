#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <imumaths.h>
#include <Arduino.h>
#include <math.h>
// Possible vector values can be:
// - VECTOR_ACCELEROMETER - m/s^2
// - VECTOR_MAGNETOMETER  - uT
// - VECTOR_GYROSCOPE     - rad/s
// - VECTOR_EULER         - degrees
// - VECTOR_LINEARACCEL   - m/s^2
// - VECTOR_GRAVITY       - m/s^2
class orientation {
public:
	Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
	imu::Quaternion quaternion; //Gets quaternion orientation of sensor.
	imu::Vector<3> position = imu::Vector<3>(0, 0, 0);
	imu::Vector<3> velocity = imu::Vector<3>(0, 0, 0);
	imu::Vector<3> acceleration = imu::Vector<3>(0, 0, 0);
	imu::Vector<3> averageCalibration = imu::Vector<3>(0, 0, 0);
	double filterStrength = 8.25; //Filter calibration Strength.
	double xf, yf, zf;
	orientation() {};
	void setup();
	void loop();
	void calibrate();
	void computeAcceleration(sensors_event_t * event);
	void computeVelocity();
	void computePosition();
	void IIRFilter(double x, double y, double z);
	String serialize();
};