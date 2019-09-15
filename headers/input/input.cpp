#include "input.h"

//   These functions return true if the correct button was pressed.
bool wPressed()
{
	return (GetKeyState('W') & 0x8000);
}

bool aPressed()
{
	return (GetKeyState('A') & 0x8000);
}

bool sPressed()
{
	return (GetKeyState('S') & 0x8000);
}

bool dPressed()
{
	return (GetKeyState('D') & 0x8000);
}

bool ePressed()
{
	return (GetKeyState('E') & 0x8000);
}

bool escPressed()
{
	return (GetKeyState(VK_ESCAPE) & 0x8000);
}

//   This function sets two bools to false if they were both true.
void cancelOut (bool plus, bool minus)
{
	//   The function checks if both of the bools are true, if they are it sets them to
	// fasle.
	if (plus && minus)
	{
		plus = false;
		minus = false;
	}
}
