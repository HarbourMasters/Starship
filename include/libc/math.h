#ifndef LIBC_MATH_H
#define LIBC_MATH_H

#include <libultra/types.h>
#include <math.h>

#define M_PI    3.14159265358979323846f
#define M_DTOR	(M_PI / 180.0f)
#define M_RTOD	(180.0f / M_PI)
#define M_SQRT2 1.41421356237309504880f
#define M_SQRT1_2 0.70710678118654752440f	/* 1/sqrt(2) */
#define FLT_MAX 340282346638528859811704183484516925440.0f
#define SHT_MAX 32767.0f
#define SHT_MINV (1.0f / SHT_MAX)

typedef union {
    struct {
        u32 hi;
        u32 lo;
    } word;

    f64 d;
} du;

typedef union {
    u32 i;
    f32 f;
} fu;

#define __floorf floorf
#define __floor floor
#define __lfloorf lfloorf
#define __lfloor lfloor
#define __ceilf ceilf
#define __ceil ceil
#define __lceilf lceilf
#define __lceil lceil
#define __truncf truncf
#define __trunc trunc
#define __ltruncf ltruncf
#define __ltrunc ltrunc
#define __roundf roundf
#define __round round
#define __lroundf lroundf
#define __lround lround
#define __nearbyintf nearbyintf
#define __nearbyint nearbyint
#define __lnearbyintf lnearbyintf
#define __lnearbyint lnearbyint

#ifdef __cplusplus
extern "C" {
f32 __sinf(f32) throw();
f32 __cosf(f32) throw();
}
#else
f32 __sinf(f32);
f32 __cosf(f32);
#endif

#endif
