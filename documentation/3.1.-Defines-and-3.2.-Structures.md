## 3.1. Defines
### 3.1.1. SCREENROWS, SCREENCOLS and MENUCOLS
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define SCREENROWS 24
#define SCREENCOLS 39

#define MENUCOLS 41
```
**Usage:** These define the dimensions of the two main segments of the console window

**Notes:** There is no need for a MENUROWS define, as it would be the same value as the SCREENROWS define. Altering these defines is not recommended, but if doing so make sure that these two segment's dimensions side by side do not exceed the dimension of the console window, which is 24 by 80.
### 3.1.2. FOVROWS and FOVCOLS
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define FOVROWS 21
#define FOVCOLS 35
```
**Usage:** These define the dimensions of the [FOV editors](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs), and also [the arrays that hold the information parsed from those editors](#3317-fov-arrays).

**Notes:** These defines can be altered if someone wishes, but I dont think that is necessary. If however you are altering these please be wary, you can accidentaly set their values to numbers that [could mess with the rendering of the newScreen array](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays), or these values [could indirectly negatively affect the map of the world](#2231-how-to-use-the-map-editor).
### 3.1.3. WORLDROWS and WORLDCOLS
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define WORLDROWS 63
#define WORLDCOLS 231
```
**Usage:** These define the dimensions of the [map editor](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), and also the [newWorld array](#3321-newworld) which holds the information parsed from said editor.

**Notes:** These values can be altered freely, just make sure they are equal to the dimensions of [the map editor file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/maps/world.txt), if you want to parse the whole of that file. Also leave 19 cells on the top and bottom and 35 cells on each side of the map unenterable, the reason for this was explained in a note [here](#2231-how-to-use-the-map-editor).
### 3.1.4. SOLIDCOUNT and WALKABLECOUNT
###### This section was last checked in the 1.0.0. version of the engine
```cpp
#define SOLIDCOUNT 1
#define WALKABLECOUNT 1
```
**Usage:** These defines are equal to the number of characters that will be parsed in their respective material editor.

**Notes:** These values should be changed if you want to add more "materials" (or characters) that have one or both of the possible attributes. These values should NEVER be any more than the number of characters their respective .txt files hold!
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
**Usage:** Any entity that can move is stored as a mob, right now these entities are the player character and the camera.

**Sub variables:**
* **row:** This variable stores the row of the [newWorld array](#3321-newworld) the mob is currently in.
* **col:** This variable stores the column of the [newWorld array](#3321-newworld) the mob is curently in.
* **up:** This is true if the player is looking up.
* **down:** This is true if the player is looking down.
* **right:** This is true if the player is looking right.
* **left:** This is true if the player is looking left.

**Notes:** Out of the four last bools one is always true, and up to two can be true at once, however these two can not be contradictory for example: up and down. The col and row coordinates are coordinates of cells, this should not be confued with coordinates of points! Details about the difference between cell and point coordinates can be found [here](#2232-further-ramblings-about-the-coordinate-system).
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
* **mapIsEdge:** This is true if the texture of the cell should be replaced with '▒', because it is between a cell that is in view and another that isn't.

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

**Notes:** The line equation I am using for this project is the following: `y = (mSlope * x) + bIntercept`. This equation can't describe lines that are vertical, but I prevented that from happening, no lines that are cast are not cast vertically (or horizontally for that matter). The isItUnderLine sub variable is only used when [determining what is and what isn't in shade](#34512-shadowfunction), when the lines are not for that purpose this sub variable can be left untouched. If the point (a; b) is under a line this inequality would be true: `b < (mSlope * a) + bIntercept`, if said point is over the line this inequality would be true: `b > (mSlope * a) + bIntercept`, if the point is on the line this equation is true: `b = (mSlope * a) + bIntercept`. For more information about this formula of the line click [here](https://en.wikipedia.org/wiki/Linear_equation#Slope%E2%80%93intercept_form).
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
