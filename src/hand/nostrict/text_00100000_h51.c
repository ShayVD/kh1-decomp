#include "common.h"

typedef struct { u8 pad0[4]; u16 dx; u16 dy; u8 pad8[8]; u64 bitblt; s32 w; u8 pad28[4]; u16 sx; u16 sy; } CopyRect;

void func_00101a70(CopyRect *r, s32 y, s32 h, u64 *pk) {
    s32 m1 = y % h;
    s32 m2 = (h - y) % h;

    pk[2] = (u64)r->sx | (u64)(r->sy + m1) << 16 | (u64)r->dx << 32 | (u64)r->dy << 48;
    pk[4] = r->w | (u64)m2 << 32;
    pk[0] = r->bitblt;
    pk[1] = 0x50;
    pk[3] = 0x51;
    pk[5] = 0x52;
    pk[6] = 2;
    pk[7] = 0x53;
    if (y != 0) {
        pk[10] = (u64)r->sx | (u64)r->sy << 16 | (u64)r->dx << 32 | (u64)(r->dy + m2) << 48;
        pk[12] = r->w | (u64)y << 32;
    } else {
        pk[10] = (u64)r->sx | (u64)(r->sy + m1) << 16 | (u64)r->dx << 32 | (u64)r->dy << 48;
        pk[12] = r->w | (u64)m2 << 32;
    }
    pk[8] = r->bitblt;
    pk[9] = 0x50;
    pk[11] = 0x51;
    pk[13] = 0x52;
    pk[14] = 2;
    pk[15] = 0x53;
}

extern s32 D_002A61F8;
extern s32 D_002A61FC;
extern u64 D_002A5430[];
extern u64 D_002A52B0[];
extern u64 D_002A5620[];
extern u64 D_002A5A90[];
extern u64 D_002A5AC0[];
void func_00106b18(void *);

#define XYZ(x, y, z) ((u64)(x) | ((u64)(y) << 16) | ((u64)(z) << 32))

s32 func_00103058(void) {
    s32 z = D_002A61FC;
    D_002A5430[5] = XYZ(0x6fe0, 0x73e0, z);
    D_002A5430[7] = XYZ(0x8fe0, 0x8be0, z);
    D_002A5430[11] = XYZ(0x6fc0, 0x73c0, z);
    D_002A5430[13] = XYZ(0x8fc0, 0x8bc0, z);
    D_002A5430[17] = XYZ(0x7000, 0x7400, z);
    D_002A5430[19] = XYZ(0x9000, 0x8c00, z);
    D_002A5430[23] = XYZ(0x6fc0, 0x7400, z);
    D_002A5430[25] = XYZ(0x8fc0, 0x8c00, z);
    D_002A5430[29] = XYZ(0x7000, 0x73c0, z);
    D_002A5430[31] = XYZ(0x9000, 0x8bc0, z);
    D_002A5430[35] = XYZ(0x6fe0, 0x73c0, z);
    D_002A5430[37] = XYZ(0x8fe0, 0x8bc0, z);
    D_002A5430[41] = XYZ(0x6fc0, 0x73e0, z);
    D_002A5430[43] = XYZ(0x8fc0, 0x8be0, z);
    D_002A5430[47] = XYZ(0x6fe0, 0x7400, z);
    D_002A5430[49] = XYZ(0x8fe0, 0x8c00, z);
    D_002A5430[53] = XYZ(0x7000, 0x73e0, z);
    D_002A5430[55] = XYZ(0x9000, 0x8be0, z);
    if (D_002A61F8 != 0) {
        D_002A52B0[4] = XYZ(0x7000, 0x7400, z);
        D_002A52B0[5] = XYZ(0x9000, 0x8c00, z);
        func_00106b18(D_002A5620);
        func_00106b18(D_002A5AC0);
    } else {
        func_00106b18(D_002A5A90);
        func_00106b18(D_002A5AC0);
    }
    return 4;
}

#include "data/types/nostrict_text_00100000_h51.h"
typedef struct { f32 x, y, z; } Vec3;
#include "data/types/nostrict_text_00100000_h51_p2.h"
#include "data/pieces/D_002A6234.h"
#include "data/pieces/D_002A6308.h"
#include "data/pieces/D_002A6318.h"
#include "data/pieces/D_002A6324.h"
void func_00104850(Vec3 *, IVec3 *);

s32 func_00104940(Vec3 *v, s32 *out) {
    IVec3 hi;
    IVec3 lo;
    s32 i, j, n;

    func_00104850(&v[0], &lo);
    func_00104850(&v[1], &hi);
    if (D_002A6324 == ((Grid *)D_002A6234) && D_002A6308.x == hi.x && D_002A6308.z == hi.z
        && D_002A6318.x == lo.x && D_002A6318.z == lo.z) {
        return -1;
    }
    n = 0;
    for (i = lo.x; i < hi.x + 1; i++) {
        for (j = lo.z; j < hi.z + 1; j++) {
            *out++ = i * ((Grid *)D_002A6234)->nz + j;
            n++;
        }
    }
/*P*/
    D_002A6308.x = hi.x;
    D_002A6308.z = hi.z;
    D_002A6318.x = lo.x;
    D_002A6318.z = lo.z;
    D_002A6324 = ((Grid *)D_002A6234);
/*Q*/
    return n;
}

typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { s16 a, b, c, d; u8 pad8[12]; } Ent20;
extern Ent20 *D_002A6238;
extern Vec3 *D_002A624C;

s32 func_00104c38(s32 idx, Vec4 *out) {
    s32 a = D_002A6238[idx].a, b = D_002A6238[idx].b, c = D_002A6238[idx].c, d = D_002A6238[idx].d;

    switch (d) {
    case -1:
            out[0].x = D_002A624C[a].x;
            out[0].y = D_002A624C[a].y;
            out[0].z = D_002A624C[a].z;
            out[0].w = 1.0f;
            out[1].x = D_002A624C[b].x;
            out[1].y = D_002A624C[b].y;
            out[1].z = D_002A624C[b].z;
            out[1].w = 1.0f;
            out[2].x = D_002A624C[c].x;
            out[2].y = D_002A624C[c].y;
            out[2].z = D_002A624C[c].z;
            out[2].w = 1.0f;
            return 3;
    case -2:
            out[0].x = D_002A624C[c].x;
            out[0].y = D_002A624C[c].y;
            out[0].z = D_002A624C[c].z;
            out[0].w = 1.0f;
            out[1].x = D_002A624C[b].x;
            out[1].y = D_002A624C[b].y;
            out[1].z = D_002A624C[b].z;
            out[1].w = 1.0f;
            out[2].x = D_002A624C[a].x;
            out[2].y = D_002A624C[a].y;
            out[2].z = D_002A624C[a].z;
            out[2].w = 1.0f;
            return 3;
    default:
        out[0].x = D_002A624C[a].x;
        out[0].y = D_002A624C[a].y;
        out[0].z = D_002A624C[a].z;
        out[0].w = 1.0f;
        out[1].x = D_002A624C[b].x;
        out[1].y = D_002A624C[b].y;
        out[1].z = D_002A624C[b].z;
        out[1].w = 1.0f;
        out[2].x = D_002A624C[c].x;
        out[2].y = D_002A624C[c].y;
        out[2].z = D_002A624C[c].z;
        out[2].w = 1.0f;
        out[3].x = D_002A624C[d].x;
        out[3].y = D_002A624C[d].y;
        out[3].z = D_002A624C[d].z;
        out[3].w = 1.0f;
        return 4;
    }
}

#include "data/types/nostrict_text_00100000_h51_p.h"
extern s32 D_002A6230;
#include "data/pieces/D_002A6274.h"
extern s32 D_002A6294;
extern u16 D_002A62F8[];
void func_0011d270(s32, s32, s32, s32);
void func_00104f10(s32, Vec4 *);
void func_00104eb0(s32, Vec4 *);
f32 func_00267390(Vec4 *, Vec4 *);

void func_001050d0(void) {
    Vec4 b;
    Vec4 a;
    s32 i;

    D_002A6230 = 0;
    for (i = 0; i < D_002A6294; i++) {
        Tri20 *t = &D_002A6274[i];
        if (t->b16.f25 == 1) {
            func_0011d270(t->u12.i, D_002A6230, i, 0);
            D_002A62F8[D_002A6230++] = D_002A6274[i].u12.h;
            func_00104f10(i, &a);
            func_00104eb0(i, &b);
            {f32 r = func_00267390(&a, &b);
            Tri20 *e = D_002A6274;
            e[i].u12.f = -r;
            e[i].b16.f25 = 0;}
        }
    }
}
#include "data/data_002A.h"
