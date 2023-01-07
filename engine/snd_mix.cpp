#include "glquake.h"

void SetCareerAudioState(int paused)
{
    // TODO: implement - ScriptedSnark
}

void CareerAudio_Command_f(void)
{
    // TODO: implement - ScriptedSnark
}

void Snd_WriteLinearBlastStereo16(void)
{
    // TODO: implement - ScriptedSnark
}

void S_TransferStereo16(int end)
{
    // TODO: implement - ScriptedSnark
}

void S_TransferPaintBuffer(int endtime)
{
    // TODO: implement - ScriptedSnark
}

void S_FreeChannel(channel_t* ch)
{
    // TODO: implement - ScriptedSnark
}

bool S_CheckWavEnd(channel_t* ch, sfxcache_t** psc, int ltime, int ichan)
{
    // TODO: implement - ScriptedSnark
    return false;
}

void S_MixChannelsToPaintbuffer(int end, int fPaintHiresSounds, int voiceOnly)
{
    // TODO: implement - ScriptedSnark
}

void S_PaintChannels(int endtime)
{
    // TODO: implement - ScriptedSnark
}

void SND_InitScaletable(void)
{
    // TODO: implement - ScriptedSnark
}

void SND_PaintChannelFrom8(channel_t* ch, sfxcache_t* sc, int count)
{
    // TODO: implement - ScriptedSnark
}

void SND_PaintChannelFrom8Offs(portable_samplepair_t* paintbuffer, channel_t* ch, sfxcache_t* sc, int count, int offset)
{
    // TODO: implement - ScriptedSnark
}

void SND_PaintChannelFrom16Offs(portable_samplepair_t* paintbuffer, channel_t* ch, short* sfx, int count, int offset)
{
    // TODO: implement - ScriptedSnark
}

void SX_Init(void)
{
    // TODO: implement - ScriptedSnark
}

void SX_Free(void)
{
    // TODO: implement - ScriptedSnark
}

bool SXDLY_Init(int idelay, float delay)
{
    // TODO: implement - ScriptedSnark
    return false;
}

void SXDLY_Free(int idelay)
{
    // TODO: implement - ScriptedSnark
}

void SXDLY_CheckNewStereoDelayVal(void)
{
    // TODO: implement - ScriptedSnark
}

void SXDLY_DoStereoDelay(int count)
{
    // TODO: implement - ScriptedSnark
}

void SXDLY_CheckNewDelayVal(void)
{
    // TODO: implement - ScriptedSnark
}

void SXDLY_DoDelay(int count)
{
    // TODO: implement - ScriptedSnark
}

void SXRVB_CheckNewReverbVal(void)
{
    // TODO: implement - ScriptedSnark
}

void SXRVB_DoReverb(int count)
{
    // TODO: implement - ScriptedSnark
}

void SXRVB_DoAMod(int count)
{
    // TODO: implement - ScriptedSnark
}

void SX_ReloadRoomFX(void)
{
    // TODO: implement - ScriptedSnark
}

void SX_RoomFX(int count, int fFilter, int fTimefx)
{
    // TODO: implement - ScriptedSnark
}

int Wavstream_Init(void)
{
    // TODO: implement - ScriptedSnark
    return 0;
}

void Wavstream_Close(int i)
{
    // TODO: implement - ScriptedSnark
}

void Wavstream_GetNextChunk(channel_t* ch, sfx_t* s)
{
    // TODO: implement - ScriptedSnark
}

void SND_ForceInitMouth(int entnum)
{
    // TODO: implement - ScriptedSnark
}

void SND_ForceCloseMouth(int entnum)
{
    // TODO: implement - ScriptedSnark
}

void SND_InitMouth(int entnum, int entchannel)
{
    // TODO: implement - ScriptedSnark
}

void SND_CloseMouth(channel_t* ch)
{
    // TODO: implement - ScriptedSnark
}

void SND_MoveMouth(channel_t* ch, sfxcache_t* sc, int count)
{
    // TODO: implement - ScriptedSnark
}

void SND_MoveMouth16(int entnum, short* pdata, int count)
{
    // TODO: implement - ScriptedSnark
}

void VOX_Init(void)
{
    // TODO: implement - ScriptedSnark
}

void VOX_ParseString(char* psz)
{
    // TODO: implement - ScriptedSnark
}

char* VOX_GetDirectory(char* szpath, char* psz, int nsize)
{
    // TODO: implement - ScriptedSnark
    return nullptr;
}

void VOX_SetChanVol(channel_t* ch)
{
    // TODO: implement - ScriptedSnark
}

int VOX_ParseWordParams(char* psz, voxword_t* pvoxword, int fFirst)
{
    // TODO: implement - ScriptedSnark
    return 0;
}

int VOX_IFindEmptySentence(void)
{
    // TODO: implement - ScriptedSnark
    return 0;
}

void VOX_MakeSingleWordSentence(channel_t* ch, int pitch)
{
    // TODO: implement - ScriptedSnark
}

sfxcache_t* VOX_LoadSound(channel_t* pchan, char* pszin)
{
    // TODO: implement - ScriptedSnark
    return nullptr;
}

int VOX_FPaintPitchChannelFrom8Offs(portable_samplepair_t* paintbuffer, channel_t* ch, sfxcache_t* sc, int count, int pitch, int timecompress, int offset)
{
    // TODO: implement - ScriptedSnark
    return 0;
}

void VOX_ReadSentenceFile(void)
{
    // TODO: implement - ScriptedSnark
}

void VOX_Shutdown(void)
{
    // TODO: implement - ScriptedSnark
}

char* VOX_LookupString(char* pszin, int* psentencenum)
{
    // TODO: implement - ScriptedSnark
    return nullptr;
}

void VOX_TrimStartEndTimes(channel_t* ch, sfxcache_t* sc)
{
    // TODO: implement - ScriptedSnark
}