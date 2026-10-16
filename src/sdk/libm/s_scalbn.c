/* newlib s_scalbn.c. sdk segment. two54/twom54 become immediates. The retail
 * compiler passed a constant from memory as the second operand of a
 * commutative soft-float call (newlib's `tiny*x` is __muldf3(x, tiny)), so
 * those products are written with the constant on the right. */
#include "fdlibm.h"

static const double
    two54 = 1.80143985094819840000e+16,
    twom54 = 5.55111512312578270212e-17,
    huge = 1.0e+300,
    tiny = 1.0e-300;

double copysign(double, double);

double scalbn(double x, int n) {
    __int32_t k, hx, lx;

    EXTRACT_WORDS(hx, lx, x);
    k = (hx & 0x7ff00000) >> 20;
    if (k == 0) {
        if ((lx | (hx & 0x7fffffff)) == 0) {
            return x;
        }
        x *= two54;
        GET_HIGH_WORD(hx, x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000) {
            return x * tiny;
        }
    }
    if (k == 0x7ff) {
        return x + x;
    }
    k = k + n;
    if (k > 0x7fe) {
        return copysign(huge, x) * huge;
    }
    if (k > 0) {
        SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
        return x;
    }
    if (k <= -54) {
        if (n > 50000) {
            return copysign(huge, x) * huge;
        } else {
            return copysign(tiny, x) * tiny;
        }
    }
    k += 54;
    SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
    return x * twom54;
}
