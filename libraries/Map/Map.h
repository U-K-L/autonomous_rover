#pragma once
#include <Arduino.h>
#include <imumaths.h>
#include <math.h>
#include <sphereNode.h>
#include <Vector3D.h>
class Map
{
	// var
private:
	float radius;
	float circleradius;
	float distance;
	int n;
	sphereNode map[25];
public:
	Map(int radius, float sphereradius);
	void flush();
	void update(float distance, float angle);
	bool read(int index);
	bool read(vector3D v);
	String serialize();
	String Sizeserialize();
};