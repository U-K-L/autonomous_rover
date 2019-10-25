/*
* Position Calculator using Bosch Sensortec BNO055 IMU
* Author: Jermaine Smith
* Email: smit8332@umn.edu
* Advisor: Yohannes Ketema
* Sponsored by UMN UROP Program
*
* Last Updated: 8/26/2018
*
* Code was modified from
*
https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/arduino-code#adafruit-unified-sensor-system4-10
* ‘Adafruit Unified Sensor System’ code
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <imumaths.h>
#define PI 3.1415926535897932384626433832795
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);


int start = 0; //variable that indicates sampling may begin
double pos_x = 0; //x- position on 2d plane (m)
double pos_y = 0; //y-position on 2d plane (m)
double pos_mag = 0; //total displacement, used in straight line walking test
double leg_len = 1.0; //leg length in meters
double acc_magnitude; //the magnitude of the acceleration vector excluding gravity
double eX_offset = 0; //This eX_offset value sets whatever direction your first step is in equal to 0 degrees
int calibration = 0; //1 when eX_offset has been set


void setup(void)
{
Serial.begin(9600);
Serial.println("Position Calculator Calibrating... Move your leg to calibrate..."); Serial.println("");
/* Initialise the sensor */
if(!bno.begin())
{
/* There was a problem detecting the BNO055 ... check your connections */
Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
while(1);
}
delay(1000);
bno.setExtCrystalUse(true);
//Calibrating the IMU
uint8_t system, gyro, accel, mag = 0;
while(system != 3)
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
start = 1;
}

void loop(void)
{
imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
//imu::Vector<3> LIN_acc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
acc_magnitude = (sqrt(pow(acc.x(),2) + pow(acc.y(),2) + pow(acc.z(),2)))-9.81;
if (start == 1)
{
  if (acc_magnitude > 0.9 & abs( euler.z() )<40 ) // values within the if statement are characteristics of data when a step is taken
  {
    if(calibration == 0)
    {
      eX_offset = euler.x(); // This eX_offset value sets whatever direction first step is in equal to 0 degrees
      calibration =1;
    }
    Serial.println("");
    Serial.println("ANGLE SAMPLE");
    Serial.print("eX: ");
    Serial.print(euler.x(),4);
    Serial.print("eY: ");
    Serial.print(euler.y(),4);
    Serial.print("eZ: ");
    Serial.println(euler.z(),4);
    // CALCULATING POSITION: right now it is assumed that every step is duplicated by the second foot
    // Factor of 3.281 used to convert meters to feet.
    pos_x = pos_x + 2*(2*leg_len*cos((euler.y()-10)*PI/180)) * cos((euler.x()-eX_offset)*PI/180)*3.281; // xposition
    pos_y = pos_y + 2*(2*leg_len*cos((euler.y()-10)*PI/180)) * sin((euler.x()-eX_offset)*PI/180)*3.281; //y-position
    pos_mag = pos_mag + 2*(2*leg_len*cos((euler.y()-10)*PI/180))*3.281;
    Serial.print("X_POS:");
    Serial.println(pos_x,4);
    Serial.print("Y_POS: ");
    Serial.println(pos_y,4);
    Serial.print("MAG_POS: ");
    Serial.println(pos_mag,4);
    //Comment out other print statements and uncomment the following for data which can be easily copied into spreadsheets
    /*
    Serial.print(pos_x,4);
    Serial.print(",");
    Serial.println(pos_y,4);
    */
  }
 }
delay(100);
}
