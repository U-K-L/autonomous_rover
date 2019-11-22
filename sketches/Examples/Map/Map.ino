#include <Map.h>
Map maps;
void setup() {
  // put your setup code here, to run once:
  maps = new Map(25, 0.5);
  maps.update(0.4,90);
  Serial.println(maps.read(8));
  maps.flush();
  Serial.println(maps.read(8));
}

void loop() {
  // put your main code here, to run repeatedly:

}
