#include <DriveTrain.h> //Deals with spinning the wheels of the rover.
#include <kalmanFilter.h> //Gets IMU device for the rover
#include "coroutine.h"

kalmanFilter kalman; //A common library for IMU devices.
DriveTrain drive;
coroutine driveCoroutine;
coroutine kalmanCoroutine;

bool useUntil = false; //Using this until we have better drive code.
enum State {
  ACTIVE,
  UNACTIVE,
  TURN,
  MOVE,
};

State machine;

void setup() {
  // put your setup code here, to run once: 
  kalmanCoroutine.setup(10);
  driveCoroutine.setup(1000);
  drive.setup();
  kalman.setup();
  reset();
  machine = ACTIVE;
  calibrate();
}

void calibrate(){
  uint8_t system, gyro, accel, mag = 0;
  while (system != 3)
  {
    kalman.orient.bno.getCalibration(&system, &gyro, &accel, &mag);
    Serial.print("CALIBRATION: Sys=");
    Serial.print(system, DEC);
    Serial.print(" Gyro=");
    Serial.print(gyro, DEC);
    Serial.print(" Accel=");
    Serial.print(accel, DEC);
    Serial.print(" Mag=");
    Serial.println(mag, DEC);
    delay(100);
    Rightspin();
    forwards(40);
  }
  reset();
  Serial.println(""); Serial.println("Calibrated");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
 kalmanCoroutine.loop();
 driveCoroutine.loop();
 double tolerance = kalman.tolerance;//Let's play with different values.
 double heading = kalman.orient.heading; //Kalman filters it for you.
 double bearing = kalman.roverGPS.bearing; //But you can just call roverGPS (no filter).
 
 forwards(80);
 if(kalmanCoroutine.readyState){
     Serial.print("differenc: ");
     Serial.println(abs(heading-bearing));
     kalman.loop();
  }
  if (abs(heading-bearing) < tolerance){
    reset();

  }
  else{
    if(useUntil == false){
      Rightspin();
      useUntil = true;
    }
      

  }
 delay(100);
 kalmanCoroutine.reset();
 driveCoroutine.reset();
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
  drive.moveTo(29, 70);

  // Back
  drive.moveTo(24, -50);
  drive.moveTo(26, 50);
}

void Leftspin() {

  // Front
  drive.moveTo(23, -50);
  drive.moveTo(29, 50);

  // Back
  drive.moveTo(24, 50);
  drive.moveTo(26, 70);
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
  //delay(1000);



  //delay(1000);
  /*
  if(driveCoroutine.readyState){
    // left
    drive.spinAt(25, 0);
    drive.spinAt(21, 0);
    drive.spinAt(20, 0);
  
    // right
    drive.spinAt(27, 0);
    drive.spinAt(22, 0);
    drive.spinAt(28, 0);    
  }
  */
}
