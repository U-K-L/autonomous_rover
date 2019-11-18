Map(int nodes, int sphereradius)
//Nodes should be a perfect square for best performance, otherwise nodes rounds down to a perfect square
{
	r = nodes;
	map[r];
	for (int i = 0; i < r; i++)
	{
			map[i] = new sphereNode();
			map[i].index = i;
	}
	int c = (r / 2)+1;
	int l = sqrt(r);
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