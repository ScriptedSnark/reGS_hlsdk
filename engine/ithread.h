#ifdef ITHREAD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in ithread.h
#else //ITHREAD_H_RECURSE_GUARD

#define ITHREAD_H_RECURSE_GUARD

#ifndef ITHREAD_H_GUARD
#define ITHREAD_H_GUARD
#pragma once

using vfunc = void (CCDAudio::*)(int, int);

class IThread
{
public:
	virtual ~IThread(void) {}
	virtual bool Init(void) = 0;
	virtual bool Shutdown(void) = 0;
	virtual bool AddThreadItem(vfunc pfn, int param1, int param2) = 0;
};

#endif //ITHREAD_H_GUARD

#undef ITHREAD_H_RECURSE_GUARD
#endif //ITHREAD_H_RECURSE_GUARD