//Created by Noah Williams on 9/7/2019.
//Echo location functions used for finding objects via sound.
#include "echo.h"

void echo :: setup() {
	//Inputs/Outputs
	pinMode(trigPin, OUTPUT);
	pinMode(receivePin, INPUT);

}
void echo :: loop() {
	pulsate(length); //Give a high then low pulse to create sound.
	duration = pulseIn(receivePin, HIGH); //reads reciever. Sends back length in microseconds.
	pinMode(receivePin, INPUT);
	//Converts speed to distance
	distance = (duration*0.5f)*0.0343642611683849f; //Approximate value for speed of sound.
}
void echo :: pulsate(float length) {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(length);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(length*2);
	digitalWrite(trigPin, LOW);
}