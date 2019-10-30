// For further infromation about the code please refer back to the documentation!


#ifndef shadow_functions_engine_system_h
#define shadow_functions_engine_system_h

#include <iostream>
#include <fstream>
#include <stdio.h>

// <Linux port curtesy of SuoerFola>

#if defined(WIN32) or defined(_WINDOWS)
	#include <windows.h>
	#include <winnt.h>
	#include <String>
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#include <unistd.h>  // for sleep
	#define Sleep sleep

	#include <X11/Xlib.h>
	#include <X11/keysym.h>
	#include <stdbool.h>

	#include <sys/ioctl.h> // For ioctl, TIOCGWINSZ
	#include <unistd.h> // For STDOUT_FILENO

	#define VK_ESCAPE XK_Escape

	inline short GetKeyState(int key)
	{
		static KeySym keymap[] = {
			XK_A, XK_B, XK_C, XK_D, XK_E, XK_F, XK_G, XK_H, XK_I, XK_J,
			XK_K, XK_L, XK_M, XK_N, XK_O, XK_P, XK_Q, XK_R, XK_S, XK_T,
			XK_U, XK_V, XK_W, XK_X, XK_Y, XK_Z
		};

		Display* dpy = XOpenDisplay(NULL);
		char keys_return[32];
		XQueryKeymap(dpy, keys_return);
		KeyCode kc2 = XKeysymToKeycode(dpy, (key == VK_ESCAPE) ? key : keymap[key - 'A']);
		bool bPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
		XCloseDisplay(dpy);

		return bPressed ? 0x8000 : 0;
	}

	#define HANDLE void*
	#define STD_OUTPUT_HANDLE 0
	#define GetStdHandle(_) nullptr

	struct COORD {
		int X, Y;
	};

	#define SetConsoleCursorPosition(_, dest) printf("\033[%d;%dH", dest.Y + 1, dest.X + 1)

	#define DWORD unsigned
	#define TCHAR char

	struct CONSOLE_SCREEN_BUFFER_INFO
	{
		struct dwSize
		{
			int X, Y;
		} dwSize;

		int wAttributes;
	};

	inline bool GetConsoleScreenBufferInfo(HANDLE h, CONSOLE_SCREEN_BUFFER_INFO* csbi)
	{
		(void) h;

		struct winsize size;
		ioctl(STDOUT_FILENO,TIOCGWINSZ, &size);

		csbi->dwSize.X = size.ws_col;
		csbi->dwSize.Y = size.ws_row;
		return true;
	}

	inline bool FillConsoleOutputCharacter(HANDLE h, TCHAR c, DWORD dwConSize, COORD coordScreen, DWORD* cCharsWritten )
	{
		(void) h; (void) c; (void) dwConSize; (void) coordScreen; (void) cCharsWritten;
		std::cout << "\f";

		return true;
	}

	inline bool FillConsoleOutputAttribute(HANDLE h, int wAttr, DWORD dwConSize, COORD coordScreen, DWORD* cCharsWritten)
	{
		(void) h; (void) wAttr; (void) dwConSize; (void) coordScreen; (void) cCharsWritten;
		std::cout << "\x1B[2J\x1B[H";

		return true;
	}
#endif  // WINDOWS OR LINUX

#endif  // shadow_functions_engine_system_h

// </Linux port curtesy of SuoerFola>

using namespace std;

#ifndef DEFINE_INIT
#define DEFINE_INIT

//   The width of the "screen" part of the console window.
#define SCREENCOLS 39

//   The width of the "screen" part of the console window.
#define MENUCOLS 41

//   The dimensions of the console window.
#define CONSOLEROWS 24
#define CONSOLECOLS 80

//   The dimensions of the FOVs and FOV arrays.
#define FOVROWS 21
#define FOVCOLS 35

//   The dimensions of the world map.
#define WORLDROWS 63
#define WORLDCOLS 231

//   The amount of characters in the solidcount.txt file.
#define SOLIDCOUNT 1
//   The amount of characters in the walkablecount.txt file.
#define WALKABLECOUNT 1

//   A small amount that helps correcting cases like x = 1/3 = 0.333333 then
// x * 3 = 0.999999 =/= 1. 
#define INFINITECIMAL 0.000001

//   The maximum amount of frames that can be in an animation.
#define MAXAMOUNTOFANIMATIONFRAMES 500

#endif //DEFINE_INIT

#ifndef STRUCT_INIT
#define STRUCT_INIT

//   This strcture holds entities in the world (right now these entities are just the
// player and the camera).
struct mob
{
	//   These variables hold the coordinate/the position of the mob/entity in the world.
	int row;
	int col;
	//   These variables hold the orientation of the mob. There are 8 different
	//  orientatins. Currentaly only the player entity uses these sub variables.
	bool up;
	bool down;
	bool right;
	bool left;
};

//   This structure holds information about the map in the engine.
struct map
{
	//   This sub variable holds the texture of the cell.
	char texture;
	//   These sub variables hold the properties of the different cells. Solid si true 
	// when the given cell blocks light, and walkable is true when the given cell does
	// not block movement.
	bool solid;
	bool walkable;
	//   These sub variables hold information about the visibility of the different 
	// cells. When mapInView is true the cell is in view, when mapIsEdge is true a 
	// less intense shadow gets displayed in the game on that cell.
	bool mapInView;
	bool mapIsEdge;
};

//   This structure holds information about the FOV arrays.
struct fov
{
	//   This is true if the cell is in view in the FOV array.
	bool inView;
	//   This is true on the cell where the player is in the FOV array.
	bool isPlayer;
};

//   This structure holds the variables that define a line in the engine.
struct line
{
	//   This is the slope of the line.
	double mSlope;
	//   This is the point where the line intercepts the y axis.
	double bIntercept;
	//   This is true if the line is below any given object we want to "compare" it to.
	bool isItLowerLine;
};

//   This structure holds two lines at once.
struct edgeLines
{
	line first;
	line second;
};

//   This structure holds coordinates.
struct koordinate
{
	double x;
	double y;
};

//   This structure holds animations.
struct animation
{
	//   The number of frames in the animation.
	int frames;
	//   The current frame of the animation the engine is playing/displaying.
	int currentFrame;
	//   The "height" of every frame of the animation.
	int height;
	//   The "width" of every frame of the animation.
	int width;
	//   This array holds every frame of the animation.
	char frameArray[MAXAMOUNTOFANIMATIONFRAMES][CONSOLEROWS][SCREENCOLS + MENUCOLS];
};

#endif //STRUCT INIT
