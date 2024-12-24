#ifndef MACROS_H
#define MACROS_H

#include "alignment.h"
#include "libc/math.h"
#include <math.h>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
// This should be part of a CVar
#define SCREEN_MARGIN 0

#define TIME_IN_SECONDS(x) (x * 30);

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define RAND_FLOAT(max) (Rand_ZeroOne()*(max))
#define RAND_INT(max) ((s32)(Rand_ZeroOne()*(max)))
#define RAND_FLOAT_CENTERED(width) ((Rand_ZeroOne()-0.5f)*(width))
#define RAND_DOUBLE_CENTERED(width) ((Rand_ZeroOne()-0.5)*(width))
#define RAND_RANGE(min, max) (((max) - (min)) * (Rand_ZeroOne() - (min) / ((min) - (max))))

#define RAND_FLOAT_SEEDED(max) (Rand_ZeroOneSeeded()*(max))
#define RAND_INT_SEEDED(max) ((s32)(Rand_ZeroOneSeeded()*(max)))
#define RAND_FLOAT_CENTERED_SEEDED(width) ((Rand_ZeroOneSeeded()-0.5f)*(width))

#define SEGMENTED_TO_VIRTUAL(segment) LOAD_ASSET(segment) 

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))
#define SIGN_OF(x) (((x) > 0) ? 1 : ((x) == 0) ? 0 : -1)
#define SQ(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))

#define DOT_XYZ(v1Ptr, v2Ptr) ((v1Ptr)->x * (v2Ptr)->x + (v1Ptr)->y * (v2Ptr)->y + (v1Ptr)->z * (v2Ptr)->z)
#define VEC3F_MAG(vecPtr) sqrtf(DOT_XYZ(vecPtr, vecPtr))
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define ABSF(x) ((x) >= 0.0f ? (x) : -(x))
#define ROUND(float) ((s32)((float)+0.5f))

#define RAD_TO_DEG(radians) (((radians) * 180.0f) / M_PI)
#define DEG_TO_RAD(degrees) (((degrees) / 180.0f) * M_PI)

extern f32 SIN_DEG(f32 angle);
extern f32 COS_DEG(f32 angle);

#define USEC_TO_CYCLES(n) (((u64)(n)*(OS_CLOCK_RATE/15625LL))/(1000000LL/15625LL))
#define MSEC_TO_CYCLES(n) (USEC_TO_CYCLES((n) * 1000LL))

#define CYCLES_TO_USEC(c)    (((u64)(c)*(1000000LL/15625LL))/(OS_CLOCK_RATE/15625LL))
#define CYCLES_TO_MSEC(c) ((s32)CYCLES_TO_USEC(c)/1000)
#define CYCLES_TO_MSEC_PC(c) (CYCLES_TO_USEC(c)/1000)

#define UNPACK_BYTE(data, bytenum) (((data) & (0xFF << ((bytenum) * 8))) >> ((bytenum) * 8))

/*
 * Macros for libultra
 */

#if defined(__sgi)
#define PRINTF
#else
#define PRINTF(...)
#endif

#define ALIGNED(x) __attribute__((aligned(x)))
#define ARRLEN(x) ((s32)(sizeof(x) / sizeof(x[0])))
#define STUBBED_PRINTF(x) ((void)(x))
#define UNUSED __attribute__((unused))

#ifndef __GNUC__
#define __attribute__(x)
#endif

#if defined(_WIN32)
    #define ALIGN_ASSET(x) __declspec(align(x))
#else
    #define ALIGN_ASSET(x) __attribute__((aligned (x)))
#endif

#endif // MACROS_H
