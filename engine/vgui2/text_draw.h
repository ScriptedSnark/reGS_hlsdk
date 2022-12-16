#ifdef TEXT_DRAW_H_RECURSE_GUARD
#error Recursive header files inclusion detected in text_draw.h
#else //TEXT_DRAW_H_RECURSE_GUARD

#define TEXT_DRAW_H_RECURSE_GUARD

#ifndef TEXT_DRAW_H_GUARD
#define TEXT_DRAW_H_GUARD
#pragma once

typedef void (*_VGUI2_ResetCurrentTexture)();
extern _VGUI2_ResetCurrentTexture ORIG_VGUI2_ResetCurrentTexture;

void VGUI2_ResetCurrentTexture();
void TextDraw_Hook();

#endif //TEXT_DRAW_H_GUARD

#undef TEXT_DRAW_H_RECURSE_GUARD
#endif //TEXT_DRAW_H_RECURSE_GUARD