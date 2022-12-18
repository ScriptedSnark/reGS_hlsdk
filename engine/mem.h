#ifdef MEM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in mem.h
#else //MEM_H_RECURSE_GUARD

#define MEM_H_RECURSE_GUARD

#ifndef MEM_H_GUARD
#define MEM_H_GUARD
#pragma once

/**
 *	@file
 *
 *	Heap allocation functions
 */

void* Mem_Malloc(size_t size);
void* Mem_ZeroMalloc(size_t size);
void* Mem_Realloc(void* ptr, size_t size);
void* Mem_Calloc(size_t nmemb, size_t size);
char* Mem_Strdup(const char* strSource);
void Mem_Free(void* ptr);

#endif //MEM_H_GUARD

#undef MEM_H_RECURSE_GUARD
#endif //MEM_H_RECURSE_GUARD