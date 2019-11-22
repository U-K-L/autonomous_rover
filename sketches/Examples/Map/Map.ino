#include <Map.h>
Map maps = Map(25, 0.5);;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  maps.update(0.4, 90);
  vector3D v(0, 0.4, 0);
  bool g = maps.read(v);
  Serial.println(g);
  delay(10);
  //Serial.println(maps.read(0));
  maps.flush();
  bool f = maps.read(v);
  Serial.println(f);
  //Serial.println(maps.read(v));

}
