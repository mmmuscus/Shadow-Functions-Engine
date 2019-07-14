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
**Usage:** These variables are true on every frame the correct button (which's name is in the ___ space) is pressed.

**Notes:** You can easily get the information from more keys as well, you just need to add a new variable in [the main .cpp file](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/ShadowFunctionsEngine.cpp) and a new function in the [input.h](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/input/input.h) and [input.cpp](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/headers/input/input.cpp) file. 
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

**Notes:** You can freely alter any of these values, but when you do please refer back to [the section explaining the mob structure](#321-mob), and [the one detailing possible complications if the player goes to certain parts of the map](#2231-how-to-use-the-map-editor).
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

**Notes:** The camera's position is defined by the upper left corner of the view it shows. Meaning that if `camera.row = a` and `camera.col = b` the cell that is described by the row a and column b will be the top left cell shown by the engine. Altering these variables right here will result in the camera being in a different position relative to the player only untill the player is first moved. If you want to alter the camera's position to the player at all times you should change [the responsible function](#3424-cammovement) alongside these variables. If you do decide to alter the camera's relative position watch out for the complications explained right [here](#2231-how-to-use-the-map-editor). For information about the mob structure click [here](#321-mob).
### 3.3.7. whereToCamera
###### This section was last checked in the 1.0.0. version of the engine
```cpp
mob whereToCamera;
whereToCamera.row = camera.row;
whereToCamera.col = camera.col;
```
**Usage:** This variable holds information about the position the camera should be.

**Notes:** Since I didn't want to teleport the camera franticly every time the player changes directions, I needed a variable that holds the position of where the camera should be (this position is changing very frantically but its not visible to the player). [The function dealing with camera pan](#3425-camerapan) brings the camera one cell closer both vertically and horizontally to its desired location on every frame. For information about the mob structure click [here](#321-mob).
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
**Usage:** This variable holds the two lines that are currently being cast from the player to objects that don't let light through. 

**Notes:** For information about the edgeLines structure click [here](#325-edgelines).
### 3.3.11. sleepTime
###### This section was last checked in the 1.0.0. version of the engine
```cpp
int sleepTime = 30;
```
**Usage:** This variable is equal to the time in miliseconds between two frames.

**Notes:** Altering this variable can be done right here, no need for any extra steps. If you want to achieve 60 FPS set the value to 16. 
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
**Usage:** This array holds the textures of the last frame of the "screen" part of the console window.

**Notes:** This array is needed for the faster and smoother running of the game. For the explanation of the segmentation of the console window click [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays). 
### 3.3.14. newScreen
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char newScreen[SCREENROWS][SCREENCOLS];
```
**Usage:** This array holds textures of the "screen" part of the console window.

**Notes:** For the explanation of the segmentation of the console window click [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays).
### 3.3.15. oldMenu
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char oldMenu[SCREENROWS][MENUCOLS];
```
**Usage:** This array holds the textures of the last frame of the "menu" part of the console window.

**Notes:** This array is needed for the faster and smoother running of the game. For the explanation of the segmentation of the console window click [here](#2212-the-whys-of-the-fov-editors-and-the-explanation-of-the-newscreen-and-newmenu-arrays).
### 3.3.16. newMenu
###### This section was last checked in the 1.0.0. version of the engine
```cpp
char newMenu[SCREENROWS][MENUCOLS];
```
**Usage:** This array holds textures of the "menu" part of the console window.

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
**Usage:** These arrays hold the information about the 8 possible fields of view in the engine.

**Notes:** These arrays get initialized from the [FOV editors](https://github.com/mmmuscus/Shadow-Functions-Engine/tree/master/FOVs), for details about these editors click [here](#221-the-fov-editors). For information about the fov structure click [here](#323-fov).
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
