/* SDK libc strtol (session 6, worker 28): ee-gcc 2.96, normal delay-slot
 * filling. newlib's _strtol_r; long is 64-bit. The ctype table must be
 * indexed in the (_ctype_ + 1)[c] pointer form. */
#include "common.h"

typedef struct { s32 _errno; } StrtolReent;
extern const char D_00491A18[]; /* newlib _ctype_: _U 1, _L 2, _N 4, _S 8 */
#define CTYPE(c) ((D_00491A18 + 1)[c]) /* pointer form; array indexing gets hoisted */

s64 func_00272a00(StrtolReent *rptr, const char *nptr, char **endptr, s32 base) {
    const char *s = nptr;
    u64 acc;
    s32 c;
    u64 cutoff;
    s32 neg = 0, any, cutlim;

    do {
        c = *s++;
    } while (CTYPE(c) & 8);
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = neg ? -(u64)0x8000000000000000LL : 0x7FFFFFFFFFFFFFFFLL;
    cutlim = cutoff % (u64)base;
    cutoff /= (u64)base;
    for (acc = 0, any = 0;; c = *s++) {
        if (CTYPE(c) & 4)
            c -= '0';
        else if (CTYPE(c) & 3)
            c -= (CTYPE(c) & 1) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = neg ? 0x8000000000000000LL : 0x7FFFFFFFFFFFFFFFLL;
        rptr->_errno = 34; /* ERANGE */
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return acc;
}
