/* Object class 8: the handlers func_0014e4b8 registers in the class table
 * D_00350D88 (func_0014f830(8, ...)) and their helpers. Flag mode: default
 * (the other modes are in the sibling files). Read from the code, not proved
 * by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/pieces/D_002E31B0.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350CE0.h"
#include "data/types/text_00140000_h57_p.h"
#include "data/types/text_00140000_h57.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_00350D78.h"
#include "data/pieces/D_002C58D0.h"
#include "data/types/text_00140000_h34.h"
#include "data/pieces/D_002E27C8.h"

/* func_0014d988 (from hand/text_00140000_s6_07.c). */
f32 func_0012ec60(struct Actor *, s32, f32 *);
void func_001315c0(void *, s32, f32 *, f32);
f32 func_00121748(f32 *, f32 *);
f32 func_00120c18(f32 *);
void func_0014d988(void *o, s32 unused, f32 *v, f32 r, f32 off, f32 scale, f32 lim) {
    f32 p[4];
    f32 d[4];
    f32 h;
    f32 s;
    f32 y;
    f32 z;
    f32 t;

    z = 0.0f;
    h = func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, d);
    func_001315c0(o, 0x8003, p, z);
    PlatVu0SubVector(d, d, p);
    if (r < func_00121748(d, v)) {
        s = (func_00120c18(d) - h - off) * scale;
        if (z < s) {
            y = d[1] / s * v[3];
            if (y < -lim) t = -lim; else if (lim < y) t = lim; else t = y;
            v[1] = t;
        }
    }
}

/* func_0014dab8 (from hand/text_00140000_h9.c). */
extern W9Tab12 D_00350D30[];
extern s32 D_002BC128;
extern s32 D_002BC130;
W9Tab12 *func_0014dab8(void) {
    W9Tab12 *p;
    for (p = D_00350D30; p->a >= 0; p++) {
        if (p->a == D_002BC128 && p->b == D_002BC130) return p;
    }
    return 0;
}

/* func_0014db20 (from hand/text_00140000_h9.c). */
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
typedef struct Actor_4db20 {
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
s32 func_0014db20(W9Ent *e) {
    W9Tab12 *p;
    if (e->x148) {
        p = func_0014dab8();
        if (p && e->x10[1] > p->f4) return 1;
    }
    return 0;
}

/* func_0014db78 (from hand/text_00140000_h9.c). */
typedef struct Actor_4db78 {
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
} W9Ent_4db78;
#define func_00120c18 ((f32 (*)(void *v)) func_00120c18)
void func_0014db78(W9Ent_4db78 *e, f32 *v) {
    f32 t[4];
    PlatVu0ScaleVector(t, v, v[3]);
    PlatVu0AddVector(t, e->x3c0, t);
    {
        f32 len = func_00120c18(t);
        if (16.0f < len) PlatVu0ScaleVector(t, t, 16.0f / len);
    }
    e->x3c0[0] = t[0];
    e->x3c0[2] = t[2];
}
#undef func_00120c18

/* func_0014dc08 (from hand/text_00140000_h9.c). */
typedef struct Actor_4dc08 {
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
} W9Ent_4dc08;
void func_0014dc08(W9Ent_4dc08 *e) {
    e->x6c->xcc.f = 0.06981316208839417f;
    e->x1cc &= ~1;
    PlatVu0ScaleVector(e->x3c0, e->x3c0, 0.29999998211860657f);
    if (e->x148) e->x148->x100 &= ~((u64)1 << 34);
}

/* func_0014dc90 (from hand/text_00140000_h9.c). */
typedef struct Actor_4dc90 {
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
} W9Ent_4dc90;
void func_00147338(s32 a, s32 b);
void func_0014dc90(W9Ent_4dc90 *e) {
    e->x6c->xcc.f = 0.19634954631328583f;
    e->x1cc |= 1;
    func_00147338(17108, e->x4 + 1);
}

/* func_0014dcd8 (from auto/text_00140000_4.c). */
s32 func_00130398(s32, s32, f32);
s32 func_0014f658(s32, s32);
void func_0014dcd8(Actor *arg0) {
    if (arg0->unk3D4 > 100.0f) {
        func_00130398(arg0, 0x75, 8.0f);
        func_0014f658(arg0, 8);
        arg0->unk3C4 = (f32) (arg0->unk3C4 * 0.3f);
        M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    }
}

/* func_0014dd48 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[0x100]; u64 f100; } Sub57_dd48;
typedef struct {
    u8 pad0[0x148];
    Sub57_dd48 *o148;
    u8 pad14c[0x3b0-0x14c];
    f32 f3b0;
} Obj57_dd48;
extern u32 D_002E3190;
f32 func_00121b08(f32);
#define func_0012ec60 ((f32 (*)(s32, s32, f32 *)) func_0012ec60)
#define func_001315c0 ((void (*)(void *, s32, f32 *, f32)) func_001315c0)
void func_0014dd48(Obj57_dd48 *o, s32 unused, f32 *v) {
    f32 b[4];
    f32 a[4];
    f32 h;
    f32 d;
    f32 t;

    if (v[3] > 0.0f) {
        if (v[3] < 0.799999967217f) v[3] = 8.0f;
        else v[3] = 16.0f;
    }
    if ((D_002E3190 >> 27) & 1) {
        v[1] = -8.0f;
    } else if ((D_002E3190 >> 28) & 1) {
        v[1] = 8.0f;
        goto skip;
    } else {
        v[1] = 0.0f;
    }
    if (o->o148) o->o148->f100 |= (u64)0x8000 << 19;
skip:
    if (D_002E31B8 >= 3 && v[3] > 0.0f && v[1] == 0.0f) {
        h = func_0012ec60((*(s32 (*)[2])&D_002E31B0)[0], (*(s32 (*)[2])&D_002E31B0)[1], a);
        func_001315c0(o, 0x8003, b, 0.0f);
        PlatVu0SubVector(a, a, b);
        if (func_00121748(a, v) > 0.5f) {
            d = (func_00120c18(a) - h - 200.0f) * 0.799999967217f;
            if (d > 0.0f) {
                t = a[1] / d * v[3];
                v[1] = t;
                if (t > 8.0f) v[1] = 8.0f;
                else if (t < -8.0f) v[1] = -8.0f;
            }
        }
    }
    o->f3b0 = func_00121b08(o->f3b0);
}
#undef func_0012ec60
#undef func_001315c0

/* func_0014df60 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[0xcc]; f32 fcc; } Prm57_df60;
typedef struct {
    u8 pad0[0x20];
    f32 v20[4];
    f32 v30[4];
    u8 pad40[0x6c-0x40];
    Prm57_df60 *prm;
    u8 pad70[0x164-0x70];
    s32 i164;
    u8 pad168[0x170-0x168];
    f32 f170;
    u8 pad174[0x178-0x174];
    s32 i178;
    u8 pad17c[0x3c0-0x17c];
    f32 v3c0[4];
    u8 pad3d0[0x440-0x3d0];
    u64 f440;
} Obj57_df60;
void func_00121fc4(f32 *, f32 *);
s32 func_001375f0(Obj57_df60 *);
f32 func_001376e8(void *, f32 *);
#define func_00130398 ((void (*)(void *, s32, f32)) func_00130398)
void func_0014df60(Obj57_df60 *o, f32 *v) {
    f32 t[4];
    f32 c[4];
    f32 spd;
    s32 id;

    if (v[0] != 0.0f || v[2] != 0.0f) {
        if (func_001375f0(o)) {
            o->prm->fcc = 0.0698131620884f;
        }
        func_001376e8(o, v);
    }
    spd = 16.0f;
    id = 117;
    if (v[3] > 0.0f) {
        if (v[3] > 8.0f) id = 119;
        else id = 118;
        PlatVu0CopyVector(t, o->v3c0);
        t[1] = 0.0f;
        func_00121fc4(t, t);
        if (t[3] >= 8.0f && PlatVu0InnerProduct(o->v30, t) < 0.866f) {
            id = 120;
            PlatVu0OuterProduct(c, o->v30, t);
            if (!(c[1] < 0.0f)) id = 121;
            if ((u32)(o->i164 - 120) < 2) spd = 24.0f;
        }
    } else if (v[1] > 0.0f) {
        id = 123;
    } else if (v[1] < 0.0f) {
        id = 122;
    }
    if (func_001375f0(o) && !((o->f440 >> 33) & 1)) {
        if (id == 117) {
            if (o->i178) goto end;
        } else if (o->f170 > 0.0f) goto end;
        func_00130398(o, id, spd);
    }
end:
    PlatVu0CopyVector(o->v20, v);
}
#undef func_00130398

/* func_0014e160 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[8]; f32 f8; } Tab57_e160;
typedef struct {
    u8 pad0[4];
    s32 i4;
    u8 pad8[0x14-8];
    f32 f14;
    u8 pad18[0x20-0x18];
    f32 v20[1];
    f32 f24;
    u8 pad28[0x2c-0x28];
    f32 f2c;
    u8 pad30[0x3c0-0x30];
    f32 v3c0[3];
    f32 f3cc;
} Obj57_e160;
extern f32 D_002BBDFC;
s32 func_0012c8e8(Obj57_e160 *);
void func_00147410(s32, s32, Obj57_e160 *);
void func_00147278(s32, s32, s32);
#define func_0014dab8 ((Tab57_e160 *(*)(void)) func_0014dab8)
void func_0014e160(Obj57_e160 *o, f32 *v) {
    f32 d;
    f32 y;
    f32 tgt;
    Tab57_e160 *p;

    d = func_00120c18(o->v3c0);
    if (o->f2c > 0.0f) {
        PlatVu0ScaleVector(v, o->v20, D_002BBDFC * 0.599999979138f);
        v[1] = 0.0f;
        PlatVu0AddVector(o->v3c0, o->v3c0, v);
    }
    PlatVu0CopyVector(v, o->v3c0);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    if (v[3] > o->f2c) {
        if (o->f2c < d) v[3] = d * 0.929999962449f;
        else v[3] = o->f2c;
    }
    PlatVu0ScaleVector(v, v, v[3]);
    o->v3c0[0] = v[0];
    o->v3c0[2] = v[2];
    if (o->v3c0[1] < o->f24) {
        o->v3c0[1] += D_002BBDFC * 0.35f;
        if (o->f24 < o->v3c0[1]) o->v3c0[1] = o->f24;
    } else if (o->f24 < o->v3c0[1]) {
        o->v3c0[1] -= D_002BBDFC * 0.35f;
        if (o->v3c0[1] < o->f24) o->v3c0[1] = o->f24;
    }
    PlatVu0ScaleVector(v, o->v3c0, D_002BBDFC);
    o->f3cc = o->f24;
    o->f24 = 0.0f;
    p = func_0014dab8();
    if (p && v[1] > 0.0f && p->f8 < o->f14 + v[1]) {
        v[1] = p->f8 - o->f14;
    }
    if (func_0012c8e8(o)) func_00147410(17108, o->i4 + 1, o);
    else func_00147278(17108, o->i4 + 1, 60);
}
#undef func_0014dab8

/* func_0014e3a0 (from hand/text_00140000_h9.c). */
typedef struct Actor_4e3a0 {
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
} W9Ent_4e3a0;
f32 func_0014cc88(W9Ent_4e3a0 *e, f32 s);
#define func_00130398 ((void (*)(W9Ent_4e3a0 *e, s32 n, f32 s)) func_00130398)
void func_0014e3a0(W9Ent_4e3a0 *e) {
    f32 s = 12.0f;
    PlatVu0ScaleVector(e->x3c0, e->x3c0, 0.7f);
    func_0014cc88(e, s);
    func_00130398(e, 6, s);
}
#undef func_00130398

/* func_0014e400 (from hand/text_00140000_h34.c). */
typedef struct { u8 pad[0x4c]; u16 x4c; } W34O130;
typedef struct { u8 pad[0x100]; union { u64 x; struct { u32 lo; u32 l2:2; u32 b34:1; u32 hi:29; } b; } x100; } W34T148b;
typedef struct {
    u8 pad[0x130];
    W34O130 *x130;
    u8 pad134[0x14];
    W34T148b *x148;
    u8 pad14c[0x370 - 0x14c];
    union { u64 x; struct { u32 lo; u32 l28:28; u32 b60:1; u32 hi:3; } b; } x370;
    u8 pad378[0x3cc - 0x378];
    f32 x3cc;
} W34Pl6;
#define func_0014e3a0 ((void (*)(W34Pl6 *)) func_0014e3a0)
s32 func_0014e400(W34Pl6 *o, s32 a) {
    W34T148b *t = o->x148;
    if ((t && t->x100.b.b34) || o->x3cc <= 0.0f || a) {
        if (t) t->x100.x &= ~(1LL << 34);
        return 8;
    }
    if (o->x130->x4c == 8) return 8;
    if (o->x370.b.b60) return 8;
    func_0014e3a0(o);
    return 2;
}
#undef func_0014e3a0

/* func_0014e4b8 (from auto/text_00140000_6.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, s32);
void func_0014e4b8(void) {
    func_0014f830(8, 0x76, &func_0014dc08, &func_0014dc90, &func_0014df60, &func_0014e160, &func_0014e400, &func_0014dd48, 0);
}

