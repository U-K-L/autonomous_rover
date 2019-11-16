Map(int radius, int sphereradius)
{
	r = radius;
	map[r][r];
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			map[i][j] = new sphereNode();
			
			map[i][j].index = r(i) + j;
		}
	}
}

void convertCoords(float distance, float angle, int index)
{
	float xcoord, ycoord;
	int i, j;
	xcoord = distance * cos(angle);
	ycoord = distance * sin(angle);
	i = index / r;
	j = index % r;
	map[i][j].position = vector3D(xcoord, ycoord, 0)

}