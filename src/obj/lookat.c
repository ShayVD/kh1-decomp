/* An entity's look-at: func_0014f9b0 / func_0014fa38 start and stop turning
 * toward a point (x1f0, the bit 33 of x470, its speed x45c), func_0014fab0 /
 * func_0014fc68 the angle to a bone or object within a limit, func_0014fe48
 * the per-frame turn. Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "data/types/text_00140000_h57_p.h"
#include "data/types/text_00140000_h57.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350D78.h"
#include "data/pieces/D_002C58D0.h"

/* func_0014f9b0 (from hand/text_00140000_h9.c). */
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
typedef struct Actor_4f9b0 {
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
void func_0014f9b0(W9Ent *e, f32 *src, f32 t) {
    PlatVu0CopyVector(e->x1f0, src);
    if (0.0f < t) {
        e->x1f0[3] = 0.0f;
        e->x45c = 1.0f / t;
    } else {
        e->x45c = 0.0f;
        e->x1f0[3] = 1.0f;
    }
    e->x470 |= (u64)1 << 33;
}

/* func_0014fa38 (from hand/text_00140000_h9.c). */
typedef struct Actor_4fa38 {
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
} W9Ent_4fa38;
void func_0014fa38(W9Ent_4fa38 *e, f32 t) {
    if ((s32)(e->x470 >> 33) & 1) {
        if (0.0f < t) {
            e->x470 |= (u64)1 << 33;
            e->x45c = -e->x1f0[3] / t;
        } else {
            e->x470 &= ~((u64)1 << 33);
        }
    }
}

/* func_0014fab0 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[0x2c]; f32 f2c; f32 f30; f32 f34; f32 f38; } Prm57_fab0;
typedef struct {
    u8 pad0[0x6c];
    Prm57_fab0 *prm;
    u8 pad70[0xd0-0x70];
    f32 md0[16];
} Obj57_fab0;
f32 atan2f(f32, f32);
void func_00121fc4(f32 *, f32 *);
void func_001315c0(void *, s32, f32 *, f32);
f32 func_0012ec88();
f32 asinf(f32);
f32 func_0014fab0(Obj57_fab0 *o, s32 id, f32 *dir, f32 lim) {
    f32 a[4];
    f32 b[4];
    f32 ang[4];
    f32 m[16];
    f32 len;

    func_001315c0(o, 0, a, 0.5f);
    func_0012ec88(id, b);
    PlatVu0SubVector(dir, b, a);
    func_00121fc4(dir, dir);
    len = dir[3];
    PlatVu0TransposeMatrix(m, o->md0);
    dir[3] = 0.0f;
    PlatVu0ApplyMatrix(dir, m, dir);
    if (lim < dir[2]) return 0.0f;
    ang[1] = atan2f(-dir[0], -dir[2]);
    ang[2] = asinf(dir[1]);
    if (ang[2] < 0.0f) {
        if (ang[2] < -o->prm->f2c) ang[2] = -o->prm->f2c;
    } else {
        if (o->prm->f30 < ang[2]) ang[2] = o->prm->f30;
    }
    if (ang[1] < 0.0f) {
        if (ang[1] < -o->prm->f34) ang[1] = -o->prm->f34;
    } else {
        if (o->prm->f38 < ang[1]) ang[1] = o->prm->f38;
    }
    PlatVu0RotMatrixX(m, D_002C58D0[0], ang[2]);
    PlatVu0RotMatrixY(m, m, ang[1]);
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = -1.0f;
    dir[3] = 0.0f;
    PlatVu0ApplyMatrix(dir, m, dir);
    return len;
}

/* func_0014fc68 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[0x2c]; f32 f2c; f32 f30; f32 f34; f32 f38; } Prm57_fc68;
typedef struct {
    u8 pad0[0x6c];
    Prm57_fc68 *prm;
    u8 pad70[0xd0-0x70];
    f32 md0[16];
    u8 pad110[0x460-0x110];
    f32 v460[4];
} Obj57_fc68;
f32 func_0014fc68(Obj57_fc68 *o, s32 id, f32 *dir, f32 lim) {
    f32 a[4];
    f32 b[4];
    f32 ang[4];
    f32 m[16];
    f32 len;

    func_001315c0(o, 0, a, 0.5f);
    func_0012ec88(id, b);
    PlatVu0InterVector(b, o->v460, b, 0.9f);
    PlatVu0CopyVector(o->v460, b);
    PlatVu0SubVector(dir, b, a);
    func_00121fc4(dir, dir);
    len = dir[3];
    PlatVu0TransposeMatrix(m, o->md0);
    dir[3] = 0.0f;
    PlatVu0ApplyMatrix(dir, m, dir);
    if (lim < dir[2]) return 0.0f;
    ang[1] = atan2f(-dir[0], -dir[2]);
    ang[2] = asinf(dir[1]);
    if (ang[2] < 0.0f) {
        if (ang[2] < -o->prm->f2c) ang[2] = -o->prm->f2c;
    } else {
        if (o->prm->f30 < ang[2]) ang[2] = o->prm->f30;
    }
    if (ang[1] < 0.0f) {
        if (ang[1] < -o->prm->f34) ang[1] = -o->prm->f34;
    } else {
        if (o->prm->f38 < ang[1]) ang[1] = o->prm->f38;
    }
    PlatVu0RotMatrixX(m, D_002C58D0[0], ang[2]);
    PlatVu0RotMatrixY(m, m, ang[1]);
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = -1.0f;
    dir[3] = 0.0f;
    PlatVu0ApplyMatrix(dir, m, dir);
    return len;
}

