/* 00237b30: 24 words off by LCS (was 63/44), mode hand/nostrict_nofill, func_002378c8 CONTEXT_ONLY at top. Off: header sq zero scheduled later (orig zeroes dst[1] before move s1,sp), and register choice s3/s4 swapped (orig: a2 m in s4, loop counters in s3, dst-giv in s4) plus first-loop reg permutation. Key shape: dst[k++] three stores per inner iteration (k biv), block-local i in first loop. */
#include "common.h"
typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef union { u128 q; s32 i[4]; } Q4;
typedef struct { u128 q[7]; } Item7;
void func_002672f8(V4 *, void *, V4 *);
void func_002674d0(V4 *, V4 *, f32);
s32 func_00267ef0(V4 *, V4 *, V4 *);
void func_00267da0(Q4 *, void *, u128 *, s32, s32);

CONTEXT_ONLY u128 *func_002378c8(Item7 *src, u128 *dst, void *m) {
    Q4 out[3];
    V4 a, b, c;
    u128 *h;
    func_002672f8(&a, m, (V4 *)&src->q[1]);
    func_002672f8(&b, m, (V4 *)&src->q[2]);
    func_002672f8(&c, m, (V4 *)&src->q[3]);
    func_002674d0(&a, &a, a.w);
    func_002674d0(&b, &b, b.w);
    func_002674d0(&c, &c, c.w);
    if (func_00267ef0(&a, &b, &c)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[0] = 0x6025C00000008001;
    ((u64 *)h)[1] = 0x414141;
    func_00267da0(out, m, &src->q[1], 3, 0);
    out[0].i[3] = 0;
    dst[2] = src->q[4];
    out[1].i[3] = 0;
    dst[3] = out[0].q;
    dst[4] = src->q[5];
    dst[5] = out[1].q;
    out[2].i[3] = 0;
    dst[6] = src->q[6];
    dst[0] = 0;
    dst[7] = out[2].q;
    *(s32 *)dst = 0x10000007;
    return dst + 8;
}
typedef struct { s32 x, y, z, w; } __attribute__((aligned(16))) I4b;
typedef struct { u128 tag; V4 v[3]; s32 n; s32 pad[3]; V4 nrm[4][3]; u128 col[4]; V4 uv[4][3]; } ObjB;
s32 func_00237548(void *, void *, void *, void *);
f32 func_00237a48(I4b *, void *, void *, s32);
void func_00267560(V4 *, void *, f32);
void func_002675f0(V4 *, void *);

u128 *func_00237b30(ObjB *o, u128 *dst, void *m) {
    I4b iv[3];
    f32 f[3];
    V4 t1, t2;
    u128 *h, *d;
    s32 i, j, k;
    if (func_00237548(&o->v[0], &o->v[1], &o->v[2], m)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[1] = 0x512512512EULL;
    ((u64 *)h)[0] = ((u64)(o->n * 3 | 0x58) << 47) | 0xA000400000008001ULL;
    k = 2;
    {
        s32 i;
        f32 *pf = f;
        I4b *pv = iv;
        V4 *ps = o->v;
        for (i = 0; i < 3; i++) {
            *pf++ = func_00237a48(pv++, m, ps++, 1);
        }
    }
    for (j = 0; j < o->n; j++) {
        V4 *pn = o->nrm[j];
        f32 *pf;
        V4 *pu;
        I4b *pi;
        dst[k++] = o->col[j];
        pu = o->uv[j];
        pi = iv;
        pf = f;
        for (i = 0; i < 3; i++) {
            func_00267560(&t1, pu, *pf);
            func_002675f0(&t2, pn);
            pf++; pu++;
            dst[k++] = *(u128 *)&t1;
            dst[k++] = *(u128 *)&t2;
            dst[k++] = *(u128 *)pi;
            pi++;
        }
    }
    return dst + k;
}
