#include "common.h"
#include "mprec.h"

/* d2b belongs in mprec.c between b2d and ratio; the CONTEXT_ONLY callees
 * above it are copies of the mprec.c definitions. */
CONTEXT_ONLY _Bigint *Balloc(struct _reent *ptr, int k) {
    int x;
    _Bigint *rv;

    if (ptr->_freelist == 0) {
        /* Allocate a list of pointers to the mprec objects */
        ptr->_freelist = (struct _Bigint **) _calloc_r(ptr, sizeof(struct _Bigint *), 16);
        if (ptr->_freelist == 0) {
            return 0;
        }
    }

    if ((rv = ptr->_freelist[k]) != 0) {
        ptr->_freelist[k] = rv->_next;
    } else {
        x = 1 << k;
        /* Allocate an mprec Bigint and stick in in the freelist */
        rv = (_Bigint *) _calloc_r(ptr, 1, sizeof(_Bigint) + (x - 1) * sizeof(rv->_x));
        if (rv == 0)
            return 0;
        rv->_k = k;
        rv->_maxwds = x;
    }
    rv->_sign = rv->_wds = 0;
    return rv;
}

CONTEXT_ONLY int hi0bits(register __ULong x) {
    register int k = 0;

    if (!(x & 0xffff0000)) {
        k = 16;
        x <<= 16;
    }
    if (!(x & 0xff000000)) {
        k += 8;
        x <<= 8;
    }
    if (!(x & 0xf0000000)) {
        k += 4;
        x <<= 4;
    }
    if (!(x & 0xc0000000)) {
        k += 2;
        x <<= 2;
    }
    if (!(x & 0x80000000)) {
        k++;
        if (!(x & 0x40000000))
            return 32;
    }
    return k;
}

CONTEXT_ONLY int lo0bits(__ULong *y) {
    register int k;
    register __ULong x = *y;

    if (x & 7) {
        if (x & 1)
            return 0;
        if (x & 2) {
            *y = x >> 1;
            return 1;
        }
        *y = x >> 2;
        return 2;
    }
    k = 0;
    if (!(x & 0xffff)) {
        k = 16;
        x >>= 16;
    }
    if (!(x & 0xff)) {
        k += 8;
        x >>= 8;
    }
    if (!(x & 0xf)) {
        k += 4;
        x >>= 4;
    }
    if (!(x & 0x3)) {
        k += 2;
        x >>= 2;
    }
    if (!(x & 1)) {
        k++;
        x >>= 1;
        if (!x & 1)
            return 32;
    }
    *y = x;
    return k;
}

_Bigint *d2b(struct _reent *ptr, double _d, int *e, int *bits) {
    union double_union d;
    _Bigint *b;
    int de, i, k;
    __ULong *x, y, z;
    d.d = _d;
#define d0 word0(d)
#define d1 word1(d)

    b = Balloc(ptr, 1);
    x = b->_x;

    z = d0 & Frac_mask;
    d0 &= 0x7fffffff; /* clear sign bit, which we ignore */
    if ((de = (int) (d0 >> Exp_shift)))
        z |= Exp_msk1;
    if (d1) {
        y = d1;
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

/* newlib qsort (libc/stdlib/qsort.c, BSD); named in session 57. */
#define min(a, b) (a) < (b) ? a : b

#define swapcode(TYPE, parmi, parmj, n) {     \
    long i = (n) / sizeof(TYPE);              \
    register TYPE *pi = (TYPE *) (parmi);     \
    register TYPE *pj = (TYPE *) (parmj);     \
    do {                                      \
        register TYPE t = *pi;                \
        *pi++ = *pj;                          \
        *pj++ = t;                            \
    } while (--i > 0);                        \
}

#define SWAPINIT(a, es) swaptype = ((char *) a - (char *) 0) % sizeof(long) || \
    es % sizeof(long) ? 2 : es == sizeof(long) ? 0 : 1;

static inline void swapfunc(char *a, char *b, int n, int swaptype) {
    if (swaptype <= 1)
        swapcode(long, a, b, n)
    else
        swapcode(char, a, b, n)
}

#define swap(a, b)                          \
    if (swaptype == 0) {                    \
        long t = *(long *) (a);             \
        *(long *) (a) = *(long *) (b);      \
        *(long *) (b) = t;                  \
    } else                                  \
        swapfunc(a, b, es, swaptype)

#define vecswap(a, b, n) if ((n) > 0) swapfunc(a, b, n, swaptype)

static inline char *med3(char *a, char *b, char *c, int (*cmp)()) {
    return cmp(a, b) < 0 ?
        (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a))
        : (cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c));
}

void qsort(void *a, size_t n, size_t es, int (*cmp)(const void *, const void *)) {
    char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
    int d, r, swaptype, swap_cnt;

loop:
    SWAPINIT(a, es);
    swap_cnt = 0;
    if (n < 7) {
        for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
            for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0; pl -= es)
                swap(pl, pl - es);
        return;
    }
    pm = (char *) a + (n / 2) * es;
    if (n > 7) {
        pl = a;
        pn = (char *) a + (n - 1) * es;
        if (n > 40) {
            d = (n / 8) * es;
            pl = med3(pl, pl + d, pl + 2 * d, cmp);
            pm = med3(pm - d, pm, pm + d, cmp);
            pn = med3(pn - 2 * d, pn - d, pn, cmp);
        }
        pm = med3(pl, pm, pn, cmp);
    }
    swap(a, pm);
    pa = pb = (char *) a + es;

    pc = pd = (char *) a + (n - 1) * es;
    for (;;) {
        while (pb <= pc && (r = cmp(pb, a)) <= 0) {
            if (r == 0) {
                swap_cnt = 1;
                swap(pa, pb);
                pa += es;
            }
            pb += es;
        }
        while (pb <= pc && (r = cmp(pc, a)) >= 0) {
            if (r == 0) {
                swap_cnt = 1;
                swap(pc, pd);
                pd -= es;
            }
            pc -= es;
        }
        if (pb > pc)
            break;
        swap(pb, pc);
        swap_cnt = 1;
        pb += es;
        pc -= es;
    }
    if (swap_cnt == 0) {
        for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
            for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0; pl -= es)
                swap(pl, pl - es);
        return;
    }

    pn = (char *) a + n * es;
    r = min(pa - (char *) a, pb - pa);
    vecswap(a, pb - r, r);
    r = min(pd - pc, pn - pd - es);
    vecswap(pb, pn - r, r);
    if ((r = pb - pa) > es)
        qsort(a, r / es, es, cmp);
    if ((r = pd - pc) > es) {
        a = pn - r;
        n = r / es;
        goto loop;
    }
}

/* ---- newlib vfprintf.c, INTEGER_ONLY + _NO_LONGLONG: _vfiprintf_r ---- */
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
extern const char D_00491B30[]; /* blanks */
extern const char D_00491B40[]; /* zeroes */
extern char D_00491B50[];       /* "0123456789abcdef" */
extern char D_00491B68[];       /* "(null)" */
extern char D_00491B70[];       /* "0123456789ABCDEF" */
extern char D_00491B88[];       /* "bug in vfprintf: bad base" */

#define __sferror(p) (((p)->_flags & __SERR) != 0)
#define cantwrite(fp) \
    ((((fp)->_flags & __SWR) == 0 || (fp)->_bf._base == 0) && __swsetup(fp))

CONTEXT_ONLY int func_002515b8(FILE *fp, register struct __suio *uio) {
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
#define __sprint func_002515b8

CONTEXT_ONLY int func_00251600(register FILE *fp, const char *fmt, va_list ap) {
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
    ret = vfiprintf(&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake))
        ret = EOF;
    if (fake._flags & __SERR)
        fp->_flags |= __SERR;
    return (ret);
}
#define __sbprintf func_00251600

#define BUF 40

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
int _vfiprintf_r(struct _reent *data, FILE *fp, const char *fmt0, va_list ap) {
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
#define blanks D_00491B30
#define zeroes D_00491B40

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
            xdigs = D_00491B50;
            flags |= HEXPREFIX;
            ch = 'x';
            goto nosign;
        case 's':
            if ((cp = va_arg(ap, char *)) == 0)
                cp = D_00491B68;
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
            xdigs = D_00491B70;
            goto hex;
        case 'x':
            xdigs = D_00491B50;
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
                    cp = D_00491B88;
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

        PRINT(cp, size);

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
