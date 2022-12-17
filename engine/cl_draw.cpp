#include "glquake.h"

msprite_t* SPR_Pointer(SPRITELIST* pList)
{
	return (msprite_t*)pList->pSprite->cache.data;
}


void CLDraw_Hook()
{
	;
}