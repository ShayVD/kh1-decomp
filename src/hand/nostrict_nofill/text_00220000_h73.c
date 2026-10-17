#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef union { u128 q; s32 i[4]; } Q4;
typedef struct { u128 q[7]; } Item7;
void func_002672f8(V4 *, void *, V4 *);
void func_002674d0(V4 *, V4 *, f32);
s32 func_00267ef0(V4 *, V4 *, V4 *);
void func_00267da0(Q4 *, void *, u128 *, s32, s32);

u128 *func_002378c8(Item7 *src, u128 *dst, void *m) {
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
