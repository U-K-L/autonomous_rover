Map(int nodes, float sphereradius)
//Nodes should be a perfect square for best performance, otherwise nodes rounds down to a perfect square
//Sphereradius should be in meters
{
	r = nodes;
	radius = sphereradius;
	map[r];
	for (int i = 0; i < r; i++)
	{
			map[i] = new sphereNode();
			map[i].index = i;
	}
	int c = (r / 2)+1;
	int l = (int)sqrt(r);
	int h = l;
	for (int j = -((h / 2) + 1); j < (h / 2) + 1; j++;)
	{
		for (int i = -((l / 2) + 1); i < (l / 2) + 1; i++;)
		{
			//Takes the relative coordinates of i and j and converts them to absolute coordinates for the array
			map[(l * (j + (h / 2) + 1)) + (i + (l / 2) + 1)].position = (2 * i * sphereradius, 2 * j * sphereradius, 0)
		}
	}


}

void flush()
{
	for (int i = 0; i < map.length; i++)
	{
		map[i].traversable = true;
	}
}

void update(float distance, float angle)
{
	angle = angle * (PI / 180);
	float xcoord = distance * cos(angle);
	float ycoord = distance * sin(angle);
	int i = round(xcoord / (2 * radius));
	int j = round(ycoord / (2 * radius));
	int l = (int)sqrt(r);
	map[(j * l) + i].traversable = false;
}

bool read(int index)
{
	return (map[index].traversable);
}

int round(float i)
{
	if ((i % 1) < 0.5)
	{
		return (int)i;
	}
	else
	{
		return (int)(i + 1);
	}
}