/* Hit reactions, default flags (docs/modules.md "Session 52"):
 * func_00153d88, func_00153e80, func_00154258, func_00154be0.  The rest is in
 * hitreact.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/pieces/D_00308CDC.h"
#include "common.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350D78.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00350CE0.h"

/* func_00153d88 (from auto/text_00150000_13.c). */
s32 func_0013c968(s32, s32);
void func_001358b8(s32, s32);
void func_001373f8(s32, f32);
void func_00141468(s32, s32);
void func_00148068(s32, f32);
void func_00153d88(s32 arg0) {
    s32 temp_a0;

    if (M2C_FIELD(arg0, s32 *, 0x88) & 0x20) {
        func_001373f8(arg0, 30.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x88) = (s32) (M2C_FIELD(arg0, s32 *, 0x88) & ~0x30);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x3C) == 0) {
        if (func_0013c968(9, (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C)) > 0) {
            func_00141468(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x40));
        } else {
            func_00141468(arg0, (s32) ((f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x40) * M2C_FIELD((*(void **)&D_00308CDC), f32 *, 0x8C)));
        }
    }
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x400);
    if (temp_a0 == 0) {
        return;
    }
    func_00148068(temp_a0, 12.0f);
    M2C_FIELD(arg0, s32 *, 0x400) = 0;
    func_001358b8(arg0, 0xC);
}

/* func_00153e80 (from hand/text_00140000_s6_07.c). */
typedef struct { u8 pad[0x70]; s32 x70; u8 pad74[0x164 - 0x74]; s32 x164; } A3e80;
void func_00130340(A3e80 *, s32, f32);
void func_00130578(A3e80 *, s32, f32);
void func_00153e80(A3e80 *a) {
    if (a->x70 == 17) {
        func_00130340(a, 0x100006d, 16.0f);
        func_00130578(a, 0x4000002d, 0.0f);
    } else {
        switch (a->x164) {
        case 67:
        case 108:
            func_00130340(a, 0x1000044, 8.0f);
            func_00130578(a, 0x40000000, 8.0f);
            break;
        case 141:
            func_00130340(a, 0x100008e, 8.0f);
            func_00130578(a, 0x40000075, 8.0f);
            break;
        }
    }
    func_00153d88(a);
}

/* func_00154258 (from hand/text_00140000_h9.c). */
typedef struct {
    u8 pad0[0x10];
    f32 x10;
    u8 pad14[0xBD - 0x14];
    s8 xbd;
    u8 padbe[0xC4 - 0xBE];
    f32 xc4;
    u8 padc8[0xCC - 0xC8];
    union { f32 f; s32 i; u8 c; } xcc;
} W9Obj6c;
typedef struct {
    u8 pad0[0x100];
    u64 x100;
    u8 pad108[0x130 - 0x108];
    f32 x130[4];
    s32 x140;
} W9Obj148;
typedef struct {
    u8 pad0[0x1C];
    u8 *x1c;
} W9Obj134;
typedef struct {
    u8 pad0[0x120];
    f32 x120[4];
    u8 pad130[0x134 - 0x130];
    W9Obj134 *x134;
} W9Obj98;
typedef union { f32 f; s32 i; void *p; u8 c; } W9U;
typedef union {
    W9U w[0x20];
    u64 d[0x10];
} W9Obj144;
typedef struct Actor_54258 {
    s32 flags;
    s32 x4;
    u8 pad8[0x10 - 8];
    f32 x10[4];
    f32 x20[4];
    f32 x30[4];
    u8 pad40[0x6C - 0x40];
    W9Obj6c *x6c;
    s32 x70;
    u8 pad74[0x8C - 0x74];
    s32 x8c;
    u8 pad90[0x98 - 0x90];
    W9Obj98 *x98;
    u8 pad9c[0xA4 - 0x9C];
    f32 xa4;
    f32 xa8;
    u8 padac[0x120 - 0xAC];
    f32 x120[4];
    u8 pad130[0x144 - 0x130];
    W9Obj144 *x144;
    W9Obj148 *x148;
    u8 pad14c[0x164 - 0x14C];
    W9U x164;
    u8 pad168[0x1CC - 0x168];
    s32 x1cc;
    u8 pad1d0[0x1F0 - 0x1D0];
    f32 x1f0[4];
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u64 lo:44; u64 b44:1; u64 hi:19; } b; } x370;
    s32 x378;
    u8 pad37c[0x3B0 - 0x37C];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 x3c0[4];
    u8 pad3d0[0x45C - 0x3D0];
    f32 x45c;
    u8 pad460[0x470 - 0x460];
    u64 x470;
    u8 pad478[0x490 - 0x478];
    f32 x490[4];
    void *x4a0;
} W9Ent;
f32 func_001348e0(W9Ent *e, f32 *o);
void func_00267e90(f32 *out, f32 *in, f32 s);
void func_00154258(W9Ent *e, f32 *o, f32 *out) {
    f32 k = e->x6c->xc4;
    f32 s;
    if (func_001348e0(e, o) * (*(Cfg_308cdc **)&D_00308CDC)->x30 < (*(Cfg_308cdc **)&D_00308CDC)->x34) {
        s = func_001348e0(e, o) * (*(Cfg_308cdc **)&D_00308CDC)->x30 * k;
    } else {
        s = (*(Cfg_308cdc **)&D_00308CDC)->x34 * k;
    }
    func_00267e90(out, o + 4, s);
}

/* func_00154be0 (from auto/text_00150000_3.c). */
#define func_00130340 ((s32 (*)(s32, s32, f32)) func_00130340)
#define func_00130578 ((s32 (*)(s32, s32, f32)) func_00130578)
void func_00154be0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v1;

    func_00130340(arg0, 0x0100006F, 0.0f);
    func_00130578(arg0, 0x40000000, 0.0f);
    func_001373f8(arg0, 8.0f);
    temp_v1 = M2C_FIELD(arg0, void **, 0x14C);
    M2C_FIELD(temp_v1, u8 *, 0x29) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x29) + 0xFF);
    M2C_FIELD(arg2, f32 *, 0xC) = 0.0f;
}
#undef func_00130340
#undef func_00130578

