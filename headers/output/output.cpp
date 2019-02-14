#include "output.h"

using namespace std;

void saveLastScreenArray(char oldS[SCREENROWS][SCREENCOLS], char newS[SCREENROWS][SCREENCOLS])
{
	for (int i = 0; i < SCREENROWS; i++)
	{
		for (int j = 0; j < SCREENCOLS; j++)
		{
			oldS[i][j] = newS[i][j];
		}
	}
}

void saveLastMenuArray(char oldM[SCREENROWS][MENUCOLS], char newM[SCREENROWS][MENUCOLS])
{
	for (int i = 0; i < SCREENROWS; i++)
	{
		for (int j = 0; j < MENUCOLS; j++)
		{
			oldM[i][j] = newM[i][j];
		}
	}
}

void initSolid(char solide[SOLIDCOUNT], string fileName)
{
	fstream fbe (fileName.c_str());
	
	for (int i = 0; i < SOLIDCOUNT; i++)
	{
		fbe>>solide[i];
	}
	
	fbe.close();
}

void initWalkable(char walkablee[WALKABLECOUNT], string fileName)
{
	fstream fbe (fileName.c_str());
	
	for (int i = 0; i < WALKABLECOUNT; i++)
	{
		fbe>>walkablee[i];
	}
	
	fbe.close();
}

void initWorld(map world[WORLDROWS][WORLDCOLS], char solide[SOLIDCOUNT], char walkablee[WALKABLECOUNT], string fileName)
{
	char cahr;
	
	freopen(fileName.c_str(),"r",stdin);
	
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			cin>>cahr;
			
			if (cahr == 'i' || cahr == '0')
			{
				world[i][j].texture = ' ';
			}
			else
			{
				world[i][j].texture = cahr;
			}
			
			world[i][j].solid = false;
			
			for (int k = 0; k <= SOLIDCOUNT; k++)
			{
				if (cahr == solide[k])
				{
					world[i][j].solid = true;
				}
			}
			
			world[i][j].walkable = false;
			
			for (int k = 0; k <= WALKABLECOUNT; k++)
			{
				if (cahr == walkablee[k])
				{
					world[i][j].walkable = true;
				}
			}
		}
	}
	
	fclose(stdin);
}

void initFOV(fov dir[FOVROWS][FOVCOLS], string fileName)
{
	char cahr;
	
	freopen(fileName.c_str(),"r",stdin);
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			cin>>cahr;
			
			if (cahr == '_')
			{
				dir[i][j].inView = true;
				dir[i][j].isEdge = false;
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fclose(stdin);
}
