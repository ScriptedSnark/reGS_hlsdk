// reGS_enginehook.cpp: hw.dll hooking
// Used libraries: SPTLib/MinHook

#include "glquake.h"

Utils utils = Utils::Utils(NULL, NULL, NULL);

_GL_Bind ORIG_GL_Bind;
_VGUI2_ResetCurrentTexture ORIG_VGUI2_ResetCurrentTexture;

bool HWHook()
{
	void* handle;
	void* base;
	size_t size;

	if (!MemUtils::GetModuleInfo(L"hw.dll", &handle, &base, &size))
		return false;

	utils = Utils::Utils(handle, base, size);

	/* Hooking all necessary funcs */
	GLDraw_Hook();
	TextDraw_Hook();

	return true;
}