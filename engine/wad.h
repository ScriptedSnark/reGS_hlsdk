#ifdef WAD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in wad.h
#else //WAD_H_RECURSE_GUARD

#define WAD_H_RECURSE_GUARD

#ifndef WAD_H_GUARD
#define WAD_H_GUARD
#pragma once

#define CMP_NONE 0
#define CMP_LZSS 1

#define TYP_NONE 0
#define TYP_LABEL 1

#define TYP_LUMPY 64 // 64 + grab command number
#define TYP_PALETTE 64
#define TYP_QTEX 65
#define TYP_QPIC 66
#define TYP_SOUND 67
#define TYP_MIPTEX 68

typedef struct
{
	int width, height;
	byte data[4]; // variably sized
} qpic_t;

typedef struct
{
	char identification[4]; // should be WAD2 or 2DAW
	int numlumps;
	int infotableofs;
} wadinfo_t;

typedef struct
{
	int filepos;
	int disksize;
	int size; // uncompressed
	char type;
	char compression;
	char pad1, pad2;
	char name[16]; // must be null terminated
} lumpinfo_t;

struct wadlist_t
{
	bool loaded;
	char wadname[32];
	int wad_numlumps;
	lumpinfo_t* wad_lumps;
	byte* wad_base;
};

#endif //WAD_H_GUARD

#undef WAD_H_RECURSE_GUARD
#endif //WAD_H_RECURSE_GUARD