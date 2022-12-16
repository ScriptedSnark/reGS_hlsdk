#ifdef GL_DRAW_H_RECURSE_GUARD
#error Recursive header files inclusion detected in gl_draw.h
#else //GL_DRAW_H_RECURSE_GUARD

#define GL_DRAW_H_RECURSE_GUARD

#ifndef GL_DRAW_H_GUARD
#define GL_DRAW_H_GUARD
#pragma once

#include "wrect.h"
#include "wad.h"

typedef int (*_Draw_String)(int x, int y, char* str);
typedef int (*_GL_Bind)(int texnum);
typedef void (*_Draw_Frame)(mspriteframe_t* pFrame, int ix, int iy, const wrect_t* prcSubRect);

extern _GL_Bind ORIG_GL_Bind;
extern _Draw_Frame ORIG_Draw_Frame;

void EnableScissorTest(int x, int y, int width, int height);
void DisableScissorTest(void);

void Draw_Init();

void Draw_FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);

int Draw_Character(int x, int y, int num, unsigned int font);

int Draw_MessageCharacterAdd(int x, int y, int num, int rr, int gg, int bb, unsigned int font);

int Draw_String(int x, int y, char* str);

int Draw_StringLen(const char* psz, unsigned int font);

void Draw_SetTextColor(float r, float g, float b);

void Draw_GetDefaultColor();

void Draw_ResetTextColor();

void Draw_FillRGBABlend(int x, int y, int w, int h, int r, int g, int b, int a);

//void GL_SelectTexture(GLenum target);

void GL_Bind(int texnum);

bool ValidateWRect(const wrect_t* prc);
bool IntersectWRect(const wrect_t* prc1, const wrect_t* prc2, wrect_t* prc);

void AdjustSubRect(mspriteframe_t* pFrame, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom, int* pw, int* ph, const wrect_t* prcSubRect);

void Draw_SpriteFrame(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect);
void Draw_SpriteFrameHoles(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect);
void Draw_SpriteFrameAdditive(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect);
void Draw_SpriteFrameGeneric(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect, int src, int dest, int width, int height);
void Draw_Pic(int x, int y, qpic_t* pic);

void Draw_BeginDisc();

void GLDraw_Hook();

#define MAX_GLTEXTURES 4800

#endif //GL_DRAW_H_GUARD

#undef GL_DRAW_H_RECURSE_GUARD
#endif //GL_DRAW_H_RECURSE_GUARD