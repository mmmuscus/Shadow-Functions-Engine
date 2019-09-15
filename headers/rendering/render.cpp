// For further infromation about the code please refer back to the documentation!


#include "render.h"

using namespace std;

//   This function puts the cursor in a set position on the console window.
//   The working of this function can be found in the link below as the fourth answer:
// https://stackoverflow.com/questions/10401724/move-text-cursor-to-particular-screen-coordinate
void goTo (int row, int column)
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD destCoord;
	
	destCoord.X = column;
	destCoord.Y = row;
	
	SetConsoleCursorPosition(hStdout, destCoord);
}

//   This function clears the console window.
//   The workings of this function can be found at this link:
// https://docs.microsoft.com/en-us/windows/console/clearing-the-screen
void clearScreen()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	

	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; 
	DWORD dwConSize;

    // Get the number of character cells in the current buffer. 

	if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if( !FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
    	dwConSize, coordScreen, &cCharsWritten ))
    	return;

	// Get the current text attribute.

	if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
    	return;

	// Set the buffer's attributes accordingly.

	if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
    	dwConSize, coordScreen, &cCharsWritten ))
    	return;

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition( hConsole, coordScreen );
}

//   This function renders the console array onto the console window.
void renderConsole(char oldC[CONSOLEROWS][CONSOLECOLS], char newC[CONSOLEROWS][CONSOLECOLS])
{
	//   First the function loops through all of the variables in the array.
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		for (int j = 0; j < CONSOLECOLS; j++)
		{
			//   We check if the variable we are on is different in the pervious frame,
			// if it is we go to the correct cell on the console window and write the 
			// variable from the current frame onto the window.
			if (newC[i][j] != oldC[i][j])
			{
				goTo(i, j);
				cout<<newC[i][j];
			}
		}
	}
}

//   This function primes the console array to clear the screen when the renderConsole
// function gets called.
void clearConsole(char newC[CONSOLEROWS][CONSOLECOLS], char oldC[CONSOLEROWS][CONSOLECOLS])
{
	//   First the function loops through all of the variables in the array.
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		for (int j = 0; j < CONSOLECOLS; j++)
		{
			//   The function sets all the current variable of the oldConsole array to
			// 'x' and the newConsoloe array to ' '.
			newC[i][j] = ' ';
			oldC[i][j] = 'x';
		}
	}
}

//   This function produces textures according to the shading information found in the
// map array.
void calculateScreen(map world[WORLDROWS][WORLDCOLS], char screen[CONSOLEROWS][CONSOLECOLS], int cameraRow, int cameraCol)
{
	//   First the function loops through all of the variables in the array.
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		for (int j = 0; j < SCREENCOLS; j++)
		{
			//   The function checks if the current cell is in view.
			if (world[i + cameraRow][j + cameraCol].mapInView)
			{
				//   If the current cell is in view the function copies the cell's
				// texture into the newConsole array.
				screen[i][j] = world[i + cameraRow][j + cameraCol].texture;
			}
			else
			{
				//   If the current cell isn't in view the function checks if the current
				// cell is an edge.
				if (world[i + cameraRow][j + cameraCol].mapIsEdge)
				{
					//   If the current cell is an edge its texture will be the character 
					// corresponding to the ASCII code of 176.
					screen[i][j] = char(176);
				}
				else
				{
					//   If the current cell isn't an edge its texture will be the
					// character  corresponding to the ASCII code of 178.
					screen[i][j] = char(178);
				}
			}
		}
	}
}
