/* Object class 0x1C, default flags (docs/modules.md "Session 52"): the
 * handlers func_00153d28 registers in the class table D_00350D88
 * (func_0014f830(0x1C, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1c.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002C58A0.h"
#include "platform/math.h"
#include "data/pieces/D_00350D78.h"
#include "data/pieces/D_00308CDC.h"

/* func_00152520 (from auto/text_00150000_3.c). */
void func_00152520(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x98) = arg1;
    M2C_FIELD(arg1, s32 *, 0x98) = arg0;
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) | 0x200);
}

/* func_00152538 (from auto/text_00150000_23.c). */
M2C_UNK func_0014f658(void *, M2C_UNK);
void func_00152538(void *arg0) {
  void **new_var;
  void *temp_a0;
  temp_a0 = *((void **) (((s8 *) arg0) + 0x98));
  if (temp_a0 != 0)
  {
 do { if ((*((s32 *) (((s8 *) temp_a0) + 0x70))) == 0x1C) { func_0014f658(temp_a0, 0); } *((s32 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x98)))) + 0x98)) = 0; } while (0);
    new_var = (void **) (((s8 *) arg0) + 0x98);
    *new_var = 0;
  }
  *((s32 *) (((s8 *) arg0) + 0)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0))) & (~0x200));
}

/* func_00152598 (from hand/text_00140000_h9.c). */
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
typedef struct Actor_52598 {
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
W9Obj144 *func_00148a40(W9Ent *e, s32 a);
void func_00152598(W9Ent *e) {
    e->x144->w[17].f = 300.0f;
    e->x144->w[18].i = 0;
    if (!e->x144->w[19].p) e->x144->w[19].p = func_00148a40(e, 3);
}

/* func_001525f0 (from hand/text_00140000_h9.c). */
typedef struct Actor_525f0 {
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
} W9Ent_525f0;
void func_00176310(void *p);
void func_001525f0(W9Ent_525f0 *e) {
    void *p;
    e->x144->w[17].i = 0;
    e->xa4 = e->xa8 = 1.0f;
    p = e->x144->w[19].p;
    if (p) {
        func_00176310(p);
        e->x144->w[19].p = 0;
    }
}

/* func_00152648 (from auto/text_00150000_3.c). */
void func_0014aab0(s32);
void func_00152648(s32 arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), s32 *, 0x40);
    if (temp_v1 != 0) {
        func_0014aab0(temp_v1);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), s32 *, 0x40) = 0;
    }
}

/* func_00152730 (from auto/text_00150000.c). */
M2C_UNK func_001247e8(s32);
M2C_UNK func_001586a8(M2C_UNK);
#define func_00152538 ((M2C_UNK (*)()) func_00152538)
#define func_001525f0 ((M2C_UNK (*)(s32)) func_001525f0)
#define func_00152648 ((M2C_UNK (*)(s32)) func_00152648)
void func_00152730(s32 arg0) {
    func_00152538();
    func_001525f0(arg0);
    func_00152648(arg0);
    func_001586a8(0x11);
    func_001247e8(arg0);
}
#undef func_00152538
#undef func_001525f0
#undef func_00152648

/* func_00152880 (from auto/text_00150000_16.c). */
s32 func_00147ed8(s32, s32, s32, s32);
void func_001315c0(s32, s32, s32, f32);
void func_00152770(s32);
void func_00152880(Actor *arg0) {
    s32 sp[4];
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0xCB) {
        func_00152770(arg0);
        return;
    }
    func_001315c0(arg0, 0x8003, (s32) sp, 0.0f);
    func_00147ed8(arg0->unk068, 0, 0x4E20, (s32) sp);
    func_00152730(arg0);
}

/* func_001528f0 (from hand/text_00140000_h9.c). */
typedef struct Actor_528f0 {
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
} W9Ent_528f0;
#define func_00152538 ((void (*)(W9Ent_528f0 *e)) func_00152538)
void func_001528f0(W9Ent_528f0 *e) {
    func_00152538(e);
    e->x144->w[1].i = 4;
    e->x144->w[7].i = 0;
}
#undef func_00152538

/* func_00152ba8 (from auto/text_00150000_14.c). */
#define func_001528f0 ((M2C_UNK (*)(void *)) func_001528f0)
void func_00152ba8(void *arg0, void *arg1, f32 fparg0) {
    PlatVu0CopyVector(arg0 + 0x3C0, arg1);
    M2C_FIELD(arg0, f32 *, 0x3CC) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x3B4) = fparg0;
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    M2C_FIELD(arg0, f32 *, 0x3B8) = (f32) (-M2C_FIELD(arg1, f32 *, 4) / fparg0);
    func_0014f658(arg0, 3);
    func_001528f0(arg0);
}
#undef func_001528f0

/* func_00152c28 (from hand/text_00140000_s6_07.c). */
void func_00121fc4(f32 *, f32 *);
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
typedef struct { u8 pad[0x10]; f32 pos[4]; } O2c28;
#define func_00152ba8 ((void (*)(void *, f32 *, f32)) func_00152ba8)
void func_00152c28(O2c28 *o, f32 *dst, f32 g) {
    f32 v[4];
    f32 h;
    f32 a;
    f32 c;
    f32 t;
    f32 b;
    f32 k;

    PlatVu0SubVector(v, dst, o->pos);
    h = -v[1];
    v[1] = 0.0f;
    func_00121fc4(v, v);
    k = 0.5f;
    a = g * k;
    c = a * 4.0f * h;
    t = MIN(MAX(20.0f, v[3] / 20.0f), 30.0f);
    b = (-g * t) * k;
    t = (PlatSqrtf(b * b - c) - b) / (a + a);
    PlatVu0ScaleVector(v, v, MIN(v[3] / t, 20.0f));
    v[1] = b;
    func_00152ba8(o, v, g);
}
#undef func_00152ba8
#undef MAX
#undef MIN

/* func_00152d50 (from hand/text_00140000_h9.c). */
typedef struct Actor_52d50 {
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
} W9Ent_52d50;
typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} W9F4;
extern W9F4 D_00351930[];
#define func_00152ba8 ((void (*)(W9Ent_52d50 *e, f32 *v, f32 s)) func_00152ba8)
void func_00152d50(W9Ent_52d50 *e, s32 i, f32 *v) {
    f32 t[4];
    e->x144->w[8].i = i;
    PlatVu0ScaleVector(t, v, D_00351930[i].b);
    t[1] = D_00351930[i].c;
    func_00152ba8(e, t, D_00351930[i].d);
}
#undef func_00152ba8

/* func_00152dc8 (from hand/text_00140000_h9.c). */
typedef struct Actor_52dc8 {
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
} W9Ent_52dc8;
void func_00152dc8(W9Ent_52dc8 *e, s32 i) {
    e->x144->w[1].i = 3;
    e->x144->w[8].i = i;
    e->x144->d[0] &= ~2;
    e->x144->w[7].f = D_00351930[i].a;
}

/* func_001531c0 (from hand/text_00140000_h9.c). */
typedef struct Actor_531c0 {
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
} W9Ent_531c0;
extern f32 D_002BBDFC;
#define func_00152880 ((void (*)(W9Ent_531c0 *e)) func_00152880)
void func_001531c0(W9Ent_531c0 *e) {
    e->x144->w[6].f -= D_002BBDFC;
    if (e->x144->w[6].f < 0.0f) func_00152880(e);
}
#undef func_00152880

/* func_001532c8 (from hand/text_00140000_h9.c). */
typedef struct {
    u8 pad0[0x4C];
    u16 x4c;
} W9Obj130;
typedef struct {
    u8 pad0[0x130];
    W9Obj130 *x130;
} W9ObjB4;
typedef struct {
    s32 x0;
    W9ObjB4 *x4;
    union {
        u64 x;
        struct { u32 lo; u32 b0:10; u32 b10:1; u32 hi:21; } b;
    } x8;
} W9Obj;
s32 func_001532c8(W9Obj *o) {
    s32 r = 0;
    if (o->x4 && !o->x4->x130->x4c) r = !o->x8.b.b10;
    return r;
}

/* func_00153300 (from hand/text_00140000_h9.c). */
typedef struct Actor_53300 {
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
} W9Ent_53300;
s32 func_00153300(W9Ent_53300 *e, W9Obj *o) {
    s32 r = 0;
    if ((((s32 *)o)[3] & 0x1f) == 5) {
        if (func_001532c8(o)) r = e->x8c == 0;
    }
    return r;
}

/* func_001533d0 (from auto/text_00150000_17.c). */
M2C_UNK func_00156260(s32, void *);
void func_001533d0(s32 arg0, s32 arg1) {
    s32 sp[4];
    PlatVu0CopyVector(sp, arg1 + 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = 30.0f;
    func_00156260(arg0, sp);
}

/* func_00153500 (from hand/text_00140000_h9.c). */
typedef struct Actor_53500 {
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
} W9Ent_53500;
typedef union { u64 d; s32 w; struct { u32 lo; u32 x:6; u32 kind:4; u32 hi:22; } b; } F8M;
typedef struct { u8 pad[8]; F8M f8; } Msg9;
void func_00147138(W9Ent_53500 *, s32);
void func_00153360(W9Ent_53500 *, Msg9 *);
void func_00145008(W9Ent_53500 *, s32);
#define func_001533d0 ((void (*)(W9Ent_53500 *, Msg9 *)) func_001533d0)
void func_00153500(W9Ent_53500 *a, Msg9 *m) {
    s32 n;
    if (m->f8.b.kind == 1) func_00147138(a, 4);
    switch (m->f8.b.kind) {
    case 2:
        if (a->x144->w[17].f > 0.0f) {
            a->x144->w[1].i = 6;
            return;
        }
        func_00152598(a);
        return;
    case 3:
        a->x144->w[2].i = 0;
        func_001525f0(a);
        return;
    }
    if (func_00153300(a, (W9Obj *)m)) {
        func_00152598(a);
        func_00153360(a, m);
        return;
    } else {
        n = m->f8.w;
        if (n > 0) {
            a->x144->w[2].i += n;
            if (a->x144->w[2].i >= a->x144->w[3].i) {
                func_00145008(a, 0);
                a->x144->w[1].i = 6;
            } else {
                if (func_001532c8((W9Obj *)m)) func_00152598(a);
                func_001533d0(a, m);
            }
        }
    }
}
#undef func_001533d0

/* func_00153b68 (from hand/text_00140000_h9.c). */
typedef struct Actor_53b68 {
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
} W9Ent_53b68;
void func_00130398(W9Ent_53b68 *e, f32 s, s32 n);
void func_00153b68(W9Ent_53b68 *e, s32 a1, f32 *v) {
    s32 n;
    if (0.0f < v[3]) {
        v[3] = 3.0f;
        n = 185;
    } else {
        v[3] = 0.0f;
        n = 182;
    }
    func_00130398(e, 8.0f, n);
}

/* func_00153bb0 (from auto/text_00150000_18.c). */
f32 func_001376e8(s32, s32);
void func_00153bb0(s32 arg0, s32 arg1) {
    if ((M2C_FIELD(arg1, f32 *, 0) != 0.0f) && (M2C_FIELD(arg1, f32 *, 8) != 0.0f)) {
        func_001376e8(arg0, arg1);
        PlatVu0CopyVector(arg0 + 0x20, arg1);
        return;
    }
    PlatVu0CopyVector(arg0 + 0x20, arg0 + 0x30);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

/* func_00153c38 (from auto/text_00150000_2.c). */
s32 func_00153c38(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 2;
    if (arg1 == 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

/* func_00153d08 (from auto/text_00150000_3.c). */
void func_00153c50(s32, s32);
s32 func_00153d08(s32 arg0) {
    func_00153c50(arg0, 0);
    return 0;
}

/* func_00153d28 (from auto/text_00150000_5.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_00153d28(void) {
    func_0014f830(0x1C, 4, 0, 0, &func_00153bb0, 0, &func_00153c38, &func_00153b68, &func_00153d08);
}

/* func_00153d78 (from auto/text_00150000.c). */
s32 func_00153d78(Actor *arg0) {
    return arg0->unk088 & 0x30;
}

