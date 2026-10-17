/* newlib libc/stdlib/mprec.h, IEEE_8087 (little endian), Pack_32, no
 * Sudden_Underflow. sdk segment. */
#ifndef KH1_SDK_MPREC_H
#define KH1_SDK_MPREC_H
#include "reent.h"

typedef int __Long;
typedef unsigned int __ULong;
typedef unsigned int __uint32_t;

union double_union {
    double d;
    __uint32_t i[2];
};

#define word0(x) (x.i[1])
#define word1(x) (x.i[0])

#define Storeinc(a, b, c) (((unsigned short *) a)[1] = (unsigned short) b, \
                           ((unsigned short *) a)[0] = (unsigned short) c, a++)

#define Exp_shift 20
#define Exp_shift1 20
#define Exp_msk1 0x100000
#define Exp_msk11 0x100000
#define Exp_mask 0x7ff00000
#define P 53
#define Bias 1023
#define IEEE_Arith
#define Emin (-1022)
#define Exp_1 0x3ff00000
#define Exp_11 0x3ff00000
#define Ebits 11
#define Frac_mask 0xfffff
#define Frac_mask1 0xfffff
#define Ten_pmax 22
#define Bletch 0x10
#define Bndry_mask 0xfffff
#define Bndry_mask1 0xfffff
#define LSB 1
#define Sign_bit 0x80000000
#define Log2P 1
#define Tiny0 0
#define Tiny1 1
#define Quick_max 14
#define Int_max 14
#define Infinite(x) (word0(x) == 0x7ff00000)

#define Big0 (Frac_mask1 | Exp_msk1 * (DBL_MAX_EXP + Bias - 1))
#define Big1 0xffffffff

#define Sign_Extend(a, b) /* no-op */

typedef struct _Bigint _Bigint;
struct _Bigint {
    struct _Bigint *_next;
    int _k, _maxwds, _sign, _wds;
    __ULong _x[1];
};

void *memcpy(void *, const void *, size_t);
void *_calloc_r(struct _reent *, size_t, size_t);

#define Bcopy(x, y) memcpy((char *) &x->_sign, (char *) &y->_sign, y->_wds * sizeof(__Long) + 2 * sizeof(int))

_Bigint *Balloc(struct _reent *p, int k);
void Bfree(struct _reent *p, _Bigint *v);
_Bigint *multadd(struct _reent *p, _Bigint *, int, int);
_Bigint *s2b(struct _reent *, const char *, int, int, __ULong);
_Bigint *i2b(struct _reent *, int);
_Bigint *mult(struct _reent *, _Bigint *, _Bigint *);
_Bigint *pow5mult(struct _reent *, _Bigint *, int k);
int hi0bits(__ULong);
int lo0bits(__ULong *);
_Bigint *d2b(struct _reent *p, double d, int *e, int *bits);
_Bigint *lshift(struct _reent *p, _Bigint *b, int k);
_Bigint *diff(struct _reent *p, _Bigint *a, _Bigint *b);
int cmp(_Bigint *a, _Bigint *b);
double ulp(double x);
double b2d(_Bigint *a, int *e);
double ratio(_Bigint *a, _Bigint *b);
double _mprec_log10(int);

/* mprec.c's tens[] table: each .c that uses it declares the D_ symbol
 * itself (the build only scans .c files for addresses). */
#define tens D_00491FE0

#endif /* KH1_SDK_MPREC_H */
