/* newlib ef_atan2.c. sdk segment. No NaN/Inf cases (_FLT_LARGEST_EXPONENT_IS_NORMAL). */
#include "fdlibm.h"

static const float
    tiny = 1.0e-30,
    zero = 0.0,
    pi_o_4 = 7.8539818525e-01,
    pi_o_2 = 1.5707963705e+00,
    pi = 3.1415925026e+00,
    pi_lo = 1.5099578832e-07;

float atanf(float);
float fabsf(float);

float __ieee754_atan2f(float y, float x) {
    float z;
    __int32_t k, m, hx, hy, ix, iy;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    GET_FLOAT_WORD(hy, y);
    iy = hy & 0x7fffffff;
    if (hx == 0x3f800000) {
        return atanf(y);
    }
    m = ((hy >> 31) & 1) | ((hx >> 30) & 2);

    if (FLT_UWORD_IS_ZERO(iy)) {
        switch (m) {
        case 0:
        case 1:
            return y;
        case 2:
            return pi + tiny;
        case 3:
            return -pi - tiny;
        }
    }
    if (FLT_UWORD_IS_ZERO(ix)) {
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    k = (iy - ix) >> 23;
    if (k > 60) {
        z = pi_o_2 + (float) 0.5 * pi_lo;
    } else if (hx < 0 && k < -60) {
        z = 0.0;
    } else {
        z = atanf(fabsf(y / x));
    }
    switch (m) {
    case 0:
        return z;
    case 1: {
        __uint32_t zh;
        GET_FLOAT_WORD(zh, z);
        SET_FLOAT_WORD(z, zh ^ 0x80000000);
    }
        return z;
    case 2:
        return pi - (z - pi_lo);
    default:
        return (z - pi_lo) - pi;
    }
}
