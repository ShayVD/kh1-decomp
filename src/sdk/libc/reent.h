/* newlib's struct _reent and FILE, as SLPS_251.98's libc was built with
 * them (offsets checked against the code: docs/sdk.md). _impure_ptr is
 * D_0046A9C8. sdk segment. */
#ifndef KH1_SDK_REENT_H
#define KH1_SDK_REENT_H

typedef unsigned int size_t;
typedef long _fpos_t;
typedef int (*__cmp_fn)(const void *, const void *);

struct __sbuf {
    unsigned char *_base;
    int _size;
};

struct _reent;

typedef struct __sFILE {
    unsigned char *_p; /* 0x00 current position in (some) buffer */
    int _r;            /* 0x04 read space left for getc() */
    int _w;            /* 0x08 write space left for putc() */
    short _flags;      /* 0x0C */
    short _file;       /* 0x0E */
    struct __sbuf _bf; /* 0x10 the buffer */
    int _lbfsize;      /* 0x18 0 or -_bf._size, for inline putc */

    void *_cookie; /* 0x1C */
    int (*_read)(void *, char *, int);
    int (*_write)(void *, const char *, int);
    _fpos_t (*_seek)(void *, _fpos_t, int);
    int (*_close)(void *);

    struct __sbuf _ub; /* 0x30 ungetc buffer */
    unsigned char *_up;
    int _ur;

    unsigned char _ubuf[3]; /* 0x40 */
    unsigned char _nbuf[1];

    struct __sbuf _lb; /* 0x44 */

    int _blksize;    /* 0x4C */
    int _offset;     /* 0x50 */
    struct _reent *_data; /* 0x54 */
} FILE;

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SEOF 0x0020
#define __SERR 0x0040
#define __SMBF 0x0080
#define __SAPP 0x0100
#define __SSTR 0x0200

struct _glue {
    struct _glue *_next;
    int _niobs;
    FILE *_iobs;
};

struct _atexit {
    struct _atexit *_next;
    int _ind;
    void (*_fns[32])(void);
};

struct _reent {
    int _errno;                         /* 0x000 */
    FILE *_stdin, *_stdout, *_stderr;   /* 0x004 */
    int _inc;                           /* 0x010 */
    char _emergency[25];                /* 0x014 */
    int _current_category;              /* 0x030 */
    const char *_current_locale;        /* 0x034 */
    int __sdidinit;                     /* 0x038 */
    void (*__cleanup)(struct _reent *); /* 0x03C */
    /* used by mprec routines */
    struct _Bigint *_result;            /* 0x040 */
    int _result_k;                      /* 0x044 */
    struct _Bigint *_p5s;               /* 0x048 */
    struct _Bigint **_freelist;         /* 0x04C */
    /* used by some fp conversion routines */
    int _cvtlen;                        /* 0x050 */
    char *_cvtbuf;                      /* 0x054 */
    char _pad058[0xA8 - 0x58];          /* _new up to _rand_next */
    unsigned long long _rand_next;      /* 0x0A8 */
    char _pad0b0[0x148 - 0xB0];
    struct _atexit *_atexit;            /* 0x148 */
    struct _atexit _atexit0;            /* 0x14C */
    void (**_sig_func)(int);            /* 0x1D4 */
    struct _glue __sglue;               /* 0x1D8 */
    FILE __sf[3];                       /* 0x1E4 */
};

extern struct _reent *D_0046A9C8;
#define _impure_ptr D_0046A9C8
#define _REENT _impure_ptr

#define _stdout_r(x) ((x)->_stdout)

/* local.h (this newlib's version sets _data first). */
#define CHECK_INIT(fp)                          \
    do {                                        \
        if ((fp)->_data == 0)                   \
            (fp)->_data = _REENT;               \
        if (!(fp)->_data->__sdidinit)           \
            __sinit((fp)->_data);               \
    } while (0)

#include "stdarg.h"

#define INT_MAX 2147483647
#define EOF (-1)

void _exit(int) __attribute__((noreturn));
void abort(void);
int vfprintf(FILE *, const char *, va_list);
int _vfprintf_r(struct _reent *, FILE *, const char *, va_list);
int vfiprintf(FILE *, const char *, va_list);
int _vfiprintf_r(struct _reent *, FILE *, const char *, va_list);
int fiprintf(FILE *, const char *, ...);
int _fwalk(struct _reent *, int (*)(FILE *));
int fflush(FILE *);
void __sinit(struct _reent *);
size_t strlen(const char *);
void *memset(void *, int, size_t);

#endif /* KH1_SDK_REENT_H */
