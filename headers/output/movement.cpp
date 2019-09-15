// For further infromation about the code please refer back to the documentation!


#include "movement.h"

//   This function increments the correct coordinate of the player according to input.
mob playerMovement(mob playr, bool w, bool s, bool a, bool d)
{
	//   The function checks for all 4 different directions and then increments the 
	// coordinates accordingly.
	
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

//   This function keeps the player in bounds.
mob keepInBounds(mob playr, mob lastPlayr, map world[WORLDROWS][WORLDCOLS])
{
	//   First the function checks if both of the coordinates of the player have changed.
	if (playr.row != lastPlayr.row && playr.col != lastPlayr.col)
	{
		//   If the coordinates of the player have changed then the function checks if
		// the cell the player wants to pass into blocks player movement.
		if (world[playr.row][playr.col].walkable == false)
		{
			//   If the cell that the player wants to pass into blocks player movement
			// the function checks if the cells that are next to the position of the
			// player from the last frame and the cell the player wants to pass both are
			// "walkable".
			if (world[playr.row][lastPlayr.col].walkable == true && world[lastPlayr.row][playr.col].walkable == true)
			{
				//   If both of the cells next to the position of the player from the
				// last frame and the cell teh player wants to pass into are true we set
				// the player's position back to it's position from the last frame.
				playr.row = lastPlayr.row;
				playr.col = lastPlayr.col;
			}
			else
			{
				//   If at least one of the cells that are next to both the position of
				// the player from the last frame and the cell the player wants to pass
				// into blocks player movement we check if both of them do.
				if (world[playr.row][lastPlayr.col].walkable == false && world[lastPlayr.row][playr.col].walkable == false)
				{
					//   If both of the cells that are next to the position of the player
					// from the last frame and the cell the player wants to pass into
					// block player movement we set the player's position back to it's
					// postion from the last frame.
					playr.row = lastPlayr.row;
					playr.col = lastPlayr.col;
				}
				
				//   After we concluded that only one of the cells that are next to both
				// the position of the player from the last frame and the cell the player
				// wants to pass into blocks player movement the function checks if the
				// cell that is above the cell the player wants to pass into blocks
				// player movement.
				if (world[lastPlayr.row][playr.col].walkable == false)
				{
					//   If the cell that is above the cell the player wants to pass into
					// blocks movement we set the column part of the position of the
					// player back to the column part of the position of the player from
					// the last frame.
					playr.col = lastPlayr.col;
				}
				else
				{
					//   If the cell that is above the cell the player wants to pass into
					// dosen't block movement (this means that the cell that is below the
					// position of the player from the last frame blocks movement) we set
					// the row part of the position of the player back to the row part of
					// the position of the player from the last frame.
					playr.row = lastPlayr.row;
				}
			}
		}
		else
		{
			//   If the cell the player wants to pass into doesn't block movement the
			// function checks if the 2 cells that are next to both the position of the
			// player on the last frame and the position the player wants to pass into
			// are both blocking player movement.
			if (world[playr.row][lastPlayr.col].walkable == false && world[lastPlayr.row][playr.col].walkable == false)
			{
				//   If both cells that are next to the position of the player on the
				// last frame and the cell the player wants to pass into block player
				// movement the function sets the player's position back to it's position
				// from the last frame.
				playr.row = lastPlayr.row;
				playr.col = lastPlayr.col;
			}
		}
	}
	else
	{
		//   If at least one coordinate of the player stayed the same, we check if the
		// cell the player wants to pass into does block player movement.
		if (world[playr.row][playr.col].walkable == false)
		{
			//   If the cell the player wants to pass into blocks player movement, we set
			// the player's position back to it's position from the last frame.
			playr.row = lastPlayr.row;
			playr.col = lastPlayr.col;
		}	
	}
	
	return playr;
}

//   This function sets the orientation of the player.
mob setDirections(mob playr, bool w, bool s, bool a, bool d)
{
	//   First the function clears the orientation of the player from the last frame.
	playr.up = false;
	playr.down = false;
	playr.right = false;
	playr.left = false;
	
	//   Next the function sets the correct orientation according to the input using the
	// orientational bools.
	
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

//   This function sets where the camera should be according to the position and the
// orientation of the player.
mob camMovement(mob cam, mob playr)
{
	//   The function hardcodes the correct one of the 8 possible cases according to the
	// orientation of the player.
	
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

//   This function pans the camera to the position it should be.
mob cameraPan(mob cam, mob camDest)
{
	//   The function increments/decrements the correct coordinate of the camera
	// according to the destination it should arrive to.
	
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

//   This function keeps the camera in bounds.
mob keepCamInBounds(mob cam)
{
	//   If the upper edge of the camera would fall onto cells that do not exist on the
	// map the function sets the coordinates of the camera so that they are at the upper
	// edge of the map.
	if (cam.row < 0)
	{
		cam.row = 0;
	}
	
	//   If the leftmost edge of the camera would fall onto cells that do not exist on
	// the map the function sets the coordinates of the camera so that they are at the
	// leftmost edge of the map.
	if (cam.col < 0)
	{
		cam.col = 0;
	}
	
	//   If the lower edge of the camera would fall onto cells that do not exist on the
	// map the function sets the coordinates of the camera so that they are at the lower
	// edge of the map.
	if (cam.row > WORLDROWS - CONSOLEROWS)
	{
		cam.row = WORLDROWS - CONSOLEROWS;
	}
	
	//   If the rightmost edge of the camera would fall onto cells that do not exist on
	// the map the function sets the coordinates of the camera so that they are at the
	// rightmost edge of the map.
	if (cam.col > WORLDCOLS - SCREENCOLS)
	{
		cam.col = WORLDCOLS - SCREENCOLS;
	}
	
	return cam;
}
