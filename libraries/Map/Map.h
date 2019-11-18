#pragma once
#include <Arduino.h>
#include <imumaths>
#include <math.h>
class Map
{
	int r;
	sphereNode map;
public:
	Map(int radius, int sphereradius);
	flush();
};