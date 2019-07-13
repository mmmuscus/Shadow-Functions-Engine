#include "movement.h"

mob playerMovement(mob playr, bool w, bool s, bool a, bool d)
{
	if (s)
	{
		playr.row++;
	}
	
	if (w)
	{
		playr.row--;
	}
	
	if (d)
	{
		playr.col++;
	}
	
	if (a)
	{
		playr.col--;
	}
	
	return playr;
}

mob keepInBounds(mob playr, mob lastPlayr, map world[WORLDROWS][WORLDCOLS])
{
	if (playr.row != lastPlayr.row && playr.col != lastPlayr.col)
	{
		if (world[playr.row][playr.col].walkable == false)
		{
			if (world[playr.row][lastPlayr.col].walkable == true && world[lastPlayr.row][playr.col].walkable == true)
			{
				playr.row = lastPlayr.row;
				playr.col = lastPlayr.col;
			}
			else
			{
				if (world[playr.row][lastPlayr.col].walkable == false && world[lastPlayr.row][playr.col].walkable == false)
				{
					playr.row = lastPlayr.row;
					playr.col = lastPlayr.col;
				}
				
				if (world[playr.row][lastPlayr.col].walkable && world[lastPlayr.row][playr.col].walkable == false)
				{
					playr.col = lastPlayr.col;
				}
				else
				{
					playr.row = lastPlayr.row;
				}
			}
		}
		else
		{
			if (world[playr.row][lastPlayr.col].walkable == false && world[lastPlayr.row][playr.col].walkable == false)
			{
				playr.row = lastPlayr.row;
				playr.col = lastPlayr.col;
			}
		}
	}
	else
	{
		if (world[playr.row][playr.col].walkable == false)
		{
			playr.row = lastPlayr.row;
			playr.col = lastPlayr.col;
		}	
	}
	
	return playr;
}

mob setDirections(mob playr, bool w, bool s, bool a, bool d)
{
	playr.up = false;
	playr.down = false;
	playr.right = false;
	playr.left = false;
	
	if (w)
	{
		playr.up = true;
	}
	
	if (s)
	{
		playr.down = true;
	}
	
	if (a)
	{
		playr.left = true;
	}
	
	if (d)
	{
		playr.right = true;
	}
	
	return playr;
}

mob camMovement(mob cam, mob playr)
{
	if (playr.right && !playr.up && !playr.down)
	{
		cam.row = playr.row - 12;
		cam.col = playr.col - 3;
	}
	
	if (playr.right && playr.up)
	{
		cam.row = playr.row - 16;
		cam.col = playr.col - 9;
	}
	
	if (playr.right && playr.down)
	{
		cam.row = playr.row - 8;
		cam.col = playr.col - 9;
	}
	
	if (playr.left && !playr.up && !playr.down)
	{
		cam.row = playr.row - 12;
		cam.col = playr.col - 35;
	}
	
	if (playr.left && playr.up)
	{
		cam.row = playr.row - 16;
		cam.col = playr.col - 29;
	}
	
	if (playr.left && playr.down)
	{
		cam.row = playr.row - 8;
		cam.col = playr.col - 29;
	}
	
	if (playr.up && !playr.right && !playr.left)
	{
		cam.row = playr.row - 22;
		cam.col = playr.col - 19;
	}
	
	if (playr.down && !playr.right && !playr.left)
	{
		cam.row = playr.row - 2;
		cam.col = playr.col - 19;
	}

	return cam;
}

mob cameraPan(mob cam, mob camDest)
{
	if (cam.row < camDest.row)
	{
		cam.row++;
	}
	
	if (cam.row > camDest.row)
	{
		cam.row--;
	}
	
	if (cam.col < camDest.col)
	{
		cam.col++;
	}
	
	if (cam.col > camDest.col)
	{
		cam.col--;
	}

	return cam;
}

mob keepCamInBounds(mob cam)
{
	if (cam.row < 0)
	{
		cam.row = 0;
	}
	
	if (cam.col < 0)
	{
		cam.col = 0;
	}
	
	if (cam.row > WORLDROWS - CONSOLEROWS)
	{
		cam.row = WORLDROWS - CONSOLEROWS;
	}
	
	if (cam.col > WORLDCOLS - SCREENCOLS)
	{
		cam.col = WORLDCOLS - SCREENCOLS;
	}
	
	return cam;
}
