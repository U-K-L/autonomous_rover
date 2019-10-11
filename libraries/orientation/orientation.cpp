#include "orientation.h"

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);

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
	serialize();
}

String orientation::serialize() {
	double x = position.x();
	double y = position.y();
	double z = position.z();
	String value = (String)"roverP" + String(x, 6) + "," + String(y, 6) + "," + String(z, 6);
	Serial.println(value);
	x = quaternion.x();
	y = quaternion.y();
	z = quaternion.z();
	double w = quaternion.w();
	value = (String)"roverQ" + String(x, 6) + "," + String(y, 6) + "," + String(z, 6) + "," + String(w, 6);
	Serial.println(value);
	return value;
}
