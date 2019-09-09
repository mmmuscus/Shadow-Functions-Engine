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
			
			
			//   After all this prep we start moving the player.
			

			//   First we calculate where the player should be moved according to the input.
			player = playerMovement(player, isWPressed, isSPressed, isAPressed, isDPressed);
			//   Next we calculate if the player can be moved into said position.
			player = keepInBounds(player, lastPlayer, newWorld);
			//   Lastly we set the direction of the player according to input.
			player = setDirections(player, isWPressed, isSPressed, isAPressed, isDPressed);
			
			
			//   After the player is moved next, we move the camera.
			

			//   First we calculate where the camera should be according to the player's position.
			whereToCamera = camMovement(whereToCamera, player);
			//   Next we "pan" the camera from the position it is to the position it should be
			// (the camera gets closer to its target by 1 cell both vertically and horizontally in
			// every frame).
			camera = cameraPan(camera, whereToCamera);
			// Lastly we make sure the camera is still in bounds.
			camera = keepCamInBounds(camera);
			
			
			//   Next we start the prep work for the binadry shading
			
			
			//   First we set the correct Field Of View according to the orientation of the player.
			setCurrentFov(player, currentFov, right, left, up, down, rightUp, rightDown, leftUp, leftDown);
			//   Next we get the position of the player in the set FOV array.
			playerInFov = getPlayerPosInFov(player, playerInFov);
			//   With the help of the position of the player in the FOV array we paste the FOV
			// information onto the map of the world.
			addFovInfoToMap(newWorld, player, playerInFov, currentFov);

			//   Lastly we get the point of view of the player from which he sees the world (and
			// from which the lines that do the shading are cast).
			playerPov = getPov(playerPov, player);
			
			
			//   After the prep work we start actually doing the shading.
			
	
			//   With all the previous information we do the shading calculations.
			shadowFunction(newWorld, camera.col, camera.row, playerPov, edges);
			//   Next we correct a bug thats due to the small resolution of the console window.
			holePlugger(newWorld, camera.col, camera.row);
		
			//   We add an edge around the visible cells of the screen to make it look prettier.
			mapIsEdgeCalculation(newWorld, camera.row, camera.col);
	
			//   Lastly we convert all this information into acual displayable textures.
			calculateScreen(newWorld, newConsole, camera.row, camera.col);
			
			
			//   Lastly we do the actual rendering of the engine using all the information
			// calculated previously.
		
			//   First we move the player's texture to the correct position in the currentFrame
			// array. We do this by first placing the correct texture onto the last position of the
			// player, and then placing the player's texture into the correct position in the array.
			if (newConsole[lastPlayer.row - camera.row][lastPlayer.col - camera.col] == playerTexture)
			{		
				newConsole[lastPlayer.row - camera.row][lastPlayer.col - camera.col] = ' ';
			}
			newConsole[player.row - camera.row][player.col - camera.col] = playerTexture;
		
			//   Next we place the line that divides the "screen" and "menu" part of the console
			// window into the correct coloumn of the window.
			for (int i = 0; i < CONSOLEROWS; i++)
			{
				newConsole[i][39] = screenDivisionTexture;
			}
		
			//   Lastly we render the console window.
			renderConsole(oldConsole, newConsole);
		}
	}
	
	clearScreen();
	
	return 0;
}
