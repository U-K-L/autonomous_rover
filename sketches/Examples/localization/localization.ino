#include <kalmanFilter.h>
kalmanFilter kalman;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  kalman.setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  kalman.loop();
  delay(100);
}
