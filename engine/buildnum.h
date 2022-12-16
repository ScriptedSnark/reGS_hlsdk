#ifdef BUILDNUM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in buildnum.h
#else //BUILDNUM_H_RECURSE_GUARD

#define BUILDNUM_H_RECURSE_GUARD

#ifndef BUILDNUM_H_GUARD
#define BUILDNUM_H_GUARD
#pragma once

int build_number();

#endif //BUILDNUM_H_GUARD

#undef BUILDNUM_H_RECURSE_GUARD
#endif //BUILDNUM_H_RECURSE_GUARD