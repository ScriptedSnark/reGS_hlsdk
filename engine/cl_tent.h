/**
 * Copyright - ScriptedSnark, 2022.
 * cl_tent.h - description
 */

#ifdef CL_TENT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in cl_tent.h
#else //CL_TENT_H_RECURSE_GUARD

#define CL_TENT_H_RECURSE_GUARD

#ifndef CL_TENT_H_GUARD
#define CL_TENT_H_GUARD
#pragma once

mspriteframe_t* R_GetSpriteFrame(msprite_t* pSprite, int frame);

#endif //CL_TENT_H_GUARD

#undef CL_TENT_H_RECURSE_GUARD
#endif //CL_TENT_H_RECURSE_GUARD