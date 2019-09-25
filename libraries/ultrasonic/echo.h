#pragma once
//Created by Noah Williams on 9/7/2019.
//Echo location functions used for finding objects via sound.
#include <Arduino.h>
using namespace std;
class echo {
public:
	//Public variable access specifiers.
	double duration, distance; //seconds, centimeters.
	float length = 5; //How long the wavelength should be. Micro-Seconds.
	const int trigPin = 11, receivePin = 12;
	void setup();
	void loop();
	void pulsate(float speed);
	String serialize();
};

