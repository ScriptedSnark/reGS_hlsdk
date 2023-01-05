#ifdef SYS_GETMODES_H_RECURSE_GUARD
#error Recursive header files inclusion detected in sys_getmodes.h
#else //SYS_GETMODES_H_RECURSE_GUARD

#define SYS_GETMODES_H_RECURSE_GUARD

#ifndef SYS_GETMODES_H_GUARD
#define SYS_GETMODES_H_GUARD
#pragma once

typedef void (*_VideoMode_GetCurrentVideoMode)(int* wide, int* tall, int* bpp);
extern _VideoMode_GetCurrentVideoMode ORIG_VideoMode_GetCurrentVideoMode;

void VideoMode_GetCurrentVideoMode(int* wide, int* tall, int* bpp);

#endif //SYS_GETMODES_H_GUARD

#undef SYS_GETMODES_H_RECURSE_GUARD
#endif //SYS_GETMODES_H_RECURSE_GUARD