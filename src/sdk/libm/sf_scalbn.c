/* newlib sf_scalbn.c. sdk segment. With _FLT_NO_DENORMALS the subnormal
 * input and output paths are compiled out. */
#include "fdlibm.h"

static const float huge = 1.0e+30, tiny = 1.0e-30;

float copysignf(float, float);

float scalbnf(float x, int n) {
    __int32_t k, ix;
    __uint32_t hx;

    GET_FLOAT_WORD(ix, x);
    hx = ix & 0x7fffffff;
    k = hx >> 23;
    if (FLT_UWORD_IS_ZERO(hx)) {
        return x;
    }
    k = k + n;
    if (k > 0xff) {
        return huge * copysignf(huge, x);
    }
    if (k > 0) {
        SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
        return x;
    }
    if (n > 50000) {
        return huge * copysignf(huge, x);
    }
    return tiny * copysignf(tiny, x);
}
