#include <AutonomousDrive.h>
AutonomousDrive autoDrive;
RoverGPS gps;
/*
 * Created by Noah Williams on 3/21/2020.
 * 
 * Purpose: Makes Rover drive to a manual destination. Set the latitude and longitude, any number of destinations can be set, just change index.
 * 
 * EXAMPLE: gps.setDestinations(LATITUDE, LONGITUDE, DESTINATION NUMBER);
 * 
 * It's best practice to use Google Maps and click "What's here" as an example: 40.091524, -75.165870.
 */
//Set destinations in here!
void SetYourDestinationsHere(){

//Paste your destinations in here. Examples:

  //gps.setDestinations(40.176001, -75.274005, 0); //Goes to Montgomery County Community College.
  /*
   * gps.setDestinations(42.176001, -72.274005, 1);
   * gps.setDestinations(44.176001, -71.274005, 2);
   * gps.setDestinations(43.176001, -72.274005, 3);
   * gps.setDestinations(41.176001, -74.274005, 4);
   */

  gps.setDestinations(40.082008, -75.163452, 0); //Note this was used for personal testing. Can be deleted in final build.
}


//THESE VARIABLES ARE TO BE CHANGED BY USER.
int detectionRangeLEFT = 20; //CENTIMETERS. DETERMINES HOW FAR OBJECT CAN BE DETECTED BEFORE TURNING.
int detectionRangeRIGHT = 80;
float accuracyRadius = 5; //How close to destination before succeeding. IN METERS. 

//Changes the pins of the ultrasound:
int LeftTrigPin = 7;
int LeftRecievePin = 8;
int RightTrigPin = 4;
int RightRecievePin = 3;

bool ObjectDetectionEnabled = true; //Turns on or off obstacle avoidance. Note: TURN OFF IF NO ULTRASOUND IS CONNECTED.

bool SDRecordingEnabled = false; //Turns on or off SD card recordings. NOTE: you need an SD card, otherwise turn it off!

bool SerializeDataEnabled = true; //Turns on or off data in the serial monitor. Note: turning off will improve performance. THIS NEEDS TO BE ON FOR SD CARD RECORDINGS.



//DO NOT TOUCH BELOW!!!!!


void setup() {
  autoDrive.detectionRangeLEFT = detectionRangeLEFT;
  autoDrive.detectionRangeRIGHT = detectionRangeRIGHT;
  autoDrive.objectDetection = ObjectDetectionEnabled;
  autoDrive.LeftTrigPin = LeftTrigPin;
  autoDrive.LeftRecievePin = LeftRecievePin;
  autoDrive.RightTrigPin = RightTrigPin;
  autoDrive.RightRecievePin = RightRecievePin;
  autoDrive.setup(true);
  gps = autoDrive.kalman.roverGPS;
  SetYourDestinationsHere();
  autoDrive.kalman.roverGPS.traverseDestination();
  autoDrive.kalman.destinationRadius = accuracyRadius;

  autoDrive.SDRecord = SDRecordingEnabled;
  autoDrive.SerializeDataEnabled = SerializeDataEnabled;
}

void loop() {
  autoDrive.loop();
}
