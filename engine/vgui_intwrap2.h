#ifdef VGUI_INTWRAP2_H_RECURSE_GUARD
#error Recursive header files inclusion detected in vgui_intwrap2.h
#else //VGUI_INTWRAP2_H_RECURSE_GUARD

#define VGUI_INTWRAP2_H_RECURSE_GUARD

#ifndef VGUI_INTWRAP2_H_GUARD
#define VGUI_INTWRAP2_H_GUARD
#pragma once

typedef void (*_VGuiWrap2_NotifyOfServerConnect)(const char* game, int IP_0, int port);

extern _VGuiWrap2_NotifyOfServerConnect ORIG_VGuiWrap2_NotifyOfServerConnect;

void VGuiWrap2_Hook();

#endif //VGUI_INTWRAP2_H_GUARD

#undef VGUI_INTWRAP2_H_RECURSE_GUARD
#endif //VGUI_INTWRAP2_H_RECURSE_GUARD