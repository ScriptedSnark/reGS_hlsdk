#ifdef SOUND_H_RECURSE_GUARD
#error Recursive header files inclusion detected in sound.h
#else //SOUND_H_RECURSE_GUARD

#define SOUND_H_RECURSE_GUARD

#ifndef SOUND_H_GUARD
#define SOUND_H_GUARD
#pragma once

#define PAINTBUFFER_SIZE 512

// sound engine rate defines
#define SOUND_DMA_SPEED 22050
#define SOUND_11k 11025

// sentence groups
#define CBSENTENCENAME_MAX 16
#define CVOXFILESENTENCEMAX 1536

//=====================================================================
// FX presets
//=====================================================================

#define SXROOM_OFF 0
#define SXROOM_GENERIC 1 // general, low reflective, diffuse room
#define SXROOM_METALIC_S 2 // highly reflective, parallel surfaces
#define SXROOM_METALIC_M 3
#define SXROOM_METALIC_L 4
#define SXROOM_TUNNEL_S 5 // resonant reflective, long surfaces
#define SXROOM_TUNNEL_M 6
#define SXROOM_TUNNEL_L 7
#define SXROOM_CHAMBER_S 8 // diffuse, moderately reflective surfaces
#define SXROOM_CHAMBER_M 9
#define SXROOM_CHAMBER_L 10
#define SXROOM_BRITE_S 11 // diffuse, highly reflective
#define SXROOM_BRITE_M 12
#define SXROOM_BRITE_L 13
#define SXROOM_WATER1 14 // underwater fx
#define SXROOM_WATER2 15
#define SXROOM_WATER3 16
#define SXROOM_CONCRETE_S 17 // bare, reflective, parallel surfaces
#define SXROOM_CONCRETE_M 18
#define SXROOM_CONCRETE_L 19
#define SXROOM_OUTSIDE1 20 // echoing, moderately reflective
#define SXROOM_OUTSIDE2 21 // echoing, dull
#define SXROOM_OUTSIDE3 22 // echoing, very dull
#define SXROOM_CAVERN_S 23 // large, echoing area
#define SXROOM_CAVERN_M 24
#define SXROOM_CAVERN_L 25
#define SXROOM_WEIRDO1 26
#define SXROOM_WEIRDO2 27
#define SXROOM_WEIRDO3 28
#define CSXROOM 29

struct portable_samplepair_t
{
	int left;
	int right;
};

struct sfx_t
{
	char name[MAX_QPATH];
	cache_user_t cache;
	int servercount;
};

struct sfxcache_t
{
	int length;
	int loopstart;
	int speed;
	int width;
	int stereo;
	byte data[1];
};

struct dma_t
{
	qboolean gamealive;
	qboolean soundalive;
	qboolean splitbuffer;
	int channels;
	int samples;
	int submission_chunk;
	int samplepos;
	int samplebits;
	int speed;
	int dmaspeed;
	unsigned char* buffer;
};

struct channel_t
{
	sfx_t* sfx;
	int leftvol;
	int rightvol;
	int end;
	int pos;
	int looping;
	int entnum;
	int entchannel;
	vec3_t origin;
	vec_t dist_mult;
	int master_vol;
	int isentence;
	int iword;
	int pitch;
};

struct wavinfo_t
{
	int rate;
	int width;
	int channels;
	int loopstart;
	int samples;
	int dataofs;
};

/*
struct wavstream_t
{
	int csamplesplayed;
	int csamplesinmem;
	FileHandle_t hFile;
	wavinfo_t info;
	int lastposloaded;
};
*/

struct voxword_t
{
	int volume;
	int pitch;
	int start;
	int end;
	int cbtrim;
	int fKeepCached;
	int samplefrac;
	int timecompress;
	sfx_t* sfx;
};

#define CVOXWORDMAX 32

void S_Init(void);
void S_Startup(void);
void S_Shutdown(void);
void S_StartDynamicSound(int entnum, int entchannel, sfx_t* sfx, vec_t* origin, float fvol, float attenuation, int flags, int pitch);
void S_StartStaticSound(int entnum, int entchannel, sfx_t* sfxin, vec_t* origin, float fvol, float attenuation, int flags, int pitch);
void S_StopSound(int entnum, int entchannel);
void S_StopAllSounds(const bool clear);
void S_ClearBuffer(void);
void S_Update(vec_t* origin, vec_t* forward, vec_t* right, vec_t* up);
void S_ExtraUpdate(void);
sfx_t* S_PrecacheSound(char* name);
void S_BeginPrecaching(void);
void S_EndPrecaching(void);
void S_PaintChannels(int endtime);
void SND_Spatialize(channel_t* ch);
qboolean SNDDMA_Init(void);
int SNDDMA_GetDMAPos(void);
void SNDDMA_Shutdown(void);

// ====================================================================

#define MAX_CHANNELS 128
#define MAX_DYNAMIC_CHANNELS 8

extern channel_t channels[MAX_CHANNELS];
extern int total_channels;
extern bool fakedma;
extern int paintedtime;
extern vec3_t listener_origin;
extern vec3_t listener_forward;
extern vec3_t listener_right;
extern vec3_t listener_up;
extern volatile dma_t* shm;
extern volatile dma_t sn;
extern vec_t sound_nominal_clip_dist;
extern cvar_t* loadas8bit;
extern cvar_t* bgmvolume;
extern cvar_t* volume;
extern cvar_t* hisound;
extern cvar_t* suitvolume;
extern bool snd_initialized;
extern int snd_blocked;
extern bool g_fUseDInput;
extern bool sound_started;
extern int cszrawsentences;
extern char* rgpszrawsentence[CVOXFILESENTENCEMAX];
extern float g_SND_VoiceOverdrive;

sfxcache_t* S_LoadSound(sfx_t* s, channel_t* channel);
sfx_t* S_FindName(char* name, int* pfInCache);
void SND_InitScaletable(void);
void SNDDMA_Submit(void);
void S_AmbientOff(void);
void S_AmbientOn(void);
void S_FreeChannel(channel_t* ch);
void S_PrintStats(void);
void ResampleSfx(sfx_t* sfx, int inrate, int inwidth, byte* data, int datasize);
void SetCareerAudioState(int paused);
void CareerAudio_Command_f(void);
void SND_PaintChannelFrom8Offs(portable_samplepair_t* paintbuffer, channel_t* ch, sfxcache_t* sc, int count, int offset);
void SND_PaintChannelFrom16Offs(portable_samplepair_t* paintbuffer, channel_t* ch, short* sfx, int count, int offset);

//=============================================================================

void S_TransferStereo16(int end);
void S_TransferPaintBuffer(int endtime);
void S_MixChannelsToPaintbuffer(int end, int fPaintHiresSounds, int voiceOnly);
bool S_CheckWavEnd(channel_t* ch, sfxcache_t** psc, int ltime, int ichan);

extern void SND_MoveMouth(channel_t* ch, sfxcache_t* sc, int count);
extern void SND_MoveMouth16(int entnum, short* pdata, int count);
extern void SND_CloseMouth(channel_t* ch);
extern void SND_InitMouth(int entnum, int entchannel);
extern void SND_ForceInitMouth(int entnum);
extern void SND_ForceCloseMouth(int entnum);

void SX_Init(void);
void SX_Free(void);
void SX_ReloadRoomFX(void);
void SX_RoomFX(int count, int fFilter, int fTimefx);

// WAVE Stream

int Wavstream_Init(void);
void Wavstream_Close(int i);
void Wavstream_GetNextChunk(channel_t* ch, sfx_t* s);
void Snd_ReleaseBuffer(void);
void Snd_AcquireBuffer(void);
void S_BlockSound(void);
void S_UnblockSound(void);
void SetMouseEnable(qboolean fEnable);

extern void VOX_Init(void);
extern void VOX_Shutdown(void);
extern char* VOX_GetDirectory(char* szpath, char* psz, int nsize);
extern void VOX_SetChanVol(channel_t* ch);
extern int VOX_ParseWordParams(char* psz, voxword_t* pvoxword, int fFirst);
extern void VOX_ReadSentenceFile(void);
extern sfxcache_t* VOX_LoadSound(channel_t* pchan, char* pszin);
extern char* VOX_LookupString(char* pszin, int* psentencenum);
extern void VOX_MakeSingleWordSentence(channel_t* ch, int pitch);
extern void VOX_TrimStartEndTimes(channel_t* ch, sfxcache_t* sc);
extern int VOX_FPaintPitchChannelFrom8Offs(portable_samplepair_t* paintbuffer, channel_t* ch, sfxcache_t* sc, int count, int pitch, int timecompress, int offset);

extern "C"
{
extern portable_samplepair_t paintbuffer[(PAINTBUFFER_SIZE + 1) * 2];
}

#endif //SOUND_H_GUARD

#undef SOUND_H_RECURSE_GUARD
#endif //SOUND_H_RECURSE_GUARD
