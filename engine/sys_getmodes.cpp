#include "glquake.h"

_VideoMode_GetCurrentVideoMode ORIG_VideoMode_GetCurrentVideoMode = NULL;

void VideoMode_GetCurrentVideoMode(int* wide, int* tall, int* bpp)
{
	ORIG_VideoMode_GetCurrentVideoMode(wide, tall, bpp);
}

void VideoMode_Hook()
{
	Hook(VideoMode_GetCurrentVideoMode);
}