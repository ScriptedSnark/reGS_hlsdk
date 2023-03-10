#include "glquake.h"

#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

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

cvar_t* bgmvolume;
cvar_t* MP3Volume;
cvar_t* MP3FadeTime;

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
	_Stop(0, 0);

	DWORD dwReturn = mciSendCommand(m_uiDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, (DWORD)NULL);

	ResetCDTimes();
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
	m_MP3.inuse = false;
	m_MP3.suspended = false;
	m_MP3.playing = false;
	m_MP3.trackname[0] = '\0';
	m_MP3.tracknum = 0;
	m_MP3.looping = false;
	m_MP3.volume = 100.0;

	memset(g_pszMP3trackFileMap, 0, sizeof(g_pszMP3trackFileMap));
	g_pszMP3trackFileMap[0] = g_pszMP3trackFileMap[1] = "";
	g_pszMP3trackFileMap[2] = "media\\Half-Life01.mp3";
	g_pszMP3trackFileMap[3] = "media\\Prospero01.mp3";
	g_pszMP3trackFileMap[4] = "media\\Half-Life12.mp3";
	g_pszMP3trackFileMap[5] = "media\\Half-Life07.mp3";
	g_pszMP3trackFileMap[6] = "media\\Half-Life10.mp3";
	g_pszMP3trackFileMap[7] = "media\\Suspense01.mp3";
	g_pszMP3trackFileMap[8] = "media\\Suspense03.mp3";
	g_pszMP3trackFileMap[9] = "media\\Half-Life09.mp3";
	g_pszMP3trackFileMap[10] = "media\\Half-Life02.mp3";
	g_pszMP3trackFileMap[11] = "media\\Half-Life13.mp3";
	g_pszMP3trackFileMap[12] = "media\\Half-Life04.mp3";
	g_pszMP3trackFileMap[13] = "media\\Half-Life15.mp3";
	g_pszMP3trackFileMap[14] = "media\\Half-Life14.mp3";
	g_pszMP3trackFileMap[15] = "media\\Half-Life16.mp3";
	g_pszMP3trackFileMap[16] = "media\\Suspense02.mp3";
	g_pszMP3trackFileMap[17] = "media\\Half-Life03.mp3";
	g_pszMP3trackFileMap[18] = "media\\Half-Life08.mp3";
	g_pszMP3trackFileMap[19] = "media\\Prospero02.mp3";
	g_pszMP3trackFileMap[20] = "media\\Half-Life05.mp3";
	g_pszMP3trackFileMap[21] = "media\\Prospero04.mp3";
	g_pszMP3trackFileMap[22] = "media\\Half-Life11.mp3";
	g_pszMP3trackFileMap[23] = "media\\Half-Life06.mp3";
	g_pszMP3trackFileMap[24] = "media\\Prospero03.mp3";
	g_pszMP3trackFileMap[25] = "media\\Half-Life17.mp3";
	g_pszMP3trackFileMap[26] = "media\\Prospero05.mp3";
	g_pszMP3trackFileMap[27] = "media\\Suspense05.mp3";
	g_pszMP3trackFileMap[28] = "media\\Suspense07.mp3";

	g_iMP3FirstMalloc = g_iMP3NumTracks = 29;

	ResetCDTimes();

	if (MP3_Init())
		MP3_SetVolume(MP3Volume->value);

	m_bInitialized = true;
	m_bEnabled = true;

	if (gEngfuncs.CheckParm("-nocdaudio", nullptr) || gEngfuncs.CheckParm("-nosound", nullptr))
		m_bEnabled = false;

	thread->AddThreadItem(&CCDAudio::_Init, 0, 0);

	return 0;
}

void CCDAudio::_Init(int, int)
{
	if (gEngfuncs.CheckParm("-nocdaudio", nullptr))
		return;

	MCI_OPEN_PARMS mciOpenParms;
	mciOpenParms.lpstrDeviceType = "cdaudio";

	DWORD dwReturn;

	if (dwReturn = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_SHAREABLE, (DWORD)(LPVOID)&mciOpenParms))
		return;

	m_uiDeviceID = mciOpenParms.wDeviceID;

	MCI_SET_PARMS mciSetParms;
	mciSetParms.dwTimeFormat = MCI_FORMAT_TMSF;

	if (dwReturn = mciSendCommand(m_uiDeviceID, MCI_SET, MCI_SET_TIME_FORMAT, (DWORD)(LPVOID)&mciSetParms))
	{
		mciSendCommand(m_uiDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
		return;
	}

	for (int n = 0; n < MAX_REMAP; n++)
		m_rgRemapCD[n] = n;

	GetAudioDiskInfo();
}

void CCDAudio::Shutdown(void)
{
	// TODO: implement - ScriptedSnark
}

void CCDAudio::_CDReset(int, int)
{
	Shutdown();
	Sleep(1000);
	Init();
}

void CCDAudio::Reset(void)
{
	thread->AddThreadItem(&CCDAudio::_CDReset, 0, 0);
}

void CCDAudio::Stop(void)
{
	thread->AddThreadItem(&CCDAudio::_Stop, 0, 0);
}

void CCDAudio::Pause(void)
{
	if (!m_bInitialized)
		return;

	thread->AddThreadItem(&CCDAudio::_Pause, 0, 0);
}

void CCDAudio::Eject(void)
{
	thread->AddThreadItem(&CCDAudio::_Eject, 0, 0);
}

void CCDAudio::CloseDoor(void)
{
	thread->AddThreadItem(&CCDAudio::_CloseDoor, 0, 0);
}

void CCDAudio::GetAudioDiskInfo(void)
{
	thread->AddThreadItem(&CCDAudio::_GetAudioDiskInfo, 0, 0);
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
	if (!m_bInitialized)
		return;

	thread->AddThreadItem(&CCDAudio::_Resume, 0, 0);
}

void CCDAudio::SwitchToLauncher(void)
{
	thread->AddThreadItem(&CCDAudio::_SwitchToLauncher, 0, 0);
}

void CCDAudio::SwitchToEngine(void)
{
	thread->AddThreadItem(&CCDAudio::_SwitchToEngine, 0, 0);
}

void CCDAudio::FadeOut(void)
{
	if (!m_bIsPlaying)
		return;

	// TODO: get realtime
	// m_dFadeOutTime = MP3FadeTime->value + realtime;
	thread->AddThreadItem(&CCDAudio::_CDUpdate, 0, 0);
}

void CCDAudio::Frame(void)
{
	if (!m_bEnabled)
		return;

	if (m_flVolume != bgmvolume->value)
	{
		if (m_flVolume != 0.0f)
		{
			m_flVolume = 0.0f;
			Pause();
		}
		else
		{
			m_flVolume = 1.0f;
			Resume();
		}

		bgmvolume->value = m_flVolume;
	}

	if (m_dFadeOutTime == 0.0 && m_flMP3Volume != MP3Volume->value)
		m_flMP3Volume = MP3_SetVolume(MP3Volume->value);

	thread->AddThreadItem(&CCDAudio::_CDUpdate, 0, 0);
}

void CDAudio_Init(void)
{
	thread->Init();
}

void CDAudio_Shutdown(void)
{
	thread->Shutdown();
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
	if (!MP3stream)
		return;

	AIL_set_stream_loop_count(MP3stream, 0);
}

void CCDAudio::MP3_SetPause(bool OnOff)
{
	if (!MP3stream)
		return;

	AIL_pause_stream(MP3stream, OnOff);
}

void CDAudio_Hook()
{
	bgmvolume = gEngfuncs.pfnGetCvarPointer("bgmvolume");
	MP3Volume = gEngfuncs.pfnGetCvarPointer("MP3Volume");
	MP3FadeTime = gEngfuncs.pfnGetCvarPointer("MP3FadeTime");
}