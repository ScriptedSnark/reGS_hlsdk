#include "glquake.h"

#undef SPR_Set

#define SPR_MAX_SPRITES 256
unsigned short gSpritePalette[256];

HSPRITE ghCrosshair = 0;
wrect_t gCrosshairRc = {};
int gCrosshairR = 0;
int gCrosshairG = 0;
int gCrosshairB = 0;

static msprite_t* gpSprite = nullptr;

static int gSpriteCount = 0;
static SPRITELIST* gSpriteList = nullptr;

msprite_t* SPR_Pointer(SPRITELIST* pList)
{
	return (msprite_t*)pList->pSprite->cache.data;
}

void SPR_Set(HSPRITE hSprite, int r, int g, int b)
{
	SPRITELIST* sprlist = nullptr;

	hSprite--;

	if (hSprite < 0 || hSprite >= gSpriteCount)
		return;

	sprlist = &gSpriteList[hSprite];

	if (sprlist)
	{
		gpSprite = SPR_Pointer(sprlist);

		if (gpSprite)
			glColor4f(r / 255.0, g / 255.0, b / 255.0, 1.0);
	}
}

void CLDraw_Hook()
{
	//gEngfuncs.pfnSPR_Set = SPR_Set;
}