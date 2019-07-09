#include "headers/system/system.h"


#include "headers/input/input.h"


#include "headers/output/output.h"
#include "headers/output/movement.h"


#include "headers/rendering/render.h"
#include "headers/rendering/shadowFunctions.h"


const char playerTexture = '@';
const char screenDivisionTexture = '#';

int main()
{
	bool isWPressed;
	bool isSPressed;
	bool isAPressed;
	bool isDPressed;
	bool isEscPressed;
	

	mob player;
	player.row = 31;
	player.col = 45;
	player.up = false;
	player.down = false;
	player.right = true;
	player.left = false;

	mob lastPlayer;

	mob camera;
	camera.row = player.row - 12;
	camera.col = player.col - 3;

	mob whereToCamera;
	whereToCamera.row = camera.row;
	whereToCamera.col = camera.col;
	
	mob playerInFov;
	
	koordinate playerPov;
	
	edgeLines edges;
	

	int sleepTime = 30;
	
	bool isNotExit = true;
	
	char oldScreen[SCREENROWS][SCREENCOLS];
	char newScreen[SCREENROWS][SCREENCOLS];
	
	char oldMenu[SCREENROWS][MENUCOLS];
	char newMenu[SCREENROWS][MENUCOLS];
	
	fov right[FOVROWS][FOVCOLS];
	fov left[FOVROWS][FOVCOLS];
	fov up[FOVROWS][FOVCOLS];
	fov down[FOVROWS][FOVCOLS];
	fov rightUp[FOVROWS][FOVCOLS];
	fov rightDown[FOVROWS][FOVCOLS];
	fov leftUp[FOVROWS][FOVCOLS];
	fov leftDown[FOVROWS][FOVCOLS];
	
	fov currentFov[FOVROWS][FOVCOLS];
	
	initFOV(right, "FOVs/right.txt");
	initFOV(left, "FOVs/left.txt");
	initFOV(down, "FOVs/down.txt");
	initFOV(up, "FOVs/up.txt");
	initFOV(rightDown, "FOVs/rightDown.txt");
	initFOV(rightUp, "FOVs/rightUp.txt");
	initFOV(leftDown, "FOVs/leftDown.txt");
	initFOV(leftUp, "FOVs/leftUp.txt");
	
	makeCurrentFov(right, currentFov);
	
	playerInFov = getPlayerPosInFov(player, playerInFov);
	
	playerPov = getPov(playerPov, player);
	
	char solid[SOLIDCOUNT];
	char walkable[WALKABLECOUNT];
	
	initSolid(solid, "materials/solid.txt");
	initWalkable(walkable, "materials/walkable.txt");
	
	map newWorld[WORLDROWS][WORLDCOLS];

	initWorld(newWorld, solid, walkable, "maps/world.txt");

	while (isNotExit)
	{
		Sleep(sleepTime);
		

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
		
		saveLastScreenArray(oldScreen, newScreen);
		saveLastMenuArray(oldMenu, newMenu);
		
		lastPlayer.row = player.row;
		lastPlayer.col = player.col;

		player = playerMovement(player, isWPressed, isSPressed, isAPressed, isDPressed);
		player = keepInBounds(player, lastPlayer, newWorld);
		player = setDirections(player, isWPressed, isSPressed, isAPressed, isDPressed);

		whereToCamera = camMovement(whereToCamera, player);
		camera = cameraPan(camera, whereToCamera);
		camera = keepCamInBounds(camera);

		setCurrentFov(player, currentFov, right, left, up, down, rightUp, rightDown, leftUp, leftDown);
		playerInFov = getPlayerPosInFov(player, playerInFov);
		addFovInfoToMap(newWorld, player, playerInFov, currentFov);

		playerPov = getPov(playerPov, player);
	
		shadowFunction(newWorld, camera.col, camera.row, playerPov, edges);
		holePlugger(newWorld, camera.col, camera.row);
		
		mapIsEdgeCalculation(newWorld, camera.row, camera.col);
	
		calculateScreen(newWorld, newScreen, camera.row, camera.col);
		
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
	}
	
	clearScreen();
	
	return 0;
}
