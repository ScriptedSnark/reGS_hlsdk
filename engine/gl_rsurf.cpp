#include "glquake.h"

typedef void (*_R_BuildLightMap)(msurface_t* psurf, unsigned __int8* dest, int stride);
_R_BuildLightMap ORIG_R_BuildLightMap = NULL;
qboolean* gl_texsort;

void R_BuildLightMap(msurface_t* psurf, unsigned __int8* dest, int stride)
{
#ifdef REGS_FIXES // gl_overbright fix ** note: detail textures won't work after that! **
    *gl_texsort = TRUE;
#endif
    ORIG_R_BuildLightMap(psurf, dest, stride);
}

void R_Hook()
{
    auto fR_BuildLightMap = utils.FindAsync(
    ORIG_R_BuildLightMap,
    patterns::engine::R_BuildLightMap,
    [&](auto pattern) {
        switch (pattern - patterns::engine::R_BuildLightMap.cbegin())
        {
        default:
        case 0: // HL-SteamPipe-8684
            gl_texsort = *reinterpret_cast<qboolean**>(reinterpret_cast<uintptr_t>(ORIG_R_BuildLightMap) + 26);
            break;
        }
    });

    auto pattern = fR_BuildLightMap.get();

	if (ORIG_R_BuildLightMap)                                                                                                     
	{                                                                                 
		gEngfuncs.Con_DPrintf("[hw dll] Found R_BuildLightMap at %p (using the %s pattern).\n", ORIG_R_BuildLightMap, pattern->name());
		void* pR_BuildLightMap = (void*)ORIG_R_BuildLightMap;                                                                              
		MH_CreateHook(pR_BuildLightMap, (void*)R_BuildLightMap, (void**)&ORIG_R_BuildLightMap);
	}
	else                                                         
		gEngfuncs.Con_DPrintf("[hw dll] Could not find R_BuildLightMap.\n");
}