#include "glquake.h"

_SCR_UpdateScreen ORIG_SCR_UpdateScreen = NULL;

void SCR_UpdateScreen()
{
	ORIG_SCR_UpdateScreen(); // TODO: implement
}

void SCR_Hook()
{
	Hook(SCR_UpdateScreen);
}