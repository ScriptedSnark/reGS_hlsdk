// reGS_enginehook.cpp: hw.dll hooking
// Used libraries: SPTLib/MinHook

#include "Utils.hpp"

bool HWHook()
{
	void* handle;
	void* base;
	size_t size;

	if (!MemUtils::GetModuleInfo(L"hw.dll", &handle, &base, &size))
		return false;

	auto utils = Utils::Utils(handle, base, size);

	/* Hooking all necessary funcs */

	return true;
}