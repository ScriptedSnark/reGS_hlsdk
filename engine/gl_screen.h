/**
 * Copyright - ScriptedSnark, 2022.
 * gl_screen.h - description
 */

#ifdef GL_SCREEN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in gl_screen.h
#else //GL_SCREEN_H_RECURSE_GUARD

#define GL_SCREEN_H_RECURSE_GUARD

#ifndef GL_SCREEN_H_GUARD
#define GL_SCREEN_H_GUARD
#pragma once

typedef void (*_SCR_UpdateScreen)();

extern _SCR_UpdateScreen ORIG_SCR_UpdateScreen;

#endif //GL_SCREEN_H_GUARD

#undef GL_SCREEN_H_RECURSE_GUARD
#endif //GL_SCREEN_H_RECURSE_GUARD