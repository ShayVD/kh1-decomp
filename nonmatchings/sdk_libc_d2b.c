/* d2b (0x00257260), sdk segment: newlib mprec.c, built like the rest of
 * src/sdk/libc (-fno-builtin, no_fill). 5 words differ: the original keeps
 * y = d1 in a1 and sets a0 = &y before storing y; ours uses v0 and the
 * other order. Paste back into src/sdk/libc/mprec.c before ratio(). */
#include "../src/sdk/libc/mprec.h"

_Bigint *d2b(struct _reent *ptr, double _d, int *e, int *bits) {
    union double_union d;
    _Bigint *b;
    int de, i, k;
    __ULong *x, y, z;
    d.d = _d;
#define d0 word0(d)
#define d1 word1(d)
    d.d = _d;

    b = Balloc(ptr, 1);
    x = b->_x;

    z = d0 & Frac_mask;
    d0 &= 0x7fffffff; /* clear sign bit, which we ignore */
    if ((de = (int) (d0 >> Exp_shift)))
        z |= Exp_msk1;
    if ((y = d1)) {
        if ((k = lo0bits(&y))) {
            x[0] = y | z << (32 - k);
            z >>= k;
        } else
            x[0] = y;
        i = b->_wds = (x[1] = z) ? 2 : 1;
    } else {
        k = lo0bits(&z);
        x[0] = z;
        i = b->_wds = 1;
        k += 32;
    }
    if (de) {
        *e = de - Bias - (P - 1) + k;
        *bits = P - k;
    } else {
        *e = de - Bias - (P - 1) + 1 + k;
        *bits = 32 * i - hi0bits(x[i - 1]);
    }
    return b;
}
#undef d0
#undef d1
