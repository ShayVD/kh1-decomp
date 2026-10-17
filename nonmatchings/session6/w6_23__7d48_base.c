#include "common.h"
typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef union { u128 q; s32 i[4]; } Q4;
typedef struct { u128 q[7]; } Item7;
void func_002672f8(V4 *, void *, V4 *);
void func_002674d0(V4 *, V4 *, f32);
s32 func_00267ef0(V4 *, V4 *, V4 *);
void func_00267da0(Q4 *, void *, u128 *, s32, s32);

typedef struct { s32 x, y, z, w; } __attribute__((aligned(16))) I4b;
typedef struct { u128 tag; V4 v[3]; s32 n; s32 pad[3]; V4 nrm[4][3]; u128 col[4]; V4 uv[4][3]; } ObjB;
s32 func_00237548(V4 *, V4 *, V4 *, void *);
f32 func_00237a48(I4b *, void *, V4 *, s32);

void func_00267560(V4 *, void *, f32);
void func_002675f0(V4 *, void *);

typedef struct { u64 a, b; } U64x2;
typedef struct { u128 tag; V4 v[3]; V4 nrm[3]; U64x2 col; V4 uv[3]; } ObjC;

u128 *func_00237d48(ObjC *o, u128 *dst, void *m) {
    I4b iv;
    V4 t1, t2;
    u128 *h, *d;
    V4 *pv, *pu, *pn;
    s32 i;
    if (func_00237548(&o->v[0], &o->v[1], &o->v[2], m)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[0] = 0xA02DC00000008001ULL;
    ((u64 *)h)[1] = 0x512512512EULL;
    { U64x2 *c = (U64x2 *)&dst[2]; *c = o->col; }
    pv = o->v;
    pn = o->nrm;
    pu = o->uv;
    d = dst + 3;
    for (i = 2; i >= 0; i--) {
        func_00267560(&t1, pu++, func_00237a48(&iv, m, pv++, 1));
        func_002675f0(&t2, pn); pn++;
        *d++ = *(u128 *)&t1;
        *d++ = *(u128 *)&t2;
        *d++ = *(u128 *)&iv;
    }
    dst[0] = 0;
    *(s32 *)dst = 0x1000000B;
    return dst + 12;
}
