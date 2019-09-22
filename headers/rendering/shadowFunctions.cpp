// For further infromation about the code please refer back to the documentation!


#include "shadowFunctions.h"

//   This function copies one FOV array into another.
void makeCurrentFov(fov presetDir[FOVROWS][FOVCOLS], fov toBeDir[FOVROWS][FOVCOLS])
{
	//   The function loops through all the variables on the array.
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			//   The function copies the correct sub variables of the current variable of
			// the array.
			toBeDir[i][j].inView = presetDir[i][j].inView;
			toBeDir[i][j].isPlayer = presetDir[i][j].isPlayer;
		}
	}
}

//   This function sets the correct FOV for the player according to its orientation.
void setCurrentFov(mob playr, fov toBecomeCurrentFov[FOVROWS][FOVCOLS], fov r[FOVROWS][FOVCOLS], fov l[FOVROWS][FOVCOLS], fov u[FOVROWS][FOVCOLS], fov d[FOVROWS][FOVCOLS], fov ru[FOVROWS][FOVCOLS], fov rd[FOVROWS][FOVCOLS], fov lu[FOVROWS][FOVCOLS], fov ld[FOVROWS][FOVCOLS])
{
	//   The function checks all of the 8 possibilities and sets the correct FOV for the 
	// player.
	
	if (playr.right && !playr.up && !playr.down)
	{
		makeCurrentFov(r, toBecomeCurrentFov);
	}
	
	if (playr.right && playr.up)
	{
		makeCurrentFov(ru, toBecomeCurrentFov);
	}
	
	if (playr.right && playr.down)
	{
		makeCurrentFov(rd, toBecomeCurrentFov);
	}
	
	if (playr.left && !playr.up && !playr.down)
	{
		makeCurrentFov(l, toBecomeCurrentFov);
	}
	
	if (playr.left && playr.up)
	{
		makeCurrentFov(lu, toBecomeCurrentFov);
	}
	
	if (playr.left && playr.down)
	{
		makeCurrentFov(ld, toBecomeCurrentFov);
	}
	
	if (playr.up && !playr.right && !playr.left)
	{
		makeCurrentFov(u, toBecomeCurrentFov);
	}
	
	if (playr.down && !playr.right && !playr.left)
	{
		makeCurrentFov(d, toBecomeCurrentFov);
	}
}

//   This function gets the position of the player from a FOV array.
mob getPlayerPosInFov(mob playr, mob fovPlayr)
{
	//   The function hardcodes the correct row and col(umn) values for the player
	// according to its orientation.
	
	if (playr.right && !playr.up && !playr.down)
	{
		fovPlayr.row = 10;
		fovPlayr.col = 1;
	}
	
	if (playr.right && playr.up)
	{
		fovPlayr.row = 14;
		fovPlayr.col = 7;
	}
	
	if (playr.right && playr.down)
	{
		fovPlayr.row = 6;
		fovPlayr.col = 7;
	}
	
	if (playr.left && !playr.up && !playr.down)
	{
		fovPlayr.row = 10;
		fovPlayr.col = 33;
	}
	
	if (playr.left && playr.up)
	{
		fovPlayr.row = 14;
		fovPlayr.col = 27;
	}
	
	if (playr.left && playr.down)
	{
		fovPlayr.row = 6;
		fovPlayr.col = 27;
	}
	
	if (playr.up && !playr.right && !playr.left)
	{
		fovPlayr.row = 20;
		fovPlayr.col = 17;
	}
	
	if (playr.down && !playr.right && !playr.left)
	{
		fovPlayr.row = 0;
		fovPlayr.col = 17;
	}
	
	return fovPlayr;
}

//   This function makes the correct cells visible on the map according to the current
// FOV of the player.
void addFovInfoToMap(map world[WORLDROWS][WORLDCOLS], mob playr, mob fovPlayr, fov fov[FOVROWS][FOVCOLS])
{
	//   First the function loops through every cell on the world map.
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			//   The function sets the current cells visibility to false (a cell can only
			// be .mapIsEdge if it isn't in view so .mapIsEdge gets set to false too).
			world[i][j].mapIsEdge = false;
			world[i][j].mapInView = false;
		}
	}
	
	//   Next the function loops over the current FOV array of the player.
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			//   The function checks if the current cell of the FOV array is in view, if
			// it is we set the correct cell of the world map to in view too. We do this 
			// by using the position of the player in the FOV array as ana nchor point
			// between the FOV and the map. So the cell in the upper left corner of the
			// FOV array is obviously (0,0) and the cell in the upper left corner of the
			// FOV array in the map (as anchored by the player) is:
			// (player.row - fovplayer.row, player.col - fovplayer.col).
			if (fov[i][j].inView)
			{
				world[playr.row - fovPlayr.row + i][playr.col - fovPlayr.col + j].mapInView = true;
			}
		}
	}
}

//   This function gets the Point Of View (or POV) of the player according to its cell
// position.
koordinate getPov(koordinate pov, mob playr)
{
	//   The function adds .5 to both of the cell coordinates of the player.
	pov.x = playr.col + 0.5;
	pov.y = playr.row + 0.5;

	return pov;
}

//   This function gets the a line that passes through two given points.
line getLineEquation(double aXCol, double aYRow, int bXCol, int bYRow)
{
	line e;

	//   The following calculations are prooven to work ro find the line that is between
	// two points. Here is a link for manually solving a problem like this:
	// https://www.khanacademy.org/math/algebra/two-var-linear-equations/writing-slope-intercept-equations/v/equation-of-a-line-3

	e.mSlope = (bYRow - aYRow) / (bXCol - aXCol);
	e.bIntercept = aYRow - (e.mSlope * aXCol);

	return e;
}

//   This function checks if a cell is under a given line.
bool isUnderLine(line e, int solidYRow, int solidXCol)
{
	//   The function checks all of the 4 corners of the cell if they are under the line,
	// if they are the function returns true.
	if ((solidYRow <= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow <= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{
		return true;
	}

	//   If there is at least one corner that isn't under the line the function returns
	// false.
	return false;
}

//   This function checks if a cell is over a given line.
bool isOverLine(line e, int solidYRow, int solidXCol)
{
	//   The function checks all of the 4 corners of the cell if they are over the line,
	// if they are the function returns true.
	if ((solidYRow >= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow >= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{
		return true;
	}

	//   If there is at least one corner that isn't over the line the function returns
	// false.
	return false;
}

//   This function determines if a cell is fully between two lines.
bool isBetweenLines(line a, line b, int yRow, int xCol)
{
	//   First the function checks if the first line is an "underline" (if it is that
	// means that the line is supposed to be under the given cell).
	if (a.isItUnderLine)
	{
		//   If the first line is supposed to be an "underline" the function checks if it
		// actually goes under the given cell, if it dosen't the function returns false.
		if (!isUnderLine(a, yRow, xCol))
		{
			return false;
		}
	}
	else
	{
		//   If the first line isn't supposed to be an "underline" that means that it is 
		// an "overline", thus the function checks if the line actually goes over the 
		// given cell, if it dosen't the function returns false.
		if (!isOverLine(a, yRow, xCol))
		{
			return false;
		}
	}

	//   Next the function checks if the second line is on an "underline".
	if (b.isItUnderLine)
	{
		//   If the second line is supposed to be an "underline" the function checks if
		// it actually goes under the given cell, if it dosen't the function returns 
		// false.
		if (!isUnderLine(b, yRow, xCol))
		{
			return false;
		}
	}
	else
	{
		//   If the second line isn't supposed to be an "underline" that means that it is 
		// an "overline", thus the function checks if the line actually goes over the
		// given cell, if it dosen't the function returns false.
		if (!isOverLine(b, yRow, xCol))
		{
			return false;
		}
	}

	//   Finally iff the function haven't returned anything so far that means that the
	// lines are what they are supposed to be, so the function returns true.
	return true;
}

//   This function checks if a line intersects a cell and if it does it checks if the
// area inside the shade is bigger than half of the area of the cell.
bool isMoreThanHalfInShade(line e, int yRow, int xCol)
{
	//   First the function checks if the line is an "underline"
	if (e.isItUnderLine)
	{
		//   If the line is an "underline" the function checks if it interests the lower
		// border of the cell.
		if (xCol - INFINITECIMAL < ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			//   If the line intersects the lower border then the function checks if the 
			// line intersects the left border if it does it returns true.
			if (yRow < (e.mSlope * xCol) + e.bIntercept && yRow + 1  > (e.mSlope * xCol) + e.bIntercept)
			{
				return true;
			}
			
			//   If the line intersects the lower border then the function checks if the 
			// line intersects the right border if it does it returns true.
			if (yRow < (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1  > (e.mSlope * (xCol + 1)) + e.bIntercept)
			{
				return true;
			}
		}
		
		//   If the line dosen't intersect the lower border of the cell, then the
		// function checks if the line intersects both the left and right border of the
		// cell.
		if (yRow - INFINITECIMAL <= (e.mSlope * xCol) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * xCol) + e.bIntercept && yRow - INFINITECIMAL <= (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * (xCol + 1)) + e.bIntercept)
		{
			//   If the line intersects both the left and right border of the cell the 
			// function checks if the area that over the line inside the cell is bigger 
			// than half of the area of the cell, if it is the function retourns true.
			if ((e.mSlope * xCol) + e.bIntercept - yRow + (e.mSlope * (xCol + 1)) + e.bIntercept - yRow + INFINITECIMAL >= 1)
			{
				return true;
			}
		}
		
		//   If the line only intersects the lower border of the cell or it dosen't
		// intersect both the left and the right border the function checks if the line
		// intersects both the upper and the lower border of the cell. 
		if (xCol - INFINITECIMAL <= (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= (yRow - e.bIntercept) / e.mSlope && xCol - INFINITECIMAL <= ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			//   If the function intercepts both the upper and lower border of the cell
			// the function checks if the segment from the top left corner of the cell to
			// the point where the line intercepts the upper border is longer than the
			// segment from the point where the line intercepts the upper border of the
			// cell to the top right corner of the cell.
			if (((yRow - e.bIntercept) / e.mSlope) - xCol > (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				//   If the segment from the top left corner of the cell to the point
				// where the line intercepts the upper border is longer than the segment 
				// from the point where the line intercepts the upper border of the cell
				// to the top right corner of the cell the function calculates if the
				// area to the left of the line inside the cell is more than half of the
				// area of the call if it is the function returns true.
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol + INFINITECIMAL >= 1)
				{
					return true;
				}
			}
			
			//   If the function intercepts both the upper and lower border of the cell 
			// the function checks if the segment from the top left corner of the cell to
			// the point where the line intercepts the upper border is shorter than the
			// segment from the point where the line intercepts the upper border of the
			// cell to the top right corner of the cell.
			if (((yRow - e.bIntercept) / e.mSlope) - xCol < (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				//   If the segment from the top left corner of the cell to the point
				// where the line intercepts the upper border is shorter than the segment 
				// from the point where the line intercepts the upper border of the cell
				// to the top right corner of the cell the function calculates if the
				// area to the right of the line inside the cell is more than half of the
				// area of the call if it is the function returns true.
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol - INFINITECIMAL <= 1)
				{
					return true;
				}
			}
		}
	}
	
	//   Next the function checks if the line is an "overline"
	if (!e.isItUnderLine)
	{
		//   If the line is an "overline" the function checks if it interests the upper
		// border of the cell.
		if (xCol - INFINITECIMAL < (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > (yRow - e.bIntercept) / e.mSlope)
		{
			//   If the line intersects the upper border then the function checks if the 
			// line intersects the left border if it does it returns true.
			if (yRow < (e.mSlope * xCol) + e.bIntercept && yRow + 1 > (e.mSlope * xCol) + e.bIntercept)
			{
				return true;
			}
			
			//   If the line intersects the upper border then the function checks if the 
			// line intersects the right border if it does it returns true.
			if (yRow < (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 > (e.mSlope * (xCol + 1)) + e.bIntercept)
			{
				return true;
			}
		}
		
		//   If the line dosen't intersect the upper border of the cell, then the
		// function checks if the line intersects both the left and right border of the
		// cell.
		if (yRow - INFINITECIMAL <= (e.mSlope * xCol) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * xCol) + e.bIntercept && yRow - INFINITECIMAL <= (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * (xCol + 1)) + e.bIntercept)
		{
			//   If the line intersects both the left and right border of the cell the 
			// function checks if the area that under the line inside the cell is bigger 
			// than half of the area of the cell, if it is the function retourns true.
			if ((e.mSlope * xCol) + e.bIntercept - yRow + (e.mSlope * (xCol + 1)) + e.bIntercept - yRow - INFINITECIMAL <= 1)
			{
				return true;
			}
		}
		
		//   If the line only intersects the upper border of the cell or it dosen't
		// intersect both the left and the right border the function checks if the line
		// intersects both the upper and the lower border of the cell. 
		if (xCol - INFINITECIMAL <= (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= (yRow - e.bIntercept) / e.mSlope && xCol - INFINITECIMAL <= ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			//   If the function intercepts both the upper and lower border of the cell
			// the function checks if the segment from the top left corner of the cell to
			// the point where the line intercepts the upper border is longer than the
			// segment from the point where the line intercepts the upper border of the
			// cell to the top right corner of the cell.
			if (((yRow - e.bIntercept) / e.mSlope) - xCol > (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				//   If the segment from the top left corner of the cell to the point
				// where the line intercepts the upper border is longer than the segment 
				// from the point where the line intercepts the upper border of the cell
				// to the top right corner of the cell the function calculates if the
				// area to the right of the line inside the cell is more than half of the
				//  area of the call if it is the function returns true.
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol - INFINITECIMAL <= 1)
				{
					return true;
				}
			}
			
			//   If the function intercepts both the upper and lower border of the cell 
			// the function checks if the segment from the top left corner of the cell to
			// the point where the line intercepts the upper border is shorter than the
			// segment from the point where the line intercepts the upper border of the
			// cell to the top right corner of the cell.
			if (((yRow - e.bIntercept) / e.mSlope) - xCol < (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				//   If the segment from the top left corner of the cell to the point
				// where the line intercepts the upper border is shorter than the segment 
				// from the point where the line intercepts the upper border of the cell
				// to the top right corner of the cell the function calculates if the
				// area to the left of the line inside the cell is more than half of the
				// area of the call if it is the function returns true.
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol + INFINITECIMAL >= 1)
				{
					return true;
				}
			}
		}
	}

	//   If the function didn't return true yet the function returns false.
	return false;
}

//   This function returns true if the cell it is checking is "behind the wall" from the 
// point of view of the player.
bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{	
	//   First the function checks if the wall its checking is one tall but not one wide,
	// and the player is in the same row as the wall.
	if (bottom - top == 1 && right - left != 1 && pov.y == top + 0.5)
	{
		//   If the wall is one tall but not one wide and the player is in the same row
		// as the wall, if it is the function checks if the player is to the left of the 
		// wall.
		if (pov.x < left)
		{
			//   If the player is to the left of the wall the function checks if the cell
			// we are checking is to the right of the left cell of the wall, if it is the
			// function returns true.
			if (xCol > left)
			{
				return true;
			}
			
			//   If the player is to the left of the wall the function checks if the cell 
			// we are checking isn't in the same row  as the wall, and it is in the same
			// column as the leftmost cell of the wall or to the right of said cells, if
			// it is the function returns true.
			if (xCol >= left && yRow != top)
			{
				return true;
			}
		}
		
		//   If the wall is one tall but not one wide and the player is in  the same row 
		// as the wall, if it is the function checks if the  player is to the right of
		// the wall.
		if (pov.x > right)
		{
			//   If the player is to the right of the wall the function  checks if the 
			// cell we are checking is to the left of the right cell of the wall, if it
			// is the fuction returns true.
			if (xCol < right - 1)
			{
				return true;
			}
			
			//   If the player is to the right of the wall the function checks if the 
			// cell we are checking isn't in the same row as the wall, and it is in the
			// same column as the rightmost cell of the wall or to the left of said 
			// cells, if it is the function returns true.
			if (xCol <= right - 1 && yRow != top)
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the wall its checking is one wide but not one tall, 
	// and the player is in the same column as the wall.
	if (right - left == 1 && bottom - top != 1 && pov.x == left + 0.5)
	{
		//   If the wall is one wide but not one tall and the player is in the same 
		// column as the wall, if it is the function checks if the player is above of the
		// wall.
		if (pov.y < top)
		{
			//   If the player is above the wall the function checks if the cell we are
			// checking is below the top cell of the wall, if it is the function returns
			// true.
			if (yRow > top)
			{
				return true;
			}
			//   If the player is above the wall the function checks if the cell we are
			// checking isn't in the same column as the wall, and it is in the same row
			// as the topmost cell of the wall or below said cells, if it is the function
			// returns true.
			if (yRow >= top && xCol != left)
			{
				return true;
			}
		}
		
		//   If the wall is one wide but not one tall and the player is in the same
		// column as the wall, if it is the function checks if the player is below the
		// wall.
		if (pov.y > bottom)
		{
			//   If the player is below the wall the function checks if the cell we are
			// checking is above the bottom cell of the wall if it is the function
			// returns true.
			if (yRow < bottom - 1)
			{
				return true;
			}
			
			//   If the player is below the wall the function checks if the cell we are
			// checking isn't in the same column as the wall, and it is in the same row
			// as the bottom cell of the wall or above said cells, if it is the function
			// returns true.
			if (yRow <= bottom - 1 && xCol != left)
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the player is below the row of the top cell of the
	// wall, above the row of the bottom cell of the wall whilst the height of the wall
	// is at least 2.
	if (pov.y > top && pov.y < bottom && bottom - top != 1)
	{
		//   If the player is below the row of the top cell of the wall, above the row of
		// the bottom cell of the wall and the wall's height is at least 2 the function
		// checks if the player is to the left of the wall.
		if (pov.x < left)
		{
			//   If the player is to the left of the wall the function checks if the cell
			// we are checking is to the right of the wall, if it is the function returns
			// true.
			if (xCol > left)
			{
				return true;
			}
			
			//   If the player is to the left of the wall the function checks if the cell
			// we are checking is in the same column as the wall and is above the top 
			// cell or below the bottom cell of the wall, if it is the function returns 
			// true.
			if (xCol == left && (yRow < top || yRow > bottom - 1))
			{
				return true;
			}
		}
		
		//   If the player is below the row of the top cell of the wall, above the row of
		// the bottom cell of the wall and the wall's height is at least 2 the function
		// checks if the player is to the right of the wall.
		if (pov.x > right - 1)
		{
			//   If the player is to the right of the wall the function checks if the 
			// cell we are checking is to the left of the wall, if it is the function
			// returns true.
			if (xCol < right - 1)
			{
				return true;
			}
			
			//   If the player is to the right of the wall the function checks if the
			// cell we are checking is in the same column as the wall and is above the
			// top cell or below the bottom cell of the wall, if it is the function
			// returns true.
			if (xCol == left && (yRow < top || yRow > bottom - 1))
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the player is to the right of the column of the
	// leftmost cell of the wall, to the left of the column of the leftmost cell of the
	// wall whilst the length of the wall is at least 2.
	if (pov.x > left && pov.x < right && right - left != 1)
	{
		//   If the player is to the right of the column of the leftmost cell of the 
		// wall, to the left of the rightmost column of the wall and the wall's length is
		// at least 2 the function checks if the player is above the wall.
		if (pov.y < top)
		{
			//   If the player is above the wall the function checks if the cell we are
			// currently checking is below the wall, if it is the function returns true.
			if (yRow > top)
			{
				return true;
			}
			
			//   If the player is above the wall the function checks if the cell we are
			// currently checking is in the same row as the wall and is to the left of
			// the rightmost cell or to the right of the leftmost cell of the wall if it
			// is the function returns true.
			if (yRow == top && (xCol < left || xCol > right - 1))
			{
				return true;
			}
		}
		
		//   If the player is to the right of the column of the leftmost cell of the
		// wall, to the left of the rightmost column of the wall and the wall's length
		// is at least 2 the function checks if the player is below the wall.
		if (pov.y > bottom - 1)
		{
			//   If the player is below the wall the function checks if the cell we are
			// currently checking is above the wall, if it is the function returns true.
			if (yRow < bottom - 1)
			{
				return true;
			}
			
			//   If the player is below the wall the function checks if the cell we are
			// currently checking is in the same row as the wall and is to the left of
			// the rightmost cell or to the right of the leftmost cell of the wall if it
			// is the function returns true. 
			if (yRow == top && (xCol < left || xCol > right - 1))
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the player is above the wall whilst the height of
	// the wall is at least 2.
	if (pov.y < top && bottom - top != 1)
	{
		//   If the player is above the wall and the heigth of that wall is at least 2
		// the function checks if the player is to the left of the wall.
		if (pov.x < left)
		{
			//   If the player is to the left of the wall the function checks if the cell
			// we are checking is to the right of the wall and is below the row of the
			// top cell of the wall, if it is the function returns true.
			if (xCol > left && yRow >= top)
			{
				return true;
			}
			
			//   If the player is to the left of the wall the function checks if the cell
			// we are checking is in the same column as the wall and is below the bottom
			// cell of the wall, if it is the function returns true.
			if (xCol == left && yRow > bottom - 1)
			{
				return true;
			}
		}
		
		//   If the player is above the wall and the heigth of that wall is at least 2
		// the function checks if the player is to the right of the wall.
		if (pov.x > right - 1)
		{
			//   If the player is to the right of the wall the function checks if the
			// cell we are checking is to the left of the wall and is below the row of
			// the top cell of the wall, if it is the function returns true.
			if (xCol < right - 1 && yRow >= top)
			{
				return true;
			}
			
			//   If the player is to the right of the wall the function checks if the
			// cell we are checking is in the same column as the wall and is below the
			// bottom cell of the wall, if it is the function returns true.
			if (xCol == left && yRow > bottom - 1)
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the player is below the wall whilst the height of
	// the wall is at least 2.
	if (pov.y > bottom - 1 && bottom - top != 1)
	{
		//   If the player is below the wall and the height of the wall is at least 2 the
		// function checks if the player is to the left of the wall.
		if (pov.x < left)
		{
			//   If the player is to the left of the wall the function checks if the cell
			// we are currently checking is to the right of the wall and is above the row
			// of the bottom cell of the wall, if it is the function returns true.
			if (xCol > left && yRow <= bottom - 1)
			{
				return true;
			}
			
			//   If the player is to the left of the wall the function checks if the cell
			// we are currently checking is in the same column as the wall and is above 
			// the top cell of the wall, if it is the function returns true.
			if (xCol == left && yRow < top)
			{
				return true;
			}
		}
		
		//   If the player is below the wall and the height of the wall is at least 2 the
		// function checks if the player is to the right of the wall.
		if (pov.x > right - 1)
		{
			//   If the player is to the right of the wall the function checks if the
			// cell we are currently checking is to the left of the wall and is above the
			// row of the bottom cell of the wall, if it is the function returns true.
			if (xCol < right - 1 && yRow <= bottom - 1)
			{
				return true;
			}
			
			//   If the player is to the right of the wall the function checks if the
			// cell we are currently checking is in the same column as the wall and is
			// above the top cell of the wall, if it is the function returns true.
			if (xCol == left && yRow < top)
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the player is to the left of the wall and the length
	// of the wall is at least 2.
	if (pov.x < left && right - left != 1)
	{
		//   If the player is to the left of the wall and the length of the wall is at
		// least 2 the function checks if the player is above the wall.
		if (pov.y < top)
		{
			//   If the player is above the wall the function checks if the cell we are 
			// checking is below the wall and is to the right of the column of the
			// leftmost cell in the wall, if it is the function returns true.
			if (yRow > top && xCol >= left)
			{
				return true;
			}
			
			//   If the player is above the wall the function checks if the cell we are 
			// checking is in the same row as the wall and is to the right of the wall, 
			// if it is the function returns true.
			if (yRow == top && xCol > right - 1)
			{
				return true;
			}
		}
		
		//   If the player is to the left of the wall and the length of the wall is at
		// least 2 the function checks if the player is below the wall.
		if (pov.y > bottom - 1)
		{
			//   If the player is below the wall the function checks if the cell we are 
			// checking is above the wall and is to the right of the column of the
			// leftomost cell in the wall, if it is the function returns true.
			if (yRow < bottom - 1 && xCol >= left)
			{
				return true;
			}
			
			//   If the player is below the wall the function checks if the cell we are 
			// checking is in the same row as the wall and is to the right of the wall,
			// if it is the function returns true.
			if (yRow == top && xCol > right - 1)
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the player is to the right of the wall and the
	// length of the wall is at least 2.
	if (pov.x > right - 1 && right - left != 1)
	{
		//   If the player is to the right of the wall and the length of the wall is at
		// least 2 the function checks if the player is above the wall.
		if (pov.y < top)
		{
			//   If the player is above the wall the function checks if the cell we are
			// checking is below the wall and is to the left of the column of the
			// rightmost cell in the wall, if it is the function returns true.
			if (yRow > bottom - 1 && xCol <= right - 1)
			{
				return true;
			}
			
			//   If the player is above the wall the function checks if the cell we are
			// checking is in the same row as the wall and is to the left of the wall, if 
			// it is the function returns true.
			if (yRow == top && xCol < left)
			{
				return true;
			}
		}
		
		//   If the player is to the right of the wall and the length of the wall is at
		// least 2 the function checks if the player is below the wall.
		if (pov.y > bottom - 1)
		{
			//   If the player is below the wall the function checks if the cell we are
			// checking is above the wall and is to the left of the column of the
			// rightmost cell in the wall, if it is the function returns true.
			if (yRow < top && xCol <= right - 1)
			{
				return true;
			}
			
				//   If the player is below the wall the function checks if the cell we
			// are checking is in the same row as the wall and is to the left of the
			// wall, if it is the function returns true.
			if (yRow == top && xCol < left)
			{
				return true;
			}
		}
	}
	
	//   Finally the function checks if both the height and length of the wall is exactly
	// one.
	if (bottom - top == 1 && right - left == 1)
	{
		//   If both the height and length of the wall is exactly one the function checks
		// if both the player and the cell we are checking is left of the column of the
		// wall, if it is the function returns false.
		if (pov.x < left && xCol < left)
		{
			return false;
		}
		
		//   If both the height and length of the wall is exactly one the function checks
		// if both the player and the cell we are checking is right of the column of the
		// wall, if it is the function returns false.
		if (pov.x > right && xCol > right - 1)
		{
			return false;
		}
		
		//   If both the height and length of the wall is exactly one the function checks
		// if both the player and the cell we are checking is above the row of the wall, 
		// if it is the function returns false.
		if (pov.y < top && yRow < top)
		{
			return false;
		}
		
		//   If both the height and length of the wall is exactly one the function checks
		// if both the player and the cell we are checking is below the row of the wall, 
		// if it is the function returns false.
		if (pov.y > bottom && yRow > bottom - 1)
		{
			return false;
		}
		
		//   If both the height and length of the wall is exactly one the function checks
		// if the cell we are checking is the cell of the wall, if it is the function
		// returns false.
		if (xCol == left && yRow == top)
		{
			return false;
		}
		
		//   If both the height and length of the wall is exactly one and the function
		// haven't returned false yet then the function returns true.
		return true;
	}
	
	//   If the function haven't returned true yet for the cell we are checking the
	// function returns false.
	return false;
}

//   This function returns true if the cell we are checking is in a "T-shape" with the
// wall.
bool tShapeDetector(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{
	//   First the function checks if the wall is one tall.
	if (bottom - top == 1)
	{
		//   If the wall is one tall the function checks if the player is to the left of
		// the wall.
		if (pov.x < left)
		{
			//   If the player is to the left of the wall the function checks if the cell
			// it is currently checking is in the same column as the leftmost cell of the
			// wall, if it is the function returns true.
			if (xCol == left)
			{
				return true;
			}
		}
		
		//   If the wall is one tall the function checks if the player is to the right of
		// the wall.
		if (pov.x > right)
		{
			//   If the player is to the right of the wall the function checks if the
			// cell we are currently checking is in the same column as the rightmost cell
			// of the wall, if it is the function returns true.
			if (xCol == right - 1)
			{
				return true;
			}
		}
	}
	
	//   Next the function checks if the wall is one wide.
	if (right - left == 1)
	{
		//   If the wall is one wide the function checks if the player is above the wall.
		if (pov.y < top)
		{
			//   If the player is above the wall the function checks if the cell it is
			// currently checking is in the same row as the top cell of the wall, if it
			// is the function returns true.
			if (yRow == top)
			{
				return true;
			}
		}
		
		//   If the wall is one wide the function checks if the player is below the wall.
		if (pov.y > bottom)
		{
			//   If the player is below the wall the function checks if the cell it is
			// currentyl cehcking is in the same row as the bottom cell of the wall, if
			// it is the function returns true.
			if (xCol == bottom - 1)
			{
				return true;
			}
		}
	}
	
	//   If the function didn't return true yet the function returns false.
	return false;
}

//   This function gets the two lines that are cast to the "edges" of a rectangle from a
// givent point.
edgeLines getEdgeLines(koordinate pov, int top, int bot, int right, int left)
{
	edgeLines edg;
	
	//   The function checks if the player is above the wall.
	if (pov.y < top)
	{
		//   If the player is above the wall the function is checks if the player is to 
		// the left of the wall, if the player is in this position the function returns 
		// the lines that are cast to the correct "edges" of the wall.
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		//   If the player is above the wall but not to the left of the wall the function
		// checks if the player is to the right of the wall if the player is in this 
		// position the function returns the lines that are cast to the correct "edges"
        // of the wall.
		else if (pov.x > right)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, right, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		else
		{
			//   If the player is above the wall but it isn't above, to the left of or to 
			// the right of the wall the function returns the lines that are cast to the 
			// correct "edges" of the wall from this position of the player.
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, top);
			edg.second.isItUnderLine = false;
			return edg;
		}
	}
	//   If the player isn't above the wall the function checks if the player is below
	// the wall.
	else if (pov.y > bot)
	{
		//   If the player is below the wall the function is checks if the player is to 
		// the left of the wall, if the player is in this position the function returns 
		// the lines that are cast to the correct "edges" of the wall.
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, right, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		//   If the player is below the wall but not to the left of the wall the function
		// checks if the player is to the right of the wall if the player is in this 
		// position the function returns the lines that are cast to the correct "edges"
        // of the wall.
		else if (pov.x > right)
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		else
		{
			//   If the player is below the wall but it isn't above, to the left of or to 
			// the right of the wall the function returns the lines that are cast to the 
			// correct "edges" of the wall from this position of the player.
			edg.first = getLineEquation(pov.x, pov.y, right, bot);
			edg.first.isItUnderLine = true;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
	}
	else
	{	
		//   If the player is neither above or below the wall the function checks if the
		// player is to the left of the wall, if it is the function returns the lines 
		// that are cast to the correct "edges" of the wall from this position of the
        // player.
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		//   If the player is neither above, below or to the left of the wall the 
		// function checks if the player is to the right of the wall, if it is the 
		// function returns the lines that are cast to the correct "edges" of the wall 
		// from this position of the player.
		else if (pov.x > right)
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, right, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
	}
}

//   This function shades the visible cells on the screen.
void shadowFunction(map world[WORLDROWS][WORLDCOLS], int cameraCol, int cameraRow, koordinate pov, edgeLines edg)
{
	//   First the function loops over every row that is currently visible on the sceen.
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		int j = 0;
		
		//   Then the function loops over every cell in the current row.
		while (j < SCREENCOLS)
		{
			//   The function checks if the current cell dosen't let light through.
			if (world[i + cameraRow][j + cameraCol].solid)
			{
				int k = 0;
				
				//   If the current cell dosen't let light through the function starts
				// checking every cell to the right of the first cell untill it finds a 
				// cell that lets light through, with this the function determines a 
				// rectangle/wall.
				while (world[i + cameraRow][j + cameraCol + k].solid)
				{
					k++;
				}
				
				//   The function checks if the wall is longer than one cell.
				if (k > 1)
				{
					//   If the legth is at least 2 the function gets the lines that are
					// cast to the "edges" of the wall from the players position.
					edg = getEdgeLines(pov, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol);
				
					//   With these lines the function starts looping over every cell of
					// the screen.
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for(int h = 0; h < SCREENCOLS; h++)
						{
							//   The function checks if the current cell is behind the
							// wall compared to the player.
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
							{
								//   If the current cell is behind the wall the function
								// checks if the area of the shaded part of the cell is 
								// more than half of the area of the cell.
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									//   If the area of the shaded part of the cell is 
									// more than half of the area of the cell the
									// function checks if the current cell lets light
									// through or isn't part of a "T-shape", if at least
									// one of those statements is true the function sets
									// the current cell's visibility to false.
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
								//   If the current cell is behind the wall the function
								// checks if said cell is entirelly between two lines, if
								// it is the function sets the cell's visibility to
                                // false.
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol))
								{
									world[g + cameraRow][h + cameraCol].mapInView = false;
								}
							}
						}
					}
				}
				
				j += k;
			}
			else
			{
				j++;
			}
		}
	}
	
	//   Next the function loops over every column that is currently visible on the 
    // screen.
	for (int i = 0; i < SCREENCOLS; i++)
	{
		int j = 0;
		
		//   Then the function loops over every cell in the current column.
		while (j < CONSOLEROWS)
		{
			//   The function checks if the current cell dosen't let light through.
			if (world[j + cameraRow][i + cameraCol].solid)
			{
				int k = 0;
				
				//   If the current cell dosen't let light through the function starts
				// checking every cell below the first cell untill it finds a cell that
				// lets light through, with this the function determines a 
                // rectangle/wall.
				while (world[j + cameraRow + k][i + cameraCol].solid)
				{
					k++;
				}
				
				//   The function checks if the wall is taller than one cell.
				if (k > 1)
				{
					//   If the height is at least 2 the function gets the lines that are
					// cast to the "edges" of the wall from the players position.
					edg = getEdgeLines(pov, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol);
				
					//   With these lines the function starts looping over every cell of
					// the screen.
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							//   The function checks if the current cell is behind the
							// wall compared to the player.
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
							{
								//   If the current cell is behind the wall the function
								// checks if the area of the shaded part of the cell is 
								// more than half of the area of the cell.
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									//   If the area of the shaded part of the cell is 
									// more than half of the area of the cell the 
									// function checks if the current cell lets light
									// through or isn't part of a "T-shape", if at least
									// one of those statements is true the function sets
									// the current cell's visibility to false.
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
								//   If the current cell is behind the wall the function
								// checks if said cell is entirelly between two lines, if
								// it is the function sets the cell's visibility to
                                // false.
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol))
								{
									world[g + cameraRow][h + cameraCol].mapInView = false;
								}
							}
						}
					}
				}
				//   If the wall isn't taller than one cell the function checks if 
				// neither of the cells to the right and to the left of the wall block
                // light.
				else if (!world[j + cameraRow][i + cameraCol + 1].solid && !world[j + cameraRow][i + cameraCol - 1].solid)
				{
					//   If neither of the cells to the right and to the left of the cell
					// block light the function gets the lines that are cast to the 
					// "edges" of the wall from the players position.
					edg = getEdgeLines(pov, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol);
					
					//   With these lines the function starts looping over every cell of
					// the screen.
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							//   The function checks if the current cell is behind the
							// wall compared to the player.
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
							{
								//   If the current cell is behind the wall the function
								// checks if the area of the shaded part of the cell is 
								// more than half of the area of the cell.
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									//   If the area of the shaded part of the cell is 
									// more than half of the area of the cell the 
									// function checks if the current cell lets light
									// through or isn't part of a "T-shape", if at least
									// one of those statements is true the function sets
									// the current cell's visibility to false.
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
								//   If the current cell is behind the wall the function
								// checks if said cell is entirelly between two lines, if
								// it is the function sets the cell's visibility to
                                // false.
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol))
								{
									world[g + cameraRow][h + cameraCol].mapInView = false;
								}
							}
						}
					}
				}
				
				j += k;
			}
			else
			{
				j++;
			}
		}
	}
}

//   This function plugs any 1 by 1 "holes" that are entirelly surrounded by cells that 
// are either not visible or don't let light through.
void holePlugger(map world[WORLDROWS][WORLDCOLS], int cameraCol, int cameraRow)
{
	//   The function loops through every cell in the frame.
	for (int i = 0; i < SCREENCOLS; i++)
	{
		for (int j = 0; j < CONSOLEROWS; j++)
		{
			//   The function checks if the current cell is visile.
			if (world[j + cameraRow][i + cameraCol].mapInView)
			{
				//   If the current cell is visible the function checks if the 4 cells
				// surrounding it are all either not visible or don't let light trhough,
				// if this is true for all 4 cells the function sets the visibility of 
				// the current cell to false.
				if ((world[j + cameraRow + 1][i + cameraCol].solid || !world[j + cameraRow + 1][i + cameraCol].mapInView) && (world[j + cameraRow - 1][i + cameraCol].solid || !world[j + cameraRow - 1][i + cameraCol].mapInView) && (world[j + cameraRow][i + cameraCol + 1].solid || !world[j + cameraRow][i + cameraCol + 1].mapInView) && (world[j + cameraRow][i + cameraCol - 1].solid || !world[j + cameraRow][i + cameraCol - 1].mapInView))
				{
					world[j + cameraRow][i + cameraCol].mapInView = false;
				}
			} 
		}
	}
}

//   This function returns true if there are any cells next to this one (diagonally as
// well) that are in view.
bool isBesideNotSolidInView(map world[WORLDROWS][WORLDCOLS], int xCol, int yRow)
{
	//   The function loops through all of the 8 cells surrounding the cell we are
	// checking with, and also said cell.
	for (int i = yRow - 1; i <= yRow + 1; i++)
	{
		for (int j = xCol - 1; j <= xCol + 1; j++)
		{
			//   If the current cell we are checking is in view the function returns
			// true.
			if (world[j][i].mapInView)
			{
				return true;
			}
		}
	}
	
	//   If the function didn't return true it returns false.
	return false;
}

//   This function determines which cells are on the edge of the not visible parts on the
// current frame.
void mapIsEdgeCalculation(map world[WORLDROWS][WORLDCOLS], int cameraRow, int cameraCol)
{
	//   First the function loops through every cell that isn't in the frame but is to
	// the left/right of a cell that is on the left/right edge of the cells in the frame,
	// and sets their visibility to false.
	for (int i = 0; i < CONSOLEROWS + 2; i++)
	{
		world[cameraRow - 1 + i][cameraCol - 1].mapInView = false;
		world[cameraRow - 1 + i][cameraCol + SCREENCOLS].mapInView = false;
	}
	
	//   Next the function loops through every cell that isn't in the frame but is
	// above/below of a cell that is on the top/bottom edge of the cells in the frame,
	// and sets their visibility to false.
	for (int i = 0; i < SCREENCOLS + 2; i++)
	{
		world[cameraRow - 1][cameraCol - 1 + i].mapInView = false;
		world[cameraRow + CONSOLEROWS][cameraCol - 1 + i].mapInView = false;
	}
	
	//   Then the function loops through every cell in the frame.
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		for (int j = 0; j < SCREENCOLS; j++)
		{
			//   The function checks if the current cell isn't visible.
			if (!world[i + cameraRow][j + cameraCol].mapInView)
			{
				//   If he current cell isn't visible the function checks if there are 
				// any cells next to it that are, if there aren't any such cells the 
				// function sets the current cell to be an "edge".
				if (isBesideNotSolidInView(world, i + cameraRow, j + cameraCol))
				{
					world[i + cameraRow][j + cameraCol].mapIsEdge = true;
				}
			}
		}
	}
}
