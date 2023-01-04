#ifdef CD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in cd.h
#else //CD_H_RECURSE_GUARD

#define CD_H_RECURSE_GUARD

#ifndef CD_H_GUARD
#define CD_H_GUARD
#pragma once

class ICDAudio
{
public:
	virtual int Init(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual void Play(int track, bool looping) = 0;
	virtual void PlayFile(const char* filename, bool looping) = 0;
	virtual void Pause(void) = 0;
	virtual void Resume(void) = 0;
	virtual void Frame(void) = 0;
	virtual void MP3_Resume_Audio(void) = 0;
	virtual void MP3_Suspend_Audio(void) = 0;
};

extern ICDAudio* cdaudio;

extern cvar_t* bgmvolume;
extern cvar_t* MP3Volume;
extern cvar_t* MP3FadeTime;

void CD_Command_f(void);
void MP3_Command_f(void);

void CDAudio_Init(void);
void CDAudio_Shutdown(void);
void CDAudio_Play(int track, int looping);
void CDAudio_Pause(void);
void CDAudio_Resume(void);

void MP3_Resume_Audio(void);
void MP3_Suspend_Audio(void);

void PrimeMusicStream(char* filename, int looping);

#endif //CD_H_GUARD

#undef CD_H_RECURSE_GUARD
#endif //CD_H_RECURSE_GUARD