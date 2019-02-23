# 1. Introduction
###### This section was last checked in the 1.0.0. version of the engine
**Note:** I was using [Dev C++](https://en.wikipedia.org/wiki/Dev-C%2B%2B) as the IDE with TMD-GCC 4.9.2. as the compiler, I have seen the project not functioning as intended with other IDEs and compilers.
## 1.1. The structure of this documentation
###### This section was last checked in the 1.0.0. version of the engine
This documentation will have three main parts and a table of contents:
* [The first](#1-introduction) is the introduction (the part you are reading right now)
* [The second](#2-how-to-use-the-engine) is an overview of [how the engine works](#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) and [how you can operate it and it's different editors](#22-how-to-use-the-editors-and-other-further-details)
* [The third](#3-detailed-description-of-everything) will go over every last detail about the [defines](#31-defines), [structures](#32-structures), [variables](#33-variables-in-the-main-cpp-file) and [functions](#34-functions) the engine uses

In the [introduction](#1-introduction) I will cover [my motivation](#12-who-the-hell-am-i-and-what-the-hecky-heck-is-this) for this engine, [the idea, the end product and plans about the future of the project](#13-so-what-is-the-project).

[The second part](#2-how-to-use-the-engine) will have two segments. [The first](#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) detailing the architecture of the system, what it does. [The second](#22-how-to-use-the-editors-and-other-further-details) will be the guide to operate it. Hopefully theese two segments will provide you with sufficent information to make a game with this engine.

[The last part](#3-detailed-description-of-everything) will (as mentioned above) go over the hows of the systems in place. It will be broken down into different subsections, each dealing with a header or cpp file and it's [defines](#31-defines), [structures](#32-structures), [variables](#33-variables-in-the-main-cpp-file), or [functions](#34-functions). [This part](#3-detailed-description-of-everything) will act more like a cheat sheet than anything, if you wish to conserve your sanity do not read it from start to finish in one sitting.

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
After the [initialization](#211-initialization), the game loop is started:
```cpp
Sleep(sleepTime);
```
The first thing it does is to wait for the set amount of time before doing anything.
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
Next it deals with incoming input. Setting back all the bools to false that store the input from the 5 different keys, then [getting the button information from the keyboard](#3411-___pressed) for each and acting accordingly. The escape key is set up to be the one that exits out of the game, so if its pressed the gameloop terminates. If however the escape key is not pressed, we [cancel out any input that would be contradictody](#3412-cancelout), such as moving right and left at the same time.
```cpp
saveLastScreenArray(oldScreen, newScreen);
saveLastMenuArray(oldMenu, newMenu);
		
lastPlayer.row = player.row;
lastPlayer.col = player.col;
```
With information from the last frame we can make the game run much faster and the graphics look much smoother, so we save the last position of our player character and the last frame of the screen with two functions: [saveLastScreenArray](#3431-savelastscreenarray) and [saveLastMenuArray](#3432-savelastmenuarray) (the screen of the console is segmented into two seperate arrays [newScreen](#3314-newscreen) and [newMenu](#3316-newmenu), with their respective counterparts from the frame before being [oldScreen](#3313-oldscreen) and [oldMenu](#3315-oldmenu), the explanation for this can be found [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays)).
#### 2.1.2.2. Player and camera movement
###### This section was last checked in the 1.0.0. version of the engine
```cpp
player = playerMovement(player, isWPressed, isSPressed, isAPressed, isDPressed);
player = keepInBounds(player, lastPlayer, newWorld);
player = setDirections(player, isWPressed, isSPressed, isAPressed, isDPressed);
```
With all of our existing input and information from the last frame, we can finally start to move the player! [The first function](#3421-playermovement) determines where the player should be moved according to the inputs. [The second function](#3422-keepinbounds) determines if said movement is possible [The final function](#3423-setdirections) sets up the direction in which the player is facing, this is also done with the input, if the D key is pressed the player will face right, if the W key is also pressed the player will face top AND right. Basically the player will face in whichever direction the inputs dictate in every frame.
```cpp
whereToCamera = camMovement(whereToCamera, player);
camera = cameraPan(camera, whereToCamera);
camera = keepCamInBounds(camera);
```
We need the camera to follow our character, so next we are dealing with this problem. [The first function](#3424-cammovement) detects where the camera should be, [next](#3425-camerapan) we pan the camera in that direction (it should be noted that panning the camera is not done instantly and needs time to be in the desired position), [lastly](#3426-keepcaminbounds) we make sure that the camera is not going out of bounds. For information about the camera click [here](#336-camera).
#### 2.1.2.3. Producing the binary shading
###### This section was last checked in the 1.0.0. version of the engine
```cpp
setCurrentFov(player, currentFov, right, left, up, down, rightUp, rightDown, leftUp, leftDown);
playerInFov = getPlayerPosInFov(player, playerInFov);
addFovInfoToMap(newWorld, player, playerInFov, currentFov);

playerPov = getPov(playerPov, player);
```
Next we start preparing for the shading of the correct places. Firstly we apply the correct field of view. Then we find out where is the player situated in the selected field of view, this will act as an anchor point between the world and the FOV array. With the help of this anchor we add the FOV to the map, after this we will know which cells of the map are currently in the field of view of the player. The last thing we will need before we can start the shading is the point from which the player "sees", or from where we can cast lines to the correct places on the map.
```cpp
shadowFunction(newWorld, camera.col, camera.row, playerPov, edges);
		
mapIsEdgeCalculation(newWorld, camera.row, camera.col);
	
calculateScreen(newWorld, newScreen, camera.row, camera.col);
```
Theese three functions are the main focus of this engine. The first one is responsible for casting lines from the player's point of view to different walls in the enviroment, and calculating which cells are fully encapsualted in shadow. The second one makes everything a little bit prettier, it draws a line that is less shadow-y, inbetween the cells that are in the light and the ones that are in the dark. Whilst theese first two functions are concerned with calculating which cells are in view, or which are at the edge of light and darkness, the third function translates all this information into textures and hands it over to the newScreen array for rendering.
#### 2.1.2.4. Rendering
###### This section was last checked in the 1.0.0. version of the engine
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
Finally the last part of the game loop is repalcing the player character from the last frame with a ' ' and then re placing the player character into the correct position in the world. Then the [newMenu](#3316-newmenu) is filled up with the line that divides it from the [newScreen](#3314-newscreen) (more about theese arrays in [the part which is discussing the FOV editors](#221-the-fov-editors)). Lastly both the [newScreen](#3314-newscreen) and [newMenu](#3316-newmenu) are rendered in the console window.

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

Since the dimensions of the field of view are this small there is plenty of space on the screen for other stuff to be displayed. Thus the console window was separated to the [newScreen](#3314-newscreen) and [newMenu array](#3316-newmenu)s. As of now the [newMenu array](#3316-newmenu) is not in use, I plan to add basic functions and/or editors that could produce a menu or an inventory system on that half of the console window. If you want to expand the dimensions of the FOV files you'll need to change the value of [FOVROWS and FOVCOLS](#312-fovrows-and-fovcols) which are defined in the [system.h header file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/system/system.h), but be prepared, if you change it to anything that is bigger than the dimensions of the [newScreen array](#3314-newscreen) (which is 24 by 39) you will run into complications. But before you do anything with any of theese values or the files please read [the part about using the map editors](#2231-how-to-use-the-map-editor), there is a note reffering to possible problems that might surface.

### 2.2.2. How to use the material editors
###### This section was last checked in the 1.0.0. version of the engine
The material "editors" are the .txt files located in [the materials folder](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/materials). One of them ([walkable.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/walkable.txt)) contains characters that don't block player movement, and the other ([solid.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/solid.txt)) contains characters that block light, thus creating shadows. Both of them function exactly the same, so I am only going to discuss the workings of the one concerned with the characters that are blocking light. Characters in the editor should be seperated by an enter. When you are updating this file, make sure that the value of [SOLIDCOUNT](#314-solidcount-and-walkablecount) equals that of the characters in this file, otherwise the function that loads theese characters would go over too few or too many of them.

### 2.2.3. The map editor
#### 2.2.3.1. How to use the map editor
###### This section was last checked in the 1.0.0. version of the engine
The map "editor" is [the text file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt) located in [the maps folder](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/maps). It is a huge 231 by 63 .txt file, as with the other editors if you want to alter its size you should alter the value of [WORLDROWS and WORLDROWS](#313-worldrows-and-worldcols) in [the system.h file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/system/system.h) as well. You might wonder why it's filled with 'i' characters, thats because I didn't figure out a way to read spaces, so any 'i' you see in any of the editors will be parsed by the engine as a ' ' character. You can write anything into [this .txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt) (except for spaces I guess) and it will be visible in the map of the game. Any character that you write here and also into at least one of [the material editors](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/materials) will have the properties associated with said editor.

**Note:** As of now it is recommended that you leave out 19 cells on the top and bottom and 35 cells at the sides of any map you create. Make sure the player can't pass into any of theese left out cells (there is an example of how you can do this in [the default world.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt)). The reason for this is that if the player would be in any of theese cells, looking in the wrong direction, the engine would make calculations with variables in the [newWorld array](#3321-newworld) that simply do not exist, leading to all sorts of problems. If you [alter the dimensions of the FOV files](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays) this recommended 19 and 35 cells might be too little to avoid any such catastrophe (or they might be too much, which can be a problem if you want to make bigger walkable maps). Hopefully the 2.0.0. update will solve this issue and we can finally use the map editor in its intended way.

#### 2.2.3.2. Further ramblings about the coordinate system
###### This section was last checked in the 1.0.0. version of the engine
I have explained the coordinate system once before, but just to be sure I will reiterate here. The coordinate system only deals with positive coordinates, and it is flipped, meaning that the (0; 0) cell is on the top left, and the (231; 63) cell is at the botom right of (in this case) [the editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt). Columns run along the x axis and rows run along the y axis, the conversion between theese names is often needed to understand the code of this engine.

**Cells and points should NOT be confused!** Cell's coordinates refer to the coordinate of a character in for example [the map editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), or in the [newWorld array](#3321-newworld), and they are often used with col and row variables instead of the x and the y of a normal coordinate system. Points on the other hand refer to actual coordinates. Theese point coordinates are used in casting the lines from the player to the differnet obstacles in the enviroment, to produce shadows. 
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
* [Functions](#34-functions)
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
**Usage:** Theese define the dimensions of the [FOV editors](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs), and also [the arrays that hold the information parsed from thoose editors](#3317-fov-arrays).

**Notes:** Theese defines can be altered if someone wishes, but I dont think that is necessary. If however you are altering theese please be wary, you can accidentaly set their values to numbers that [could mess with the rendering of the newScreen array](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays), or theese values [could indirectly negatively affect the map of the world](#2231-how-to-use-the-map-editor).
### 3.1.3. WORLDROWS and WORLDCOLS
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define WORLDROWS 63
#define WORLDCOLS 231
```
**Usage:** Theese define the dimensions of the [map editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), and also the [newWorld array](#3321-newworld) which holds the information parsed from said editor.

**Notes:** Theese values can be altered freely, just make sure they are equal to the dimensions of [the map editor file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), if you want to parse the whole of that file. Also leave 19 cells on the top and bottom and 35 cells on each side of the map unenterable, the reason for this was explained in a note [here](#2231-how-to-use-the-map-editor).
### 3.1.4. SOLIDCOUNT and WALKABLECOUNT
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define SOLIDCOUNT 1
#define WALKABLECOUNT 1
```
**Usage:** Theese defines are equal to the number of characters that will be parsed in their respective material editor.

**Notes:** Theese values should be changed if you want to add more "materials" (or characters) that have one or both of the possible attributes. Theese values should NEVER be any more than the number of characters their respective .txt files hold!
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
* **row:** This variable stores the row of the [newWorld array](#3321-newworld) the mob is currently in.
* **col:** This variable stores the column of the [newWorld array](#3321-newworld) the mob is curently in.
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
**Usage:** This structure alone can hold every needed information about a cell of any map. In the engine it is used as a base for the [newWorld array](#3321-newworld), that array holds every parsed information from [the map editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt).

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
**Usage:** This structure alone can hold every needed information about a cell in [the FOV arrays](#3317-fov-arrays) or the [FOV text files](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs). In the engine it is used as the base for every FOV array.

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
### 3.3.1. playerTexture
###### This section was last checked in the 1.0.0. version of the engine
```cpp
const char playerTexture = '@';
```
**Usage:** This is the texture of the player character.

**Notes:** This is a constant variable because I don't think there is a reason the texture of the player should change.
### 3.3.2. screenDivisionTexture
###### This section was last checked in the 1.0.0. version of the engine
```cpp
const char screenDivisionTexture = '#';
```
**Usage:** This is the texture of the line that divides the console window into the [newScreen](#3314-newscreen) and [newMenu](#3316-newmenu) arrays.

**Notes:** This is a constant character because I don't think the texture of the line should change. This line is stored in the [newMenu](#3316-newmenu) array, and gets rendered from there.
### 3.3.3. is___Pressed
###### This section was last checked in the 1.0.0. version of the engine
```cpp
bool isWPressed;
bool isSPressed;
bool isAPressed;
bool isDPressed;
bool isEscPressed;
```
**Usage:** Theese variables are true on every frame the correct button (which's name is in the ___ space) is pressed.

**Notes:** You can easily get the information from more key as well, you just need to add a new variable in [this .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp) and a new function in the [input.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/input/input.h) and [input.cpp](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/input/input.cpp) file. 
### 3.3.4. player
###### This section was last checked in the 1.0.0. version of the engine
```cpp
mob player;
player.row = 31;
player.col = 45;
player.up = false;
player.down = false;
player.right = true;
player.left = false;
```
**Usage:** This variable holds all the important information about the player's location and orientation.

**Notes:** You can freely alter any of theese values, but when you do please refer back to [the section explaining the mob structure](#321-mob), and [the one detailing possible complications if the player goes to certain parts of the map](#2231-how-to-use-the-map-editor).
### 3.3.5. lastPlayer
###### This section was last checked in the 1.0.0. version of the engine
```cpp
mob lastPlayer;
```
**Usage:** This variable holds information about the position of the player in the last frame.

**Notes:** This information is needed to make the rendering run smoother and faster, for information about the mob structure click [here](#321-mob).
### 3.3.6. camera
###### This section was last checked in the 1.0.0. version of the engine
```cpp
mob camera;
camera.row = player.row - 12;
camera.col = player.col - 3;
```
**Usage:** This variable holds information about the position of the camera.

**Notes:** The camera's position is defined by the upper left corner of the view it shows. Meaning that if `camera.row = a` and `camera.col = b` the cell that is described by the row a and column b will be the top left cell shown by the engine. Altering theese variables right here will result in the camera being in a different position relative to the player only untill the player is first moved. If you want to alter the camera's position to the player at all times you should change the responsible function alongside theese variables. If you do decide to alter the camera's relative position watch out for the complications explained right [here](#2231-how-to-use-the-map-editor). For information about the mob structure click [here](#321-mob).
### 3.3.7. whereToCamera
###### This section was last checked in the 1.0.0. version of the engine
```cpp
mob whereToCamera;
whereToCamera.row = camera.row;
whereToCamera.col = camera.col;
```
**Usage:** This variable holds information about the position the camera should be.

**Notes:** Since I didn't want to teleport the camera franticly every time the player changes directions, I needed a variable that holds the position of where the camera should be (this position is changing very frantically but its not visible to the player). The function dealing with camera pan brings the camera one cell closer both vertically and horizontally to its desired location on every frame. For information about the mob structure click [here](#321-mob).
### 3.3.8. playerInFov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
mob playerInFov;
```
**Usage:** This variable holds information about the player's location in the current [FOV array](#3317-fov-arrays). This position acts as an anchor between the current FOV and the map of the world. 

**Notes:** Further details about the need for this variable and the workings of it can be found in [the part discussing the usage of the FOV editors](#2211-how-to-use-the-fov-editors). For information about the mob structure click [here](#321-mob).
### 3.3.9. playerPov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
koordinate playerPov;
```
**Usage:** This variable holds information about the point of view of the player. Its the point from which lines are cast to objects to produce the binary shading effect.

**Notes:** For information about the koordinate structure click [here](#326-koordinate).
### 3.3.10. edges
###### This section was last checked in the 1.0.0. version of the engine
```cpp
edgeLines edges;
```
**Usage:** This variable holds the two lines that are currently being cast from the player to objects that dont let light through. 

**Notes:** For information about the edgeLines structure click [here](#325-edgelines).
### 3.3.11. sleepTime
###### This section was last checked in the 1.0.0. version of the engine
```cpp
int sleepTime = 30;
```
**Usage:** This variable is equal to the time in miliseconds between two frames.

**Notes:** Altering this variable can be done right here, no need for any extra steps. If you want to achieve 60 FPS set the value of this variable to 16. 
### 3.3.12. isNotExit
###### This section was last checked in the 1.0.0. version of the engine
```cpp
bool isNotExit = true;
```
**Usage:** While this is true the game loop gets called.

**Notes:** When the escape key is pressed this is set to false, that final loop still gets processed even after pressing the escape key.
### 3.3.13. oldScreen
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char oldScreen[SCREENROWS][SCREENCOLS];
```
**Usage:** This array holds the textures of the last frame of the screen part of the console window.

**Notes:** This array is needed for the faster and smoother running of the game. For the explanation of the segmentation of the console window click [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays). 
### 3.3.14. newScreen
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char newScreen[SCREENROWS][SCREENCOLS];
```
**Usage:** This array holds textures of the screen part of the console window.

**Notes:** For the explanation of the segmentation of the console window click [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays).
### 3.3.15. oldMenu
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char oldMenu[SCREENROWS][MENUCOLS];
```
**Usage:** This array holds the textures of the last frame of the menu part of the console window.

**Notes:** This array is needed for the faster and smoother running of the game. For the explanation of the segmentation of the console window click [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays).
### 3.3.16. newMenu
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char newMenu[SCREENROWS][MENUCOLS];
```
**Usage:** This array holds textures of the menu part of the console window.

**Notes:** For the explanation of the segmentation of the console window click [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays).
### 3.3.17. FOV arrays
###### This section was last checked in the 1.0.0. version of the engine
```cpp
fov right[FOVROWS][FOVCOLS];
fov left[FOVROWS][FOVCOLS];
fov up[FOVROWS][FOVCOLS];
fov down[FOVROWS][FOVCOLS];
fov rightUp[FOVROWS][FOVCOLS];
fov rightDown[FOVROWS][FOVCOLS];
fov leftUp[FOVROWS][FOVCOLS];
fov leftDown[FOVROWS][FOVCOLS];
```
**Usage:** Theese arrays hold the information about the 8 possible fields of view in the engine.

**Notes:** Theese arrays get initialized from the [FOV editors](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs), for details about theese editors click [here](#221-the-fov-editors). For information about the fov structure click [here](#323-fov).
### 3.3.18. currentFov
###### This section was last checked in the 1.0.0. version of the engine
```cpp
fov currentFov[FOVROWS][FOVCOLS];
```
**Usage:** This is where the according to the current orientation of the player the correct FOV array is stored. 

**Notes:** For information about the fov structure click [here](#323-fov).
### 3.3.19. solid
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char solid[SOLIDCOUNT];
```
**Usage:** This array holds all the characters that block light.

**Notes:** This array gets initialized from the [solid.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/solid.txt), for details about this editor click [here](#222-how-to-use-the-material-editors).
### 3.3.20. walkable
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char walkable[WALKABLECOUNT];
```
**Usage:** This array holds all the characters that do not block player movement. 

**Notes:** This array gets initialized from the [walkable.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/walkable.txt), for details about this editor click [here](#222-how-to-use-the-material-editors).
### 3.3.21. newWorld
###### This section was last checked in the 1.0.0. version of the engine
```cpp
map newWorld[WORLDROWS][WORLDCOLS];
```
**Usage:** This array holds all of the needed information about the world.

**Notes:** This array gets initalized from the [map editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), for details about this editor click [here](#223-the-map-editor). For details about the map structure click [here](#322-map).
## 3.4. Functions
###### This section was last checked in the 1.0.0. version of the engine
This section of [the third chapter of the documentation](#3-detailed-description-of-everything) will not gover the functions in order of apperance (as opposed to the previous sections) but in the order that they are in their header files. Thus this section will have the following parts:
* [input.h](#341-inputh)
* [movement.h](#342-movementh)
* [output.h](#343-outputh)
* [render.h](#344-renderh)
* shadowFunctions.h
### 3.4.1. [input.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/input/input.h)
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

**Usage:** Theese functions return true when the correct key is pressed down.

**Variables:** -

**How it's done & notes:** The functions use another function called [GetKeyState](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getkeystate). This function can be found in [the windiws.h header](https://en.wikipedia.org/wiki/Windows.h) which countains lots of useful functions from the windows API. The ___Pressed functions are one of the three places where I used external resources to solve my problem. The other link I used to write theese can be found [here](https://stackoverflow.com/questions/6331868/using-getkeystate).
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

**How it's done & notes:** The function checks for each of the four bools and increments the player's position if any is true. This function only calculates the possible position of the player. This position can be inside walls the [keepInBounds](#3422-keepinbounds) function is the one responsible for clearing up thoose sort of messes.
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
* **playr:** This variable holds the current caluclated possible position of the player (or in other words the cell the player wants to pass into).
* **lastPlayr:** This variable holds the player's position from the last frame.
* **world:** This array holds the map of the world with all of the attributes of each cell.

**How it's done & notes:** First we check if both of the coordinates of the player have changed. We do this because if it haven't, we have an easy time, we only need to set back the player into the last frame's position if the cell he passed into blocks player movement (this attribute is stored in the .walkable part of the map structure, more information can be found [here](#322-map)). If however both of the coordinates have changed from the last frame's position we need to check a few more things. 

For the rest of this explanation let's assume that the player on the last frame was on the (a; b) cell, and now he wants to pass into the (a + 1; b + 1) cell. I will use some small graphs to explain the different cases in this function. In theese graphs the '@' represents the player on the last frame (or the (a; b) cell), the '#' represents the calculated possible location of the player for this frame (or the (a + 1; b + 1) cell) and the 'x' characters represent cells that block player movement (if the '#' and 'x' characters would overlap they will be replaced by an '0'). The '|' characters are only there to make the graphs prettier and easier to interpret.

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
After the above cases we can be sure, that the desired location blocks movement, and that at least one of the cells that are next to the player from the last frame in the direction of the desired location block movement (see the first two figures from [this very section](#3422-keepinbounds)). We check for theese cells one by one, if both of them block movement we don't move the player. If only one is blocking movement we "slide" the player in the logical direction (see the figures above: in the case of the 1st figure we "slide" him to the right, and in the case of the 2nd figure we "slide" him downwards). The logic behind this is the following: The player wants to move to (a + 1; b + 1) but that cell is not avalaible for movement. The inputs consist of the s button (which signals the desire to move downwards) and the d button (which signals the desire to move to the right), so if the player can't move downward AND to the right, he should move to at least in one of the directions he wants to.
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

**How it's done & notes:** First the function sets all directional bools to false (to learn more about the mob structure click [here](#321-mob)), then it turns the correct bools to ture according to the input. Theese bools in themselves don't translate into the game, we need another function to parse them and load the correct FOV assoicated with this direction (to see all possible FOVs click [here](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs)).
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
**Usage:** Reurns the position of where the camera SHOULD be, accordin to the orientation of the player.

**Variables:**
* **cam:** Holds the position of where the camera SHOULD be.
* **playr:** Holds the position of the player.

**How it's done & notes:** The different camera positions associated with every orientation are hardcoded into this function. For further information about how this should work adn plans for future updates click [here](#2211-how-to-use-the-fov-editors).
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

**How it's done & notes:** First the function checks if any of the camera's coordinates are lower than 0, if they are they get set back to 0. Since what the camera shows is displayed in [the newScreen array](#3314-newscreen), the next thing the function checks is if any of the camera's coordinates are bigger than the world's correct dimension minus the screen's correct dimension, if they are they get set back to the difference of thoose dimensions. For information about the camera click [here](#336-camera).
### 3.4.3. [output.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/output/output.h)
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
**Usage:** This function gets all of the characters loaded from [the solid.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/solid.txt), theese characters block light and thus create shadow.

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
**Usage:** This function gets all of the characters loaded from [the walkable.txt](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/materials/walkable.txt), theese characters don't block player movement.

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

**How it's done & notes:** Firstly the function opens [the world.txt file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt). Then it starts looping through each character. If the character is an 'i' the function replaces it with a ' ' character for the texture (click [here](#2231-how-to-use-the-map-editor) if you want to find out why this is). Then the function loops through both the solid and walkable characters, and sets the correct attributes of [the structure](#322-map) to the correct walues. For more information about the map editor click [here](#223-the-map-editor).
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
