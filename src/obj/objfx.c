/* Effects started on objects: func_0012bd98(o, kind, mask, pos) asks the
 * effect manager D_0029B410 (func_00176578) for an effect of the object's
 * class (D_002E2FB8) and places it, func_0012c010 at a bone; effect tasks
 * (func_0012c180, func_0012c238, func_0012c328) and a timed one keyed by the
 * tuning block D_00308CDC (func_0012c560); func_0012c760 / func_0012c880 end
 * them. Flag mode: default (the other modes are in the sibling files). Read
 * from the code, not proved by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_004F.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"
#include "data/types/text_00120000_h5.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/pieces/D_00308CDC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC098.h"
#include "m2c.h"
#include "data/pieces/D_00350CE0.h"

/* func_0012bd30 (from hand/text_00120000_h5.c). */
typedef struct E4 {
    s32 w0;
    u8 pad[0x39e - 4];
    u8 f39e;
    u8 pad39f[0x3d4 - 0x39f];
    f32 f3d4;
} E4;
s32 func_0012bd30(E4 *e) {
    switch (e->f39e) {
    case 0:
        return 1;
    case 10:
    case 11:
    case 12:
        if (e->w0 & 0x400000) return 1;
        break;
    }
    if (10.0f < e->f3d4) return 0;
    return 1;
}

/* func_0012c010 (from hand/text_00120000_h31.c). */
extern void func_0012bd98(void *, s32, u32, f32 *);
typedef struct { u32 f0; u8 pad[0x15c - 4]; s32 f15c; u8 pad160[0x324 - 0x160]; f32 f324; u8 pad328[0x39e - 0x328]; u8 f39e; } E10;
extern s32 func_001232f0(E10 *);
extern void func_00162218(s32, s32, f32 *, f32);
#define func_0012bd30 ((s32 (*)(E10 *)) func_0012bd30)
void func_0012c010(E10 *e, s32 bit, s32 b) {
    f32 v[4];
    if (func_001232f0(e) && func_0012bd30(e)) {
        func_00162218(e->f15c, b, v, 1.0f);
        if ((u8)(e->f39e - 10) < 3 && !(e->f0 & 0x400000)) v[1] = e->f324;
        func_0012bd98(e, e->f39e, (1 << (bit % 8)) | (0x80000000 >> (bit / 8)), v);
    }
}
#undef func_0012bd30

/* func_0012c0e8 (from hand/text_00120000_h5.c). */
extern void func_00121eb0(void *);
extern s32 func_00122ff8(void *);
typedef struct C14 { void *f0; u8 pad[0x10]; s32 f14; } C14;
typedef struct C10 { u8 pad[0x50]; u8 f50[16]; } C10;
typedef struct C20 { u8 pad[0x10]; u8 f10[16]; u8 f20[16]; } C20;
typedef struct C0 { u8 pad[0x10]; C10 *f10; C14 *f14; u8 pad18[8]; C20 *f20; } C0;
s32 func_0012c0e8(C0 *a) {
    C20 *s = a->f20;
    if (a->f14 == 0 || (a->f14->f14 & 3) != 1) {
        func_00121eb0(s);
        return 4;
    }
    if (func_00122ff8(a->f10)) {
        PlatVu0CopyVector(a->f14->f0, s->f10);
        PlatVu0AddVector(s->f10, a->f10->f50, s->f20);
    }
    return 0;
}

/* func_0012c180 (from auto/text_00120000_15.c). */
M2C_UNK func_0012eba0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern M2C_UNK D_002E2FCF;
s32 func_00121e28(M2C_UNK, void *);
s32 func_00147ed8(s32, u8, M2C_UNK, s32);
void *func_00147d18(M2C_UNK *);
void func_0012c180(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_v0_2;
    void *temp_v0;

    temp_v0 = func_00147d18(&func_0012c0e8);
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg1;
    temp_v0_2 = func_00121e28(0x40, temp_v0 + 0x20);
    temp_s0 = temp_v0_2 + 0x10;
    func_0012eba0(arg1, 1, -1, 0, temp_s0);
    PlatVu0SubVector(temp_v0_2 + 0x20, temp_s0, arg1 + 0x50);
    M2C_FIELD(temp_v0, s32 *, 0x14) = func_00147ed8(D_00350CE0, *(M2C_UNK *)((s8 *)(s8 *)&D_002E2FCF + arg0), 0x4E20, temp_s0);
}

/* func_0012c238 (from auto/text_00120000_2.c). */
M2C_UNK func_00137330(void *, s32, s32);
M2C_UNK func_00149660(s32, void *);
M2C_UNK func_00157a30(void *, M2C_UNK, M2C_UNK);
s32 func_0012f040(void *, M2C_UNK);
s32 func_00153d78(void *);
#define func_0012c180 ((M2C_UNK (*)(s32, void *)) func_0012c180)
void func_0012c238(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_s1;

    temp_s1 = arg1 & ~0x400;
    if (!(((u32) *M2C_FIELD(arg2, u32 **, 0x6C) >> 2) & 1)) {
        func_00149660(temp_s1, arg2);
        func_00137330(arg2, arg0, temp_s1 | 0x10000);
        if (M2C_FIELD(arg2, s32 *, 0) & 0x8000) {
            if (arg0 != arg2) {
                if (M2C_FIELD(M2C_FIELD(arg2, void **, 0x130), s8 *, 0x54) == 1) {
                    if ((func_0012f040(arg2, -1) != 0) && (func_00153d78(arg2) == 0)) {
                        func_00157a30(arg2, 0x17, 0);
                    }
                }
            }
            func_0012c180(temp_s1, arg2);
        }
    }
}
#undef func_0012c180

/* func_0012c698 (from hand/text_00120000_h31.c). */
typedef struct { u8 pad[0x50]; f32 f50[4]; u8 pad60[0x10]; s32 f70; u8 pad74[0x2d4 - 0x74]; f32 f2d4; u8 pad2d8[0x39e - 0x2d8]; u8 f39e; } E12;
extern void func_00146c98(E12 *, s32);
void func_0012c698(E12 *e) {
    f32 v[4];
    if ((u8)(e->f39e - 11) < 2) {
        PlatVu0CopyVector(v, e->f50);
        v[1] = e->f2d4;
        switch (e->f70) {
        case 2: case 3: case 4: case 5:
            func_0012bd98(e, e->f39e, 0x80000008, v);
            func_00146c98(e, 10);
            break;
        case 10:
        case 13:
            func_0012bd98(e, 10, 0x8000008, v);
            break;
        }
    }
}

/* func_0012c880 (from hand/text_00120000_h5.c). */
typedef union Arg {
    s32 i;
    u32 u;
    f32 f;
    void *p;
} Arg;
extern void func_00176310(void *);
typedef struct S14c { u8 pad[0x14]; Arg f14; u8 pad18[4]; Arg f1c; Arg f20; Arg f24; } S14c;
typedef struct E5 { u8 pad[0x14c]; S14c *f14c; } E5;
void func_0012c880(E5 *a, s32 b) {
    if (a->f14c->f1c.p) func_00176310(a->f14c->f1c.p);
    a->f14c->f1c.p = 0;
    a->f14c->f20.i = a->f14c->f14.i;
    a->f14c->f24.i = b | 0x40000000;
}

