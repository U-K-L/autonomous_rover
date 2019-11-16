#pragma once
#include <Arduino.h>
#include <imumaths>
class Map
{
	int r;
	sphereNode map;
public:
	Map(int radius, int sphereradius);
};