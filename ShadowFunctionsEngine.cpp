// For further infromation about the code please refer back to the documentation!


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
	// First the engine initializes all the variables that are needed fot it to run
	
	
	// The first kind of variables that the engine initializes are called "system variables".
	// These are variables that the engine manipulates, they should not be altered.
	//
	// The second kind of variables are ones that could be altered, if one wants to change
	// them, tho some have some restrictions about how you can alter them e.g.: player.row,
	// player.pow etc.
	//
	// The thrid type of variables are the ones that hold the information that is getting
	// parsed from the different kinds of editors.
	
	
	// In the following comments I will provide some detail about the variables that should
	// help the cursory glancer to understand some basics about the code. However theese comments
	// wont go into detail about the engine, for that please refer back to the documentation.
	
	
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


	// After initialization we start the game loop.
	
	
	while (isNotExit)
	{
		//   The game loop starts off with the intro.
		
		
		if (isIntro)
		{
			//   The loop first waits for the set amount of time before computing anything.
			Sleep(sleepTime);
			
			//   First we check if the 'E' button was pressed.
			isEPressed = ePressed();
			
			if (isEPressed)
			{
				//   If the 'E' button was pressed then we prime the game loop to exit the intro
				// part and enter the game part.
				
				//   For this we first set the correct bool to false (so the game loop starts).
				isIntro = false;
				
				//   Next we set the variable controlling the framerate to the correct value for
				// the gameplay.
				sleepTime = 30;
				
				//   After that we prime the console window for cleariing the screen.
				clearConsole(newConsole, oldConsole);
			}
			else
			{
				//   If the 'E' button wasn't pressed we continue playing the animation.
				
				//   For any type of rendering in the engine we need to save the last frame of the
				// console window.
				saveLastConsoleArray(oldConsole, newConsole);
				
				//   Next we update the current frame of the console window by "playing" the next
				// frame of the animation.
				playAnimation(newConsole, logo, 0, 0);
				if (logo.currentFrame < logo.frames)
				{
					logo.currentFrame++;
				}
			}
			
			//   Lastly we render the console window.
			renderConsole(oldConsole, newConsole);
		}
		else
		{
			//   If the intro part of the loop has ended, we start the game part of the loop.
			
			
			//   The loop first waits for the set amount of time before computing anything.
			Sleep(sleepTime);
			
			
			//   Next we deal with the incoming input.
			
			
			//   First we set back all the bools that deal with the input to false.
			isWPressed = false;
			isAPressed = false;
			isSPressed = false;
			isDPressed = false;
			isEPressed = false;
			isEscPressed = false;
		
			//   Next we get the input by using the correct functions of the engine.
			isWPressed = wPressed();
			isAPressed = aPressed();
			isSPressed = sPressed();
			isDPressed = dPressed();
			isEPressed = ePressed();
			isEscPressed = escPressed();
		
			//   After that we check if the escape key was pressed. If it was we set the bool that
			// is responsible for getting into the game loop false, thus terminating the loop in
			// the next pass.
			if (isEscPressed)
			{
				isNotExit = false;
			}
			
			//   Lastly we cancel out any contradictory input (such as left AND right). 
			cancelOut(isWPressed, isSPressed);
			cancelOut(isAPressed, isDPressed);
			
			
			//   After the input we ensure the smoother running of the engine by saving information
			// from the last frame.
			
		
			//   Firstly we save the last frame of the console window.
			saveLastConsoleArray(oldConsole, newConsole);
		
			//   Next we save the position of the player in the last frame.
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
