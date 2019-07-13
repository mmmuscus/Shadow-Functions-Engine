#include "headers/system/system.h"


#include "headers/input/input.h"


#include "headers/output/output.h"
#include "headers/output/movement.h"


#include "headers/rendering/render.h"
#include "headers/rendering/shadowFunctions.h"
#include "headers/rendering/animation.h"


const char playerTexture = '@';
const char screenDivisionTexture = '#';

int main()
{
	bool isWPressed;
	bool isSPressed;
	bool isAPressed;
	bool isDPressed;
	bool isEPressed;
	bool isEscPressed;
	

	mob player;
	player.row = 31;
	player.col = 45;
	player.up = false;
	player.down = false;
	player.right = true;
	player.left = false;

	mob lastPlayer;
	lastPlayer.row = player.row;
	lastPlayer.col = player.col;

	mob camera;
	camera = camMovement(camera, player);

	mob whereToCamera;
	whereToCamera.row = camera.row;
	whereToCamera.col = camera.col;
	
	mob playerInFov;
	
	koordinate playerPov;
	
	edgeLines edges;
	

	int sleepTime = 60;
	
	bool isNotExit = true;
	bool isIntro = true;
	
	char oldConsole[CONSOLEROWS][CONSOLECOLS];
	char newConsole[CONSOLEROWS][CONSOLECOLS];
	
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
	
	animation logo = initNewAnimation(logo, "animations/logo.txt");

	while (isNotExit)
	{
		if (isIntro)
		{
			Sleep(sleepTime);
			
			isEPressed = ePressed();
			
			if (isEPressed)
			{
				isIntro = false;
				
				sleepTime = 30;
				
				clearConsole(newConsole, oldConsole);
			}
			else
			{
				saveLastConsoleArray(oldConsole, newConsole);
				
				playAnimation(newConsole, logo, 0, 0);
				if (logo.currentFrame < logo.frames)
				{
					logo.currentFrame++;
				}
			}
			
			renderConsole(oldConsole, newConsole);
		}
		else
		{
			Sleep(sleepTime);
			

			isWPressed = false;
			isAPressed = false;
			isSPressed = false;
			isDPressed = false;
			isEPressed = false;
			isEscPressed = false;
		
			isWPressed = wPressed();
			isAPressed = aPressed();
			isSPressed = sPressed();
			isDPressed = dPressed();
			isEPressed = ePressed();
			isEscPressed = escPressed();
			
			cancelOut(isWPressed, isSPressed);
			cancelOut(isAPressed, isDPressed);
		
			if (isEscPressed)
			{
				isNotExit = false;
			}
		
			saveLastConsoleArray(oldConsole, newConsole);
		
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
	
			calculateScreen(newWorld, newConsole, camera.row, camera.col);
		
			if (newConsole[lastPlayer.row - camera.row][lastPlayer.col - camera.col] == playerTexture)
			{		
				newConsole[lastPlayer.row - camera.row][lastPlayer.col - camera.col] = ' ';
			}
			newConsole[player.row - camera.row][player.col - camera.col] = playerTexture;
		
			for (int i = 0; i < CONSOLEROWS; i++)
			{
				newConsole[i][39] = screenDivisionTexture;
			}
		
			renderConsole(oldConsole, newConsole);
		}
	}
	
	clearScreen();
	
	return 0;
}
