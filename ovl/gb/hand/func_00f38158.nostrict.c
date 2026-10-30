/* gb.x func_00f38158: matched by hand. */
#include "ovl.h"

typedef struct { u8 e[24]; } BoxEdges;
typedef struct { u8 f[18]; } BoxFaces;
typedef union { kh1_u128 q; s32 w[4]; } IVec;
extern BoxEdges D_00F71950;
extern BoxFaces D_00F71968;
u64 *func_00f38158(f32 *mn, f32 *mx, u64 tag, OvlMtx m, u64 *p) {
    OvlVec v;
    IVec out[8];
    BoxEdges e = D_00F71950;
    BoxFaces f = D_00F71968;
    s32 i;
    u64 *pk;
    IVec *o = out;
    v[3] = 1.0f;
    v[0] = mn[0];
    v[1] = mn[1];
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
    p[0] = 0x3060C0000000800C;
    p[1] = 0x44E;
    pk = p + 2;
    for (i = 0; i < 24; i += 2) {
        IVec *q = (IVec *)pk;
        pk[0] = tag;
        q[1].q = out[e.e[i]].q;
        q[2].q = out[e.e[i + 1]].q;
        pk[1] = 1;
        q[1].w[3] = 16;
        q[2].w[3] = 16;
        pk += 6;
    }
    return pk;
}
