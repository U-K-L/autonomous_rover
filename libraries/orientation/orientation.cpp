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
	sensors_event_t accel, comp;
	bno.getEvent(&accel, Adafruit_BNO055::VECTOR_LINEARACCEL);
	//bno.getEvent(&comp, Adafruit_BNO055::VECTOR_MAGNETOMETER);

	//computeCompass(&comp);
	ax = acceleration.x();
	ay = acceleration.y();
	az = acceleration.z();
	computeAcceleration(&accel);
	trapezoidalIntegration();
	//computeVelocity();
	//computePosition();
	//computeMagnitude();
}

void orientation::calibrate() {
	sensors_event_t event;
	bno.getEvent(&event, Adafruit_BNO055::VECTOR_LINEARACCEL);
	double x, y, z;
	x = event.acceleration.x;
	y = event.acceleration.y;
	z = event.acceleration.z;
	
	IIRFilter(x, y, z);

	acceleration.x() = xf;
	acceleration.y() = yf;
	acceleration.z() = zf;
}

void orientation::callibrateCompass() {
	uint8_t system, gyro, accel, mag = 0;
	while (system != 3)
	{
		bno.getCalibration(&system, &gyro, &accel, &mag);
		Serial.print("CALIBRATION: Sys=");
		Serial.print(system, DEC);
		Serial.print(" Gyro=");
		Serial.print(gyro, DEC);
		Serial.print(" Accel=");
		Serial.print(accel, DEC);
		Serial.print(" Mag=");
		Serial.println(mag, DEC);
		delay(100);
	}
	Serial.println(""); Serial.println("Calibrated");
	delay(2000);
}

void orientation::computeCompass(sensors_event_t * event) {
	heading = 180 + toDegrees(quaternion.toEuler().x());
	incline = -toDegrees(quaternion.toEuler().z());
}

void orientation::computeAcceleration(sensors_event_t * event) {
	double x, y, z;
	acceleration.x() = 0;
	acceleration.y() = 0;
	acceleration.z() = 0;

	x = event->acceleration.x;
	y = event->acceleration.y;
	z = event->acceleration.z;
	IIRFilter(x, y, z);

	if( abs(x) >= abs(( averageCalibration.x()* filterStrength )))
		acceleration.x() = xf;


	if (abs(y) >= abs((averageCalibration.y()* (filterStrength*0.8))))
		acceleration.y() = yf;


	if (abs(z) >= abs((averageCalibration.z()* (filterStrength*0.2))))
		acceleration.z() = zf;

}

void orientation::computeVelocity() {

	
	/*
	//Use Euler integration to compute velocity.
	velocity.x() += acceleration.x();
	velocity.y() += acceleration.y();
	velocity.z() += acceleration.z();
	*/
}

void orientation::computePosition() {
	//Use Euler integration to compute position.
	float tol = 0.0001f;
	position.x() += velocity.x();
	position.y() += velocity.y();
	position.z() += velocity.z();
}


float orientation::computeMagnitude() {
	//Use Euler integration to compute position.


	position.x() += velocity.x();
	position.y() += velocity.y();
	position.z() += velocity.z();
	float x = position.x();
	float y = position.y();
	float z = position.z();

	float magnitude = 0;

	magnitude = sqrt(x*x + y*y + z*z);
	return magnitude;

}

void orientation::trapezoidalIntegration() {

	float tolerance = 0.03;

	if (abs(acceleration.x()) < tolerance) {
		velocity.x() = 0;
	}
	if (abs(acceleration.y()) < tolerance) {
		velocity.y() = 0;
	}
	if (abs(acceleration.z()) < tolerance) {
		velocity.z() = 0;
	}
	
	float basepositionx = position.x();
	float basepositiony = position.y();
	float basepositionz = position.z();



	float basevelocityx = abs(velocity.x());
	float basevelocityy = abs(velocity.y());
	float basevelocityz = abs(velocity.z());

	float baseaccelerationx = ax;
	float baseaccelerationy = ay;
	float baseaccelerationz = az;

	float accelerationx = acceleration.x();
	float accelerationy = acceleration.y();
	float accelerationz = acceleration.z();

	
	
	velocity.x() = basevelocityx + baseaccelerationx + ((accelerationx - baseaccelerationx) / 2);
	velocity.y() = basevelocityy + baseaccelerationy + ((accelerationy - baseaccelerationy) / 2);
	velocity.z() = basevelocityz + baseaccelerationz + ((accelerationz - baseaccelerationz) / 2);

	velocity.x() *= 0.01;
	velocity.y() *= 0.01;
	velocity.z() *= 0.01;

	position.x() = basepositionx + basevelocityx + ((abs(velocity.x()) - basevelocityx) / 2);
	position.y() = basepositiony + basevelocityy + ((abs(velocity.y()) - basevelocityy) / 2);
	position.z() = basepositionz + basevelocityz + ((abs(velocity.z()) - basevelocityz) / 2);

	position.x() *= 0.01;
	position.x() *= 0.01;
	position.x() *= 0.01;

}

//Infinite Impulse Response
void orientation::IIRFilter(double x, double y, double z) {
	double k = 0.9;
	xf = k * xf + (1.0 - k) * x;
	yf = k * yf + (1.0 - k) * y;
	zf = k * zf + (1.0 - k) * z;
}

String orientation::serialize() {
	double x = position.x();
	double y = position.y();
	double z = position.z();
	String value = (String)"roverP" + String(x, 6) + "," + String(y, 6) + "," + String(z, 6);
	Serial.println(value);
	x = velocity.x();
	y = velocity.y();
	z = velocity.z();
	value = (String)"roverV" + String(x, 6) + "," + String(y, 6) + "," + String(z, 6);
	Serial.println(value);
	x = quaternion.x();
	y = quaternion.y();
	z = quaternion.z();
	double w = quaternion.w();
	value = (String)"roverQ" + String(x, 6) + "," + String(y, 6) + "," + String(z, 6) + "," + String(w, 6);
	Serial.println(value);
	return value;
}
