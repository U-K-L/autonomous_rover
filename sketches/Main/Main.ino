//The main sketch will include ALL FILES via an include method. The microprocessor will only load a single sketch (file). 
//Echolocation library and objects.
#include <echo.h>
#include <Vector3D.h>
#include <sphereNode.h>
#include <internalMapping.h>
int success = 8; //Pin that lights up when reach target.
echo echo;
vector3D point = vector3D(3.1415926,2,3);
internalMapping internalMap;
//-----
void setup() {
   Serial.begin (9600);
  internalMap.r = 10; //How large a single sphere is.

  // put your setup code here, to run once:
  echo.setup();
  echo.loop();
  internalMap.createMap(vector3D(echo.distance,0,0));
  Serial.println(internalMap.serialize());
  pinMode(success, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  echo.loop();
  Serial.println(internalMap.serialize());
  Serial.println(echo.serialize());
  goalReached();
}

void goalReached(){
  if(internalMap.nodes[0].bounded(vector3D(echo.distance,0,0),internalMap.r)){
    digitalWrite(success, HIGH);
  }else{
    digitalWrite(success, LOW);
  }
}

