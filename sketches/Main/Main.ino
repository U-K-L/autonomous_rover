//The main sketch will include ALL FILES via an include method. The microprocessor will only load a single sketch (file). 
//Echolocation library and objects.
#include <echo.h>
#include <Vector3D.h>
#include <sphereNode.h>
#include <internalMapping.h>
echo echo;
vector3D point = vector3D(3.1415926,2,3);
internalMapping internalMap;
//-----
void setup() {
  Serial.begin (9600);
  // put your setup code here, to run once:
  echo.setup();
  internalMap.createMap();
  Serial.print(internalMap.map);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  echo.loop();
  Serial.println(internalMap.map);
}
