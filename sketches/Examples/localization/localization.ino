
#include <kalmanFilter.h>
kalmanFilter kalman;
void setup() {
  // put your setup code here, to run once:
  kalman.setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  kalman.loop();
  delay(100);
}
