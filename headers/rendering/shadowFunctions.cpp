#include "shadowFunctions.h"

void makeCurrentFov(fov presetDir[FOVROWS][FOVCOLS], fov toBeDir[FOVROWS][FOVCOLS])
{
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			toBeDir[i][j].inView = presetDir[i][j].inView;
			toBeDir[i][j].isPlayer = presetDir[i][j].isPlayer;
		}
	}
}

void setCurrentFov(mob playr, fov toBecomeCurrentFov[FOVROWS][FOVCOLS], fov r[FOVROWS][FOVCOLS], fov l[FOVROWS][FOVCOLS], fov u[FOVROWS][FOVCOLS], fov d[FOVROWS][FOVCOLS], fov ru[FOVROWS][FOVCOLS], fov rd[FOVROWS][FOVCOLS], fov lu[FOVROWS][FOVCOLS], fov ld[FOVROWS][FOVCOLS])
{
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

mob getPlayerPosInFov(mob playr, mob fovPlayr)
{
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

void addFovInfoToMap(map world[WORLDROWS][WORLDCOLS], mob playr, mob fovPlayr, fov fov[FOVROWS][FOVCOLS])
{
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			world[i][j].mapIsEdge = false;
			world[i][j].mapInView = false;
		}
	}
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			if (fov[i][j].inView)
			{
				world[playr.row - fovPlayr.row + i][playr.col - fovPlayr.col + j].mapInView = true;
			}
		}
	}
}

koordinate getPov(koordinate pov, mob playr)
{
	pov.x = playr.col + 0.5;
	pov.y = playr.row + 0.5;

	return pov;
}

line getLineEquation(double aXCol, double aYRow, int bXCol, int bYRow)
{
	line e;

	e.mSlope = (bYRow - aYRow) / (bXCol - aXCol);
	e.bIntercept = aYRow - (e.mSlope * aXCol);

	return e;
}

bool isUnderLine(line e, int solidYRow, int solidXCol)
{
	if ((solidYRow <= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow <= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{
		return true;
	}

	return false;
}

bool isOverLine(line e, int solidYRow, int solidXCol)
{
	if ((solidYRow >= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow >= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{
		return true;
	}

	return false;
}

bool isBetweenLines(line a, line b, int yRow, int xCol)
{
	if (a.isItUnderLine)
	{
		if (!isUnderLine(a, yRow, xCol))
		{
			return false;
		}
	}
	else
	{
		if (!isOverLine(a, yRow, xCol))
		{
			return false;
		}
	}

	if (b.isItUnderLine)
	{
		if (!isUnderLine(b, yRow, xCol))
		{
			return false;
		}
	}
	else
	{
		if (!isOverLine(b, yRow, xCol))
		{
			return false;
		}
	}

	return true;
}

bool isMoreThanHalfInShade(line e, int yRow, int xCol)
{
	if (e.isItUnderLine)
	{
		if (xCol - INFINITECIMAL < ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			if (yRow < (e.mSlope * xCol) + e.bIntercept && yRow + 1  > (e.mSlope * xCol) + e.bIntercept)
			{
				return true;
			}
			
			if (yRow < (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1  > (e.mSlope * (xCol + 1)) + e.bIntercept)
			{
				return true;
			}
		}
		
		if (yRow - INFINITECIMAL <= (e.mSlope * xCol) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * xCol) + e.bIntercept && yRow - INFINITECIMAL <= (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * (xCol + 1)) + e.bIntercept)
		{
			if ((e.mSlope * xCol) + e.bIntercept - yRow + (e.mSlope * (xCol + 1)) + e.bIntercept - yRow + INFINITECIMAL >= 1)
			{
				return true;
			}
		}
		
		if (xCol - INFINITECIMAL <= (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= (yRow - e.bIntercept) / e.mSlope && xCol - INFINITECIMAL <= ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			if (((yRow - e.bIntercept) / e.mSlope) - xCol > (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol + INFINITECIMAL >= 1)
				{
					return true;
				}
			}
			
			if (((yRow - e.bIntercept) / e.mSlope) - xCol < (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol - INFINITECIMAL <= 1)
				{
					return true;
				}
			}
		}
	}
	
	if (!e.isItUnderLine)
	{
		if (xCol - INFINITECIMAL < (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > (yRow - e.bIntercept) / e.mSlope)
		{
			if (yRow < (e.mSlope * xCol) + e.bIntercept && yRow + 1 > (e.mSlope * xCol) + e.bIntercept)
			{
				return true;
			}
				
			if (yRow < (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 > (e.mSlope * (xCol + 1)) + e.bIntercept)
			{
				return true;
			}
		}
		
		if (yRow - INFINITECIMAL <= (e.mSlope * xCol) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * xCol) + e.bIntercept && yRow - INFINITECIMAL <= (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * (xCol + 1)) + e.bIntercept)
		{
			if ((e.mSlope * xCol) + e.bIntercept - yRow + (e.mSlope * (xCol + 1)) + e.bIntercept - yRow - INFINITECIMAL <= 1)
			{
				return true;
			}
		}
		
		if (xCol - INFINITECIMAL <= (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= (yRow - e.bIntercept) / e.mSlope && xCol - INFINITECIMAL <= ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			if (((yRow - e.bIntercept) / e.mSlope) - xCol > (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol - INFINITECIMAL <= 1)
				{
					return true;
				}
			}
			
			if (((yRow - e.bIntercept) / e.mSlope) - xCol < (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol + INFINITECIMAL >= 1)
				{
					return true;
				}
			}
		}
	}

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
				return false;
			}
		}
	}
	
	return true;
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
	for (int i = 0; i < SCREENROWS; i++)
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
				
					for (int g = 0; g < SCREENROWS; g++)
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
								
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol)/* || (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))*/)
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
		
		while (j < SCREENROWS)
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
				
					for (int g = 0; g < SCREENROWS; g++)
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
								
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol)/* || (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))*/)
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
					
					for (int g = 0; g < SCREENROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
							{
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									world[g + cameraRow][h + cameraCol].mapInView = false;
								}
								
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol)/* || (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))*/)
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
		for (int j = 0; j < SCREENROWS; j++)
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
			if (world[j][i].mapInView/* && !world[j][i].solid*/)
			{
				return true;
			}
		}
	}
	
	return false;
}

void mapIsEdgeCalculation(map world[WORLDROWS][WORLDCOLS], int cameraRow, int cameraCol)
{
	for (int i = 0; i < SCREENROWS + 2; i++)
	{
		world[cameraRow - 1 + i][cameraCol - 1].mapInView = false;
		world[cameraRow - 1 + i][cameraCol + SCREENCOLS].mapInView = false;
	}
	
	for (int i = 0; i < SCREENCOLS + 2; i++)
	{
		world[cameraRow - 1][cameraCol - 1 + i].mapInView = false;
		world[cameraRow + SCREENROWS][cameraCol - 1 + i].mapInView = false;
	}
	
	for (int i = 0; i < SCREENROWS; i++)
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
