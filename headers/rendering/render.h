#include "../system/system.h"

void goTo (int row, int column);

void clearScreen();

void renderScreen(char oldS[SCREENROWS][SCREENCOLS], char newS[SCREENROWS][SCREENCOLS]);

void renderMenu(char oldM[SCREENROWS][MENUCOLS], char newM[SCREENROWS][MENUCOLS]);

void calculateScreen(map world[WORLDROWS][WORLDCOLS], char screen[SCREENROWS][SCREENCOLS], int cameraRow, int cameraCol);
