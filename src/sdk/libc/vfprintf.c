/* newlib stdio/vfprintf.c, the vfprintf wrapper (the _vfprintf_r engine is
 * not decompiled yet). sdk segment. */
#include "reent.h"

/* vfprintf.c's floating point helpers (static there). */
#include "mprec.h"

#define ALT 0x001
#define MAXEXP 308
#define to_char(n) ((n) + '0')

char *_dtoa_r(struct _reent *, double, int, int, int *, int *, char **);

#define cvt func_00253b10
static char *cvt(struct _reent *data, double value, int ndigits, int flags, char *sign, int *decpt, int ch,
                 int *length) {
    int mode, dsgn;
    char *digits, *bp, *rve;
    union double_union tmp;

    if (ch == 'f') {
        mode = 3; /* ndigits after the decimal point */
    } else {
        /* To obtain ndigits after the decimal point for the 'e' and 'E'
           formats, round to ndigits + 1 significant figures. */
        if (ch == 'e' || ch == 'E') {
            ndigits++;
        }
        mode = 2; /* ndigits significant digits */
    }

    tmp.d = value;
    if (word0(tmp) & Sign_bit) { /* this will check for < 0 and -0.0 */
        value = -value;
        *sign = '-';
    } else
        *sign = '\000';
    digits = _dtoa_r(data, value, mode, ndigits, decpt, &dsgn, &rve);
    if ((ch != 'g' && ch != 'G') || flags & ALT) { /* Print trailing zeros */
        bp = digits + ndigits;
        if (ch == 'f') {
            if (*digits == '0' && value)
                *decpt = -ndigits + 1;
            bp += *decpt;
        }
        if (value == 0) /* kludge for __dtoa irregularity */
            rve = bp;
        while (rve < bp)
            *rve++ = '0';
    }
    *length = rve - digits;
    return (digits);
}

#define exponent func_00253cd0
static int exponent(char *p0, int exp, int fmtch) {
    register char *p, *t;
    char expbuf[MAXEXP];

    p = p0;
    *p++ = fmtch;
    if (exp < 0) {
        exp = -exp;
        *p++ = '-';
    } else
        *p++ = '+';
    t = expbuf + MAXEXP;
    if (exp > 9) {
        do {
            *--t = to_char(exp % 10);
        } while ((exp /= 10) > 9);
        *--t = to_char(exp);
        for (; t < expbuf + MAXEXP; *p++ = *t++)
            ;
    } else {
        *p++ = '0';
        *p++ = to_char(exp);
    }
    return (p - p0);
}

/* vfprintf.c's static __sbprintf: flush a temporary buffer for unbuffered
 * files. */
#define __sbprintf func_00252370
static int __sbprintf(register FILE *fp, const char *fmt, va_list ap) {
    int ret;
    FILE fake;
    unsigned char buf[1024]; /* BUFSIZ */

    /* copy the important variables */
    fake._data = fp->_data;
    fake._flags = fp->_flags & ~__SNBF;
    fake._file = fp->_file;
    fake._cookie = fp->_cookie;
    fake._write = fp->_write;

    /* set up the buffer */
    fake._bf._base = fake._p = buf;
    fake._bf._size = fake._w = sizeof(buf);
    fake._lbfsize = 0; /* not actually used, but Just In Case */

    /* do the work, then copy any error status */
    ret = vfprintf(&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake))
        ret = EOF;
    if (fake._flags & __SERR)
        fp->_flags |= __SERR;
    return (ret);
}

int vfprintf(FILE *fp, const char *fmt0, va_list ap) {
    CHECK_INIT(fp);
    return _vfprintf_r(fp->_data, fp, fmt0, ap);
}
