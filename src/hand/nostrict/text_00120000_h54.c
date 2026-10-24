#include "common.h"
#include "data/bss_004F.h"
#include "data/bss_0052.h"
typedef struct {
    s32 f0; s32 f4; s32 f8;
    s8 c[4]; s8 d[4];
    s32 f14;
    s8 e[4]; s8 f[4];
    s32 f20; s32 f24; s32 f28; s32 f2c; s32 f30; s32 f34;
    u64 f38; u64 f40;
} Pkt;
#include "data/pieces/D_002BC0F0.h"
typedef Cam_2BC0F0 Cam;
extern s32 D_004F82C0;
extern s32 D_004F82C4;
typedef struct { s32 f4; s32 f0; } L14c;
typedef struct { u32 f0; u8 pad[0x114]; f32 f118; u8 p2[0x14c-0x11c]; s32 *f14c; u8 p3[0x15c-0x150]; s32 f15c; u8 p4[0x390-0x160]; s32 f390; } E1;
extern f32 func_00135ca0(f32);
extern void func_001621e0(s32, s32, Pkt *, E1 *);
void func_00127960(E1 *e, s32 a1, s32 a2) {
    Pkt p;
    s32 i;
    s32 *q;
    u64 k;
    if (e->f0 & 0x100) {
        p.c[0] = 0x80;
        p.c[1] = 0x80;
        p.c[2] = 0x80;
        p.c[3] = 0x80;
        p.f0 = 0x101;
        p.d[0] = D_002BC0F0.cam.f10;
        p.d[1] = D_002BC0F0.cam.f14;
        p.d[2] = D_002BC0F0.cam.f18;
        p.d[3] = func_00135ca0(e->f118);
    } else {
        p.f0 = 0x101;
        p.c[3] = a2;
        p.c[0] = 0; p.c[1] = 0; p.c[2] = 0;
        p.d[0] = 0x80; p.d[1] = 0x80;
        p.d[2] = 0x80;
        p.d[3] = 0xff;
    }
    p.f4 = 0;
    q = &D_004F82C0;
    p.f8 = D_004F82C4 + *q;
    *q += 10;
    p.f20 = 0;
    p.f28 = e->f390;
    if (e->f390 & 0x40000000) p.f28 = -1;
    p.f2c = 0;
    if (e->f14c && e->f14c[0] && (e->f0 & 0x4000)) {
        p.f14 = e->f14c[1];
        for (i = 0; i < 4; i++) {
            p.e[i] = p.c[i];
            p.f[i] = p.d[i];
        }
    } else {
        p.f14 = 0;
    }
    k = 0x1000401d0LL;
    p.f38 = 0x3a0001c0;
    p.f40 = k;
    p.f30 = 0;
    p.f34 = 0;
    func_001621e0(e->f15c, a1, &p, e);
}
#include "data/pieces/D_002C58A0.h"
typedef FVec4 V4;
typedef struct { V4 a; V4 b; V4 c; s16 f30; s16 pad32; s32 f34; } Ray2;
#include "data/pieces/D_002C5C80.h"
typedef Lt64_2c5c80 Lt2;
typedef union { u64 x; struct { u32 lo:24; u32 b3:8; u32 b4:8; u32 k:2; u32 hi:22; } b; } F370;
typedef struct { u8 pad[0x50]; V4 pos; u8 p60[0x2c4-0x60]; f32 f2c4; u8 p2c8[4]; s32 f2cc; u8 p2d0[0x320-0x2d0]; V4 v320; u8 p330[0x370-0x330]; F370 f370; } E2;
extern s32 func_001232f0(E2 *);
extern void func_002675a8(V4 *, V4 *);
extern void func_00267530(V4 *, V4 *, V4 *);
extern void func_00121fc4(V4 *, V4 *);
extern void func_00118668(Ray2 *);
extern void func_00127c20(E2 *, V4 *, f32);
void func_00128218(E2 *e, f32 k) {
    V4 v;
    Ray2 r;
    Lt2 *l;
    s32 i;
    if (e->f370.b.k == 3) return;
    if (!func_001232f0(e)) {
        func_002675a8(&r.a, &e->pos);
        r.b.w = r.a.w = 1.0f;
        r.b.x = 0;
        r.b.z = 0;
        r.a.y -= e->f2c4;
        r.b.y = e->f2c4 + 300.0f;
        func_00118668(&r);
        if (r.f30 < 0) return;
        func_002675a8(&e->v320, &r.c);
        e->f2cc = r.f34;
    }
    k *= e->f370.b.b3 * 0.0078125f;
    l = &D_002C5C80;
    for (i = 0; i < 31; i++, l++) {
        if (!(l->flags & 4)) continue;
        switch (l->kind) {
        case 2:
            func_002675a8(&v, &l->dir);
            v.w = 1.0f;
            func_00127c20(e, &v, k);
            break;
        case 3:
        case 5:
            func_002675a8(&v, &e->pos);
            v.y -= e->f2c4;
            func_00267530(&v, &v, &l->pos);
            func_00121fc4(&v, &v);
            if (v.w < l->radius && v.y > 0.5f) {
                v.w = 1.0f;
                func_00127c20(e, &v, k);
            }
            break;
        }
    }
}

#include "data/types/nostrict_text_00120000_h54.h"
static inline s32 min54(s32 a, s32 b) { return a < b ? a : b; }
static inline s32 max54(s32 a, s32 b) { return a > b ? a : b; }
extern f32 func_00135ca0(f32);
extern void func_00128218(E2 *, f32);

/* needs make: uses rodata */
s32 D_00525358 ALIGNED(8);
#include "data/types/nostrict_text_00120000_h54_p.h"
s32 D_00525294 ALIGNED(4);
#include "data/data_0029.h"
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/data_002E.h"
