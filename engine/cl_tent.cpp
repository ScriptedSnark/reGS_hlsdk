#include "glquake.h"

mspriteframe_t* R_GetSpriteFrame(msprite_t* pSprite, int frame)
{
	if (!pSprite)
	{
		gEngfuncs.Con_Printf("Sprite:  no pSprite!!!\n");
		return NULL;
	}

	if (!pSprite->numframes)
	{
		gEngfuncs.Con_Printf("Sprite:  pSprite has no frames!!!\n");
		return NULL;
	}

	if (frame >= pSprite->numframes || frame < 0)
		gEngfuncs.Con_DPrintf("Sprite: no such frame %d\n", frame);

	if (pSprite->frames[frame].type == SPR_SINGLE)
		return pSprite->frames[frame].frameptr;

	return NULL;
}