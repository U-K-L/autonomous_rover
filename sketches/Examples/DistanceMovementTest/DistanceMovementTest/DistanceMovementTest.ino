#include <DriveTrain.h> //Deals with spinning the wheels of the rover.
#include "coroutine.h"
#include <kalmanFilter.h>
kalmanFilter kalman;
DriveTrain drive;
coroutine driveCoroutine;

void setup() {
  // put your setup code here, to run once:
  driveCoroutine.setup(1000);
  drive.setup();
  kalman.setup();
  Serial.begin(9600);

  
}

void loop() {
  kalman.loop();
  
  
  // put your main code here, to run repeatedly:

  forwards(0);
  delay(10);
}

void forwards(int speed) {
  // left side
  drive.spinAt(25, speed);
  drive.spinAt(21, speed);
  drive.spinAt(20, speed);

  // right side
  drive.spinAt(27, -speed);
  drive.spinAt(22, -speed);
  drive.spinAt(28, -speed);
}

void Rightspin() {

  // Front
  drive.moveTo(23, 50);
  drive.moveTo(29, 50);

  // Back
  drive.moveTo(24, -50);
  drive.moveTo(26, -50);
}

void Leftspin() {

  // Front
  drive.moveTo(23, -50);
  drive.moveTo(29, -50);

  // Back
  drive.moveTo(24, 50);
  drive.moveTo(26, 50);
}

void reset() {
  /* Turn right */
  // front
  drive.moveTo(23, 0);
  drive.moveTo(29, 0);

  // back
  drive.moveTo(24, 0);
  drive.moveTo(26, 0);

  if(driveCoroutine.readyState){
      /* Turn Left */
    // front
    drive.moveTo(23, 0);
    drive.moveTo(29, 0);
  
    // back
    drive.moveTo(24, 0);
    drive.moveTo(26, 0);
  }
}
