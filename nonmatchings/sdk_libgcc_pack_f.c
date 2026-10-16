/* __pack_f (0x00265028), sdk segment: gcc fp-bit.c, single precision, as
 * the SDK built it (bitfield layout, no NaN/Inf, no denormals, no rounding;
 * see src/sdk/libgcc/). One word differs: the original fills the delay slot
 * of the `normal_exp > 128` test with `li a3,255` as a branch-likely
 * (beqzl), ours as a plain beqz. Everything else matches. */
#define FLOAT
#include "../src/sdk/libgcc/fp-bit.h"

/* Single precision has no NaN or infinity either (the largest exponent is a
 * normal number), on top of no denormals and no rounding. */
FLO_type __pack_f(fp_number_type *src) {
    FLO_union_type dst;
    fractype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;

    if (iszero(src)) {
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < NORMAL_EXPMIN) {
            fraction = 0;
        } else if (src->normal_exp > EXPBIAS + 1) {
            exp = EXPMAX;
            fraction = 0;
        } else {
            exp = src->normal_exp + EXPBIAS;
            if (src->normal_exp == EXPBIAS + 1 && (intfrac) fraction < 0) {
                exp = EXPMAX;
                fraction = 0;
            } else {
                fraction >>= NGARDS;
            }
        }
    }

    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}

