/* newlib s_floor.c. sdk segment. Double arithmetic goes through libgcc's
 * soft-float routines. newlib writes `huge+x`; the retail compiler passed the
 * operands to __adddf3 the other way round, which `x + huge` reproduces. */
#include "fdlibm.h"

static const double huge = 1.0e300;

double floor(double x) {
    __int32_t i0, i1, j0;
    __uint32_t i, j;

    EXTRACT_WORDS(i0, i1, x);
    j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
    if (j0 < 20) {
        if (j0 < 0) {
            if (x + huge > 0.0) {
                if (i0 >= 0) {
                    i0 = i1 = 0;
                } else if (((i0 & 0x7fffffff) | i1) != 0) {
                    i0 = 0xbff00000;
                    i1 = 0;
                }
            }
        } else {
            i = (0x000fffff) >> j0;
            if (((i0 & i) | i1) == 0) {
                return x;
            }
            if (x + huge > 0.0) {
                if (i0 < 0) {
                    i0 += (0x00100000) >> j0;
                }
                i0 &= (~i);
                i1 = 0;
            }
        }
    } else if (j0 > 51) {
        if (j0 == 0x400) {
            return x + x;
        } else {
            return x;
        }
    } else {
        i = ((__uint32_t) (0xffffffff)) >> (j0 - 20);
        if ((i1 & i) == 0) {
            return x;
        }
        if (x + huge > 0.0) {
            if (i0 < 0) {
                if (j0 == 20) {
                    i0 += 1;
                } else {
                    j = i1 + (1 << (52 - j0));
                    if (j < i1) {
                        i0 += 1;
                    }
                    i1 = j;
                }
            }
            i1 &= (~i);
        }
    }
    INSERT_WORDS(x, i0, i1);
    return x;
}
