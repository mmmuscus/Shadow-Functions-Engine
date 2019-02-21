#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
#include <stdio.h>
#include <String>
using namespace std;

#ifndef DEFINE_INIT
#define DEFINE_INIT

#define SCREENROWS 24
#define SCREENCOLS 39

#define MENUCOLS 41

#define FOVROWS 21
#define FOVCOLS 35

#define WORLDROWS 63
#define WORLDCOLS 231

#define SOLIDCOUNT 1
#define WALKABLECOUNT 1

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
	bool isEdge;
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

#endif //STRUCT INIT
