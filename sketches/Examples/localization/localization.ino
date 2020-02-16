#define BNO055_SAMPLERATE_DELAY_MS (100)
#include <kalmanFilter.h>
#include <coroutine.h>
kalmanFilter kalman;
coroutine serialCoroutine;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  kalman.setup();
  serialCoroutine.setup(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  kalman.loop();
  /*
  serialCoroutine.loop();
  if(serialCoroutine.readyState){
     kalman.serialize();
     serialCoroutine.reset(); 
  }
  */
  kalman.serialize();
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
