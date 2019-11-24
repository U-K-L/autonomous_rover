#include "Map.h"
Map::Map(int nodes, float sphereradius)
//Nodes must be less than 25, otherwise program crashes
//Sphereradius should be in meters
{
	n = nodes;
	radius = sphereradius;

	float circleradius = n * radius;
	float distance = circleradius / (2 * PI);
	float angle = (2 * PI) / n;
	for (int i = 0; i < n; i++)
	{
		map[i].position.x = distance * cos(angle * i);
		map[i].position.y = distance * sin(angle * i);
		map[i].position.z = 0;
	}
}

void Map::flush()
{
	for (int i = 0; i < sizeof(map)/sizeof(*map); i++)
	{
		map[i].traversable = true;
	}
}

void Map::update(float distance, float angle)
//Distance should be in meters, angle should be in degrees
{
	angle = angle * (PI / 180);
	float xcoord = distance * cos(angle);
	float ycoord = distance * sin(angle);
	vector3D v(xcoord, ycoord, 0);
	for (int i = 0; i < n; i++)
	{
		if (map[i].distance(v) <= radius)
		{
			map[i].traversable = false;
		}
	}
}

bool Map::read(int index)
{
	return (map[index].traversable);
}
bool Map::read(vector3D v)
{
	for (int i = 0; i < n; i++)
	{
		if (map[i].distance(v) <= radius)
		{
			return (map[i].traversable);
		}
	}
}