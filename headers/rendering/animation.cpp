// For further infromation about the code please refer back to the documentation!


#include "animation.h"

//   This function initalizes an anmiation.
animation initNewAnimation(animation anim, string fileName)
{
	//   First we get a temporary variable we can read characters into and check for 
	// different things.
	char cahr;
	
	//   Next we open the file.
	fstream fbe (fileName.c_str());
	
	//   After that we read the amount of frames the animation has, the height of each
	// frame and the widht of every frame.
	fbe>>anim.frames>>anim.height>>anim.width;
	
	//   Then we set the currentFrame sub variable of the structure to 0.
	anim.currentFrame = 0;
	
	//   After all that we loop over evey cell of every frame of the animation.
	for (int g = 0; g < anim.frames; g++)
	{
		for (int i = 0; i < anim.height; i++)
		{
			for (int j = 0; j < anim.width; j++)
			{
				//   We read the next character into cahr.
				fbe>>cahr;
				
				//   We check if the character we just read was an 'i'.
				if (cahr == 'i')
				{
					//   If the character we just read was an 'i' we make the texture of 
					// the variable a ' ' character.
					anim.frameArray[g][i][j] = ' ';
				}
				else
				{
					//   If the character we just read wasn't an 'i' we make the texture
					// of the variable the character we just read.
					anim.frameArray[g][i][j] = cahr;
				}
			}
		}
	}

	//   Lastly the function closes the .txt file.
	fbe.close();

	return anim;
}

//   This function plays the animation frame by frame.
void playAnimation(char console[CONSOLEROWS][CONSOLECOLS], animation anim, int yRow, int xCol)
{
	//   The function checks if the current frame of the animation is still an existing
	// frame of the animation.	
	if (anim.currentFrame < anim.frames)
	{
		//   If the current frame does exist we loop through all the variables of the 
		// current frame of the animation.
		for (int i = 0; i < anim.height; i++)
		{
			for (int j = 0; j < anim.width; j++)
			{
				//   The function writes every variable into the correct cell (all
				// positions being offset with yRow and xCol).
				console[yRow + i][xCol + j] = anim.frameArray[anim.currentFrame][i][j];
			}
		}
	}
}
