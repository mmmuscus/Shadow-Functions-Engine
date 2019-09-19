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

	//   If the function didn't return true yet the function returns false;
	return false;
}

bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{	
	if (bottom - top == 1 && right - left != 1 && pov.y == top + 0.5)
	{
		if (pov.x < left)
		{
			if (xCol > left)
			{
				return true;
			}
			
			if (xCol >= left && yRow != top)
			{
				return true;
			}
		}
		
		if (pov.x > right)
		{
			if (xCol < right - 1)
			{
				return true;
			}
			
			if (xCol <= right - 1 && yRow != top)
			{
				return true;
			}
		}
	}
	
	if (right - left == 1 && bottom - top != 1 && pov.x == left + 0.5)
	{
		if (pov.y < top)
		{
			if (yRow > top)
			{
				return true;
			}
			
			if (yRow >= top && xCol != left)
			{
				return true;
			}
		}
		
		if (pov.y > bottom)
		{
			if (yRow < bottom - 1)
			{
				return true;
			}
			
			if (yRow <= bottom - 1 && xCol != left)
			{
				return true;
			}
		}
	}
	
	if (pov.y > top && pov.y < bottom && bottom - top != 1)
	{
		if (pov.x < left)
		{
			if (xCol > left)
			{
				return true;
			}
			
			if (xCol == left && (yRow < top || yRow > bottom - 1))
			{
				return true;
			}
		}
		
		if (pov.x > right - 1)
		{
			if (xCol < right - 1)
			{
				return true;
			}
			
			if (xCol == left && (yRow < top || yRow > bottom - 1))
			{
				return true;
			}
		}
	}
	
	if (pov.x > left && pov.x < right && right - left != 1)
	{
		if (pov.y < top)
		{
			if (yRow > top)
			{
				return true;
			}
			
			if (yRow == top && (xCol < left || xCol > right - 1))
			{
				return true;
			}
		}
		
		if (pov.y > bottom - 1)
		{
			if (yRow < bottom - 1)
			{
				return true;
			}
			
			if (yRow == top && (xCol < left || xCol > right - 1))
			{
				return true;
			}
		}
	}
	
	if (pov.y < top && bottom - top != 1)
	{
		if (pov.x < left)
		{
			if (xCol > left && yRow >= top)
			{
				return true;
			}
			
			if (xCol == left && yRow > bottom - 1)
			{
				return true;
			}
		}
		
		if (pov.x > right - 1)
		{
			if (xCol < right - 1 && yRow >= top)
			{
				return true;
			}
			
			if (xCol == left && yRow > bottom - 1)
			{
				return true;
			}
		}
	}
	
	if (pov.y > bottom - 1 && bottom - top != 1)
	{
		if (pov.x < left)
		{
			if (xCol > left && yRow <= bottom - 1)
			{
				return true;
			}
			
			if (xCol == left && yRow < top)
			{
				return true;
			}
		}
		
		if (pov.x > right - 1)
		{
			if (xCol < right - 1 && yRow <= bottom - 1)
			{
				return true;
			}
			
			if (xCol == left && yRow < top)
			{
				return true;
			}
		}
	}
	
	if (pov.x < left && right - left != 1)
	{
		if (pov.y < top)
		{
			if (yRow > top && xCol >= left)
			{
				return true;
			}
			
			if (yRow == top && xCol > right - 1)
			{
				return true;
			}
		}
		
		if (pov.y > bottom - 1)
		{
			if (yRow < bottom - 1 && xCol >= left)
			{
				return true;
			}
			
			if (yRow == top && xCol > right - 1)
			{
				return true;
			}
		}
	}
	
	if (pov.x > right - 1 && right - left != 1)
	{
		if (pov.y < top)
		{
			if (yRow > bottom - 1 && xCol <= right - 1)
			{
				return true;
			}
			
			if (yRow == top && xCol < left)
			{
				return true;
			}
		}
		
		if (pov.y > bottom - 1)
		{
			if (yRow < top && xCol <= right - 1)
			{
				return true;
			}
			
			if (yRow == top && xCol < left)
			{
				return true;
			}
		}
	}
	
	if (bottom - top == 1 && right - left == 1)
	{
		if (pov.x < left && xCol < left)
		{
			return false;
		}
		
		if (pov.x > right && xCol > right - 1)
		{
			return false;
		}
		
		if (pov.y < top && yRow < top)
		{
			return false;
		}
		
		if (pov.y > bottom && yRow > bottom - 1)
		{
			return false;
		}
		
		if (xCol == left && yRow == top)
		{
			return false;
		}
		
		return true;
	}
	
	return false;
}

bool tShapeDetector(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{
	if (bottom - top == 1)
	{
		if (pov.x < left)
		{
			if (xCol == left)
			{
				return true;
			}
		}
		
		if (pov.x > right)
		{
			if (xCol == right - 1)
			{
				return true;
			}
		}
	}
	
	if (right - left == 1)
	{
		if (pov.y < top)
		{
			if (yRow == top)
			{
				return true;
			}
		}
		
		if (pov.y > bottom)
		{
			if (xCol == bottom - 1)
			{
				return true;
			}
		}
	}
	
	return false;
}

edgeLines getEdgeLines(koordinate pov, int top, int bot, int right, int left)
{
	edgeLines edg;
	
	if (pov.y < top)
	{
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
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
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, top);
			edg.second.isItUnderLine = false;
			return edg;
		}
	}
	else if (pov.y > bot)
	{
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, right, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
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
			edg.first = getLineEquation(pov.x, pov.y, right, bot);
			edg.first.isItUnderLine = true;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
	}
	else
	{
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
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

void shadowFunction(map world[WORLDROWS][WORLDCOLS], int cameraCol, int cameraRow, koordinate pov, edgeLines edg)
{
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		int j = 0;
			
		while (j < SCREENCOLS)
		{
			if (world[i + cameraRow][j + cameraCol].solid)
			{
				int k = 0;
				
				while (world[i + cameraRow][j + cameraCol + k].solid)
				{
					k++;
				}
				
				if (k > 1)
				{
					edg = getEdgeLines(pov, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol);
				
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for(int h = 0; h < SCREENCOLS; h++)
						{
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
							{
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
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
	
	for (int i = 0; i < SCREENCOLS; i++)
	{
		int j = 0;
		
		while (j < CONSOLEROWS)
		{
			if (world[j + cameraRow][i + cameraCol].solid)
			{
				int k = 0;
				
				while (world[j + cameraRow + k][i + cameraCol].solid)
				{
					k++;
				}
				
				if (k > 1)
				{
					edg = getEdgeLines(pov, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol);
				
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
							{
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol))
								{
									world[g + cameraRow][h + cameraCol].mapInView = false;
								}
							}
						}
					}
				}
				else if (!world[j + cameraRow][i + cameraCol + 1].solid && !world[j + cameraRow][i + cameraCol - 1].solid)
				{
					edg = getEdgeLines(pov, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol);
					
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
							{
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
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

void holePlugger(map world[WORLDROWS][WORLDCOLS], int cameraCol, int cameraRow)
{
	for (int i = 0; i < SCREENCOLS; i++)
	{
		for (int j = 0; j < CONSOLEROWS; j++)
		{
			if (world[j + cameraRow][i + cameraCol].mapInView)
			{
				if ((world[j + cameraRow + 1][i + cameraCol].solid || !world[j + cameraRow + 1][i + cameraCol].mapInView) && (world[j + cameraRow - 1][i + cameraCol].solid || !world[j + cameraRow - 1][i + cameraCol].mapInView) && (world[j + cameraRow][i + cameraCol + 1].solid || !world[j + cameraRow][i + cameraCol + 1].mapInView) && (world[j + cameraRow][i + cameraCol - 1].solid || !world[j + cameraRow][i + cameraCol - 1].mapInView))
				{
					world[j + cameraRow][i + cameraCol].mapInView = false;
				}
			} 
		}
	}
}

bool isBesideNotSolidInView(map world[WORLDROWS][WORLDCOLS], int xCol, int yRow)
{
	for (int i = yRow - 1; i <= yRow + 1; i++)
	{
		for (int j = xCol - 1; j <= xCol + 1; j++)
		{
			if (world[j][i].mapInView)
			{
				return true;
			}
		}
	}
	
	return false;
}

void mapIsEdgeCalculation(map world[WORLDROWS][WORLDCOLS], int cameraRow, int cameraCol)
{
	for (int i = 0; i < CONSOLEROWS + 2; i++)
	{
		world[cameraRow - 1 + i][cameraCol - 1].mapInView = false;
		world[cameraRow - 1 + i][cameraCol + SCREENCOLS].mapInView = false;
	}
	
	for (int i = 0; i < SCREENCOLS + 2; i++)
	{
		world[cameraRow - 1][cameraCol - 1 + i].mapInView = false;
		world[cameraRow + CONSOLEROWS][cameraCol - 1 + i].mapInView = false;
	}
	
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		for (int j = 0; j < SCREENCOLS; j++)
		{
			if (!world[i + cameraRow][j + cameraCol].mapInView)
			{
				if (isBesideNotSolidInView(world, i + cameraRow, j + cameraCol))
				{
					world[i + cameraRow][j + cameraCol].mapIsEdge = true;
				}
			}
		}
	}
}
