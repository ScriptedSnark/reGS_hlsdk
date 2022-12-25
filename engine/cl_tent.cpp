#include "glquake.h"

cvar_t* violence_hblood;
cvar_t* violence_ablood;

BOOL CL_ShowTEBlood()
{
	return violence_hblood->value != 0.0 || violence_ablood->value != 0.0;
}

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

void CL_TEnt_Hook()
{
	violence_hblood = gEngfuncs.pfnGetCvarPointer("violence_hblood");
	violence_ablood = gEngfuncs.pfnGetCvarPointer("violence_ablood");
}