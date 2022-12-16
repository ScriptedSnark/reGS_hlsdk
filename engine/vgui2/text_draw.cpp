#include "glquake.h"

void VGUI2_ResetCurrentTexture()
{
	ORIG_VGUI2_ResetCurrentTexture(); // TODO: implement
}

void TextDraw_Hook()
{
	Hook(VGUI2_ResetCurrentTexture);
}