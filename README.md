# 1. Introduction
###### This section was last checked in the 1.0.0. version of the engine
**Note:** I was using [Dev C++](https://en.wikipedia.org/wiki/Dev-C%2B%2B) as the IDE with TMD-GCC 4.9.2. as the compiler, I have seen the project not functioning as intended with other IDEs and compilers, but it's most probably gonna be fine.
## 1.1. The structure of this documentation
###### This section was last checked in the 1.0.0. version of the engine
This documentation will have three main parts and a [table of contents](#4-table-of-contents):
* [The first](#1-introduction) is the introduction (the part you are reading right now)
* [The second](#2-how-to-use-the-engine) is an overview of [how the engine works](#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) and [how you can operate it and it's different editors](#22-how-to-use-the-editors-and-other-further-details)
* [The third](#3-detailed-description-of-everything) will go over every last detail about the [defines](#31-defines), [structures](#32-structures), [variables](#33-variables-in-the-main-cpp-file) and [functions](#34-functions) the engine uses

In the [introduction](#1-introduction) I will cover [my motivation](#12-who-the-hell-am-i-and-what-the-hecky-heck-is-this) for this engine, [the idea, the end product and plans about the future of the project](#13-so-what-is-the-project).

[The second part](#2-how-to-use-the-engine) will have two segments. [The first](#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) detailing the architecture of the system, what it does. [The second](#22-how-to-use-the-editors-and-other-further-details) will be the guide to operate it. Hopefully these two segments will provide you with sufficent information to make a game with this engine.

[The last part](#3-detailed-description-of-everything) will (as mentioned above) go over the hows of the systems in place. It will be broken down into different subsections, each dealing with a header or cpp file and it's [defines](#31-defines), [structures](#32-structures), [variables](#33-variables-in-the-main-cpp-file), or [functions](#34-functions). [This part](#3-detailed-description-of-everything) will act more like a cheat sheet than anything, if you wish to conserve your sanity do not read it from start to finish in one sitting.

## 1.2. Who the hell am I and what the hecky heck is this?
###### This section was last checked in the 1.0.0. version of the engine
I am a highschool student, who is interested in computer science and more specifically, creating video games. This project was a challange I gave myself. The aim was to find out if I am able to create something rather complex with my basic understanding of programming, whilst not looking up solutions to my problems. I have already tried my hands at [a project similar to this](https://github.com/mmmuscus/Snake), but this was way more abitious so it was also a test in planning and creating coexsiting systems.

## 1.3. So what is the project?
###### This section was last checked in the 1.0.0. version of the engine
The bare minimum I wanted to accomplish was a real time 2D top down game, with a "realistic" binary shading system (this was all planned to be running in the windows console). The concept of the shading system is the following: There is a player (represented by the '@' character); who has a field of view in which he can see things; anything that would block his view (e.g.: an 'x' character) casts a shadow, meaning that he can't see the things behind the "wall", even if those things would be in his field of view.

Here is an example for the shading system in action:

![example](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/screenShots/example.png)

Right now this system has a small bug, which I will discuss in [a later section of the documentation](#34512-shadowfunction). Besides the minimum goal I created basic text file based level and field of view editors. I also created the option to make new characters that could block light, or player movement.

Features as of now:
* Real time 8 directional player movement
* Binary shading
* Map and field of view editors
* Character attribute editors (can this character block light? can it block player movement?)

The next main goal of the project is to make an animation pipeline. The plan for it is to have every frame drawn in a textfile under each other, with a general function that can read any animation text file into a 3 dimensional array, and another general function that could play said animation in a set position on the screen. Beside this main goal I plan to make several quality of life changes to the different text based editors and to the structure and efficency of the code in general.

# 3. Detailed description of EVERYTHING
###### This section was last checked in the 1.0.0. version of the engine
This segment of the documentation will have four main subsections:
* [Defines](#31-defines)
* [Structures](#32-structures)
* [Variables](#33-variables-in-the-main-cpp-file)
* [Functions](#34-functions)

## 3.4. Functions
###### This section was last checked in the 1.0.0. version of the engine
This section of [the third chapter of the documentation](#3-detailed-description-of-everything) will not go over the functions in order of apperance (as opposed to the previous sections) but in the order that they are in their header files. Thus this section will have the following parts:
* [input.h](#341-inputh)
* [movement.h](#342-movementh)
* [output.h](#343-outputh)
* [render.h](#344-renderh)
* [shadowFunctions.h](#345-shadowfunctionsh)
### 3.4.1. [input.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/input/input.h)
###### This section was last checked in the 1.0.0. version of the engine
This header file contains functions that deal with the input coming form the keboard.
#### 3.4.1.1. ___Pressed
###### This section was last checked in the 1.0.0. version of the engine
```cpp
bool wPressed()
{
	if (GetKeyState('W') & 0x8000)
	{
		return true;
	}
}

bool aPressed()
{
	if (GetKeyState('A') & 0x8000)
	{
		return true;
	}
}

bool sPressed()
{
	if (GetKeyState('S') & 0x8000)
	{
		return true;
	}
}

bool dPressed()
{
	if (GetKeyState('D') & 0x8000)
	{
		return true;
	}
}

bool escPressed()
{
	if (GetKeyState(VK_ESCAPE) & 0x8000) 
	{
		return true;
	}
}
```

**Usage:** These functions return true when the correct key is pressed down.

**Variables:** -

**How it's done & notes:** The functions use another function called [GetKeyState](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getkeystate). This function can be found in [the windiws.h header](https://en.wikipedia.org/wiki/Windows.h) which countains lots of useful functions from the windows API. The ___Pressed functions are one of the three places where I used external resources to solve my problem. The other link I used to write these can be found [here](https://stackoverflow.com/questions/6331868/using-getkeystate).
#### 3.4.1.2. cancelOut
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void cancelOut (bool plus, bool minus)
{
	if (plus && minus)
	{
		plus = false;
		minus = false;
	}
}
```
**Usage:** This function cancels out two bools if they are both true.

**Variables:**
* **plus:** Holds the first bool we want to check.
* **minus:** Holds the second bool we want to check.

**How it's done & notes:** We check if both of the variables are ture. If they are we set them both to false. This is used to cancel out contradictory input (for example when both the a and d keys are pressed), but it could be used for any form of cancellation of contradictory bools.
### 3.4.2. [movement.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/output/movement.h)
###### This section was last checked in the 1.0.0. version of the engine
This header file contains functions that deal with moving the player and the camera according to what the inputs and the game world dictates.
#### 3.4.2.1. playerMovement
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function calculates where the player would be according to this frame's inputs.

**Variables:**
* **playr:** This variable holds the position of the player character.
* **w:** This is true when the w key is pressed down, if it is the player gets moved up. 
* **s:** This is true when the s key is pressed down, if it is the player gets moved down.
* **a:** This is true when the a key is pressed down, if it is the player gets moved to the left.
* **d:** This is true when the d key is pressed down, if it is the player gets moved to the right.

**How it's done & notes:** The function checks for each of the four bools and increments the player's position if any is true. This function only calculates the possible position of the player. This position can be inside walls, the [keepInBounds](#3422-keepinbounds) function is the one responsible for clearing up those sort of messes.
#### 3.4.2.2. keepInBounds
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function prevents the player from passing into unpassable objects.

**Variables:**
* **playr:** This variable holds the current caluclated possible position of the player (or in other words the cell the player wants to pass into accordint to the input).
* **lastPlayr:** This variable holds the player's position from the last frame.
* **world:** This array holds the map of the world with all of the attributes of each cell.

**How it's done & notes:** First we check if both of the coordinates of the player have changed. We do this because if it haven't, we have an easy time, we only need to set back the player into the last frame's position if the cell he passed into blocks player movement (this attribute is stored in the .walkable part of the map structure, more information can be found [here](#322-map)). If however both of the coordinates have changed from the last frame's position we need to check a few more things. 

For the rest of this explanation let's assume that the player on the last frame was on the (a; b) cell, and now he wants to pass into the (a + 1; b + 1) cell. I will use some small graphs to explain the different cases in this function. In these graphs the '@' represents the player on the last frame (or the (a; b) cell), the '#' represents the calculated possible location of the player for this frame (or the (a + 1; b + 1) cell) and the 'x' characters represent cells that block player movement (if the '#' and 'x' characters would overlap they will be replaced by an '0'). The '|' characters are only there to make the graphs prettier and easier to interpret.

```
|@x|
|x#|
```
The next thing we need to check is if the cell the player wants to pass into blocks player movement. If it doesn't we still need to check if the two cells that are next to the player from the last frame in the direction of the desired location block movement (see the figure above), if they do we don't let the player move, because the player would pass through walls, and that is not something we want.

```
|@ |
| 0|
```
If the cell the player wishes to pass into does block movement we need to check if the cells that are next to the player from the last frame in the direction of the desired location block movement (see the figure above), if they don't, we don't let the player move, because he is up against the edge of the deisred location (which blocks movement), and opposed to later cases (see below) the character can't really "slide" on either side of said cell.

```
1. |@ |
   |x0|
   
2. |@x|
   | 0|
```
After the above cases we can be sure, that the desired location blocks movement, and that at least one of the cells that are next to the player from the last frame in the direction of the desired location block movement (see the first two figures from [this very section](#3422-keepinbounds)). We check for these cells one by one, if both of them block movement we don't move the player. If only one is blocking movement we "slide" the player in the logical direction (see the figures above: in the case of the 1st figure we "slide" him to the right, and in the case of the 2nd figure we "slide" him downwards). The logic behind this is the following: the player wants to move to (a + 1; b + 1) but that cell is not avalaible for movement. The inputs consist of the s button (which signals the desire to move downwards) and the d button (which signals the desire to move to the right), so if the player can't move downward AND to the right, he should move to at least in one of the directions he wants to.
#### 3.4.2.3. setDirections
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function sets the orientational bools into the correct position (accordint to the input) in the player variable.

**Variables:**
* **playr:** This variable holds the orientation of the player character.
* **w:** This is true when the w key is pressed down. 
* **s:** This is true when the s key is pressed down.
* **a:** This is true when the a key is pressed down.
* **d:** This is true when the d key is pressed down.

**How it's done & notes:** First the function sets all directional bools to false (to learn more about the mob structure click [here](#321-mob)), then it turns the correct bools to ture according to the input. These bools in themselves don't translate into the game, we need [another function to parse them and load the correct FOV assoicated with this direction](#3452-setcurrentfov) (to see all possible FOVs click [here](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs)).
#### 3.4.2.4. camMovement
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** Reurns the position of where the camera SHOULD be, according to the orientation of the player.

**Variables:**
* **cam:** Holds the position of where the camera SHOULD be.
* **playr:** Holds the position of the player.

**How it's done & notes:** The different camera positions associated with every orientation are hardcoded into this function. For further information about how this should work and plans for future updates click [here](#2211-how-to-use-the-fov-editors). To learn more about the variable that holds where the camera SHOULD be click [here](#337-wheretocamera).
#### 3.4.2.5. cameraPan
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function brings the camera closer on every frame to the position it should be.

**Variables:**
* **cam:** This variable holds information about the position of the camera.
* **camDest:** This variable holds information about where the camera SHOULD be.

**How it's done & notes:** This function increments or decrements (or does nothing with) the camera's correct coordinate. Since this gets called every frame the camera gets closer to it's destination on every frame, or if the camera is on the destination it should be the camera doesn't get moved. Since the movement speed of the camera, and the player character is the same, when the player turns quickly around and keeps moving in that direction the camera can't catch up with its destination and thus the camera doesn't show the majority of the player's FOV. A fix for this issue is planned for a future update of the engine. For information about the camera click [here](#336-camera), and for information about the camera's destination click [here](#337-wheretocamera).
#### 3.4.2.6. keepCamInBounds
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
	
	if (cam.row > WORLDROWS - SCREENROWS)
	{
		cam.row = WORLDROWS - SCREENROWS;
	}
	
	if (cam.col > WORLDCOLS - SCREENCOLS)
	{
		cam.col = WORLDCOLS - SCREENCOLS;
	}
	
	return cam;
}
```
**Usage:** This function makes sure the camera dosen't show anything that would be out of bounds of the map.

**Variables:**
* **cam:** Holds information about the position of the camera.

**How it's done & notes:** First the function checks if any of the camera's coordinates are lower than 0, if they are they get set back to 0. Since what the camera shows is displayed in [the newScreen array](#3314-newscreen), the next thing the function checks is if any of the camera's coordinates are bigger than the world's correct dimension minus the screen's correct dimension, if they are they get set back to the difference of those dimensions. For information about the camera click [here](#336-camera).
### 3.4.3. [output.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/output/output.h)
###### This section was last checked in the 1.0.0. version of the engine
This header file containts two functions that make rendering smoother and the game run faster and other functions that initialize the information from the different editors. I don't know why I named it output, but its too late now!
#### 3.4.3.1. saveLastScreenArray
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function saves the textures from the last frame of the "screen" part of the console window.

**Variables:**
* **oldS:** This array will hold the textures from the last frame of the "screen" part of the console window.
* **newS:** This array currently holds the textures from the last frame of the "screen" part of the console window.

**How it's done & notes:** The function loops over every variable of the arrays and saves the information from the newS array into the oldS array. With this information the engine will run much smoother and faster.
#### 3.4.3.2. saveLastMenuArray
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function saves the textures from the last frame of the "menu" part of the console window.

**Variables:**
* **oldM:** This array will hold the textures from the last frame of the "menu" part of the console window.
* **newM:** This array currently holds the textures from the last frame of the "menu" part of the console window.

**How it's done & notes:** The function loops over every variable of the arrays and saves the information from the newM array into the oldM array. With this information the engine will run much smoother and faster. 
#### 3.4.3.3. initSolid
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void initSolid(char solide[SOLIDCOUNT], string fileName)
{
	fstream fbe (fileName.c_str());
	
	for (int i = 0; i < SOLIDCOUNT; i++)
	{
		fbe>>solide[i];
	}
	
	fbe.close();
}
```
**Usage:** This function gets all of the characters loaded from [the solid.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/solid.txt), these characters block light and thus create shadow.

**Variables:**
* **solide:** This array will hold all of the characters that block light.
* **fileName:** This string holds the path from [the main .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp) to [the solid.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/solid.txt).

**How it's done & notes:** The function opens and reads [the solid.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/solid.txt). [SOLIDCOUNT](#314-solidcount-and-walkablecount) determines how many of the characters from the file the function loops through. For more information about the solid material editor click [here](#222-how-to-use-the-material-editors).
#### 3.4.3.4. initWalkable
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void initWalkable(char walkablee[WALKABLECOUNT], string fileName)
{
	fstream fbe (fileName.c_str());
	
	for (int i = 0; i < WALKABLECOUNT; i++)
	{
		fbe>>walkablee[i];
	}
	
	fbe.close();
}
```
**Usage:** This function gets all of the characters loaded from [the walkable.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/walkable.txt), these characters don't block player movement.

**Variables:**
* **solide:** This array will hold all of the characters that don't block player movement.
* **fileName:** This string holds the path from [the main .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp) to [the walkable.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/walkable.txt).

**How it's done & notes:** The function opens and reads [the walkable.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/walkable.txt). [WALKABLECOUNT](#314-solidcount-and-walkablecount) determines how many of the characters from the file the function loops through. For more information about the walkable material editor click [here](#222-how-to-use-the-material-editors).
#### 3.4.3.5. initWorld
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void initWorld(map world[WORLDROWS][WORLDCOLS], char solide[SOLIDCOUNT], char walkablee[WALKABLECOUNT], string fileName)
{
	char cahr;
	
	freopen(fileName.c_str(),"r",stdin);
	
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			cin>>cahr;
			
			if (cahr == 'i')
			{
				world[i][j].texture = ' ';
			}
			else
			{
				world[i][j].texture = cahr;
			}
			
			world[i][j].solid = false;
			
			for (int k = 0; k < SOLIDCOUNT; k++)
			{
				if (cahr == solide[k])
				{
					world[i][j].solid = true;
				}
			}
			
			world[i][j].walkable = false;
			
			for (int k = 0; k < WALKABLECOUNT; k++)
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
```
**Usage:** This function initializes the map of the world, with all of the important information such as textures, cells blocking light, or player movement etc. attached to each cell.

**Variables:**
* **world:** This array will hold all of the important information about each cell of the map of the game.
* **soldie:** This array holds all of the characters that block light, and thus create shadows.
* **walkablee:** This array holds all of the characters that don't block player movement.
* **fileName:** This string holds the path from [the main .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp) to [the world.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt).

**How it's done & notes:** Firstly the function opens [the world.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt). Then it starts looping through each character. If the character is an 'i' the function replaces it with a ' ' character for the texture (click [here](#2231-how-to-use-the-map-editor) if you want to find out why this is). Then the function loops through both the solid and walkable characters, and sets the correct attributes of [the structure](#322-map) to the correct values. For more information about the map editor click [here](#223-the-map-editor).
#### 3.4.3.6. initFOV
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
			}
			else
			{
				dir[i][j].inView = false;
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
```
**Usage:** This function is used to initialize all of the [FOV arrays](#3317-fov-arrays).

**Variables:**
* **dir:** This array will hold all of the information about the FOV we are initializing right now. 
* **fileName:** This string holds the path from [the main .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp) to the desired FOV file.

**How it's done & notes:** First we open the desired FOV file. Then we start looping through all of the characters. According to the '_' and '@' characters we set the correct sub variable of the structure to true or false. For the meaning of the different characters in the FOV files click [here](#2211-how-to-use-the-fov-editors). For more information about the FOV editors click [here](#221-the-fov-editors).

### 3.4.4. [render.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/rendering/render.h)
###### This section was last checked in the 1.0.0. version of the engine
This header contains functions that either help rendering, or actually render stuff.
#### 3.4.4.1. goTo
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void goTo (int row, int column)
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD destCoord;
	
	destCoord.X = column;
	destCoord.Y = row;
	
	SetConsoleCursorPosition(hStdout, destCoord);
}
```
**Usage:** This function puts the cursor into a set position in the console window.

**Variables:**
* **row:** The row of the cell to which the cursor will be put on the console window.
* **col:** The column of the cell to which the cursor will be put on the console window.

**How it's done & notes:** This was one of the three times where I resorted to outside sources to solve my problem. I found my answer [here](https://stackoverflow.com/questions/10401724/move-text-cursor-to-particular-screen-coordinate) in the fourth answer. For information about the coordinate system in place please click [here](#2232-further-ramblings-about-the-coordinate-system).
#### 3.4.4.2. clearScreen
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** Clears the console window. 

**Variables:** -

**How it's done & notes:** This was one of the three times where I resorted to outside sources to solve my problem. Sadly I didn't keep the original link, but I found this implementation of a clear screen function right [here](https://docs.microsoft.com/en-us/windows/console/clearing-the-screen)!
#### 3.4.4.3. renderScreen
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void renderScreen(char oldS[SCREENROWS][SCREENCOLS], char newS[SCREENROWS][SCREENCOLS])
{
	for (int i = 0; i < SCREENROWS; i++)
	{
		for (int j = 0; j < SCREENCOLS; j++)
		{
			if (newS[i][j] != oldS[i][j])
			{
				goTo(i, j);
				cout<<newS[i][j];
			}
		}
	}
	
	goTo(SCREENROWS, 0);
}
```
**Usage:** This renders the "screen" part of the console window. 

**Variables:**
* **oldS:** This array holds the textures from the last frame of the "screen" part of the console window.
* **newS:** This array holds the textures from this frame of the "screen" part of the console window.

**How it's done & notes:** The function loops through both of the arrays and compares each cell's textures. If there is a difference, it goes to the correct cell of the console window with [the goTo function](#3441-goto), and updates the cell with the correct texture. This means that the engine only updates cells that's texture changed in this frame, if the engine would update every cell every frame that would lead to flashing, sometimes not even completing the updates properly and (obviously) a much slower runtime.
#### 3.4.4.4. renderMenu
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void renderMenu(char oldM[SCREENROWS][MENUCOLS], char newM[SCREENROWS][MENUCOLS])
{
	for (int i = 0; i < SCREENROWS; i++)
	{
		for (int j = 0; j < MENUCOLS; j++)
		{
			if (newM[i][j] != oldM[i][j])
			{
				goTo(i, SCREENCOLS + j);
				cout<<newM[i][j];
			}
		}
	}
}
```
**Usage:** This renders the "menu" part of the console window.

**Variables:**
* **oldM:** This array holds the textures from the last frame of the "menu" part of the console window.
* **newM:** This array holds the textures from this frame of the "menu" part of the console window.

**How it's done & notes:** The function loops through both of the arrays and compares each cell's textures. If there is a difference, it goes to the correct cell of the console window with [the goTo function](#3441-goto), and updates the cell with the correct texture. This means that the engine only updates cells that's texture changed in this frame, if the engine would update every cell every frame that would lead to flashing, sometimes not even completing the updates properly and (obviously) a much slower runtime.
#### 3.4.4.5. calculateScreen
###### This section was last checked in the 1.0.0. version of the engine
```cpp
void calculateScreen(map world[WORLDROWS][WORLDCOLS], char screen[SCREENROWS][SCREENCOLS], int cameraRow, int cameraCol)
{
	for (int i = 0; i < SCREENROWS; i++)
	{
		for (int j = 0; j < SCREENCOLS; j++)
		{
			if (world[i + cameraRow][j + cameraCol].mapInView)
			{
				screen[i][j] = world[i + cameraRow][j + cameraCol].texture;
			}
			else
			{
				if (world[i + cameraRow][j + cameraCol].mapIsEdge)
				{
						screen[i][j] = char(176);
				}
				else
				{
					screen[i][j] = char(178);
				}
			}
		}
	}
}
```
**Usage:** This function translates all of the information calculated by the [shadowFunction](#34512-shadowfunction) and [mapIsEdgeCalculation](#34514-mapisedgecalculation) functions into textures that can be rendered.

**Variables:**
* **world:** This array holds all of the information about the cells of the world, like what is or isn't visible, etc.
* **screen:** This array will hold the textures of the "screen" part of the console window after the function is finished.
* **cameraRow:** This is the value that holds in which row the camera is currently.
* **cameraCol:** This is the value that holds in which column the camera is currently.

**How it's done & notes:** The function loops through a part of the map that is equal in size to the "screen" part of the console window. Then if the cell of the world is not in view the texture of the cell on the screen becomes '▓'. If the cell of the world is in the edge, the texture of the cell on the screen becomes'░', and if neither of those are true the texture of the cell on the screen becomes the texture of the cell on the world. For mor information about the map structure click [here](#322-map).
### 3.4.5. [shadowFunctions.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/rendering/shadowFunctions.h)
###### This section was last checked in the 1.0.0. version of the engine
This header contains functions that prepare for the shading of the correct parts of the game world, and also [the function that actually shades the correct places](#34512-shadowfunction).
#### 3.4.5.1. makeCurrentFov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function copies a [FOV array](#3317-fov-arrays) into another [FOV array](#3317-fov-arrays).

**Variables:**
* **presetDir:** This is the [FOV array](#3317-fov-arrays) that gets copied.
* **toBeDir:** This is the [FOV array](#3317-fov-arrays) that gets overwritten.

**How it's done & notes:** The function loops through each variable of the arrays, and copies the different sub variables from one to the other. For more information about the fov structure click [here](#323-fov).
#### 3.4.5.2. setCurrentFov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function sets the current [FOV array](#3317-fov-arrays) to the correct [FOV array](#3317-fov-arrays) according to the input.

**Variables:**
* **playr:** This variable holds the needed information about the input.
* **toBecomeCurrentFov:** This array will contain the correct [FOV array](#3317-fov-arrays) according to this frame's inputs.
* **r:** This array holds the information about how the FOV looks when the player is looking to the right.
* **l:** This array holds the information about how the FOV looks when the player is looking to the left.
* **u:** This array holds the information about how the FOV looks when the player is looking upwards.
* **d:** This array holds the information about how the FOV looks when the player is looking downwards.
* **ru:** This array holds the information about how the FOV looks when the player is looking upwards and to the right.
* **rd:** This array holds the information about how the FOV looks when the player is looking downwards and to the right.
* **lu:** This array holds the information about how the FOV looks when the player is looking upwards and to the left.
* **ld:** This array holds the information about how the FOV looks when the player is looking downwards and to the left.

**How it's done & notes:** The function checks each of the 8 cases one by one and then copies the correct FOV array into the toBecomeCurrentFov array, with the use of [the makeCurrentFov function](#3451-makecurrentfov).
#### 3.4.5.3. getPlayerPosInFov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function sets where the player is in the [FOV array](#3317-fov-arrays) accoding to the orientation of the player, or in other worlds which FOV does the player currently use.

**Variables:**
* **playr:** This variable holds the needed information about the input.
* **fovPlayr:** This variable will hold where the player is in the current [FOV array](#3317-fov-arrays).

**How it's done & notes:** The function checks each of the 8 cases one by one, then hardcodes the correct values into the .col and .row sub variables of the fovPlayr variable. For more information about the mob structure click [here](#321-mob). The information from this fovPlayr variable will be used as an anchor point by [the function that adds the information from the current FOV array into the map](#3454-addfovinfotomap). A better implementation of this function is planned for the 2.0.0. update!
#### 3.4.5.4. addFovInfoToMap
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function adds the infromation from [the current FOV array](#3318-currentfov) about the different cells (if they are visible or not) into the map of the world.

**Variables:**
* **world:** This array will hold the information if the cell is in view or not, for all of the cells in the world.
* **playr:** This variable holds the position of the player in the world.
* **fovplayr:** This variable holds the position of the player in [the current FOV array](#3318-currentfov).
* **fov:** This array holds information about the current FOV of the player. 

**How it's done & notes:** First the function sets all of the cells to not visible in [the world array](#3321-newworld). Then we start looping over a chunk of the world which's size equals that of [the FOV ararys](#3317-fov-arrays). If a cell in [the current FOV array](#3318-currentfov) is in view we set the correct cell in the world to in view. We do this with the help of our anchor point. Since the anchor point is the position of the player in [the current FOV array](#3318-currentfov), if we subtract it from the player's position in the world we get the top left point of the FOV of the player in the world. After that we can just simply loop over every cell of [the current FOV array](#3318-currentfov) by adding i and j to the correct dimensions.  
#### 3.4.5.5. getPov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
koordinate getPov(koordinate pov, mob playr)
{
	pov.x = playr.col + 0.5;
	pov.y = playr.row + 0.5;

	return pov;
}
```
**Usage:** This gets the point of view from which the player "sees" things.

**Variables:**
* **pov:** This variable will contain the coordinates of the point from which the player "sees" things.
* **playr:** This variable holds the position of the player in the world.

**How it's done & notes:** We just simply add 0.5 to the position of the player. Since we will cast lines to the edges of different cells in [the function that shades things](#34512-shadowfunction), and since the edges of the cells all have integer cordinates for their four points, adding 0.5 to both of the coordinates of the player prevents the engine from casting lines that are vertical (vertical lines can't be described by the line equation the engine is using, for more information click [here](#324-line)). **Important:** the playr variable has cell coordinates in it and the pov variable will have point coordinates in it, for more information about the difference between the two click [here](#2232-further-ramblings-about-the-coordinate-system).
#### 3.4.5.6. getLineEquation
###### This section was last checked in the 1.0.0. version of the engine
```cpp
line getLineEquation(double aXCol, double aYRow, int bXCol, int bYRow)
{
	line e;

	e.mSlope = (bYRow - aYRow) / (bXCol - aXCol);
	e.bIntercept = aYRow - (e.mSlope * aXCol);

	return e;
}
```
**Usage:** This function determines the line that passes throught two points.

**Variables:**
* **aXCol:** The x coordinate of the first point.
* **aYRow:** The y coordinate of the first point.
* **bXCol:** The x coordinate of the second point.
* **bYRow:** The y coordinate of the second point.

**How it's done & notes:** It can be proven that the operations I'm doing with those variables produce the desired values (for an explanation click [here](https://www.khanacademy.org/math/algebra/two-var-linear-equations/writing-slope-intercept-equations/v/equation-of-a-line-3) and for an explanation of the line formula the engine uses click [here](#324-line)). It should be noted that the second point's coordinates are set as integers, this is because I use this function to cast lines from the player to the edges of objects, and the edges of the objects are always integers (for further information about this click [here](#2232-further-ramblings-about-the-coordinate-system)).
#### 3.4.5.7. isUnderLine
###### This section was last checked in the 1.0.0. version of the engine
```cpp
bool isUnderLine(line e, int solidYRow, int solidXCol)
{
	if ((solidYRow <= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow <= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{
		return true;
	}

	return false;
}
```
**Usage:** This function returns true if a cell is under a line (this icludes the case when the cell is just touching the line).

**Variables:**
* **e:** The line in question.
* **solidYRow:** The y coordinate of the cell.
* **solidXCol:** The x coordinate of the cell.

**How it's done & notes:** The function checks for all of the four points of the cell if its under the given line, if all four are then it returns true. For the difference between cell and point coordinates click [here](#2232-further-ramblings-about-the-coordinate-system). For more information about the line formula click [here](#324-line).
#### 3.4.5.8. isOverLine
###### This section was last checked in the 1.0.0. version of the engine
```cpp
bool isOverLine(line e, int solidYRow, int solidXCol)
{
	if ((solidYRow >= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow >= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{
		return true;
	}

	return false;
}
```
**Usage:** This function returns true if a cell is over a line (this icludes the case when the cell is just touching the line).

**Variables:**
* **e:** The line in question.
* **solidYRow:** The y coordinate of the cell.
* **solidXCol:** The x coordinate of the cell.

**How it's done & notes:** The function checks for all of the four points of the cell if its over the given line, if all four are then it returns true. For the difference between cell and point coordinates click [here](#2232-further-ramblings-about-the-coordinate-system). For more information about the line formula click [here](#324-line).
#### 3.4.5.9. isBetweenLines
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function returns true if a cell is between two lines (a cell is also determined to be between two lines if any of the lines touch it in just one point).

**Variables:**
* **a:** The first line. 
* **b:** The second line.
* **yRow:** The y coordinate of the cell.
* **xCol:** The x coordinate of the cell.

**How it's done & notes:** The engine checks both of the possibilities (is the line under or over the cell we are checking) for both of the lines. This is done by utilizing properties of the line structure (for more info click [here](#324-line)), [the isUnderline function](#3457-isunderline) and [the isOverLine function](#3458-isoverline).
#### 3.4.5.10. isBehindWall
###### This section was last checked in the 1.0.0. version of the engine
```cpp
bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{
	if (pov.x < left && xCol < left + 1)
	{
		return false;
	}
	
	if (pov.x > right && xCol > right - 2)
	{
		return false;
	}
	
	if (pov.y < top && yRow < top + 1)
	{
		return false;
	}
	
	if (pov.y > bottom && yRow > bottom - 2)
	{
		return false;
	}
	
	return true;
}
```
**Usage:** This function returns true if the cell and the player character are on "opposite sides" of a rectangle.

**Variables:**
* **pov:** This variable holds the point from which the player "sees" things. 
* **yRow:** This variable holds the y coordinate of the cell.
* **xCol:** This variable holds the x coordinate of the cell.
* **top:** This variable holds the y coordinate of the top side of the rectangle.
* **bottom:** This variable holds the y coordinate of the bottom side of the rectangle.
* **right:** This variable holds the x coordinate of the right side of the rectangle.
* **left:** This variable holds the x coordinate of the left side of the rectangle.

**How it's done & notes:** For explaining the workings of this function I will use small figures. In these the '@' character will represent the player character, the 'x' will represent the wall of the rectangels, and the '#' will represent the cells that are deemed to be "behind the wall" by the function (if the 'x' and '#' characters would overlap I will use '0' characters to represent both of the in one cell). The '|' characters are just there to make everything preiiter.
```
1. |   ######| 2. |######   | 3. |   ######| 4. |    @    | 5. |    @    |
   |   ######|    |######   |    |  x######|    |         |    |         |
   |@ x000000|    |000000x @|    |@ x######|    | xxxxxxx |    |    x    |
   |   ######|    |######   |    |  x######|    |#########|    |####0####|
   |   ######|    |######   |    |   ######|    |#########|    |####0####|
```
This function will be used to help determine which cells are behind the ones casting shadows. This is the reasoning behind the lone 'x' character (in the first two and last figures) not being "behind the wall", since that character is the one casting shadows. In the above cases the function would return true or false according to the figures. Basically the function determines whether the cell is behind (from the perspective of the player) the first cell(s) of a rectangle.
```
|@        |
|         |
|   xxx   |
|    #####|
|    #####|
```
The function only checks for the cases when it would need to return false, or in other words when the player and the cell are in on the same sides of the rectangle. If thats not the case it goes on to check all of the other ifs as well. So in the end it will combine all of the ifs and produce a result when the player is not in one line with any of the cells, like the on in the figure above.

Since cell coordinates refer to the top left point of the cell, and the above mentioned reasons the wierd requirements of `xCol > right - 2` and `yRow < top + 1` are required. For further information about the coordinate sytem and the difference between cell and point coordinates click [here](#2232-further-ramblings-about-the-coordinate-system).
#### 3.4.5.11. getEdgeLines
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function returns the two lines that are cast from the player, both touch the rectangle in just one point, and encapsulate it. 

**Variables:**
* **pov:** This variable holds the point from which the player "sees" things. 
* **top:** This variable holds the y coordinate of the top side of the rectangle.
* **bot:** This variable holds the y coordinate of the bottom side of the rectangle.
* **right:** This variable holds the x coordinate of the right side of the rectangle.
* **left:** This variable holds the x coordinate of the left side of the rectangle.

**How it's done & notes:** The function checks all of the 8 different possibilites one by one and then sets the two line's variables to the correct values using [the getLineEquation function](#3456-getlineequation).
#### 3.4.5.12. shadowFunction
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
				
				edg = getEdgeLines(pov, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol);
				
				for (int g = 0; g < SCREENROWS; g++)
				{
					for(int h = 0; h < SCREENCOLS; h++)
					{
						if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol) && isBehindWall(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
						{
							world[g + cameraRow][h + cameraCol].mapInView = false;
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
				
				edg = getEdgeLines(pov, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol);
				
				for (int g = 0; g < SCREENROWS; g++)
				{
					for(int h = 0; h < SCREENCOLS; h++)
					{
						if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol) && isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
						{
							world[g + cameraRow][h + cameraCol].mapInView = false;
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
```
**Usage:** This function determines which cells are in shade in the world.

**Variables:**
* **world:** This array will hold the information about the visibility of the cells.
* **cameraCol:** The column in which the camera is.
* **cameraRow:** The row in which the camera is.
* **pov:** This variable holds the point from which the player "sees" things. 
* **edg:** This variable will be used to hold the lines that are cast from the player to the rectangle.

**How it's done & notes:** The function goes over the screen of the game first horizontally, then vertically searching for rectangles that are 1 by x (or x by 1) in dimension. For the rest of this explanation I will be talking about the horizontal search of the screen, since the vertical search is the same, all the same porcesses happen they are just just flipped by 90 degrees. So, the function starts sweeping the screen horizontally, starting with the first line then going down to the next one by one. If it finds a cell that has the ability to block light it will find the end of that x long rectangle. This will be done with a while function that increments untill the cell it is on dosen't block light. 

Now we have the edges of that rectangle (`i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol`), we will hand this information to [the getEdgeLines function](#34511-getedgelines), which will determine the two lines that will get cast from the player to the rectangle.

Now that we have these lines we start to go over every cell of the screen again, and determine if that cell is between the lines AND if that cell is behind the rectangle (this is done with the help of [the isBetweenLines](#3459-isbetweenlines) and [the isBehindWall](#34510-isbehindwall) functions). If both is true we set that cells visibility to false (all of the cells that are in the FOV of the player are set to visible by [the addFovInfoToMap function](#3454-addfovinfotomap), for more info about the map structure click [here](#322-map)).

![bug](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/screenShots/bug.png)

Since this function only shades cells that are FULLY between the two lines, wierd things like the one you see above can happen. This is not a bug, just a flaw in planning. I plan to adress this issue in further updates.
#### 3.4.5.13. isBesideNotSolidInView
###### This section was last checked in the 1.0.0. version of the engine
```cpp
bool isBesideNotSolidInView(map world[WORLDROWS][WORLDCOLS], int xCol, int yRow)
{
	for (int i = yRow - 1; i <= yRow + 1; i++)
	{
		for (int j = xCol - 1; j <= xCol + 1; j++)
		{
			if (world[j][i].mapInView && !world[j][i].solid)
			{
				return true;
			}
		}
	}
	
	return false;
}
```
**Usage:** This function returns true if there are any cells beside this one that are in view and do not block light.

**Variables:**
* **world:** This array holds information about the world of the game.
* **xCol:** This varaible holds the x coordinate of the cell.
* **yRow:** This varaible holds the y coordinate of the cell.

**How it's done & notes:** Checks for all of the 8 cells that are beside this one if these conditions apply. The function also checks for the cell that is given to it whan called, but this is not a problem since we will oly call this function in [the mapIsEdgeCalculation function](#34514-mapisedgecalculation) for cells that are not in view.
#### 3.4.5.14. mapIsEdgeCalculation
###### This section was last checked in the 1.0.0. version of the engine
```cpp
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
```
**Usage:** This function calculates where the less shadow-y shadows should be displayed (they should be around everything that is in view).

**Variables:**
* **world:** This array holds information about the world of the game.
* **cameraRow:** This variable holds the row of the camera.
* **cameraCol:** This variable holds the column of the camera.

**How it's done & notes:** First we need to set all of the cells around the screen to not being in view, since if we don't all sorts of funny buisness can happen (less shadow-y shadows appearing at the edge of the screen where they shouldn't be). Then we go over all of the cells that will be displayed and call [the isBesideNotSolidInView function](#34513-isbesidenotsolidinview) with them if they are not in view. If that function returns ture we set the isEdge sub variable of the cell to true (for more information about the map structure click [here](#322-map)).
# 4. Table of contents
###### This section was last checked in the 1.0.0. version of the engine
[1. Introduction](#1-introduction)  
* [1.1. The structure of this documentation](#11-the-structure-of-this-documentation)
* [1.2. Who the hell am I and what the hecky heck is this?](#12-who-the-hell-am-i-and-what-the-hecky-heck-is-this)
* [1.3. So what is the project?](#13-so-what-is-the-project)

[2. How to use the engine](#2-how-to-use-the-engine)
* [2.1. How the engine works: a breakdown of the main .cpp file](#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file)
  * [2.1.1. Initialization](#211-initialization)
    * [2.1.1.1. System variables](#2111-system-variables)
    * [2.1.1.2. Alterable variables](#2112-alterable-variables)
    * [2.1.1.3. Variables that hold information parsed from the editors](#2113-variables-that-hold-information-parsed-from-the-editors)
  * [2.1.2. The game loop](#212-the-game-loop)
    * [2.1.2.1. Keeping the loop going, storing input and information from the last frame](#2121-keeping-the-loop-going-storing-input-and-information-from-the-last-frame)
    * [2.1.2.2. Player and camera movement](#2122-player-and-camera-movement)
    * [2.1.2.3. Producing the binary shading](#2123-producing-the-binary-shading)
    * [2.1.2.4. Rendering](#2124-rendering)
* [2.2. How to use the editors, and other further details](22-how-to-use-the-editors-and-other-further-details)
  * [2.2.1. The FOV editors](#221-the-fov-editors)
    * [2.2.1.1. How to use the FOV editors](#2211-how-to-use-the-fov-editors)
    * [2.2.1.2. The whys of the FOV editors and the explanation of the newScreen and newMenu arrays](2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays)
  * [2.2.2. How to use the material editors](#222-how-to-use-the-material-editors)
  * [2.2.3. The map editor](#223-the-map-editor)
    * [2.2.3.1. How to use the map editor](#2231-how-to-use-the-map-editor)
    * [2.2.3.2. Further ramblings about the coordinate system](#2232-further-ramblings-about-the-coordinate-system)
    
[3. Detailed description of EVERYTHING](#3-detailed-description-of-everything)
* [3.1. Defines](#31-defines)
  * [3.1.1. SCREENROWS, SCREENCOLS and MENUCOLS](#311-screenrows-screencols-and-menucols)
  * [3.1.2. FOVROWS and FOVCOLS](#312-fovrows-and-fovcols)
  * [3.1.3. WORLDROWS and WORLDCOLS](#313-worldrows-and-worldcols)
  * [3.1.4. SOLIDCOUNT and WALKABLECOUNT](#314-solidcount-and-walkablecount)
* [3.2. Structures](#32-structures)
  * [3.2.1. mob](#321-mob)
  * [3.2.2. map](#322-map)
  * [3.2.3. fov](#323-fov)
  * [3.2.4. line](#324-line)
  * [3.2.5. edgeLines](#325-edgelines)
  * [3.2.6. koordinate](#326-koordinate)
* [3.3. Variables in the main .cpp file](#33-variables-in-the-main-cpp-file)
  * [3.3.1. playerTexture](#331-playertexture)
  * [3.3.2. screenDivisionTexture](#332-screendivisiontexture)
  * [3.3.3. is___Pressed](#333-is___pressed)
  * [3.3.4. player](#334-player)
  * [3.3.5. lastPlayer](#335-lastplayer)
  * [3.3.6. camera](#336-camera)
  * [3.3.7. whereToCamera](#337-wheretocamera)
  * [3.3.8. playerInFov](#338-playerinfov)
  * [3.3.9. playerPov](#339-playerpov)
  * [3.3.10. edges](#3310-edges)
  * [3.3.11. sleepTime](#3311-sleeptime)
  * [3.3.12. isNotExit](#3312-isnotexit)
  * [3.3.13. oldScreen](#3313-oldscreen)
  * [3.3.14. newScreen](#3314-newscreen)
  * [3.3.15. oldMenu](#3315-oldmenu)
  * [3.3.16. newMenu](#3316-newmenu)
  * [3.3.17. FOV arrays](#3317-fov-arrays)
  * [3.3.18. currentFov](#3318-currentfov)
  * [3.3.19. solid](3319-solid)
  * [3.3.20. walkable](3320-walkable)
  * [3.3.21. newWorld](#3321-newworld)
* [3.4. Functions](#34-functions)
  * [3.4.1. input.h](#341-inputh)
    * [3.4.1.1. ___Pressed](#3411-___pressed)
    * [3.4.1.2. cancelOut](#3412-cancelout)
  * [3.4.2. movement.h](#342-movementh)
    * [3.4.2.1. playerMovement](#3421-playermovement)
    * [3.4.2.2. keepInBounds](#3422-keepinbounds)
    * [3.4.2.3. setDirections](#3423-setdirections)
    * [3.4.2.4. camMovement](#3424-cammovement)
    * [3.4.2.5. cameraPan](#3425-camerapan)
    * [3.4.2.6. keepCamInBounds](#3426-keepcaminbounds)
  * [3.4.3. output.h](#343-outputh)
    * [3431-savelastscreenarray](#3431-savelastscreenarray)
    * [3.4.3.2. saveLastMenuArray](#3432-savelastmenuarray)
    * [3.4.3.3. initSolid](#3433-initsolid)
    * [3.4.3.4. initWalkable](#3434-initwalkable)
    * [3.4.3.5. initWorld](#3435-initworld)
    * [3.4.3.6. initFOV](#3436-initfov)
  * [3.4.4. render.h](#344-renderh)
    * [3.4.4.1. goTo](#3441-goto)
    * [3.4.4.2. clearScreen](#3442-clearscreen)
    * [3.4.4.3. renderScreen](#3443-renderscreen)
    * [3.4.4.4. renderMenu](#3444-rendermenu)
    * [3.4.4.5. calculateScreen](#3445-calculatescreen)
  * [3.4.5. shadowFunctions.h](#345-shadowfunctionsh)
    * [3.4.5.1. makeCurrentFov](#3451-makecurrentfov)
    * [3.4.5.2. setCurrentFov](#3452-setcurrentfov)
    * [3.4.5.3. getPlayerPosInFov](#3453-getplayerposinfov)
    * [3.4.5.4. addFovInfoToMap](#3454-addfovinfotomap)
    * [3.4.5.5. getPov](3455-getpov)
    * [3.4.5.6. getLineEquation](#3456-getlineequation)
    * [3.4.5.7. isUnderLine](#3457-isunderline)
    * [3.4.5.8. isOverLine](#3458-isoverline)
    * [3.4.5.9. isBetweenLines](#3459-isbetweenlines)
    * [3.4.5.10. isBehindWall](#34510-isbehindwall)
    * [3.4.5.11. getEdgeLines](#34511-getedgelines)
    * [3.4.5.12. shadowFunction](#34512-shadowfunction)
    * [3.4.5.13. isBesideNotSolidInView](#34513-isbesidenotsolidinview)
    * [3.4.5.14. mapIsEdgeCalculation](#34514-mapisedgecalculation)

[4. Table of contents](#4-table-of-contents)
