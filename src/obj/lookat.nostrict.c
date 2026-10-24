/* An entity's look-at: func_0014f9b0 / func_0014fa38 start and stop turning
 * toward a point (x1f0, the bit 33 of x470, its speed x45c), func_0014fab0 /
 * func_0014fc68 the angle to a bone or object within a limit, func_0014fe48
 * the per-frame turn. Flag mode: nostrict (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/pieces/D_002E26A0.h"

/* func_0014fe48 (from hand/nostrict/text_00140000_b04.c). */
typedef struct { u8 pad[0x1c]; f32 x1c; f32 x20; f32 x24; f32 x28; u8 pad2c[0x48 - 0x2c]; s32 x48; s32 x4c; u8 pad50[0x68 - 0x50]; s32 x68; u8 pad6c[0xd4 - 0x6c]; f32 xd4; u8 padd8[4]; f32 xdc; } B4Prm;
typedef struct { u8 pad[0x48]; s16 x48; s16 x4a; u16 x4c; } B4C130;
typedef struct { u8 pad[0x170]; union { u64 x; struct { u32 lo; u32 b0:5; u32 b5:1; u32 r:26; } b; } x170; } B4C148;
typedef struct Actor_4fe48 {
    s32 x0; u8 pad4[0x30 - 4]; u8 x30[0x10]; f32 x40; u8 pad44[0x68 - 0x44]; s32 x68; B4Prm *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0xd0 - 0x8c]; f32 xd0[4][4]; u8 pad110[0x130 - 0x110];
    B4C130 *x130; u8 pad134[0x148 - 0x134]; B4C148 *x148;
    u8 pad14c[0x160 - 0x14c]; union { u64 x; struct { s32 lo; s32 hi; } w; } x160; u8 pad168[0x1cc - 0x168]; u32 x1cc;
    u8 pad1d0[0x1f0 - 0x1d0]; f32 x1f0[3]; f32 x1fc;
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b7:6; u32 b13:1; u32 hi:18; } b; } x370;
    u8 pad378[0x450 - 0x378]; f32 x450[4]; u8 pad460[0x470 - 0x460];
    union { u64 x; struct { struct Actor_4fe48 *lo; u32 hi; } w; } x470;
} B4Ent;
void func_001315c0(void *, s32, void *, f32);
s32 func_00122ff8(B4Ent *);
extern f32 D_002BBDFC;
f32 cosf(f32);
f32 acosf(f32);
f32 func_0014fc68(B4Ent *, B4Ent *, f32 *, f32);
f32 func_0014fab0(B4Ent *, B4Ent *, f32 *, f32);
void func_00120cf8(f32 *, f32 (*)[4], f32);
void func_0014fe48(B4Ent *e) {
    f32 v[4];
    f32 ax[4];
    f32 m[4][4];
    f32 d;
    f32 a;
    f32 lim;
    f32 c;
    e->x1cc &= ~0xc;
    if ((s32)(e->x470.x >> 33) & 1) {
        e->x1fc = e->x1fc + e->x450[3] * D_002BBDFC;
        if (1.0f < e->x1fc) {
            e->x1fc = 1.0f;
        } else if (e->x1fc < 0.0f) {
            e->x470.x &= ~(1ULL << 33);
            return;
        }
        e->x1cc |= 4;
        return;
    }
    d = 500.0f;
    if (!func_00122ff8(e->x470.w.lo)) {
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = -1.0f;
        e->x470.x &= ~(1ULL << 32);
    } else {
        c = cosf(((s32)(e->x470.x >> 32) & 1) ? e->x6c->x20 : e->x6c->x1c);
        if (((s32)(e->x370.x >> 37) & 3) == 1) d = func_0014fc68(e, e->x470.w.lo, v, -c);
        else d = func_0014fab0(e, e->x470.w.lo, v, -c);
        if (0.0f < d) {
            e->x470.x |= 1ULL << 32;
        } else {
            e->x470.x &= ~(1ULL << 32);
            v[1] = v[0] = 0.0f;
            v[2] = -1.0f;
        }
    }
    a = acosf(PlatVu0InnerProduct(e->x450, v));
    lim = e->x6c->x24 * D_002BBDFC;
    if (lim < a) a = lim;
    PlatVu0OuterProduct(ax, e->x450, v);
    PlatVu0Normalize(ax, ax);
    func_00120cf8(ax, m, a);
    e->x450[3] = 0.0f;
    PlatVu0ApplyMatrix(e->x450, m, e->x450);
    PlatVu0Normalize(e->x450, e->x450);
    if (e->x450[2] <= -1.0f) return;
    c = -cosf(e->x6c->x28);
    if (e->x450[2] < c) e->x450[3] = (-1.0f - e->x450[2]) / (-1.0f - c);
    else e->x450[3] = 1.0f;
    if (e->x130->x4c == 507) {
        PlatVu0CopyMatrix(m, e->xd0);
        func_001315c0(e, 0, m[3], 0.5f);
        PlatVu0CopyVector(v, e->x450);
        PlatVu0ScaleVector(v, v, d);
        v[3] = 1.0f;
        PlatVu0ApplyMatrix(e->x1f0, m, v);
        e->x1fc = e->x450[3];
        e->x1cc |= 4;
    } else {
        e->x1cc |= 8;
    }
}

