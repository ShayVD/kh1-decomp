/* newlib libm (fdlibm): simple functions and the _IEEE_LIBM wrappers.
 * Rewritten to match SLPS_251.98; same behaviour as fdlibm (Sun
 * Microsystems, freely distributable). sdk segment, not ported. */
#include "fdlibm.h"

/* w_*.c: with _IEEE_LIBM the public names call the internals directly. */
double asin(double x) { return __ieee754_asin(x); }
double atan2(double y, double x) { return __ieee754_atan2(y, x); }
double sqrt(double x) { return __ieee754_sqrt(x); }
float acosf(float x) { return __ieee754_acosf(x); }
float asinf(float x) { return __ieee754_asinf(x); }
float atan2f(float y, float x) { return __ieee754_atan2f(y, x); }
float fmodf(float x, float y) { return __ieee754_fmodf(x, y); }
float powf(float x, float y) { return __ieee754_powf(x, y); }
float sqrtf(float x) { return __ieee754_sqrtf(x); }

float fabsf(float x) {
    __uint32_t ix;
    GET_FLOAT_WORD(ix, x);
    SET_FLOAT_WORD(x, ix & 0x7fffffff);
    return x;
}

float copysignf(float x, float y) {
    __uint32_t ix, iy;
    GET_FLOAT_WORD(ix, x);
    GET_FLOAT_WORD(iy, y);
    SET_FLOAT_WORD(x, (ix & 0x7fffffff) | (iy & 0x80000000));
    return x;
}

double copysign(double x, double y) {
    __uint32_t hx, hy;
    GET_HIGH_WORD(hx, x);
    GET_HIGH_WORD(hy, y);
    SET_HIGH_WORD(x, (hx & 0x7fffffff) | (hy & 0x80000000));
    return x;
}

double nan(void) {
    double x;
    INSERT_WORDS(x, 0x7ff80000, 0);
    return x;
}

float sinf(float x) {
    float y[2], z = 0.0;
    __int32_t n, ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix <= 0x3f490fd8) {
        return __kernel_sinf(x, z, 0);
    } else {
        n = __ieee754_rem_pio2f(x, y);
        switch (n & 3) {
        case 0: return __kernel_sinf(y[0], y[1], 1);
        case 1: return __kernel_cosf(y[0], y[1]);
        case 2: return -__kernel_sinf(y[0], y[1], 1);
        default: return -__kernel_cosf(y[0], y[1]);
        }
    }
}

float cosf(float x) {
    float y[2], z = 0.0;
    __int32_t n, ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix <= 0x3f490fd8) {
        return __kernel_cosf(x, z);
    } else {
        n = __ieee754_rem_pio2f(x, y);
        switch (n & 3) {
        case 0: return __kernel_cosf(y[0], y[1]);
        case 1: return -__kernel_sinf(y[0], y[1], 1);
        case 2: return -__kernel_cosf(y[0], y[1]);
        default: return __kernel_sinf(y[0], y[1], 1);
        }
    }
}

float tanf(float x) {
    float y[2], z = 0.0;
    __int32_t n, ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix <= 0x3f490fda) {
        return __kernel_tanf(x, z, 1);
    } else {
        n = __ieee754_rem_pio2f(x, y);
        return __kernel_tanf(y[0], y[1], 1 - ((n & 1) << 1));
    }
}
