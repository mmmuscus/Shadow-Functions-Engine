#if defined(WIN32) or defined(_WINDOWS)
	#include <windows.h>
	#include <winnt.h>
	#include <String>
#elif defined(UNIX)
	#include <unistd.h>  // for sleep
	#define Sleep sleep
#endif

#include <iostream>
#include <fstream>
#include <stdio.h>
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
