#include "orientation.h"

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address

void orientation::setup(){
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin())
  {
	  /* There was a problem detecting the BNO055 ... check your connections */
	  Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
	  while (1);
  }
	delay(1000);
	bno.setExtCrystalUse(true);
}

void orientation::loop() {
	quaternion = bno.getQuat();
	sensors_event_t accel;
	bno.getEvent(&accel, Adafruit_BNO055::VECTOR_LINEARACCEL);


	computeAcceleration(&accel);
	computeVelocity();
	computePosition();
}

void orientation::calibrate() {
	sensors_event_t event;
	bno.getEvent(&event, Adafruit_BNO055::VECTOR_LINEARACCEL);
	double x, y, z;
	double k = 0.9;
	x = event.acceleration.x;
	y = event.acceleration.y;
	z = event.acceleration.z;

	xf = k * xf + (1.0 - k) * x;
	yf = k * yf + (1.0 - k) * y;
	zf = k * zf + (1.0 - k) * z;

	acceleration.x() = xf;
	acceleration.y() = yf;
	acceleration.z() = zf;
}

void orientation::computeAcceleration(sensors_event_t * event) {
	double x, y, z;
	x = event->acceleration.x;
	y = event->acceleration.y;
	z = event->acceleration.z;

	acceleration.x() = x;
	acceleration.y() = y;
	acceleration.z() = z;
}

void orientation::computeVelocity() {
	//Use Euler integration to compute velocity.
	velocity.x() += acceleration.x();
	velocity.y() += acceleration.y();
	velocity.z() += acceleration.z();
}

void orientation::computePosition() {
	//Use Euler integration to compute position.
	position.x() += velocity.x();
	position.y() += velocity.y();
	position.z() += velocity.z();
}

String orientation::serialize() {
	double x = acceleration.x();
	double y = acceleration.y();
	double z = acceleration.z();
	String value = (String)"roverP" + String(x, 6) + "," + String(y, 6) + "," + String(z, 6);
	Serial.println(value);
	x = quaternion.x();
	y = quaternion.y();
	z = quaternion.z();
	double w = quaternion.w();
	value = (String)"roverQ" + String(x, 6) + "," + String(y, 6) + "," + String(z, 6) + "," + String(w, 6);
	//Serial.println(value);
	return value;
}
