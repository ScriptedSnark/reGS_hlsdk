#include "glquake.h"

_VGuiWrap2_NotifyOfServerConnect ORIG_VGuiWrap2_NotifyOfServerConnect = NULL;

void VGuiWrap2_NotifyOfServerConnect(const char* game, int IP_0, int port)
{
#ifdef REGS_FIXES // https://github.com/ValveSoftware/halflife/issues/570
	ORIG_VGuiWrap2_NotifyOfServerConnect("valve", IP_0, port);
#else
	ORIG_VGuiWrap2_NotifyOfServerConnect(game, IP_0, port);
#endif
}

void VGuiWrap2_Hook()
{
	Hook(VGuiWrap2_NotifyOfServerConnect);
}