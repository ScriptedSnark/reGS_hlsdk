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

#include "wad.h"
#include "gl_model.h"
#include "gl_draw.h"
#include "vgui2/text_draw.h"
#include "gl_screen.h"

#endif //GLQUAKE_H_GUARD

#undef GLQUAKE_H_RECURSE_GUARD
#endif //GLQUAKE_H_RECURSE_GUARD