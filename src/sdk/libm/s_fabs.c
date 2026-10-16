/* newlib s_fabs.c. sdk segment. The final `move v0, a0` stays out of the
 * `jr ra` delay slot because the SDK's assembler never filled slots itself
 * (no_fill in kh1.toml). */
#include "fdlibm.h"

double fabs(double x) {
    __uint32_t high;
    GET_HIGH_WORD(high, x);
    SET_HIGH_WORD(x, high & 0x7fffffff);
    return x;
}
