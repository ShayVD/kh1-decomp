/* gb.x func_00f38408: matched by hand. */
#include "ovl.h"

typedef struct { u64 lo, hi; } GQ;
typedef union { kh1_u128 q; s32 w[4]; GQ d; } GPkt;
typedef struct { u8 b[18]; } Idx;
extern Idx D_00F71980;
static inline void ad(GQ *q, u64 v, u64 r) {
    q->lo = v;
    q->hi = r;
}
GPkt *func_00f38408(f32 *mn, f32 *mx, u64 prim, OvlMtx m, GPkt *p) {
    OvlVec v;
    GPkt iv[8];
    Idx id;
    u8 *idx = id.b;
    GPkt *o = iv;
    GPkt *q;
    v[3] = 1.0f;
    v[0] = mn[0];
    v[1] = mn[1];
    v[2] = mn[2];
    id = D_00F71980;
    PlatVu0RotTransPers(o++, m, v, 0);
    v[0] = mx[0];
    v[2] = mn[2];
    PlatVu0RotTransPers(o++, m, v, 0);
    v[0] = mn[0];
    v[2] = mx[2];
    PlatVu0RotTransPers(o++, m, v, 0);
    v[0] = mx[0];
    v[2] = mx[2];
    PlatVu0RotTransPers(o++, m, v, 0);
    v[0] = mn[0];
    v[1] = mx[1];
    v[2] = mn[2];
    PlatVu0RotTransPers(o++, m, v, 0);
    v[0] = mx[0];
    v[2] = mn[2];
    PlatVu0RotTransPers(o++, m, v, 0);
    v[0] = mn[0];
    v[2] = mx[2];
    PlatVu0RotTransPers(o++, m, v, 0);
    v[0] = mx[0];
    v[2] = mx[2];
    PlatVu0RotTransPers(o++, m, v, 0);
    ad(&p[0].d, 0x5022400000008001, 0x4444E);
    q = &p[1];
    ad(&q[0].d, prim, 1);
    q[1].q = iv[idx[0]].q; q[1].w[3] = 16;
    q[2].q = iv[idx[1]].q; q[2].w[3] = 16;
    q[3].q = iv[idx[2]].q; q[3].w[3] = 16;
    q[4].q = iv[idx[3]].q; q[4].w[3] = 16;
    q = &p[6];
    ad(&q[0].d, 0x5022400000008001, 0x4444E);
    q = &p[7];
    ad(&q[0].d, prim, 1);
    q[1].q = iv[idx[4]].q; q[1].w[3] = 16;
    q[2].q = iv[idx[5]].q; q[2].w[3] = 16;
    q[3].q = iv[idx[6]].q; q[3].w[3] = 16;
    q[4].q = iv[idx[7]].q; q[4].w[3] = 16;
    q = &p[12];
    ad(&q[0].d, 0xB022400000008001, 0x444444444444444E);
    q = &p[13];
    ad(&q[0].d, prim, 1);
    q[1].q = iv[idx[8]].q; q[1].w[3] = 16;
    q[2].q = iv[idx[9]].q; q[2].w[3] = 16;
    q[3].q = iv[idx[10]].q; q[3].w[3] = 16;
    q[4].q = iv[idx[11]].q; q[4].w[3] = 16;
    q[5].q = iv[idx[12]].q; q[5].w[3] = 16;
    q[6].q = iv[idx[13]].q; q[6].w[3] = 16;
    q[7].q = iv[idx[14]].q; q[7].w[3] = 16;
    q[8].q = iv[idx[15]].q; q[8].w[3] = 16;
    q[9].q = iv[idx[16]].q; q[9].w[3] = 16;
    q[10].q = iv[idx[17]].q; q[10].w[3] = 16;
    return p + 24;
}
