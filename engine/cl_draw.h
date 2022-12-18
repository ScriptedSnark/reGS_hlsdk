/**
 * Copyright - ScriptedSnark, 2022.
 * cl_draw.h - description
 */

#ifdef CL_DRAW_H_RECURSE_GUARD
#error Recursive header files inclusion detected in cl_draw.h
#else //CL_DRAW_H_RECURSE_GUARD

#define CL_DRAW_H_RECURSE_GUARD

#ifndef CL_DRAW_H_GUARD
#define CL_DRAW_H_GUARD
#pragma once

struct SPRITELIST
{
	model_t* pSprite;
	char* pName;
	int frameCount;
};

msprite_t* SPR_Pointer(SPRITELIST* pList);
//int SPR_Frames(HSPRITE hSprite);
int SPR_Height(HSPRITE hSprite, int frame);
int SPR_Width(HSPRITE hSprite, int frame);



#endif //CL_DRAW_H_GUARD

#undef CL_DRAW_H_RECURSE_GUARD
#endif //CL_DRAW_H_RECURSE_GUARD