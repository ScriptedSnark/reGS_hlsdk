#include "glquake.h"

void S_AmbientOff(void)
{
    // TODO: implement - ScriptedSnark
}

void S_AmbientOn(void)
{
     // TODO: implement - ScriptedSnark
}

void S_SoundInfo_f(void)
{
     // TODO: implement - ScriptedSnark
}

void S_Startup(void)
{
    // TODO: implement - ScriptedSnark
}

void S_Init(void)
{
     // TODO: implement - ScriptedSnark
}

void S_Shutdown(void)
{
     // TODO: implement - ScriptedSnark
}

sfx_t* S_FindName(char* name, int* pfInCache)
{
     // TODO: implement - ScriptedSnark
    return nullptr;
}

sfx_t* S_PrecacheSound(char* name)
{
     // TODO: implement - ScriptedSnark
    return nullptr;
}

bool SND_FStreamIsPlaying(sfx_t* sfx)
{
     // TODO: implement - ScriptedSnark
    return false;
}

channel_t* SND_PickDynamicChannel(int entnum, int entchannel, sfx_t* sfx)
{
     // TODO: implement - ScriptedSnark
    return nullptr;
}

channel_t* SND_PickStaticChannel(int entnum, int entchannel, sfx_t* sfx)
{
     // TODO: implement - ScriptedSnark
    return nullptr;
}

int S_AlterChannel(int entnum, int entchannel, sfx_t* sfx, int vol, int pitch, int flags)
{
     // TODO: implement - ScriptedSnark
    return 0;
}

void S_StartDynamicSound(int entnum, int entchannel, sfx_t* sfx, vec_t* origin, float fvol, float attenuation, int flags, int pitch)
{
     // TODO: implement - ScriptedSnark
}

void S_StartStaticSound(int entnum, int entchannel, sfx_t* sfxin, vec_t* origin, float fvol, float attenuation, int flags, int pitch)
{
     // TODO: implement - ScriptedSnark
}

void S_ClearBuffer(void)
{
     // TODO: implement - ScriptedSnark
}

void S_StopSound(int entnum, int entchannel)
{
     // TODO: implement - ScriptedSnark
}

void S_StopAllSounds(const bool clear)
{
     // TODO: implement - ScriptedSnark
}

void S_StopAllSoundsC(void)
{
     // TODO: implement - ScriptedSnark
}

void S_PrintStats(void)
{
     // TODO: implement - ScriptedSnark
}

void S_UpdateAmbientSounds(void)
{
     // TODO: implement - ScriptedSnark
}

void SND_Spatialize(channel_t* ch)
{
     // TODO: implement - ScriptedSnark
}

void S_Update(vec_t* origin, vec_t* forward, vec_t* right, vec_t* up)
{
     // TODO: implement - ScriptedSnark
}

void S_ExtraUpdate(void)
{
     // TODO: implement - ScriptedSnark
}

void GetSoundtime(void)
{
     // TODO: implement - ScriptedSnark
}

void S_Update_(void)
{
     // TODO: implement - ScriptedSnark
}

void S_BeginPrecaching(void)
{
     // TODO: implement - ScriptedSnark
}

void S_EndPrecaching(void)
{
     // TODO: implement - ScriptedSnark
}

void S_Play(void)
{
     // TODO: implement - ScriptedSnark
}

void S_PlayVol(void)
{
     // TODO: implement - ScriptedSnark
}

void S_Say(void)
{
     // TODO: implement - ScriptedSnark
}

void S_Say_Reliable(void)
{
     // TODO: implement - ScriptedSnark
}

void S_SoundList(void)
{
     // TODO: implement - ScriptedSnark
}