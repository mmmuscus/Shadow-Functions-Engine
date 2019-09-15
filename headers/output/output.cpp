// For further infromation about the code please refer back to the documentation!


#include "output.h"

using namespace std;

//   This function copies a console array into another console array.
void saveLastConsoleArray(char oldC[CONSOLEROWS][CONSOLECOLS], char newC[CONSOLEROWS][CONSOLECOLS])
{
	//   The function loops through all the values in the array and copies all of them
	// from one array to another.
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		for (int j = 0; j < CONSOLECOLS; j++)
		{
			oldC[i][j] = newC[i][j];
		}
	}
}

//   This function initializes all the characters that block light.
void initSolid(char solide[SOLIDCOUNT], string fileName)
{
	//   First the function opens the file.
	fstream fbe (fileName.c_str());
	
	//   Next the function loops through all the characters in the .txt file and reads
	// them in.
	for (int i = 0; i < SOLIDCOUNT; i++)
	{
		fbe>>solide[i];
	}
	
	//   Lastly the function closes the .txt file.
	fbe.close();
}

//   This function initializes all the characters that don't block player movement.
void initWalkable(char walkablee[WALKABLECOUNT], string fileName)
{
	//   First the function opens the file.
	fstream fbe (fileName.c_str());
	
	//   Next the function loops through all the characters in the .txt file and reads
	// them in.
	for (int i = 0; i < WALKABLECOUNT; i++)
	{
		fbe>>walkablee[i];
	}
	
	//   Lastly the function closes the .txt file.
	fbe.close();
}

//   This function initializes the world map.
void initWorld(map world[WORLDROWS][WORLDCOLS], char solide[SOLIDCOUNT], char walkablee[WALKABLECOUNT], string fileName)
{
	//   First we get a temporary variable we can read characters into and check for 
	// different things.
	char cahr;
	
	//   Next we open the file.
	freopen(fileName.c_str(),"r",stdin);
	
	//   After that we start looping through the characters in the .txt file.
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			//   We read the next character into cahr.
			cin>>cahr;
			
			//   We check if the character we read was an 'i'.
			if (cahr == 'i')
			{
				//   If the character we read was an 'i' we set the texture of the cell
				// to a ' ' character.
				world[i][j].texture = ' ';
			}
			else
			{
				//   If the character we read wasn't an 'i' we set the texture of the
				// cell to what we read in.
				world[i][j].texture = cahr;
			}
			
			//   Next we check if the cell we just read blocks light or player movement.
			
			//   We set the .solid sub variable of the cell to false.
			world[i][j].solid = false;
			
			//   After that we start looping through all the characters that block light.
			for (int k = 0; k < SOLIDCOUNT; k++)
			{
				//   If the character we read is one of the characters that block light
				// we set the .solid sub variable of the cell to true.
				if (cahr == solide[k])
				{
					world[i][j].solid = true;
				}
			}
			
			//   We set the .walkable sub variable of the cell to false.
			world[i][j].walkable = false;
			
			//   After that we start looping through all the characters that don't block
			// movement.
			for (int k = 0; k < WALKABLECOUNT; k++)
			{
				//   If the character we read is one of the characters that don't block
				// movement we set the .solid sub variable of the cell to true.
				if (cahr == walkablee[k])
				{
					world[i][j].walkable = true;
				}
			}
		}
	}
	
	//   Lastly the function closes the .txt file.
	fclose(stdin);
}

//   This function initializes a FOV array.
void initFOV(fov dir[FOVROWS][FOVCOLS], string fileName)
{
	//   First we get a temporary variable we can read characters into and check for 
	// different things.
	char cahr;
	
	//   Next we open the file.
	freopen(fileName.c_str(),"r",stdin);
	
	//   After that we start looping through the characters in the .txt file.
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			//   We read the next character into cahr.
			cin>>cahr;
			
			//   We check if the character we read was an '_'.
			if (cahr == '_')
			{
				//   If the character we read was an '_' we set the .inView sub variable
				// of the cell to true.
				dir[i][j].inView = true;
			}
			else
			{
				//   If the character we read wasn't an '_' we set the .inView sub
				// variable of the cell to false.
				dir[i][j].inView = false;
			}
			
			//   We check if the character we read was an '@'.
			if (cahr == '@')
			{
				//   If the character we read was an '@' we set both the .isPlayer and
				// the .inView sub variable of the cell to true.
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				//   If the character we read wasn't an '@' we set the .isPlayer sub
				// variable of the cell to false.
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	//   Lastly the function closes the .txt file.
	fclose(stdin);
}
