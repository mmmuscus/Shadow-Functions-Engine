#include "../system/system.h"

void goTo (int row, int column);

void clearScreen();

void renderConsole(char oldC[CONSOLEROWS][CONSOLECOLS], char newC[CONSOLEROWS][CONSOLECOLS]);

void clearConsole(char newC[CONSOLEROWS][CONSOLECOLS], char oldC[CONSOLEROWS][CONSOLECOLS]);

void calculateScreen(map world[WORLDROWS][WORLDCOLS], char screen[CONSOLEROWS][CONSOLECOLS], int cameraRow, int cameraCol);
