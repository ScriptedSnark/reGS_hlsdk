// reGS_enginehook.cpp: hw.dll hooking
// Used libraries: SPTLib/MinHook

#include "glquake.h"

Utils utils = Utils::Utils(NULL, NULL, NULL);

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
	VGuiWrap2_Hook();

	MH_EnableHook(MH_ALL_HOOKS);

	return true;
}