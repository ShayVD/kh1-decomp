/* Object class 0x18, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_0015e7a8 registers in the class table D_00350D88
 * (func_0014f830(0x18, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class18.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_00304BE8_s.h"

/* func_0015e178 (from hand/nostrict/text_00140000_b04.c). */
void func_001315c0(void *, s32, f32, void *);
extern f32 D_002BBDFC;
typedef struct { u8 pad[0x20]; f32 x20; f32 x24; f32 x28; u8 pad2c[0x3b0 - 0x2c]; f32 x3b0; } B4E5;
extern u32 D_002E3190;
f32 D_00551D70 ALIGNED(16);  /* moved from hand/nostrict/text_00140000_b04.c (session 53) */
void func_0014f658(B4E5 *, s32);
f32 func_0012ec60(struct Actor_5e178 *, s32, f32 *);
f32 func_00121748(f32 *, f32 *);
f32 func_00120c18(f32 *);
f32 func_00121b08(f32);
void func_0015e178(B4E5 *e, s32 unused, f32 *v) {
    f32 a[4];
    f32 b[4];
    f32 d;
    f32 t;
    if (0.0f < v[3]) {
        if (v[3] < 0.7999999523162842f) v[3] = 4.0f;
        else v[3] = 8.0f;
    }
    if (v[0] == 0.0f && v[2] == 0.0f) {
        v[0] = e->x20;
        v[2] = e->x28;
    }
    if ((D_002E3190 >> 27) & 1) v[1] = -8.0f;
    else if ((D_002E3190 >> 28) & 1) v[1] = 8.0f;
    else v[1] = 0.0f;
    if (((*(u32 *)&D_002E27C8) >> 6) & 1) {
        if (D_002E3190 & 0x18000000) {
            if (0.0f < D_00551D70 && D_00551D70 < 16.0f) func_0014f658(e, 25);
            else D_00551D70 = 16.0f;
        } else if (0.0f < D_00551D70) {
            D_00551D70 -= D_002BBDFC;
        }
    }
    if (D_002E31B8 >= 3 && 0.0f < v[3] && v[1] == 0.0f) {
        d = func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, a);
        func_001315c0(e, 0x8003, 0.0f, b);
        PlatVu0SubVector(a, a, b);
        if (0.5f < func_00121748(a, v)) {
            t = (func_00120c18(a) - d - 200.0f) * 0.7999999523162842f;
            if (0.0f < t) {
                v[1] = a[1] / t * v[3];
                if (8.0f < v[1]) v[1] = 8.0f;
                else if (v[1] < -8.0f) v[1] = -8.0f;
            }
        }
    }
    e->x3b0 = func_00121b08(e->x3b0);
}

/* func_0015e438 (from hand/nostrict/text_00150000_h59.c). */
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4];
    u8 pad30[0x170 - 0x30];
    f32 x170;
    u8 pad174[4];
    s32 x178;
    u8 pad17c[0x440 - 0x17c];
    u64 x440;
} Ob5e;
void func_001376e8(Ob5e *, f32 *);
s32 func_001375f0(Ob5e *);
void func_00130398(void *, s32, f32);
void func_0015e438(Ob5e *o, f32 *v) {
    s32 st = 0;
    if (v[1] > 0.0f) st = 125;
    else if (v[1] < 0.0f) st = 124;
    if (v[0] != 0.0f || v[2] != 0.0f) func_001376e8(o, v);
    if (v[3] > 0.0f) {
        if (v[3] > 4.0f) {
            switch (st) {
            case 0: st = 2; break;
            case 125: st = 130; break;
            case 124: st = 129; break;
            }
        } else {
            switch (st) {
            case 0: st = 1; break;
            case 125: st = 128; break;
            case 124: st = 127; break;
            }
        }
    }
    if (func_001375f0(o) && !(o->x440 >> 33 & 1)) {
        if (st == 0) {
            if (o->x178 != 0) goto end;
        } else if (o->x170 > 0.0f) {
            goto end;
        }
        func_00130398(o, st, 16.0f);
    }
end:
    PlatVu0CopyVector(o->x20, v);
}

/* func_0015e5c8 (from hand/nostrict/text_00150000_h59.c). */
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4];
    u8 pad30[0x3c0 - 0x30];
    f32 x3c0[4];
} Ob5f;
void func_00121fc4(f32 *, f32 *);
static inline f32 inl_min(f32 a, f32 b) { if (!(a < b)) a = b; return a; }
static inline f32 inl_max(f32 a, f32 b) { if (!(b < a)) a = b; return a; }
void func_0015e5c8(Ob5f *o, f32 *v) {
    f32 tmp[4];
    f32 s, t, y, c, k;
    s = o->x3c0[3];
    k = 0.199999988079071044921875f;
    if (o->x20[3] > 0.0f) {
        PlatVu0InterVectorXYZ(v, o->x20, o->x3c0, k);
        v[1] = 0.0f;
        func_00121fc4(tmp, v);
        if (tmp[3] > 1.0f) PlatVu0CopyVector(v, tmp);
    } else {
        PlatVu0CopyVector(v, o->x3c0);
        v[1] = 0.0f;
    }
    if (s < o->x20[3]) {
        t = s + D_002BBDFC * 0.199999988079071044921875f;
        s = inl_min(t, o->x20[3]);
    } else if (o->x20[3] < s) {
        t = s - k * D_002BBDFC;
        s = inl_max(t, o->x20[3]);
    }
    o->x3c0[0] = v[0];
    o->x3c0[2] = v[2];
    o->x3c0[3] = s;
    PlatVu0ScaleVector(v, v, s);
    y = o->x3c0[1];
    c = o->x20[1];
    if (y < c) {
        o->x3c0[1] = o->x3c0[1] + D_002BBDFC * 0.35f;
        if (c < o->x3c0[1]) o->x3c0[1] = c;
    } else if (c < o->x3c0[1]) {
        o->x3c0[1] = o->x3c0[1] - D_002BBDFC * 0.35f;
        if (o->x3c0[1] < c) o->x3c0[1] = c;
    }
    o->x20[1] = 0.0f;
    v[1] = o->x3c0[1];
    PlatVu0ScaleVector(v, v, D_002BBDFC);
}

