#include "sys.h"
#include "prevent_bss_reordering.h"

s32 sSeededRandSeed3;
s32 sRandSeed1;
s32 sRandSeed2;
s32 sRandSeed3;
s32 sSeededRandSeed1;
s32 sSeededRandSeed2;

f32 Math_ModF(f32 value, f32 mod) {
    return value - ((s32) (value / mod) * mod);
}

void Rand_Init(void) {
    sRandSeed1 = (s32) osGetTime() % 30000;
    sRandSeed2 = (s32) osGetTime() % 30000;
    sRandSeed3 = (s32) osGetTime() % 30000;
}

f32 Rand_ZeroOne(void) {
    sRandSeed1 = (sRandSeed1 * 171) % 30269;
    sRandSeed2 = (sRandSeed2 * 172) % 30307;
    sRandSeed3 = (sRandSeed3 * 170) % 30323;

    return fabsf(Math_ModF((sRandSeed1 / 30269.0f) + (sRandSeed2 / 30307.0f) + (sRandSeed3 / 30323.0f), 1.0f));
}

void Rand_SetSeed(s32 seed1, s32 seed2, s32 seed3) {
    sSeededRandSeed1 = seed1;
    sSeededRandSeed2 = seed2;
    sSeededRandSeed3 = seed3;
}

f32 Rand_ZeroOneSeeded(void) {
    sSeededRandSeed1 = (sSeededRandSeed1 * 171) % 30269;
    sSeededRandSeed2 = (sSeededRandSeed2 * 172) % 30307;
    sSeededRandSeed3 = (sSeededRandSeed3 * 170) % 30323;

    return fabsf(
        Math_ModF((sSeededRandSeed1 / 30269.0f) + (sSeededRandSeed2 / 30307.0f) + (sSeededRandSeed3 / 30323.0f), 1.0f));
}

f32 Math_Atan2F(f32 y, f32 x) {
    if ((y == 0.0f) && (x == 0.0f)) {
        return 0.0f;
    }

    if (x == 0.0f) {
        if (y < 0.0f) {
            return -M_PI / 2.0f;
        } else {
            return M_PI / 2.0f;
        }
    }

    if (x < 0.0f) {
        if (y < 0.0f) {
            return -(M_PI - Math_FAtanF(fabs(y / x)));
        } else {
            return M_PI - Math_FAtanF(fabs(y / x));
        }
    } else {
        return Math_FAtanF(y / x);
    }
}

f32 Math_Atan2F_XY(f32 x, f32 y) {
    if ((x == 0.0f) && (y == 0.0f)) {
        return 0.0f;
    }

    if (x == 0.0f) {
        if (y < 0.0f) {
            return -M_PI / 2.0f;
        } else {
            return M_PI / 2.0f;
        }
    }

    if (y == 0.0f) {
        if (x > 0.0f) {
            return 0.0f;
        } else {
            return M_PI;
        }
    }

    if (x < 0.0f) {
        if (y < 0.0f) {
            return -(M_PI - Math_FAtanF(fabs(x / y)));
        } else {
            return M_PI - Math_FAtanF(fabs(x / y));
        }
    } else {
        return Math_FAtanF(x / y);
    }
}

f32 Math_Atan2F_XYAlt(f32 x, f32 y) {
    if ((x == 0.0f) && (y == 0.0f)) {
        return 0.0f;
    }

    if (x == 0.0f) {
        if (y < 0.0f) {
            return -M_PI / 2.0f;
        }
        return M_PI / 2.0f;
    }

    if (y == 0.0f) {
        return 0.0f;
    }
    return -Math_FAtanF(x / y);
}

f32 Math_FactorialF(f32 n) {
    f32 out = 1.0f;
    s32 i;

    for (i = (s32) n; i > 1; i--) {
        out *= i;
    }

    return out;
}

f32 D_800C45E0[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600 };

f32 Math_Factorial(s32 n) {
    f32 out;
    s32 i;

    if (n > 12) {
        out = 1.0f;

        for (i = n; i > 1; i--) {
            out *= i;
        }
    } else {
        out = D_800C45E0[n];
    }
    return out;
}

f32 Math_PowF(f32 base, s32 exp) {
    f32 out = 1.0f;

    while (exp > 0) {
        exp--;
        out *= base;
    }
    return out;
}

void Math_MinMax(s32* min, s32* max, s32 val1, s32 val2, s32 val3) {
    if (val1 < val2) {
        if (val2 < val3) {
            *min = val1;
            *max = val3;
            return;
        }
        *max = val2;

        if (val1 < val3) {
            *min = val1;
            return;
        }
        *min = val3;
        return;
    }

    if (val1 < val3) {
        *min = val2;
        *max = val3;
        return;
    }
    *max = val1;

    if (val2 < val3) {
        *min = val2;
        return;
    }
    *min = val3;
}
