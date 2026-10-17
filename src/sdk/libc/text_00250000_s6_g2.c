#include "common.h"

/* newlib vfprintf.c, FLOATING_POINT + _NO_LONGLONG: _vfprintf_r */
#include "reent.h"
#include "fvwrite.h"

typedef long long quad_t;
typedef unsigned long long u_quad_t;
typedef unsigned long u_long;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef int wchar_t;

int __swsetup(FILE *);
int __sfvwrite(FILE *, struct __suio *);
void *memchr(const void *, int, size_t);
int _mbtowc_r(struct _reent *, wchar_t *, const char *, size_t, int *);
extern int D_0046AE30; /* __mb_cur_max */
#define MB_CUR_MAX D_0046AE30
extern const char D_00491D20[]; /* blanks */
extern const char D_00491D30[]; /* zeroes */
extern char D_00491D40[];       /* "Inf" */
extern char D_00491D48[];       /* "NaN" */
extern char D_00491D50[];       /* "0123456789abcdef" */
extern char D_00491D68[];       /* "(null)" */
extern char D_00491D70[];       /* "0123456789ABCDEF" */
extern char D_00491D88[];       /* "bug in vfprintf: bad base" */
extern char D_00491DA8[];       /* "0" */
extern char D_00491DB0[];       /* "." */
struct lconv { char *decimal_point; };
struct lconv *localeconv(void);
int isinf(double);
int isnan(double);
char *func_00253b10(struct _reent *, double, int, int, char *, int *, int, int *);
#define cvt func_00253b10
int func_00253cd0(char *, int, int);
#define exponent func_00253cd0

#define __sferror(p) (((p)->_flags & __SERR) != 0)
#define cantwrite(fp) \
    ((((fp)->_flags & __SWR) == 0 || (fp)->_bf._base == 0) && __swsetup(fp))

CONTEXT_ONLY int func_00252328(FILE *fp, register struct __suio *uio) {
    register int err;

    if (uio->uio_resid == 0) {
        uio->uio_iovcnt = 0;
        return (0);
    }
    err = __sfvwrite(fp, uio);
    uio->uio_resid = 0;
    uio->uio_iovcnt = 0;
    return (err);
}
#define __sprint func_00252328

CONTEXT_ONLY int func_00252370(register FILE *fp, const char *fmt, va_list ap) {
    int ret;
    FILE fake;
    unsigned char buf[1024];

    fake._data = fp->_data;
    fake._flags = fp->_flags & ~__SNBF;
    fake._file = fp->_file;
    fake._cookie = fp->_cookie;
    fake._write = fp->_write;
    fake._bf._base = fake._p = buf;
    fake._bf._size = fake._w = sizeof(buf);
    fake._lbfsize = 0;
    ret = vfprintf(&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake))
        ret = EOF;
    if (fake._flags & __SERR)
        fp->_flags |= __SERR;
    return (ret);
}
#define __sbprintf func_00252370

#define MAXEXP 308
#define MAXFRACT 39
#define BUF (MAXEXP + MAXFRACT + 1)
#define DEFPREC 6

#define to_digit(c) ((c) - '0')
#define is_digit(c) ((unsigned) to_digit(c) <= 9)
#define to_char(n) ((n) + '0')

#define ALT 0x001
#define HEXPREFIX 0x002
#define LADJUST 0x004
#define LONGDBL 0x008
#define LONGINT 0x010
#define QUADINT 0x020
#define SHORTINT 0x040
#define ZEROPAD 0x080
#define FPT 0x100

/* rodata */
int _vfprintf_r(struct _reent *data, FILE *fp, const char *fmt0, va_list ap) {
    register char *fmt;
    register int ch;
    register int n, m;
    register char *cp;
    register struct __siov *iovp;
    register int flags;
    int ret;
    int width;
    int prec;
    char sign;
    wchar_t wc;
    char *decimal_point = localeconv()->decimal_point;
    char softsign;
    double _double;
    int expt;
    int expsize;
    int ndig;
    char expstr[7];
    u_quad_t _uquad;
    enum { OCT, DEC, HEX } base;
    int dprec;
    int realsz;
    int size;
    char *xdigs;
#define NIOV 8
    struct __suio uio;
    struct __siov iov[NIOV];
    char buf[BUF];
    char ox[2];
    int state = 0;

#define PADSIZE 16
#define blanks D_00491D20
#define zeroes D_00491D30

#define PRINT(ptr, len) { \
    iovp->iov_base = (ptr); \
    iovp->iov_len = (len); \
    uio.uio_resid += (len); \
    iovp++; \
    if (++uio.uio_iovcnt >= NIOV) { \
        if (__sprint(fp, &uio)) \
            goto error; \
        iovp = iov; \
    } \
}
#define PAD(howmany, with) { \
    if ((n = (howmany)) > 0) { \
        while (n > PADSIZE) { \
            PRINT(with, PADSIZE); \
            n -= PADSIZE; \
        } \
        PRINT(with, n); \
    } \
}
#define FLUSH() { \
    if (uio.uio_resid && __sprint(fp, &uio)) \
        goto error; \
    uio.uio_iovcnt = 0; \
    iovp = iov; \
}

#define SARG() \
    (flags & LONGINT ? va_arg(ap, long) : \
     flags & SHORTINT ? (long) (short) va_arg(ap, int) : \
     (long) va_arg(ap, int))
#define UARG() \
    (flags & LONGINT ? va_arg(ap, u_long) : \
     flags & SHORTINT ? (u_long) (u_short) va_arg(ap, int) : \
     (u_long) va_arg(ap, u_int))

    if (cantwrite(fp))
        return (EOF);

    if ((fp->_flags & (__SNBF | __SWR | __SRW)) == (__SNBF | __SWR) &&
        fp->_file >= 0)
        return (__sbprintf(fp, fmt0, ap));

    fmt = (char *) fmt0;
    uio.uio_iov = iovp = iov;
    uio.uio_resid = 0;
    uio.uio_iovcnt = 0;
    ret = 0;

    for (;;) {
        cp = fmt;
        while ((n = _mbtowc_r(_REENT, &wc, fmt, MB_CUR_MAX, &state)) > 0) {
            fmt += n;
            if (wc == '%') {
                fmt--;
                break;
            }
        }
        if ((m = fmt - cp) != 0) {
            PRINT(cp, m);
            ret += m;
        }
        if (n <= 0)
            goto done;
        fmt++;

        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';

    rflag:
        ch = *fmt++;
    reswitch:
        switch (ch) {
        case ' ':
            if (!sign)
                sign = ' ';
            goto rflag;
        case '#':
            flags |= ALT;
            goto rflag;
        case '*':
            if ((width = va_arg(ap, int)) >= 0)
                goto rflag;
            width = -width;
            /* FALLTHROUGH */
        case '-':
            flags |= LADJUST;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if ((ch = *fmt++) == '*') {
                n = va_arg(ap, int);
                prec = n < 0 ? -1 : n;
                goto rflag;
            }
            n = 0;
            while (is_digit(ch)) {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            }
            prec = n < 0 ? -1 : n;
            goto reswitch;
        case '0':
            flags |= ZEROPAD;
            goto rflag;
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            n = 0;
            do {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            } while (is_digit(ch));
            width = n;
            goto reswitch;
        case 'L':
            flags |= LONGDBL;
            goto rflag;
        case 'h':
            flags |= SHORTINT;
            goto rflag;
        case 'l':
            if (*fmt == 'l') {
                fmt++;
                flags |= QUADINT;
            } else {
                flags |= LONGINT;
            }
            goto rflag;
        case 'q':
            flags |= QUADINT;
            goto rflag;
        case 'c':
            *(cp = buf) = va_arg(ap, int);
            size = 1;
            sign = '\0';
            break;
        case 'D':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'd':
        case 'i':
            _uquad = SARG();
            if ((quad_t) _uquad < 0) {
                _uquad = -_uquad;
                sign = '-';
            }
            base = DEC;
            goto number;
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
            if (prec == -1) {
                prec = DEFPREC;
            } else if ((ch == 'g' || ch == 'G') && prec == 0) {
                prec = 1;
            }
            if (flags & LONGDBL) {
                _double = (double) va_arg(ap, long double);
            } else {
                _double = va_arg(ap, double);
            }
            if (isinf(_double)) {
                if (_double < 0)
                    sign = '-';
                cp = D_00491D40;
                size = 3;
                break;
            }
            if (isnan(_double)) {
                cp = D_00491D48;
                size = 3;
                break;
            }
            flags |= FPT;
            cp = cvt(data, _double, prec, flags, &softsign, &expt, ch, &ndig);
            if (ch == 'g' || ch == 'G') {
                if (expt <= -4 || expt > prec)
                    ch = (ch == 'g') ? 'e' : 'E';
                else
                    ch = 'g';
            }
            if (ch <= 'e') {
                --expt;
                expsize = exponent(expstr, expt, ch);
                size = expsize + ndig;
                if (ndig > 1 || flags & ALT)
                    ++size;
            } else if (ch == 'f') {
                if (expt > 0) {
                    size = expt;
                    if (prec || flags & ALT)
                        size += prec + 1;
                } else
                    size = prec + 2;
            } else if (expt >= ndig) {
                size = expt;
                if (flags & ALT)
                    ++size;
            } else
                size = ndig + (expt > 0 ? 1 : 2 - expt);

            if (softsign)
                sign = '-';
            break;
        case 'n':
            if (flags & LONGINT)
                *va_arg(ap, long *) = ret;
            else if (flags & SHORTINT)
                *va_arg(ap, short *) = ret;
            else
                *va_arg(ap, int *) = ret;
            continue;
        case 'O':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'o':
            _uquad = UARG();
            base = OCT;
            goto nosign;
        case 'p':
            _uquad = (long) va_arg(ap, void *);
            base = HEX;
            xdigs = D_00491D50;
            flags |= HEXPREFIX;
            ch = 'x';
            goto nosign;
        case 's':
            if ((cp = va_arg(ap, char *)) == 0)
                cp = D_00491D68;
            if (prec >= 0) {
                char *p = memchr(cp, 0, prec);

                if (p != 0) {
                    size = p - cp;
                    if (size > prec)
                        size = prec;
                } else
                    size = prec;
            } else
                size = strlen(cp);
            sign = '\0';
            break;
        case 'U':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'u':
            _uquad = UARG();
            base = DEC;
            goto nosign;
        case 'X':
            xdigs = D_00491D70;
            goto hex;
        case 'x':
            xdigs = D_00491D50;
        hex:
            _uquad = UARG();
            base = HEX;
            if (flags & ALT && _uquad != 0)
                flags |= HEXPREFIX;
        nosign:
            sign = '\0';
        number:
            if ((dprec = prec) >= 0)
                flags &= ~ZEROPAD;
            cp = buf + BUF;
            if (_uquad != 0 || prec != 0) {
                switch (base) {
                case OCT:
                    do {
                        *--cp = to_char(_uquad & 7);
                        _uquad >>= 3;
                    } while (_uquad);
                    if (flags & ALT && *cp != '0')
                        *--cp = '0';
                    break;
                case DEC:
                    while (_uquad >= 10) {
                        *--cp = to_char(_uquad % 10);
                        _uquad /= 10;
                    }
                    *--cp = to_char(_uquad);
                    break;
                case HEX:
                    do {
                        *--cp = xdigs[_uquad & 15];
                        _uquad >>= 4;
                    } while (_uquad);
                    break;
                default:
                    cp = D_00491D88;
                    size = strlen(cp);
                    goto skipsize;
                }
            }
            size = buf + BUF - cp;
        skipsize:
            break;
        default:
            if (ch == '\0')
                goto done;
            cp = buf;
            *cp = ch;
            size = 1;
            sign = '\0';
            break;
        }

        realsz = dprec > size ? dprec : size;
        if (sign)
            realsz++;
        else if (flags & HEXPREFIX)
            realsz += 2;

        if ((flags & (LADJUST | ZEROPAD)) == 0)
            PAD(width - realsz, blanks);

        if (sign) {
            PRINT(&sign, 1);
        } else if (flags & HEXPREFIX) {
            ox[0] = '0';
            ox[1] = ch;
            PRINT(ox, 2);
        }

        if ((flags & (LADJUST | ZEROPAD)) == ZEROPAD)
            PAD(width - realsz, zeroes);

        PAD(dprec - size, zeroes);

        if ((flags & FPT) == 0) {
            PRINT(cp, size);
        } else {
            if (ch >= 'f') {
                if (_double == 0) {
                    PRINT(D_00491DA8, 1);
                    if (expt < ndig || (flags & ALT) != 0) {
                        PRINT(decimal_point, 1);
                        PAD(ndig - 1, zeroes);
                    }
                } else if (expt <= 0) {
                    PRINT(D_00491DA8, 1);
                    if (expt || ndig) {
                        PRINT(decimal_point, 1);
                        PAD(-expt, zeroes);
                        PRINT(cp, ndig);
                    }
                } else if (expt >= ndig) {
                    PRINT(cp, ndig);
                    PAD(expt - ndig, zeroes);
                    if (flags & ALT)
                        PRINT(D_00491DB0, 1);
                } else {
                    PRINT(cp, expt);
                    cp += expt;
                    PRINT(D_00491DB0, 1);
                    PRINT(cp, ndig - expt);
                }
            } else {
                if (ndig > 1 || flags & ALT) {
                    ox[0] = *cp++;
                    ox[1] = '.';
                    PRINT(ox, 2);
                    if (_double || flags & ALT == 0) {
                        PRINT(cp, ndig - 1);
                    } else
                        PAD(ndig - 1, zeroes);
                } else
                    PRINT(cp, 1);
                PRINT(expstr, expsize);
            }
        }

        if (flags & LADJUST)
            PAD(width - realsz, blanks);

        ret += width > realsz ? width : realsz;

        FLUSH();
    }
done:
    FLUSH();
error:
    return (__sferror(fp) ? EOF : ret);
}
