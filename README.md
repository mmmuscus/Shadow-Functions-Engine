# 1. Introduction
###### This section was last checked in the 1.0.0. version of the engine
**Note:** I was using [Dev C++](https://en.wikipedia.org/wiki/Dev-C%2B%2B) as the IDE with TMD-GCC 4.9.2. as the compiler, I have seen the project not functioning as intended with other IDEs and compilers.
## 1.1. The structure of this documentation
###### This section was last checked in the 1.0.0. version of the engine
This documentation will have three main parts and a table of contents:
* [The first](#1-introduction) is the introduction (the part you are reading right now)
* [The second](#2-how-to-use-the-engine) is an overview of [how the engine works](#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) and [how you can operate it and it's different editors](#22-how-to-use-the-editors-and-other-further-details)
* [The third](#3-detailed-description-of-everything) will go over every last detail about the [defines](#31-defines), [structures](#32-structures), [variables](#33-variables-in-the-main-cpp-file) and functions the engine uses

In the [introduction](#1-introduction) I will cover [my motivation](#12-who-the-hell-am-i-and-what-the-hecky-heck-is-this) for this engine, [the idea, the end product and plans about the future of the project](#13-so-what-is-the-project).

[The second part](#2-how-to-use-the-engine) will have two segments. [The first](#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) detailing the architecture of the system, what it does. [The second](#22-how-to-use-the-editors-and-other-further-details) will be the guide to operate it. Hopefully theese two segments will provide you with sufficent information to make a game with this engine.

[The last part](#3-detailed-description-of-everything) will (as mentioned above) go over the hows of the systems in place. It will be broken down into different subsections, each dealing with a header or cpp file and it's [defines](#31-defines), [structures](#32-structures), [variables](#33-variables-in-the-main-cpp-file), or functions.

## 1.2. Who the hell am I and what the hecky heck is this?
###### This section was last checked in the 1.0.0. version of the engine
I am a highschool student, who is interested in computer science and more specifically, creating video games. This project was a challange I gave myself. The aim was to find out if I am able to create something rather complex with my basic understanding of programming, whilst not looking up solutions to my problems. I have already tried my hands at [a project similar to this](https://github.com/mmmuscus/Snake), but this was way more abitious so it was also a test in planning and creating coexsiting systems.

## 1.3. So what is the project?
###### This section was last checked in the 1.0.0. version of the engine
The bare minimum I wanted to accomplish was a real time 2D top down game, with a "realistic" binary shading system (this was all planned to be running in the windows console). The concept of the shading system is the following: There is a player (represented by the '@' character); who has a field of view in which he can see things; anything that would block his view (e.g.: an 'x' character) casts a shadow, meaning that he can't see the things behind the "wall", even if those things would be in his field of view.

Right now this shading system has a small bug, which I will discuss in a later section of the documentation. Besides the minimum goal I created basic text file based level and field of view editors. I also created the option to make new characters that could block light, or player movement.

Features as of now:
* Real time 8 directional player movement
* Binary shading
* Map and field of view editors
* Character attribute editors (can this character block light? can it block player movement?)

The next main goal of the project is to make an animation pipeline. The plan for it is to have every frame drawn in a textfile under each other, with a general function that can read any animation text file into a 3 dimensional array, and another general function that could play said animation in a set position on the screen. Beside this main goal I plan to make several quality of life changes to the different text based editors and to the structure and efficency of the code in general.

# 2. How to use the engine
## 2.1. How the engine works: a breakdown of [the main .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp)
### 2.1.1. Initialization
#### 2.1.1.1. System variables
###### This section was last checked in the 1.0.0. version of the engine
First things first. The system adds all variables, most of theese are vital for the engine and should not be altered (unless you understand how theese systems work, in that case go nuts!). All of theese will be explained in bigger detail in [the next big segement of the documentation](#3-detailed-description-of-everything), but here are some examples:
```cpp
bool isWPressed;
```
This variable is true on any frame on which the W button is pressed.
```cpp
koordinate playerPov;
```
[The koordinate structure](#326-koordinate) has two sub variables: one for the x and another for the y axis. This koordinate variable stores the coordinate from which the player "sees" things. Algorythmically speaking it stores the coordinate from which lines are cast that will determine whether something is in the shadows or not.
```cpp
bool isNotExit = true;
```
While this variable is true the game loop keeps being called every x miliseconds.

#### 2.1.1.2. Alterable variables
###### This section was last checked in the 1.0.0. version of the engine
The next category of variables are ones that are hardcoded, but can be freely altered to anyone's desire. Again I will provide some examples but every variable will be explained in detail in [the next segment of the documentation](#3-detailed-description-of-everything):
```cpp
player.row = 31;
player.col = 45;
```
This is the starting position of the player. The row runs along the x axis and the col runs along the y axis. It should be noted that theese are different from the coordinates that are mentioned above. Theese refer to a set cell's row and column on the map. Each cell's four points have different coordinates. The cell that is defined by row = a and col = b has the following four coordinates associated with it's points: (a; b), (a + 1; b), (a; b + 1) and (a + 1; b + 1). It should also be noted that the coordinate system is only dealing with positive coordinates, and it's flipped, meaning that the (0; 0) point is in the top left, and the (infinity; infinity) point would be in the bottom right. For further information check out [the correct subsection](#2232-further-ramblings-about-the-coordinate-system) of [the part concerned with the map editor](#223-the-map-editor).
```cpp
int sleepTime = 30;
```
This variable is the number of miliseconds that pass between every iteration of the game loop.

#### 2.1.1.3. Variables that hold information parsed from the editors
###### This section was last checked in the 1.0.0. version of the engine
The last variables that need initialization are all arrays. The values for theese variables are all stored in the text files that you can (and are meant to) edit. Theese variables will also be explored in a [later section of the docmentaton](#3-detailed-description-of-everything). Some examples:
```cpp
fov right[FOVROWS][FOVCOLS];
```
This is a 2 dimensional array with information about the shape of the field of view when the player is facing the right side of the screen. Both [FOVROWS and FOVCOLS](#312-fovrows-and-fovcols) are defined in the [system.h header](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/system/system.h). [The description of the fov structure](#323-fov) will bes discussed later down the line.
```cpp
map newWorld[WORLDROWS][WORLDCOLS];
```
This array contains information about the texture of the map, different parts that are blocking player movement and different parts that are blocking light thus producing shadows. Both [WORLDROWS and WORLDCOLS](#313-worldrows-and-worldcols) are defined in the [system.h header](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/system/system.h). [The workings of the map structure](#322-map) will be discussed in a later part.

For more information about theese arrays please refer to [the part concerned with the editors](#22-how-to-use-the-editors-and-other-further-details).

### 2.1.2. The game loop
#### 2.1.2.1. Keeping the loop going, storing input and information from the last frame
###### This section was last checked in the 1.0.0. version of the engine
After the [initialization](#211-initialization), the game loop is started. The first thing it does is to wait for the set amount of time before doing anything:
```cpp
Sleep(sleepTime);
```
Next it deals with incoming input. Setting back all the bools to false that store the input from the 5 different keys, then getting the button information from the keyboard for each and acting accordingly. The escape key is set up to be the one that exits out of the game, so if its pressed the gameloop terminates. If however the escape key is not pressed, we cancel out any input that would be contradictody, such as moving right and left at the same time:
```cpp
isWPressed = false;
isAPressed = false;
isSPressed = false;
isDPressed = false;
isEscPressed = false;

isWPressed = wPressed();
isAPressed = aPressed();
isSPressed = sPressed();
isDPressed = dPressed();
isEscPressed = escPressed();

if (isEscPressed)
{
	isNotExit = false;
}

cancelOut(isWPressed, isSPressed);
cancelOut(isAPressed, isDPressed);
```
With information from the last frame we can make the game run much faster and the graphics look much smoother, so we save the last position of our player character and the last frame of the screen (the screen of the console is segmented into two seperate arrays newScreen and newMenu, with their respective counterparts from the frame before being oldScreen and oldMenu, the explanation for this can be found [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays)):
```cpp
saveLastScreenArray(oldScreen, newScreen);
saveLastMenuArray(oldMenu, newMenu);
		
lastPlayer.row = player.row;
lastPlayer.col = player.col;
```
#### 2.1.2.2. Player and camera movement
###### This section was last checked in the 1.0.0. version of the engine
With all of our existing input and information from the last frame, we can finally start to move the player! The first two functions are making sure the player moves according (if he can!) to the input. The final function sets up the direction in which the player is facing, this is also done with the input, if the D key is pressed the player will face right, if the W key is also pressed the player will face top AND right. Basically the player will face in whichever direction the inputs dictate in every frame:
```cpp
player = playerMovement(player, isWPressed, isSPressed, isAPressed, isDPressed);
player = keepInBounds(player, lastPlayer, newWorld);
player = setDirections(player, isWPressed, isSPressed, isAPressed, isDPressed);
```
We need the camera to follow our character, so next we are dealing with this problem. The first function detects where the camera should be, next we pan the camera in that direction (it should be noted that panning the camera is not done instantly and needs time to be in the desired position), lastly we make sure that the camera is not going out of bounds:
```cpp
whereToCamera = camMovement(whereToCamera, player);
camera = cameraPan(camera, whereToCamera);
camera = keepCamInBounds(camera, newWorld);
```
#### 2.1.2.3. Producing the binary shading
###### This section was last checked in the 1.0.0. version of the engine
Next we start preparing for the shading of the correct places. Firstly we apply the correct field of view. Then we find out where is the player situated in the selected field of view, this will act as an anchor point between the world and the FOV array. With the help of this anchor we add the FOV to the map, after this we will know which cells of the map are currently in the field of view of the player. The last thing we will need before we can start the shading is the point from which the player "sees", or from where we can cast lines to the correct places on the map:
```cpp
setCurrentFov(player, currentFov, right, left, up, down, rightUp, rightDown, leftUp, leftDown);
playerInFov = getPlayerPosInFov(player, playerInFov);
addFovInfoToMap(newWorld, player, playerInFov, currentFov);

playerPov = getPov(playerPov, player);
```
Theese three functions are the main focus of this engine. The first one is responsible for casting lines from the player's point of view to different walls in the enviroment, and calculating which cells are fully encapsualted in shadow. The second one makes everything a little bit prettier, it draws a line that is less shadow-y, inbetween the cells that are in the light and the ones that are in the dark. Whilst theese first two functions are concerned with calculating which cells are in view, or which are at the edge of light and darkness, the third function translates all this information into textures and hands it over to the newScreen array for rendering:
```cpp
shadowFunction(newWorld, camera.col, camera.row, playerPov, edges);
		
mapIsEdgeCalculation(newWorld, camera.row, camera.col);
	
calculateScreen(newWorld, newScreen, camera.row, camera.col);
```
#### 2.1.2.4. Rendering
###### This section was last checked in the 1.0.0. version of the engine
Finally the last part of the game loop is repalcing the player character from the last frame with a ' ' and then re placing the player character into the correct position in the world. Then the newMenu is filled up with the line that divides it from the newScreen (more about theese arrays in [the part which is discussing the FOV editors](#221-the-fov-editors)). Lastly both the newScreen and newMenu are rendered in the console window:
```cpp
if (newScreen[lastPlayer.row - camera.row][lastPlayer.col - camera.col] == playerTexture)
{		
	newScreen[lastPlayer.row - camera.row][lastPlayer.col - camera.col] = ' ';
}
newScreen[player.row - camera.row][player.col - camera.col] = playerTexture;

for (int i = 0; i < SCREENROWS; i++)
{
	newMenu[i][0] = screenDivisionTexture;
}

renderScreen(oldScreen, newScreen);

renderMenu(oldMenu, newMenu);
```

And thus the cycle continues, if there is anything that needs clearing up the exact workings of the engine will be detailed in [the third part of the documentation](#3-detailed-description-of-everything), and some details which I omited here will be covered in [the next half of the second part](#22-how-to-use-the-editors-and-other-further-details).

## 2.2. How to use the editors, and other further details
### 2.2.1. The FOV editors
#### 2.2.1.1. How to use the FOV editors
###### This section was last checked in the 1.0.0. version of the engine
The FOV "editors" are the textfiles located in [the FOVs folder](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs). There is a file for each of the eight directions the player can look. For exaple, this is the [rightUp.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/FOVs/rightUp.txt):
```
0000000000000000____________0000000  
00000000000_____________________000  
000000___________________________00  
0000______________________________0  
0__________________________________  
___________________________________  
___________________________________  
___________________________________  
0__________________________________  
00________________________________0  
000_______________________________0  
0000_____________________________00  
00000___________________________000  
000000_________________________0000  
0000000@______________________00000  
00000000_____________________000000  
000000000___________________0000000  
0000000000_________________00000000  
00000000000_______________000000000  
0000000000000___________00000000000  
000000000000000_______0000000000000  
```
The description of each character:
* The '@' character represents the player, there should be exactly 1 of theese characters per FOV file because it acts as the anchor point between the .txt and the map on which the information about the field of view is pasted onto. (As of version 1.0.0. the position of this character does not get automatically parsed by the engine, so if you want to change it in this file you'll need to hardcode that change into the correct function as well. Fixing this issue is a planned goal for version 2.0.0.)
* The '_' characters represent cells that are in the player's field of view.
* The '0' characters represent cells that are not in the player's field of view.

You can freely redraw any part of theese .txt files, with the '@', '_' and '0' characters. The engine will parse the information and produce the new fields of view in the game. (When dealing with the '@' character please refer back to the description of it to make sure everything will work properly)

#### 2.2.1.2. The whys of the FOV editors and the explanation of the newScreen and newMenu arrays
###### This section was last checked in the 1.0.0. version of the engine
All of theese .txt files have a set height (21) and width (35). I wanted to make FOVs that are symmetrical, because it doesn't make sense if for example the player has a bigger field of view when he is looking right than when he is looking up. Since the console window is 24 cells by 80 cells the maximum width of the field of view can only be roughly equal to the height of 24 cells. That comes to about 39 cells in width. I also wanted to make a margin around all of the field of views. The reasoning behind this decision was that I think it looks wierd if there is a cell that is in the field of view and also on the edge of the screen. Any such cell could mistakenly communicate that the field of view stretches beyond the screen which is (in my opinion) not something we want. As a result of all of this the field of view files shrunk to 21 by 35 (however upon further thinking for an easier time interpreting the editors I plan to expand their dimensions to 24 by 39 for the 2.0.0. version of the engine).

Since the dimensions of the field of view are this small there is plenty of space on the screen for other stuff to be displayed. Thus the console window was separated to the newScreen and newMenu arrays. As of now the newMenu array is not in use, I plan to add basic functions and/or editors that could produce a menu or an inventory system on that half of the console window. If you want to expand the dimensions of the FOV files you'll need to change the value of [FOVROWS and FOVCOLS](#312-fovrows-and-fovcols) which are defined in the [system.h header file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/system/system.h), but be prepared, if you change it to anything that is bigger than the dimensions of the newScreen array (which is 24 by 39) you will run into complications. But before you do anything with any of theese values or the files please read [the part about using the map editors](#2231-how-to-use-the-map-editor), there is a note reffering to possible problems that might surface.

### 2.2.2. How to use the material editors
###### This section was last checked in the 1.0.0. version of the engine
The material "editors" are the .txt files located in [the materials folder](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/materials). One of them ([walkable.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/walkable.txt)) contains characters that don't block player movement, and the other ([solid.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/solid.txt)) contains characters that block light, thus creating shadows. Both of them function exactly the same, so I am only going to discuss the workings of the one concerned with the characters that are blocking light. Characters in the editor should be seperated by an enter. When you are updating this file, make sure that the value of [SOLIDCOUNT](#314-solidcount-and-walkablecount) equals that of the characters in this file, otherwise the function that loads theese characters would go over too few or too many of them.

### 2.2.3. The map editor
#### 2.2.3.1. How to use the map editor
###### This section was last checked in the 1.0.0. version of the engine
The map "editor" is [the text file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt) located in [the maps folder](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/maps). It is a huge 231 by 63 .txt file, as with the other editors if you want to alter its size you should alter the value of [WORLDROWS and WORLDROWS](#313-worldrows-and-worldcols) in [the system.h file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/system/system.h) as well. You might wonder why it's filled with 'i' characters, thats because I didn't figure out a way to read spaces, so any 'i' you see in any of the editors will be parsed by the engine as a ' ' character. You can write anything into [this .txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt) (except for spaces I guess) and it will be visible in the map of the game. Any character that you write here and also into at least one of [the material editors](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/materials) will have the properties associated with said editor.

**Note:** As of now it is recommended that you leave out 19 cells on the top and bottom and 35 cells at the sides of any map you create. Make sure the player can't pass into any of theese left out cells (there is an example of how you can do this in [the default world.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt)). The reason for this is that if the player would be in any of theese cells, looking in the wrong direction, the engine would make calculations with variables in the newWorld array that simply do not exist, leading to all sorts of problems. If you [alter the dimensions of the FOV files](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays) this recommended 19 and 35 cells might be too little to avoid any such catastrophe (or they might be too much, which can be a problem if you want to make bigger walkable maps). Hopefully the 2.0.0. update will solve this issue and we can finally use the map editor in its intended way.

#### 2.2.3.2. Further ramblings about the coordinate system
###### This section was last checked in the 1.0.0. version of the engine
I have explained the coordinate system once before, but just to be sure I will reiterate here. The coordinate system only deals with positive coordinates, and it is flipped, meaning that the (0; 0) cell is on the top left, and the (231; 63) cell is at the botom right of (in this case) [the editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt). Columns run along the x axis and rows run along the y axis, the conversion between theese names is often needed to understand the code of this engine.

**Cells and points should NOT be confused!** Cell's coordinates refer to the coordinate of a character in for example [the map editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), or in the newWorld array, and they are often used with col and row variables instead of the x and the y of a normal coordinate system. Points on the other hand refer to actual coordinates. Theese point coordinates are used in casting the lines from the player to the differnet obstacles in the enviroment, to produce shadows. 
```
Coordinate of the upper left point:                                 Coordinate of the upper right point:
                             (a; b)  _____________________________  (a + 1; b)
                                     |                           |
                                     |                           |
                                     |                           |
                                     |                           |
                                     |  Coordinate of the cell:  |
                                     |           (a; b)          |
                                     |                           |
                                     |                           |
                                     |                           |
Coordinate of the bottom left point: |___________________________|  Coordinate of the bottom right point:
                          (a; b + 1)                                (a + 1; b + 1)
```
Each cell has four point coordinates associated with it. If the cell's coordinates are (a; b) then the point on the upper left is (a; b) the point on the upper right is (a + 1; b) the point on the bottom left is (a; b + 1) and the point on the bottom right is (a + 1; b + 1), as the figure above represents.

# 3. Detailed description of EVERYTHING
###### This section was last checked in the 1.0.0. version of the engine
This segment of the documentation will have four main subsections:
* [Defines](#31-defines)
* [Structures](#32-structures)
* [Variables](#33-variables-in-the-main-cpp-file)
* Functions
## 3.1. Defines
### 3.1.1. SCREENROWS, SCREENCOLS and MENUCOLS
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define SCREENROWS 24
#define SCREENCOLS 39

#define MENUCOLS 41
```
**Usage:** Theese define the dimensions of the two main segments of the console window

**Notes:** There is no need for a MENUROWS define, as it would be the same value as the SCREENROWS define. Altering theese defines is not recommended, but if doing so make sure that theese two segment's dimensions side by side do not exceed the dimension of the console window, which is 24 by 80.
### 3.1.2. FOVROWS and FOVCOLS
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define FOVROWS 21
#define FOVCOLS 35
```
**Usage:** Theese define the dimensions of the [FOV editors](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs), and also the arrays that hold the information parsed from thoose editors.

**Notes:** Theese defines can be altered if someone wishes, but I dont think that is necessary. If however you are altering theese please be wary, you can accidentaly set their values to numbers that [could mess with the rendering of the newScreen array](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays), or theese values [could indirectly negatively affect the map of the world](#2231-how-to-use-the-map-editor).
### 3.1.3. WORLDROWS and WORLDCOLS
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define WORLDROWS 63
#define WORLDCOLS 231
```
**Usage:** Theese define the dimensions of the [map editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), and also the newWorld array which holds the information parsed from said editor.

**Notes:** Theese values can be altered freely, just make sure they are equal to the dimensions of [the map editor file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), if you want to parse the whole of that file. Also leave 19 cells on the top and bottom and 35 cells on each side of the map unenterable, the reason for this was explained in a note [here](#2231-how-to-use-the-map-editor).
### 3.1.4. SOLIDCOUNT and WALKABLECOUNT
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define SOLIDCOUNT 1
#define WALKABLECOUNT 1
```
**Usage:** Theese defines are equal to the number of characters that will be parsed in their respective material editor.

**Notes:** Theese values should be changed if you want to add more "materials" (or characters) that have one or both of the possible attributes.
## 3.2. Structures
### 3.2.1. mob
###### This section was last checked in the 1.0.0. version of the engine
```cpp
struct mob
{
	int row;
	int col;
	bool up;
	bool down;
	bool right;
	bool left;
};
```
**Usage:** Any entity that can move is stored as a mob, right now theese entities are the player character and the camera.

**Sub variables:**
* **row:** This variable stores the row of the newWorld array the mob is currently in.
* **col:** This variable stores the column of the newWorld array the mob is curently in.
* **up:** This is true if the player is looking up.
* **down:** This is true if the player is looking down.
* **right:** This is true if the player is looking right.
* **left:** This is true if the player is looking left.

**Notes:** Out of the four last bools one is always true, and up to two can be true at once, however theese two can not be contradictory for example: up and down. The col and row coordinates are coordinates of cells, this should not be confued with coordinates of points! Details about the difference between cell and point coordinates can be found [here](#2232-further-ramblings-about-the-coordinate-system).
### 3.2.2. map
###### This section was last checked in the 1.0.0. version of the engine
```cpp
struct map
{
	char texture;
	bool solid;
	bool walkable;
	bool mapInView;
	bool mapIsEdge;
};
```
**Usage:** This structure alone can hold every needed information about a cell of any map. In the engine it is used as a base for the newWorld array, that array holds every parsed information from the map editor.

**Sub variables:**
* **texture:** This is the ASCII character that is displayed in game.
* **solid:** This is true if this cell blocks light and thus creates shadows.
* **walkable:** This is true if this cell does not block player movement. 
* **mapInView:** This is true if the texture of the cell should be displayed.
* **mapIsEdge:** This is true if the texture of the cell should be replaced with '▒'.

**Notes:** Throughout the gameloop mapInView is changed, firstly it is true for every cell that is in the field of view of the player, after that the shadows are calculated and mapInView is actually only true for cells that are in fact in view.
### 3.2.3. fov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
struct fov
{
	bool inView;
	bool isPlayer;
};
```
**Usage:** This structure alone can hold every needed information about a cell in the FOV arrays or the [FOV text files](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs). In the engine it is used as the base for every FOV array.

**Sub variables:**
* **inView:** This is true if this cell of the FOV is in view.
* **isPlayer:** This is true if this cell of the FOV is the player.

**Notes:** In version 1.0.0. isPlayer is not dinamically used by the engine, further information can be found [here](#2211-how-to-use-the-fov-editors).
### 3.2.4. line
###### This section was last checked in the 1.0.0. version of the engine
```cpp
struct line
{
	double mSlope;
	double bIntercept;
	bool isItUnderLine;
};
```
**Usage:** This is the structure that holds every needed information about the lines that are cast from the player to the correct objects.

**Sub variables:**
* **mSlope:** The slope of the line.
* **bIntercept:** The value where the line intercepts the y axis.
* **isItUnderLine:** This is true if the line is under the object which we are trying to shade.

**Notes:** The line equation I am using for this project is the following: `y = (mSlope * x) + bIntercept`. This equation can't describe lines that are vertical, but I prevented that from happening, no lines that are cast are cast vertically (or horizontally for that matter). The isItUnderLine sub variable is only used when determining what is and what isn't in shade, when the lines are not for that purpose this sub variable can be left untouched.
### 3.2.5. edgeLines
###### This section was last checked in the 1.0.0. version of the engine
```cpp
struct edgeLines
{
	line first;
	line second;
};
```
**Usage:** This structure holds two [lines](#324-line) at once.

**Sub variables:**
* **first:** The first line.
* **second:** The second line. 

**Notes:** This structure makes accesing the two lines that are cast to a rectangle (binary shading is produced by casting lines to only rectangles) from a player easier.
### 3.2.6. koordinate
###### This section was last checked in the 1.0.0. version of the engine
```cpp
struct koordinate
{
	double x;
	double y;
};
```
**Usage:** This struct holds the values of a coordinate.

**Sub variables:**
* **x:** The x value.
* **y:** The y value.

**Notes:** This should not be confused with the coordinates of cells. This is the coordinate of points, this structure is used when casting lines from the player to objects. Details about the difference between cell and point coordinates can be found [here](#2232-further-ramblings-about-the-coordinate-system).
## 3.3. Variables in [the main .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp)
###### This section was last checked in the 1.0.0. version of the engine
