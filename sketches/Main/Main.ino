//The main sketch will include ALL FILES via an include method. The microprocessor will only load a single sketch (file). 

//Echolocation library and objects.
#include <echo.h>
echo echo;
//-----
void setup() {
  Serial.begin (9600);
  // put your setup code here, to run once:
  echo.setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  echo.loop();
}
