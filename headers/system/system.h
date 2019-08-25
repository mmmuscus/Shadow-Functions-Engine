#ifndef shadow_functions_engine_system_h
#define shadow_functions_engine_system_h

#include <iostream>
#include <fstream>
#include <stdio.h>

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

using namespace std;

#ifndef DEFINE_INIT
#define DEFINE_INIT

#define SCREENCOLS 39

#define MENUCOLS 41

#define CONSOLEROWS 24
#define CONSOLECOLS 80

#define FOVROWS 21
#define FOVCOLS 35

#define WORLDROWS 63
#define WORLDCOLS 231

#define SOLIDCOUNT 1
#define WALKABLECOUNT 1

#define INFINITECIMAL 0.000001

#define MAXAMOUNTOFANIMATIONFRAMES 500

#endif //DEFINE_INIT

#ifndef STRUCT_INIT
#define STRUCT_INIT

struct mob
{
	int row;
	int col;
	bool up;
	bool down;
	bool right;
	bool left;
};

struct map
{
	char texture;
	bool solid;
	bool walkable;
	bool mapInView;
	bool mapIsEdge;
};

struct fov
{
	bool inView;
	bool isPlayer;
};

struct line
{
	double mSlope;
	double bIntercept;
	bool isItUnderLine;
};

struct edgeLines
{
	line first;
	line second;
};

struct koordinate
{
	double x;
	double y;
};

struct animation
{
	int frames;
	int currentFrame;
	int height;
	int width;
	char frameArray[MAXAMOUNTOFANIMATIONFRAMES][CONSOLEROWS][SCREENCOLS + MENUCOLS];
};

#endif //STRUCT INIT
