
#include <kalmanFilter.h>
kalmanFilter kalman;
void setup() {
  // put your setup code here, to run once:
  kalman.setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  kalman.loop();
  Serial.println(String(kalman.averageCalibration.x(), 6));
  Serial.println(String(kalman.averageCalibration.y(), 6));
  Serial.println(String(kalman.averageCalibration.z(), 6));
  delay(60);
}
