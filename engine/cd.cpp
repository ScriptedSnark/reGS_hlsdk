#include "glquake.h"

#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>

#include <Miles/MSS.H>

static CCDAudio g_CDAudio;
ICDAudio* cdaudio = (ICDAudio*)&g_CDAudio;

const float CCDAudio::TRACK_EXTRA_TIME = 2.0f;

HDIGDRIVER MP3digitalDriver;
HSTREAM MP3stream;
char* g_pszMP3trackFileMap[200];
int g_iMP3FirstMalloc, g_iMP3NumTracks;

CCDAudio* GetInteralCDAudio(void)
{
	return &g_CDAudio;
}

void CD_Command_f(void)
{
	// TODO: implement - ScriptedSnark
}

int MP3_GetTrack(const char* pszTrack)
{
	// TODO: implement - ScriptedSnark
	return 0;
}

void MP3_Command_f(void)
{
	// TODO: implement - ScriptedSnark
}

void PrimeMusicStream(char* filename, int looping)
{
	// TODO: implement - ScriptedSnark
}

CCDAudio::CCDAudio(void)
{
	m_nMaxCDTrack = 0;
	m_uiDeviceID = 0;

	ResetCDTimes();

	m_bIsCDValid = false;
	m_bIsPlaying = false;
	m_bIsPrimed = false;
	m_bIsInMiddleOfPriming = false;
	m_bWasPlaying = false;
	m_bInitialized = false;
	m_bEnabled = false;
	m_bIsLooping = false;

	m_flVolume = 1.0;
	m_flMP3Volume = 1.0;
	m_dFadeOutTime = 0.0;

	m_nPlayTrack = 0;

	m_szPendingPlayFilename[0] = '\0';

	m_bResumeOnSwitch = false;

	memset(m_rgRemapCD, 0, sizeof(m_rgRemapCD));
}

CCDAudio::~CCDAudio(void)
{
}

void CCDAudio::ResetCDTimes(void)
{
	m_flPlayTime = 0.0;
	m_dStartTime = 0.0;
	m_dPauseTime = 0.0;
}

void CCDAudio::_Stop(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_Pause(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_Eject(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_CloseDoor(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_GetAudioDiskInfo(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_Play(int track, int looping)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_PrimeTrack(int track, int looping)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_Resume(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_SwitchToLauncher(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_SwitchToEngine(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::CD_f(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_CDUpdate(int, int)
{
	// TODO: implement - ScriptedSnark
}

int CCDAudio::Init(void)
{
	// TODO: implement - ScriptedSnark
	return 0;
}

void CCDAudio::_Init(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Shutdown(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_CDReset(int, int)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Reset(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Stop(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Pause(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Eject(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::CloseDoor(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::GetAudioDiskInfo(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Play(int track, bool looping)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::PlayFile(const char* filename, bool looping)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::PrimeTrack(char* filename, int looping)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Resume(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::SwitchToLauncher(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::SwitchToEngine(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::FadeOut(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::Frame(void)
{
	// TODO: implement - ScriptedSnark
}

void CDAudio_Init(void)
{
	// TODO: implement - ScriptedSnark
}

void CDAudio_Shutdown(void)
{
	// TODO: implement - ScriptedSnark
}

void CDAudio_Play(int track, int looping)
{
	// TODO: implement - ScriptedSnark
}

void CDAudio_Pause(void)
{
	// TODO: implement - ScriptedSnark
}

void CDAudio_Resume(void)
{
	// TODO: implement - ScriptedSnark
}

void MP3_Resume_Audio(void)
{
	// TODO: implement - ScriptedSnark
}

void MP3_Suspend_Audio(void)
{
	// TODO: implement - ScriptedSnark
}

bool CCDAudio::MP3_PlayTrack(int trackNum, bool looping)
{
	// TODO: implement - ScriptedSnark
	return false;
}

bool CCDAudio::MP3_PlayTrack(const char* filename, bool looping)
{
	// TODO: implement - ScriptedSnark
	return false;
}

void CCDAudio::MP3_PlayTrackFinalize(int trackNum, bool looping)
{
	// TODO: implement - ScriptedSnark
}

bool CCDAudio::MP3_Init(void)
{
	MP3_ReleaseDriver();

	AIL_set_redist_directory(".");
	AIL_startup();
	AIL_set_preference(17, 0);
	AIL_set_preference(6, 10);

	MP3digitalDriver = AIL_open_digital_driver(22050, 16, 2, AIL_OPEN_DIGITAL_FORCE_PREFERENCE);
	return MP3digitalDriver != 0;
}

void CCDAudio::MP3_Shutdown(void)
{
	MP3_StopStream();
	MP3_ReleaseDriver();
	AIL_shutdown();

	for (int i = g_iMP3FirstMalloc; i < ARRAYSIZE(g_pszMP3trackFileMap); i++)
	{
		if (g_pszMP3trackFileMap[i])
			Mem_Free(g_pszMP3trackFileMap[i]);
	}
}

void CCDAudio::MP3_Resume_Audio(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::MP3_Suspend_Audio(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::MP3_ReleaseDriver(void)
{
	// TODO: implement - ScriptedSnark
}

float CCDAudio::MP3_SetVolume(float NewVol)
{
	// TODO: implement - ScriptedSnark
	return 1;
}

bool CCDAudio::MP3_InitStream(int trackNum, bool looping)
{
	// TODO: implement - ScriptedSnark
	return false;
}

bool CCDAudio::MP3_InitStream(const char* filename, bool looping)
{
	// TODO: implement - ScriptedSnark
	return false;
}

void CCDAudio::MP3_StartStream(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::MP3_StopStream(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::MP3_Loop(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::MP3_SetPause(bool OnOff)
{
	// TODO: implement - ScriptedSnark
}