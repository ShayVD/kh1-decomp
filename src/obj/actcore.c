/* The actor core under the object classes: func_0014f830 registers a class
 * in the table D_00350D88 (32-byte records: a parameter and seven handlers),
 * func_0014f5c8 / func_0014f600 / func_0014f658 call an actor's class
 * handlers (func_0014f658(o, n) changes its motion state), the default
 * handlers func_0014f748 / func_0014f778 / func_0014f828, and the reset of
 * an actor's stats to D_00304C70 (func_0014f398). Flag mode: default (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "data/pieces/D_002E27C8.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "data/types/text_00140000_h57_p.h"
#include "data/types/text_00140000_h57.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_00350D78.h"
#include "data/pieces/D_002C58D0.h"

/* func_0014f370 (from auto/text_00140000_16.c). */
s32 func_00141a40();
void func_0014f370(void *arg0) {
  s32 new_var;
 do { new_var = func_00141a40(); } while (0);
  *((s32 *) (((s8 *) arg0) + 0x6C)) = new_var;
}

/* func_0014f398 (from auto/text_00140000_4.c). */
void func_00141ab8(s32);
void func_0014f398(s32 arg0) {
    func_00141ab8(M2C_FIELD(arg0, s32 *, 0x6C));
    M2C_FIELD(arg0, s32 *, 0x6C) = (s32) &D_00304C70;
}

/* func_0014f3d0 (from hand/text_00140000_h9.c). */
void *func_00134928(void *a);
void func_001350d0(void *p);
void func_0014f3d0(void *a) {
    void *p;
    while ((p = func_00134928(a)) != 0) func_001350d0(p);
}

/* func_0014f410 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[8]; f32 f8; } Prm57_f410;
typedef struct {
    s32 flags;
    u8 pad4[0x2c-4];
    f32 f2c;
    u8 pad30[0x6c-0x30];
    Prm57_f410 *prm;
    s32 i70;
    u8 pad74[0x164-0x74];
    s32 i164;
    u8 pad168[0x178-0x168];
    s32 i178;
    u8 pad17c[0x378-0x17c];
    s32 i378;
    u8 pad37c[0x39e - 0x37c];
    u8 b39e;
    u8 pad39f[0x3d0-0x39f];
    s32 i3d0;
    u8 pad3d4[0x440-0x3d4];
    u64 f440;
} Obj57_f410;
void func_00130398(void *, s32, f32);
void func_001315c0(void *, s32, f32 *, f32);
void func_00130340(Obj57_f410 *, s32, f32);
void func_00130578(Obj57_f410 *, s32, f32);
void func_00146c98(Obj57_f410 *, s32);
void func_0012bd98(Obj57_f410 *, s32, s32, f32 *);
#define func_0014f3d0 ((void (*)(Obj57_f410 *)) func_0014f3d0)
void func_0014f410(Obj57_f410 *o) {
    f32 v[4];
    s32 id;

    func_0014f3d0(o);
    if ((s32)(o->f440 >> 33) & 1) return;
    if (o->flags & 0x400) {
        switch (o->i70) {
        case 0:
            if (o->i378 == 2) {
                func_00130340(o, (o->i3d0 + 7) | 0x01000000, 0.0f);
                func_00130578(o, 0x40000000, 8.0f);
            }
            break;
        case 2:
            func_00130340(o, 6, 8.0f);
            break;
        }
    }
    if (o->i70) return;
    if (o->f2c == 0.0f) {
        if (o->i178) return;
        if ((u32)(o->i164 - 1) < 2) func_00146c98(o, 8);
        func_00130398(o, 0, 10.0f);
        return;
    }
    if (o->f2c < o->prm->f8) id = 1;
    else id = 2;
    if (o->i164 == 0) {
        func_001315c0(o, 41, v, 1.0f);
        func_0012bd98(o, o->b39e, 0x80000002, v);
        func_001315c0(o, 40, v, 1.0f);
        func_0012bd98(o, o->b39e, 0x80000002, v);
    }
    func_00130398(o, id, 8.0f);
}
#undef func_0014f3d0

/* func_0014f5c8 (from auto/text_00140000_15.c). */
s32 func_0014f5c8(void *arg0) {
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x70);
    var_v0 = 1;
    if (temp_v1 == 0x17) {
        return var_v0;
    }
    var_v0 = (*(M2C_UNK *)((s8 *)(s8 *)&D_00350D88 + (temp_v1 << 5)) & 3) == 2;
    return var_v0;
}

/* func_0014f600 (from hand/text_00140000_h9.c). */
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
typedef struct Actor_4f600 {
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
s32 func_0014f600(W9Ent *e) {
    switch (e->x70) {
    case 2:
    case 11:
    case 16:
    case 17:
    case 19:
    case 20:
    case 22:
        return 1;
    }
    return (D_00350D88[e->x70].f0 & 3) == 1;
}

/* func_0014f658 (from hand/text_00140000_h9.c). */
typedef struct Actor_4f658 {
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
} W9Ent_4f658;
typedef void (*W9Fn)(W9Ent_4f658 *);
s32 func_0014f658(W9Ent_4f658 *e, s32 s) {
    s32 old = e->x70;
    if (old != s) {
        e->x378 = old;
        e->x70 = s;
        e->flags |= 0x400;
        if (D_00350D88[old].f8) ((W9Fn)D_00350D88[old].f8)(e);
        if (D_00350D88[s].f4) ((W9Fn)D_00350D88[s].f4)(e);
        return 1;
    }
    return 0;
}

/* func_0014f6f8 (from auto/text_00140000_11.c). */
M2C_UNK func_001376e8();
M2C_UNK func_002675a8(s32, void *);
void func_0014f6f8(s32 arg0, void *arg1) {
    if (M2C_FIELD(arg1, f32 *, 0xC) > 0.0f) {
        func_001376e8();
    }
    func_002675a8(arg0 + 0x20, arg1);
}

/* func_0014f748 (from auto/text_00140000_11.c). */
M2C_UNK func_00267e90(s32, void *, f32);
extern f32 D_002BBDFC;
void func_0014f748(void *arg0, s32 arg1) {
    func_00267e90(arg1, arg0 + 0x20, M2C_FIELD(arg0, f32 *, 0x2C) * D_002BBDFC);
}

/* func_0014f778 (from auto/text_00140000_12.c). */
#define func_002675a8 ((M2C_UNK (*)(s32, M2C_UNK *)) func_002675a8)
void func_0014f778(s32 arg0, s32 arg1) {
    func_002675a8(arg1, ((M2C_UNK *)&D_002C58A0));
}
#undef func_002675a8

/* func_0014f798 (from auto/text_00140000_13.c). */
M2C_UNK func_00267370(void *, void *, void *);
f32 func_002673b8(void *, void *);
#define func_00267e90 ((M2C_UNK (*)(void *, void *, f32)) func_00267e90)
void func_0014f798(void *arg0, void *arg1) {
    s32 sp[4];
    void *temp_s2;

    temp_s2 = arg0 + 0xC0;
    func_00267370(sp, temp_s2, arg0 + 0x20);
    func_002673b8(sp, sp);
    func_00267370(arg1, sp, temp_s2);
    func_002673b8(arg1, arg1);
    func_00267e90(arg1, arg1, M2C_FIELD(arg0, f32 *, 0x2C) * D_002BBDFC);
}
#undef func_00267e90

/* func_0014f828 (from auto/text_00140000_2.c). */
s32 func_0014f828(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}

/* func_0014f830 (from auto/text_00140000_9.c). */
void func_0014f830(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0) {
    void *temp_a0;

    temp_a0 = (s8 *)&D_00350D88 + (arg0 << 5);
    M2C_FIELD(temp_a0, s32 *, 0) = arg1;
    M2C_FIELD(temp_a0, s32 *, 4) = arg2;
    M2C_FIELD(temp_a0, s32 *, 8) = arg3;
    M2C_FIELD(temp_a0, s32 *, 0xC) = arg4;
    M2C_FIELD(temp_a0, s32 *, 0x10) = arg5;
    M2C_FIELD(temp_a0, s32 *, 0x14) = arg6;
    M2C_FIELD(temp_a0, s32 *, 0x18) = arg7;
    M2C_FIELD(temp_a0, s32 *, 0x1C) = arg_sp0;
}

/* func_0014f868 (from auto/text_00140000_10.c). */
M2C_UNK func_0013bf20();
M2C_UNK func_0013fc80();
M2C_UNK func_00141138();
M2C_UNK func_00144e38();
M2C_UNK func_0014cb38();
M2C_UNK func_0014d890();
M2C_UNK func_0014e4b8();
M2C_UNK func_00150cd8();
M2C_UNK func_001524c8();
M2C_UNK func_00153d28();
M2C_UNK func_001556a8();
M2C_UNK func_00158648();
M2C_UNK func_001598e0();
M2C_UNK func_0015a418();
M2C_UNK func_0015d560();
M2C_UNK func_0015dbf8();
M2C_UNK func_0015e128();
M2C_UNK func_0015e7a8();
M2C_UNK func_0015ea40();
void func_0014f868(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v1 = 0x3A;
    var_v0 = &D_00350D88;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        M2C_FIELD(var_v0, s32 *, 8) = 0;
        M2C_FIELD(var_v0, s32 *, 0xC) = 0;
        M2C_FIELD(var_v0, s32 *, 0x10) = 0;
        M2C_FIELD(var_v0, s32 *, 0x14) = 0;
        M2C_FIELD(var_v0, s32 *, 0x18) = 0;
        M2C_FIELD(var_v0, s32 *, 0x1C) = 0;
        var_v0 += 0x20;
    } while (var_v1 >= 0);
    func_0015e7a8();
    func_0015ea40();
    func_0015e128();
    func_0014e4b8();
    func_0014cb38();
    func_001524c8();
    func_00150cd8();
    func_00141138();
    func_0015d560();
    func_00153d28();
    func_0015dbf8();
    func_001556a8();
    func_0014d890();
    func_0013fc80();
    func_00158648();
    func_00144e38();
    func_001598e0();
    func_0015a418();
    func_0013bf20();
}

/* func_0014f948 (from auto/text_00140000_10.c). */
M2C_UNK func_0012ec88(s32, void *);
s32 func_00122ff8(s32);
void func_0014f948(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x470) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x470) = arg1;
        if (func_00122ff8(arg1) != 0) {
            func_0012ec88(arg1, arg0 + 0x460);
        }
    }
}

