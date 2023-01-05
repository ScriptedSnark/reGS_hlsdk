#ifdef GLQUAKE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in glquake.h
#else //GLQUAKE_H_RECURSE_GUARD

#define GLQUAKE_H_RECURSE_GUARD

#ifndef GLQUAKE_H_GUARD
#define GLQUAKE_H_GUARD
#pragma once

#include "hud.h"
#include "cl_util.h"

#include "PlatformHeaders.h"
#include <GL/glew.h>
#include <gl/GL.h>

#include "reGS_enginehook.h"
#include "Utils.hpp"
#include "MinHook.h"
#include "reGS_patterns.hpp"

extern Utils utils;

#include "mem.h"
#include "wad.h"
#include "sys_getmodes.h"
#include "gl_model.h"
#include "cl_tent.h"
#include "gl_draw.h"
#include "cl_draw.h"
#include "vgui2/text_draw.h"
#include "gl_screen.h"
#include "vgui_intwrap2.h"
#include "cd.h"
#include "cdaudio.h"
#include "ithread.h"

#endif //GLQUAKE_H_GUARD

#undef GLQUAKE_H_RECURSE_GUARD
#endif //GLQUAKE_H_RECURSE_GUARD