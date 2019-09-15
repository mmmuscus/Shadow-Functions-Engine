// For further infromation about the code please refer back to the documentation!


#include "../system/system.h"

void saveLastConsoleArray(char oldC[CONSOLEROWS][CONSOLECOLS], char newC[CONSOLEROWS][CONSOLECOLS]);

void initSolid(char solide[SOLIDCOUNT], string fileName);

void initWalkable(char walkablee[WALKABLECOUNT], string fileName);

void initWorld(map world[WORLDROWS][WORLDCOLS], char solide[SOLIDCOUNT], char walkablee[WALKABLECOUNT], string fileName);

void initFOV(fov [FOVROWS][FOVCOLS], string fileName);
