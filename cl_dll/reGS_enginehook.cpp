// reGS_enginehook.cpp: hw.dll hooking
// Used libraries: SPTLib/MinHook

#include "glquake.h"
#include "Utils.hpp"
#include "MinHook.h"
#include "reGS_patterns.hpp"

_GL_Bind ORIG_GL_Bind;
_VGUI2_ResetCurrentTexture ORIG_VGUI2_ResetCurrentTexture;

bool HWHook()
{
	void* handle;
	void* base;
	size_t size;

	if (!MemUtils::GetModuleInfo(L"hw.dll", &handle, &base, &size))
		return false;

	auto utils = Utils::Utils(handle, base, size);

	/* Hooking all necessary funcs */
	Hook(GL_Bind);
	Hook(VGUI2_ResetCurrentTexture);

	gEngfuncs.pfnFillRGBA = Draw_FillRGBA;

	return true;
}