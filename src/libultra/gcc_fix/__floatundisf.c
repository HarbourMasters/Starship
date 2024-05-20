#ifdef COMPILER_GCC

typedef union DoubleFloatUnion {
    double d;
    long long int ll;
    unsigned long long ull;
} DoubleFloatUnion;

/**
 * Gets float32 from uint64_t.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__floatundisf
 */
float __floatundisf(unsigned long long i) {
    register DoubleFloatUnion dull;
    register float ret;

    dull.ull = i;
    __asm__("cvt.s.l %0, %1" : "=f"(ret) : "f"(dull.d));
    if ((long) i < 0) {
        // cvt.s.l assumes signed input, adjust output
        ret += 4294967296.0f; // 2^32
    }

    return ret;
}
#endif
