/* Object draw jobs: func_001371f0 queues a draw job on the task list
 * D_0052A100 (func_00136bc0 runs it) with a per-kind draw callback
 * (func_001368e8, func_001369e8, func_00136ab8), func_00136428 draws a model
 * with a colour and alpha, func_001372a0 resets the lists (func_00135ed0 and
 * func_00136d38 of this range stay in hand/nostrict/text_00130000_c02.c with
 * func_0013cfe8). Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00120000_b02.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002E26C0.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00120000_h54.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0A8.h"

/* func_00136428 (from hand/nostrict/text_00120000_b02.c). */
typedef struct { u8 p0[4]; u32 f4; u8 p8[0x4c - 8]; u16 h4c; } K14;
typedef struct { s32 f0; s32 f4; u8 p8[4]; u8 c[4]; } Q14;
typedef struct { s32 f0; s32 f4; } R14;
typedef struct {
    u32 f0;
    u8 p4[0x48 - 4];
    f32 f48;
    u8 p4c[4];
    V4 f50;
    u8 p60[0xd0 - 0x60];
    f32 fd0[4][4];
    u8 p110[0x130 - 0x110];
    K14 *f130;
    u8 p134[0x14c - 0x134];
    Q14 *f14c;
    u8 p150[0x15c - 0x150];
    s32 f15c;
    u64 f160;
    u8 p168[0x370 - 0x168];
    u64 f370;
    u8 p378[0x410 - 0x378];
    f32 f410;
    f32 f414;
    u8 p418[8];
    s32 f420;
} O14;
typedef struct {
    u32 f40;
    s32 f44;
    s32 f48;
    u8 c[4];
    u8 b[4];
    s32 f54;
    u8 d[4];
    u8 e[4];
    void *fn;
    void *p;
    u32 fl;
    s32 f6c;
    void *fn1;
    void *fn2;
    u64 g[2];
} S14;
extern void func_00122770(void);
extern void func_001229c0(void);
extern void func_00135ed0(void);
extern void func_00175600(void);
extern R14 *func_001357b8(void);
extern void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
extern void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void func_002675a8(f32 *, V4 *);
extern void func_00135a68(u8 *, f32, f32);
extern s32 func_00121000(f32 (*)[4], u8 *);
extern void func_001621e0(s32, f32 (*)[4], S14 *, O14 *);
void func_00136428(O14 *o, u32 fl, s32 a2, f32 *col, f32 alpha) {
    f32 m[4][4];
    S14 s;
    u8 buf[128];
    s32 i;
    Q14 *q;
    R14 *r;

    s.f44 = o->f420;
    s.f48 = -1;
    s.fn1 = func_00122770;
    s.fn2 = func_001229c0;
    s.b[0] = D_002BC0F0.i[4];
    s.b[1] = D_002BC0F0.i[5];
    s.b[2] = D_002BC0F0.i[6];
    s.b[3] = (s32)alpha;
    s.f40 = 0;
    switch (o->f130->h4c) {
    case 35:
    case 516:
        r = func_001357b8();
        r->f0 = (s32)o;
        r->f4 = o->f48 * 128.0f;
        s.p = r;
        s.fn = func_00135ed0;
        break;
    case 507:
        if ((s32)(o->f160 >> 10) & 1) {
            fl |= 4;
            s.fn = func_00175600;
        } else {
            s.fn = 0;
        }
        break;
    default:
        s.p = o;
        s.fn = 0;
        break;
    }
    s.fl = fl;
    s.f6c = a2;
    for (i = 0; i < 4; i++) s.c[i] = (s32)col[i];
    q = o->f14c;
    if (q && q->f0 && (o->f0 & 0x4000)) {
        s.f54 = q->f4;
        for (i = 0; i < 4; i++) {
            s.d[i] = s.c[i];
            s.e[i] = q->c[i];
        }
    } else {
        s.f54 = 0;
    }
    sceVu0CopyMatrix(m, o->fd0);
    func_002675a8(m[3], &o->f50);
    m[3][3] = 1.0f;
    sceVu0MulMatrix(m, D_002E26C0, m);
    if (!((o->f370 >> 49) & 1)) {
        func_00135a68(buf, o->f410, o->f414);
        if (func_00121000(m, buf)) s.f40 |= 0x100;
    }
    if (o->f130->f4 & 4) s.f40 |= 0x200;
    {
        u64 t = 0x000800d0;
        s.g[0] = 0x31000070;
        s.g[1] = t;
    }
    func_001621e0(o->f15c, D_002E26C0, &s, o);
}

/* func_00136768 (from hand/nostrict/text_00120000_h54.c). */
typedef union { u64 x; struct { u32 lo:24; u32 b3:8; u32 b4:8; u32 k:2; u32 hi:22; } b; } F370;
typedef struct { u8 pad[0x50]; V4 pos; u8 p60[0x2c4-0x60]; f32 f2c4; u8 p2c8[4]; s32 f2cc; u8 p2d0[0x320-0x2d0]; V4 v320; u8 p330[0x370-0x330]; F370 f370; } E2;
typedef struct { u8 p[0x4c]; u16 f4c; } I21;
typedef struct Actor_36768 { u32 f0; u8 p4[2]; u8 f6; u8 p7[0x118 - 7]; f32 f118; u8 p11c[0x130 - 0x11c]; I21 *f130; u8 p134[0x144 - 0x134]; s32 f144; u8 p148[0x370 - 0x148]; u64 f370; u8 p378[0x38c - 0x378]; s32 f38c; u8 p390[4]; s32 f394; u8 p398[0x430 - 0x398]; V4 f430; } E21;
typedef struct { void *p; s32 n; } Arg21;
extern f32 func_00135ca0(f32);
extern void func_00122588(E21 *);
extern void func_00135df0(E21 *, V4 *);
extern void func_00267548(V4 *, V4 *, V4 *);
extern s32 func_00135bb0(E21 *);
extern void func_0012bce0(s32, s32, s32, Arg21 *, s32);
extern void func_00128218(E2 *, f32);
#define func_00136428 ((s32 (*)(E21 *, f32, s32, s32, V4 *)) func_00136428)
void func_00136768(E21 *e) {
    Arg21 a;
    V4 v;
    s32 w;
    f32 s = func_00135ca0(e->f118);
    func_00122588(e);
    func_00135df0(e, &v);
    func_00267548(&v, &v, &e->f430);
    if (v.w <= 0.0f) return;
    if (func_00135bb0(e) && (e->f0 & 1)) {
        s32 f = e->f38c;
        if (e->f130->f4c == 8) {
            if (e->f6 == 3) {
                if (e->f0 & 0x4000) f |= 2;
            }
        }
        w = func_00136428(e, s, f, e->f394, &v);
        if (((s32)(e->f370 >> 48) & 1) && e->f144) {
            a.p = &w;
            a.n = 4;
            func_0012bce0(e->f144, 4, 1, &a, 0);
        }
        e->f370 |= 0x800000000LL;
    }
    if (e->f0 & 2) {
        if (e == D_002E26A0[0] && D_00304BE8->f880) return;
        func_00128218((E2 *)e, v.w * s * (1.0f / 32640.0f));
    }
}
#undef func_00136428

/* func_001369e8 (from hand/nostrict/text_00130000_s6_na.c). */
typedef union { u64 x; struct { u32 lo; u32 x32:3; u32 b35:1; u32 hi:28; } b; } F370d;
typedef struct { u32 f0; u8 p4[0xd0-4]; u8 fd0[0x154-0xd0]; s32 f154; u8 p158[0x370-0x158]; F370d f370; } Ob8;
extern s32 func_00114a38(void *, s32, s32, f32 *);
#define func_00135df0 ((void (*)(Ob8 *, f32 *)) func_00135df0)
#define func_00128218 ((void (*)(Ob8 *, f32)) func_00128218)
void func_001369e8(Ob8 *o) {
    f32 v[4];
    s32 i;
    if (!(o->f0 & 1)) return;
    if (!(D_002BC0A8.u & 1)) return;
    func_00135df0(o, v);
    for (i = 0; i < 4; i++) v[i] *= 0.0078125f;
    { u64 m = 0x800000000ULL;
    func_00114a38(o->fd0, o->f154, v[3] < 1.0f ? 0xc35a : 0x9c40, v);
    o->f370.x |= m; }
    if (o->f0 & 2) func_00128218(o, 1.0f);
}
#undef func_00135df0
#undef func_00128218

