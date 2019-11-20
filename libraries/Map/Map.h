#pragma once
#include <Arduino.h>
#include <imumaths>
#include <math.h>
class Map
{
	float radius;
	int r;
	sphereNode[] map;
	int round(float i);
public:
	Map(int radius, int sphereradius);
	void flush();
	void update(float distance, float angle);
	bool read(int index);
};