/* Object class 0x11: the handlers func_00144e38 registers in the class table
 * D_00350D88 (func_0014f830(0x11, ...)) and their helpers. Flag mode:
 * nostrict (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "m2c.h"
#include "data/pieces/D_00308CDC.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_003044E0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_00304BE8.h"
#include "data/types/nostrict_text_00130000_b03_p2.h"
#include "data/pieces/D_00304D64.h"
#include "data/pieces/D_00304C70.h"

/* func_001443a8 (from hand/nostrict/text_00130000_s6_06.c). */
typedef struct W606Ch W606Ch;
struct W606Ch {
    u32 flags;
    f32 x4[4];
    f32 x14;
    f32 x18;
    f32 x1c;
    u8 pad020[0x6c - 0x20];
    void *x6c;
    s32 x70;
    u8 pad074[0x130 - 0x74];
    u8 *info;
    u8 pad134[0x148 - 0x134];
    s32 x148;
    u8 pad14c[0x2D4 - 0x14C];
    f32 x2d4;
    u8 pad2d8[0x360 - 0x2D8];
    s32 x360;
    u8 pad364[0x370 - 0x364];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    W606Ch *x398;
};
typedef struct { f32 f; s32 pad; } W606F8;
extern W606F8 D_00304D60[];
s32 func_001443a8(W606Ch *o) {
    if (o->x148 != 0 && ((s32)(o->x370 >> 56) & 1)) {
        if (D_00304D60[*(u16 *)(o->info + 0x4c)].f < o->x14 - o->x2d4) return 1;
    }
    return 0;
}

/* func_00144410 (from hand/nostrict/text_00140000.c). */
s32 func_00130398(s32, s32, f32);
s32 func_00137618(s32);
s32 func_0014f658(s32, s32);
s32 func_00153e80(s32);
void func_00144958();
#define func_001443a8 ((s32 (*)(s32)) func_001443a8)
#define func_00144958 ((void (*)(s32, s32)) func_00144958)
s32 func_00144410(s32 arg0, s32 arg1) {
    if (func_001443a8(arg0) != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x164) == 0x43) {
            func_0014f658(arg0, 0x11);
            func_00153e80(arg0);
            return 1;
        }
        if (func_00137618(arg0) != 0) {
            func_0014f658(arg0, 0x11);
            func_00130398(arg0, 0x4000002D, 16.0f);
            PlatVu0CopyVector(M2C_FIELD(arg0, void **, 0x148) + 0xA0, arg1);
            if (M2C_FIELD(arg1, f32 *, 0xC) > 0.0f) {
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB8) = 4.0f;
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB0) = 4e+01f;
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB4) = 3e+01f;
            }
            func_00144958(arg0, arg1);
            return 1;
        }
        goto block_8;
    }
block_8:
    return 0;
}
#undef func_001443a8
#undef func_00144958

/* func_00144510 (from hand/nostrict/text_00140000_h33.c). */
typedef FVec4 V4f;
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
} Sub148;
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
    u8 pad316[0x39E - 0x316];
    u8 b39e;
    u8 pad39f[0x3C4 - 0x39F];
    f32 f3c4;
} ObjF3;
extern f32 D_002BBDFC;
extern s32 D_002BC128;
extern s32 D_002BC130;
#define func_0014f658 ((void (*)(ObjF3 *, s32)) func_0014f658)
#define func_00130398 ((void (*)(ObjF3 *, s32, f32)) func_00130398)
#define func_001443a8 ((s32 (*)(ObjF3 *)) func_001443a8)
#define func_00153e80 ((void (*)(ObjF3 *)) func_00153e80)
#define func_00144958 ((void (*)(ObjF3 *, V4f *)) func_00144958)
s32 func_00144510(ObjF3 *o, V4f *v) {
    s32 k;
    f32 f;
    if (D_002BC128 == 13 && D_002BC130 == 8) return 0;
    if (!func_001443a8(o)) return 0;
    func_0014f658(o, 17);
    PlatVu0ScaleVector(&o->p148->va0, v, v->w * 0.5f);
    o->p148->va0.y = o->f3c4;
    f = 16.0f;
    o->f3c4 = o->f3c4 / D_002BBDFC;
    k = 45;
    if (v->w > 0.0f) o->f3c4 = o->f3c4 * 0.19999999f;
    if (o->w88 & 0x20) {
        func_00153e80(o);
    } else {
        func_00130398(o, k, f);
        o->flags &= ~4;
        v->w = 0.0f;
        func_00144958(o, v);
    }
    return 1;
}
#undef func_0014f658
#undef func_00130398
#undef func_001443a8
#undef func_00153e80
#undef func_00144958

/* func_00144650 (from hand/nostrict/text_00140000_h56.c). */
typedef struct {
    u32 flags;
    u8 pad4[0xc];
    f32 pos[4];
    f32 v20[3];
    f32 f2c;
    u8 pad30[0x90 - 0x30];
    u64 d90;
    u8 pad98[0x120 - 0x98];
    f32 v120[4];
    u8 pad130[0x160 - 0x130];
    u64 w160;
    u8 pad168[0x200 - 0x168];
    f32 v200[4];
    u8 pad210[0x3c0 - 0x210];
    f32 v3c0[4];
    u8 pad3d0[0x490 - 0x3d0];
    f32 v490[4];
} Pl;
void func_00121fc4(f32 *, f32 *);
typedef struct { u8 pad[0xa0]; f32 va0[3]; f32 fac; f32 fb0; f32 fb4; f32 fb8; } Cam148;
typedef struct {
    u32 flags;
    u8 pad4[0x88 - 4];
    u32 w88;
    u8 pad8c[0x148 - 0x8c];
    Cam148 *c148;
    u8 pad14c[0x2d4 - 0x14c];
    f32 f2d4;
    u8 pad2d8[0x39e - 0x2d8];
    u8 b39e;
    u8 pad39f[0x3c0 - 0x39f];
    f32 v3c0[4];
} Pk;
void func_001315c0(Pk *, s32, f32 *, f32);
void func_0012bd98(Pk *, u8, u32, f32 *);
void func_00146c98(Pk *, s32);
#define func_0014f658 ((s32 (*)(Pl *, s32)) func_0014f658)
#define func_00153e80 ((void (*)(Pk *, s32, f32)) func_00153e80)
#define func_00130398 ((void (*)(Pk *, s32, f32)) func_00130398)
void func_00144650(Pk *o) {
    f32 v[4];

    if (D_002BC128 == 13 && D_002BC130 == 8) return;
    func_001315c0(o, 0x8003, v, 0.0f);
    if (v[1] > o->f2d4) {
        func_0014f658((Pl *)o, 17);
        PlatVu0CopyVector(o->c148->va0, o->v3c0);
        o->c148->va0[1] = 0.0f;
        func_00121fc4(o->c148->va0, o->c148->va0);
        o->c148->fb8 = o->c148->fac * 0.7f;
        o->c148->fb0 = 40.0f;
        o->c148->fb4 = 30.0f;
        if (o->w88 & 0x20) {
            func_00153e80(o, 45, 16.0f);
        } else {
            func_00130398(o, 45, 16.0f);
            o->flags &= ~4;
        }
        func_0012bd98(o, o->b39e, 0x80000008, v);
        func_00146c98(o, 10);
    }
}
#undef func_0014f658
#undef func_00153e80
#undef func_00130398

/* func_00144810 (from hand/nostrict/text_00130000_s6_na.c). */
typedef struct { f32 x, y, z, w; } V4f_44810;
typedef struct { u8 pad[0xb0]; f32 fb0; } S148;
typedef struct { u8 pad[0xc]; void *cb; } Ev;
typedef struct {
    u32 flags;
    u8 pad4[0x14 - 4];
    f32 x14;
    u8 pad18[0x148 - 0x18];
    S148 *p148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x310 - 0x154];
    u16 x310;
} O4810;
f32 atan2f(f32, f32);
void func_00105a30(s32, s32, V4f_44810 *);
f32 func_00121748(V4f_44810 *, V4f_44810 *);
Ev *func_00130578(O4810 *, s32, f32);
f32 func_00144378(O4810 *);
void func_001447a0();
#define func_00130398 ((void (*)(O4810 *, s32, f32)) func_00130398)
#define func_0014f658 ((void (*)(O4810 *, s32)) func_0014f658)
s32 func_00144810(O4810 *o, V4f_44810 *v) {
    V4f_44810 t;
    f32 z = 0.0f;
    u16 id;
    f32 d;
    if (v->w == z) goto r0;
    if (o->p148->fb0 > z) goto r0;
    id = o->x310;
    if (id == 0xffff) {
r0:
        return 0;
    }
    d = func_00144378(o);
    if (fabsf(d) > 5.0f) return 0;
    func_00105a30(-1, id, &t);
    if (func_00121748(&t, v) > -0.7f) return 0;
    o->x14 -= d;
    o->x150 = atan2f(-t.x, -t.z);
    func_00130398(o, 0x1000031, 8.0f);
    func_00130578(o, 0x40000006, z)->cb = func_001447a0;
    func_0014f658(o, 16);
    return 1;
}
#undef func_00130398
#undef func_0014f658

/* func_00144958 (from hand/nostrict/text_00130000_b03.c). */
extern u32 D_002C5BB4;
extern f32 D_002C5970;
s32 func_001232f0(B3Ob *);
s32 func_00137660(B3Ob *);
#define func_00130398 ((void (*)(B3Ob *o, s32 a, f32 f)) func_00130398)
#define func_00144810 ((void (*)(B3Ob *, f32 *)) func_00144810)
void func_00144958(B3Ob *o, f32 *v) {
    f32 t[4];
    f32 h, k, r, s, sc, nh;

    if (!func_001232f0(o)) {
        PlatVu0CopyVector(o->x20, v);
        PlatVu0CopyVector(o->x148->xa0, (*(f32 (*)[0x4])&D_002C58B0));
        o->x148->xb0 = 0.0f;
        return;
    }
    PlatVu0CopyVector(t, o->x148->xa0);
    t[1] = 0.0f;
    func_00121fc4(t, t);
    if (0.0f < o->x148->xb0) {
        if (0.0f < o->x148->xbc) {
            sc = 0.0f;
            s = 1.0f;
            o->x148->xbc -= D_002BBDFC;
        } else {
            if (o->x148->xb4 < o->x148->xb0) {
                s = o->x148->xb8;
                if (!(D_002C5BB4 & 4)) o->x148->xb0 = o->x148->xb4;
                sc = 0.0f;
            } else {
                r = o->x148->xb0 / o->x148->xb4;
                s = (o->x148->xb8 - 4.0f) * r + 4.0f;
                sc = r * -0.5f + 0.5f;
            }
            o->x148->xb0 -= D_002BBDFC;
        }
        PlatVu0ScaleVector(t, t, s);
        t[3] = s;
    } else {
        sc = 0.5f;
        PlatVu0ScaleVectorXYZ(t, t, t[3]);
        if (func_00137660(o)) {
            if (0.0f < v[3]) {
                func_00130398(o, 46, 16.0f);
            } else {
                func_00130398(o, 45, 16.0f);
            }
        }
    }
    h = o->x2d4 + D_00304D64[o->x130->x4c].x0 - o->x10[1];
    t[1] = h;
    nh = -h;
    if (h < 0.0f) {
        k = h * (D_002C5970 * 0.015f);
    } else {
        k = h * (D_002C5970 * 0.1f);
    }
    t[1] = k + o->x3c0[1];
    o->x3c0[1] = t[1] * 0.8f;
    PlatVu0CopyVector(o->x20, t);
    if (t[0] != 0.0f && t[2] != 0.0f) o->x150 = atan2f(t[0], t[2]);
    if (0.0f < v[3]) {
        s = (20.0f < nh) ? 2.0f : 4.0f;
        PlatVu0ScaleVector(v, v, sc);
        PlatVu0AddVector(v, v, t);
        v[1] = 0.0f;
        func_00121fc4(v, v);
        PlatVu0ScaleVector(t, v, v[3] < (t[3] < s ? s : t[3]) ? v[3] : (t[3] < s ? s : t[3]));
    } else {
        PlatVu0ScaleVector(t, t, 0.9f);
    }
    PlatVu0CopyVector(o->x148->xa0, t);
    func_00144810(o, v);
}
#undef func_00130398
#undef func_00144810

/* func_00144d08 (from hand/nostrict/text_00140000_s7_w26.c). */
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; u8 pad60[0x40]; V4f va0; f32 fb0; f32 fb4; f32 fb8; f32 fbc; } Sub148_44d08;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x148 - 0x8C];
    Sub148_44d08 *p148;
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
} ObjF3_44d08;
#define func_00130398 ((void (*)(ObjF3_44d08 *, s32, f32)) func_00130398)
#define func_00130578 ((void (*)(ObjF3_44d08 *, s32, f32)) func_00130578)
#define func_00121fc4 ((void (*)(V4f *, V4f *)) func_00121fc4)
/* func_00144d08 (hand/nostrict): the call func_00130398(o, k, 0.0f) and the fbc store written in each branch of the inner if/else. cse then reuses the 0.0f of the fb0 test for the f12 argument (mtc1 zero,$f12 at entry), and jump2 cross-jumps the two tails back into one. With only the call duplicated, a (use (const_int 0)) left by the sibcall pass after the else-branch call blocks the cross-jump. */
s32 func_00144d08(ObjF3_44d08 *o) {
    V4f t;
    if (o->p148->fb0 <= 0.0f) {
        s32 k;
        f32 a, s;
        if (((*(u32 *)&D_002E27C8) >> 6) & 1) {
            k = 48;
            o->p148->fb0 = 75.0f;
            a = 45.0f;
            s = 12.0f;
            o->p148->fb4 = a;
            func_00130398(o, k, 0.0f);
            o->p148->fbc = 4.0f;
        } else {
            k = 47;
            o->p148->fb0 = 45.0f;
            a = 30.0f;
            s = 9.0f;
            o->p148->fb4 = a;
            func_00130398(o, k, 0.0f);
            o->p148->fbc = 4.0f;
        }
        func_00130578(o, 46, 16.0f);
        PlatVu0CopyVector(&t, &o->p148->va0);
        t.y = 0;
        func_00121fc4(&t, &t);
        if (t.w == 0.0f) PlatVu0CopyVector(&t, (V4f *)((u8 *)o + 0x30));
        PlatVu0ScaleVector(&o->p148->va0, &t, s);
        o->p148->fb8 = s;
    }
    return 0;
}
#undef func_00130398
#undef func_00130578
#undef func_00121fc4

