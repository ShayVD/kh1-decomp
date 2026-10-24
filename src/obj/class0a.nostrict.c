/* Object classes 9, 0xA and 0xB: the handlers func_00141138 registers in the
 * class table D_00350D88 (func_0014f830(9 / 0xA / 0xB, ...)) that lie in
 * 0x00140000-0x00141200, and their helpers (class 9's and 0xA's first two
 * handlers, 0x0013fd10-0x0013fd60, are in src/obj/class09.c
 * with the helpers these handlers call). Flag mode:
 * nostrict (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0037A378.h"
#include "vm/script_vm.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0053.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_003044E0.h"

/* func_00140070 (from hand/nostrict/text_00130000_h55.c). */
typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct Actor_40070 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob;
void func_00105a30(s32 a, s32 id, f32 *v);
void func_00105ad0(s32 a, s32 id, f32 *v);
s32 func_0015bcb8(W55Ob *o, f32 *r);
s32 func_0013ff00(W55Ob *o, f32 *seg, f32 *v, f32 *r);
#define W55MIN(a, b) ((a) < (b) ? (a) : (b))
s32 func_00140070(W55Ob *o, f32 *dir, f32 *r) {
    f32 pts[4][4];
    f32 v[4], d[4];
    f32 h;
    if (o->x2de == 0xffff) return 0;
    func_00105a30(-1, o->x2de, v);
    PlatVu0CopyVector(d, dir);
    d[1] = 0.0f;
    PlatVu0Normalize(d, d);
    if (PlatVu0InnerProduct(v, d) > -0.7f) return 0;
    func_00105ad0(-1, o->x2de, pts[0]);
    h = o->pos[1] - o->x2c4;
    if (h < W55MIN(pts[0][1], W55MIN(pts[1][1], pts[2][1]))) return 0;
    if (!func_0013ff00(o, pts[0], v, r)) return 0;
    if (func_0015bcb8(o, r)) return 0;
    PlatVu0CopyVector(o->x148, v);
    return 1;
}
#undef W55MIN

/* func_001401d8 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_401d8 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob_401d8;
void func_00130398(void *o, s32 a, f32 f);
void *func_00130578(void *, s32, f32);
s32 func_001375f0(W55Ob_401d8 *o);
s32 func_0014f658(void *, s32);
f32 fmodf(f32 x, f32 y);
f32 atan2f(f32 y, f32 x);
#define func_0015bcb8 ((s32 (*)(W55Ob_401d8 *o, f32 *r)) func_0015bcb8)
/* uses rodata. func_001401d8 only matches with func_0013fe28 defined above it. */
/* CONTEXT_ONLY copy of func_0013fe28 (defined in class09.nostrict.c). */
f32 func_0013fe10();
CONTEXT_ONLY s32 func_0013fe28(W55Ob_401d8 *o) {
    f32 t = func_0013fe10(o);
    s32 r = 0;
    if (t < 0.015f || t > 0.985f) r = 1;
    return r;
}
s32 func_001401d8(W55Ob_401d8 *o, f32 *d) {
    f32 r[4];
    f32 m;
    s32 k;
    if (!func_001375f0(o) || d[3] == 0.0f) return 0;
    k = func_00140070(o, d, r);
    if (k == 1) {
        if (!func_0013fe28(o)) {
            m = fmodf(o->pos[1] + 10.0f, 66.66666412353516f);
            if (m < 0.0f) m += 66.66666412353516f;
            r[1] = r[1] + 10.0f - m;
        }
        if (func_0015bcb8(o, r)) return 0;
        PlatVu0CopyVector(o->pos, r);
        PlatVu0CopyVector(o->x148 + 8, r);
        func_0014f658(o, 10);
        func_00130398(o, 0x1000013, 4.0f);
        func_00130578(o, 0x40000011, 0.0f);
        PlatVu0ScaleVector(d, o->x148, -1.0f);
        d[3] = 0.0f;
        o->x150 = atan2f(-o->x148[0], -o->x148[2]);
        o->x148[5] = o->pos[1];
    }
    return k;
}
#undef func_0015bcb8

/* func_00140370 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_40370 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob_40370;
#define func_0015bcb8 ((s32 (*)(W55Ob_40370 *o, f32 *r)) func_0015bcb8)
s32 func_00140370(W55Ob_40370 *o, f32 *d) {
    f32 r[4];
    f32 m;
    s32 k;
    k = func_00140070(o, d, r);
    if (k == 1) {
        if (o->x30c != 0xffff) return 0;
        m = fmodf(o->pos[1], 66.66666412353516f);
        if (m < 0.0f) m += 66.66666412353516f;
        if (m < 10.0f) r[1] -= m;
        else if (m > 56.66666412353516f) r[1] += 66.66666412353516f - m;
        else return 0;
        if (func_0015bcb8(o, r)) return 0;
        func_0014f658(o, 10);
        func_00130398(o, 0x1000014, 0.0f);
        func_00130578(o, 0x40000011, 0.0f);
        PlatVu0CopyVector(o->pos, r);
        PlatVu0ScaleVector(d, o->x148, -1.0f);
        d[3] = 0.0f;
        o->x20[3] = 0.0f;
        o->x150 = atan2f(-o->x148[0], -o->x148[2]);
    }
    return k;
}
#undef func_0015bcb8

/* func_001404d8 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_404d8 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob_404d8;
f32 func_0013fd88(f32 y);
#define W55MAX2(a, b) ((a) > (b) ? (a) : (b))
#define func_001375f0 ((s32 (*)(W55Ob_404d8 *o)) func_001375f0)
#define func_0015bcb8 ((s32 (*)(W55Ob_404d8 *o, f32 *r)) func_0015bcb8)
s32 func_001404d8(W55Ob_404d8 *o, f32 *d) {
    f32 pts[4][4];
    f32 v[4], r[4];
    f32 t;
    if (o->x30c == 0xffff || !func_001375f0(o)) goto fail;
    func_00105a30(-1, o->x30c, v);
    if (PlatVu0InnerProduct(v, d) < -0.7f) return 0;
    func_00105ad0(-1, o->x30c, pts[0]);
    if (!func_0013ff00(o, pts[0], v, r)) return 0;
    r[1] = W55MAX2(W55MAX2(pts[0][1], pts[1][1]), pts[2][1]) + o->x2c4;
    t = func_0013fd88(r[1]);
    if (t > 0.015f && t < 0.985f) r[1] += (1.0f - t) * 66.66666412353516f;
    if (func_0015bcb8(o, r)) {
    fail:
        return 0;
    }
    PlatVu0CopyVector(o->x148 + 4, o->pos);
    PlatVu0CopyVector(o->x148 + 8, r);
    o->x148[12] = 0.0f;
    PlatVu0CopyVector(o->x148, v);
    func_0014f658(o, 9);
    func_00130398(o, 0x1010012, 0.0f);
    PlatVu0CopyVector(d, o->x148);
    d[3] = 0.0f;
    return 1;
}
#undef func_001375f0
#undef func_0015bcb8
#undef W55MAX2

/* func_001406d0 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_406d0 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob_406d0;
extern f32 D_002BBDFC;
void func_00121fc4(f32 *d, f32 *s);
f32 func_00131a68(W55Ob_406d0 *o, s32 a);
f32 sinf(f32 x);
void func_001406d0(W55Ob_406d0 *o, f32 *d) {
    f32 t;
    o->x148[12] += D_002BBDFC;
    t = o->x148[12] / func_00131a68(o, 18);
    if (t >= 1.0f) {
        func_0014f658(o, 10);
        func_00130398(o, 20, 0.0f);
        func_00130578(o, 0x40000011, 0.0f);
        PlatVu0CopyVector(o->pos, o->x148 + 8);
        o->x20[1] = 0.0f;
        o->x20[3] = 0.0f;
        return;
    }
    PlatVu0InterVector(d, o->x148 + 8, o->x148 + 4, t);
    d[1] -= sinf(t * 3.1415928f) * 50.0f;
    PlatVu0SubVector(d, d, o->pos);
    func_00121fc4(o->x20, d);
    o->x20[3] /= D_002BBDFC;
    o->x150 = atan2f(-o->x148[0], -o->x148[2]);
}

/* func_00140838 (from hand/nostrict/text_00140000_s7_w26.c). */
typedef FVec4 V4f;
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; u8 pad60[0x40]; V4f va0; f32 fb0; f32 fb4; f32 fb8; f32 fbc; } Sub148;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x148 - 0x8C];
    Sub148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
    u8 pad316[0x3C4 - 0x316];
    f32 f3c4;
} ObjF3;
f32 func_0013fe80(f32);
s32 func_001186a8(V4f *);
#define func_0015bcb8 ((s32 (*)(ObjF3 *, V4f *)) func_0015bcb8)
/* func_00140838: the failure tail (flag set + return 0) written once per failing test; jump2 cross-jumps the copies into one block but the register choice follows the per-path copies. */
s32 func_00140838(ObjF3 *o, V4f *v) {
    V4f t;
    s32 r;
    PlatVu0CopyVector(&o->v2a0, &o->pos);
    o->v2a0.y = func_0013fe80(o->pos.y);
    o->v2a0.w = 1.0f;
    PlatVu0CopyVector(&o->v2b0, &D_002C58A0);
    if (v->y < 0.0f) {
        r = 1;
        o->v2a0.y -= 66.66666412353516f;
    } else {
        r = 2;
        o->v2a0.y += 66.66666412353516f;
    }
    if (func_001186a8(&o->v2a0) == 0xFFFF) {
        o->p148->d30 |= (u64)0x8000 << 17;
        return 0;
    }
    PlatVu0AddVector(&t, &o->pos, &o->v2b0);
    if (func_0015bcb8(o, &t)) {
        o->p148->d30 |= (u64)0x8000 << 17;
        return 0;
    }
    return r;
}
#undef func_0015bcb8

/* func_00140960 (from hand/nostrict/text_s7_w34.c). */
typedef struct { f32 x, y, z, w; } V4f_40960;
typedef struct { f32 x; f32 x4; f32 z; u8 padc[0x14 - 0xc]; f32 f14; u8 pad18[0x24 - 0x18]; f32 f24; } P96;
typedef struct {
    u32 flags;
    u8 pad4[0xc];
    V4f_40960 x10;
    V4f_40960 x20;
    u8 pad30[0x148 - 0x30];
    P96 *p148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x164 - 0x154];
    s32 x164;
    u8 pad168[4];
    f32 x16c;
    u8 pad170[0x1cc - 0x170];
    u32 x1cc;
    u8 pad1d0[0x490 - 0x1d0];
    V4f_40960 x490;
} O96;
s32 func_001375d8(O96 *);
#define func_00130398 ((void (*)(O96 *, s32, f32)) func_00130398)
#define func_00140838 ((s32 (*)(O96 *, V4f_40960 *)) func_00140838)
/* func_00140960 (s7 w34): MATCH with wqb03_rr.py 0048e1f0 (rodata jtbl 0x48e1f0). Fix: the k=3/4 cross product goes through a function-level f32 c that the d-block cross product also assigns (a pseudo used in two blocks is not tied by local-alloc, so the sub.s result gets f0). */
void func_00140960(O96 *o, V4f_40960 *v) {
    V4f_40960 tmp;
    V4f_40960 d;
    f32 r;
    f32 t;
    f32 c;
    u32 k;
    P96 *p;
    if (o->flags & 4) {
        if (o->x164 == 19) {
        t = o->x16c;
        if (t < 15.0f) {
            v->x = 0.0f;
            v->y = -1.0f;
            v->z = 0.0f;
            v->w = (o->x10.y - (o->p148->f14 + (o->p148->f24 - o->p148->f14) * (t / 15.0f))) / D_002BBDFC;
            PlatVu0CopyVector(&o->x20, v);
        }
        } else {
            v->w = 0.0f;
        }
        return;
    }
    if (func_001375d8(o)) v->y = 0.0f;
    k = 0;
    r = func_0013fd88(o->x10.y);
    if (o->x20.y != 0.0f) {
        if (o->x20.y < 0.0f) {
            if (fabsf(r - func_0013fd88(o->x10.y - (D_002BBDFC + D_002BBDFC))) < 0.5f) k = 1;
        } else {
            if (fabsf(r - func_0013fd88(o->x10.y + (D_002BBDFC + D_002BBDFC))) < 0.5f) k = 2;
        }
    }
    if (k == 0) {
        if (v->y == 0.0f) {
            if (v->w > 0.0f) {
                c = o->p148->x * v->z - v->x * o->p148->z; if (c < 0.0f) k = 3;
                else k = 4;
                v->y = 0.0f;
                v->w = 1.5f;
            } else if (r > 0.5f) {
                o->x10.y += (1.0f - r) * 66.66666412353516f;
            } else {
                o->x10.y -= r * 66.66666412353516f;
            }
        } else {
            k = func_00140838(o, v);
        }
    }
    switch (k) {
    case 0:
        v->y = 0.0f;
        v->w = 0.0f;
        break;
    case 1:
        v->x = 0.0f;
        v->y = -1.0f;
        v->w = 2.0f;
        v->z = 0.0f;
        func_00130398(o, 21, v->x);
        break;
    case 2:
        v->x = 0.0f;
        v->y = 1.0f;
        v->w = 2.0f;
        v->z = 0.0f;
        func_00130398(o, 22, v->x);
        break;
    case 3:
    case 4:
        break;
    }
    PlatVu0OuterProduct(&tmp, v, o->p148);
    PlatVu0OuterProduct(&o->x20, o->p148, &tmp);
    o->x20.w = v->w;
    o->x150 = atan2f(-o->p148->x, -o->p148->z);
    PlatVu0SubVector(&d, &o->x10, &o->x490);
    if (d.y == 0.0f) {
        if (d.x == 0.0f && d.z == 0.0f) {
            if (!(o->x1cc & 0x100000)) func_00130398(o, 17, 8.0f);
        } else {
            c = o->p148->x * d.z - d.x * o->p148->z; if (c < 0.0f) func_00130398(o, 24, 0.0f);
            else func_00130398(o, 23, 0.0f);
        }
    }
}
#undef func_00130398
#undef func_00140838

/* func_00140db8 (from hand/nostrict/text_00140000_h33.c). */
typedef struct Eff154 { u8 pad[0x10]; u8 *p10; u32 w14; } Eff154;
typedef struct S130 { u8 pad[0x5C]; u8 b5c; } S130;
typedef struct {
    u8 pad[0x30];
    u64 d30;
    u8 pad38[8];
    V4f p;
    f32 f50;
    f32 f54;
    u8 pad58[4];
    s32 w5c;
    u8 pad60[0x40];
    V4f va0;
    f32 fb0;
    f32 fb4;
    f32 fb8;
    f32 fbc;
    u8 padc0[0x154 - 0xC0];
    Eff154 *p154;
    f32 f158;
} Sub148_40db8;
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x8];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x130 - 0x8C];
    S130 *p130;
    u8 pad134[0x148 - 0x134];
    Sub148_40db8 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
    u8 pad316[0x39E - 0x316];
    u8 b39e;
    u8 pad39f[0x3C4 - 0x39F];
    f32 f3c4;
} ObjF3_40db8;
void func_0014cc88(ObjF3_40db8 *, f32);
#define func_00130578 ((void (*)(ObjF3_40db8 *, s32, f32)) func_00130578)
#define func_00130398 ((void (*)(ObjF3_40db8 *, s32, f32)) func_00130398)
void func_00140db8(ObjF3_40db8 *o, V4f *v) {
    f32 s;
    u32 fl = 0;
    if (v->y < 0.0f) {
        s = 20.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else if (v->w > 0.0f) {
        s = 15.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else {
        s = 5.0f;
        fl = 0x10000;
        func_00130398(o, 6, 12.0f);
    }
    v->y = 0.0f;
    PlatVu0AddVector(v, v, (V4f *)o->p148);
    PlatVu0Normalize(v, v);
    v->w = 2.0f;
    func_0014cc88(o, s);
    o->flags |= fl;
}
#undef func_00130578
#undef func_00130398

