/* Object class 0x1A, default flags (docs/modules.md "Session 52"): the
 * handlers func_00150cd8 registers in the class table D_00350D88
 * (func_0014f830(0x1A, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1a.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "m2c.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00304BE8.h"
#include "data/types/text_00140000_h57_p.h"
#include "data/types/text_00140000_h57.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350D78.h"
#include "data/pieces/D_002C58D0.h"

/* func_001501c0 (from hand/text_00140000_h9.c). */
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
typedef struct Actor_501c0 {
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
void func_00137318(W9Ent *e);
void func_001501c0(W9Ent *e) {
    func_00137318(e);
    e->x144->w[0].i = 4;
    e->x144->w[2].i = 0;
    e->flags |= 0x20;
}

/* func_00150208 (from auto/text_00150000_3.c). */
s32 func_0012cc38(s32, s32);
s32 func_0012ccb0(s32);
s32 func_00137618(s32);
void func_00121eb0(s32);
s32 func_00150208(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;

    switch (arg2) {                                 /* switch 1; irregular */
    case -1:                                        /* switch 1 */
        if (M2C_FIELD(arg1, s32 *, 0x98) == arg0) {
            func_0012cc38(0, 0x44);
            func_0012ccb0(0);
        } else if ((func_00137618(arg0) != 0) && (M2C_FIELD(arg0, s32 *, 0x164) == 1)) {
            temp_a1 = M2C_FIELD(arg1, s32 *, 0x70);
            switch (temp_a1) {                      /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                func_0012cc38(3, 0x45);
                break;
            case 26:                                /* switch 2 */
                func_0012cc38(0, 0x44);
                break;
            }
        }
        break;
    case -2:                                        /* switch 1 */
        func_00121eb0(M2C_FIELD(arg0, s32 *, 0x144));
        break;
    }
    return 0;
}

/* func_00150660 (from auto/text_00150000.c). */
#define func_00137318 ((M2C_UNK (*)()) func_00137318)
void func_00150660(void) {
    func_00137318();
}
#undef func_00137318

/* func_001507d0 (from hand/text_00140000_h57.c). */
typedef struct { u8 x[20]; } Col57_07d0;
typedef struct { u8 pad0[4]; u8 n[4]; u8 pad8[8]; Col57_07d0 *cols[4]; } ColSet57_07d0;
typedef struct { u8 pad0[0x54]; s8 kind; } Info57_07d0;
typedef struct { u8 pad0[0xc]; f32 fc; } Sub57_07d0;
typedef struct { u8 pad0[0x140]; s32 i140; } Sub148_07d0;
typedef struct {
    u8 pad0[0x130];
    Info57_07d0 *info;
    ColSet57_07d0 *cs;
    u8 pad138[0x144-0x138];
    Sub57_07d0 *o144;
    Sub148_07d0 *o148;
    u8 pad14c[0x164-0x14c];
    u32 i164;
} Chr57_07d0;
void func_0015bad0(Chr57_07d0 *, Col57_07d0 *, f32 *);
s32 func_0015b998(f32 *, f32 *);
Chr57_07d0 *func_001230a0(Chr57_07d0 *);
s32 func_00123330(Chr57_07d0 *);
void func_00150678(Chr57_07d0 *, Chr57_07d0 *);
s32 func_001507d0(Chr57_07d0 *o) {
    f32 a[8];
    f32 b[8];
    Chr57_07d0 *p;
    Col57_07d0 *c;
    s32 n;
    s32 i;

    p = 0;
    func_0015bad0(o, o->cs->cols[0], a);
    while ((p = func_001230a0(p)) != 0) {
        if (p->info->kind != 11) continue;
        if (!func_00123330(p)) continue;
        if (p->i164 >= 2) continue;
        if (p->o144 && p->o144->fc > 0.0f) continue;
        n = p->cs->n[3];
        c = p->cs->cols[3];
        for (i = 0; i < n; i++, c++) {
            if ((c->x[0] & 0xf) != 3) continue;
            func_0015bad0(p, c, b);
            if (func_0015b998(a, b)) {
                o->o148->i140 = i;
                func_00150678(o, p);
                return 1;
            }
        }
    }
    return (s32)p;
}

/* func_00150930 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[0x54]; s8 kind; } Info57_0930;
typedef struct { u8 pad0[0xc]; f32 fc; } Sub57_0930;
typedef struct { u8 pad0[4]; f32 f4; } Ret57_0930;
typedef struct { u8 pad0[8]; f32 f8; } Prm57_0930;
typedef struct Chr57_0930 {
    u8 pad0[0x10];
    f32 v10[4];
    u8 pad20[0x6c-0x20];
    Prm57_0930 *prm;
    u8 pad70[0x98-0x70];
    struct Chr57_0930 *o98;
    u8 pad9c[0x130-0x9c];
    Info57_0930 *info;
    u8 pad134[0x144-0x134];
    Sub57_0930 *o144;
    u8 pad148[0x3b0-0x148];
    f32 f3b0;
    f32 f3b4;
    f32 f3b8;
    u8 pad3bc[4];
    f32 v3c0[1];
    f32 f3c4;
    u8 pad3c8[4];
    f32 f3cc;
} Chr57_0930;
void func_00121fc4(f32 *, f32 *);
void func_001376e8(void *, f32 *);
void func_0012ec88();
Ret57_0930 *func_0014cb90(Chr57_0930 *);
s32 func_0014f658(Chr57_0930 *, s32);
void func_00150930(Chr57_0930 *o, Chr57_0930 *t, f32 *v) {
    f32 a[4];
    f32 h;
    f32 d;
    f32 k;
    f32 vy;

    if (o->o98 && o->o98->info->kind == 11) o->o98->o144->fc = 180.0f;
    func_0014cb90(o)->f4 = 4.0f;
    func_0012ec88(t, a);
    if (t->info->kind == 11) {
        a[0] = t->v10[0];
        a[2] = t->v10[2];
        a[1] += 120.0f;
    }
    PlatVu0SubVector(v, a, o->v10);
    h = v[1];
    v[1] = 0.0f;
    func_00121fc4(v, v);
    d = v[3];
    k = (d / o->prm->f8 > 30.0f) ? d / o->prm->f8 : 30.0f;
    vy = (h - k * 0.484693862498f * k * 0.5f) / k;
    PlatVu0ScaleVector(o->v3c0, v, d / k);
    o->f3b4 = 0.484693862498f;
    o->f3cc = 0.99f;
    o->f3b0 = 0.0f;
    o->f3c4 = vy;
    o->f3b8 = -vy / 0.484693862498f;
    func_0014f658(o, 3);
    func_001376e8(o, v);
}

/* func_00150af0 (from hand/text_00140000_h9.c). */
typedef struct Actor_50af0 {
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
} W9Ent_50af0;
extern f32 D_002C5970;
void func_0014cce0(W9Ent_50af0 *e, f32 s);
#define func_00121fc4 ((void (*)(void *dst, void *src)) func_00121fc4)
#define func_0014cb90 ((W9Obj144 *(*)(W9Ent_50af0 *e)) func_0014cb90)
void func_00150af0(W9Ent_50af0 *e, f32 *v) {
    func_0014cb90(e)->w[1].f = 4.0f;
    func_0014cce0(e, e->x6c->x10);
    PlatVu0CopyVector(v, e->x148->x130);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    v[3] *= D_002C5970;
}
#undef func_00121fc4
#undef func_0014cb90

/* func_00150b70 (from hand/text_00140000_h9.c). */
typedef struct Actor_50b70 {
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
} W9Ent_50b70;
#define func_0014cb90 ((W9Obj144 *(*)(W9Ent_50b70 *e)) func_0014cb90)
#define func_0014cce0 ((void (*)(W9Ent_50b70 *e, f32 s)) func_0014cce0)
void func_00150b70(W9Ent_50b70 *e) {
    f32 t[4];
    if (e->x98) return;
    func_0014cb90(e)->w[1].f = 4.0f;
    PlatVu0CopyVector(t, e->x148->x130);
    t[1] = 0.0f;
    PlatVu0ScaleVector(e->x3c0, t, D_002C5970);
    func_0014cce0(e, 10.0f);
    e->flags &= ~0x400;
}
#undef func_0014cb90
#undef func_0014cce0

/* func_00150bf8 (from auto/text_00150000_16.c). */
s32 func_00130398(s32, s32, f32);
s32 func_00150bf8(s32 arg0) {
    return func_00130398(arg0, 0xBF, 0.0f);
}

/* func_00150c18 (from hand/text_00140000_h9.c). */
typedef struct Actor_50c18 {
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
} W9Ent_50c18;
#define func_0015bad0 ((void (*)(W9Obj98 *o, void *ent, f32 *out)) func_0015bad0)
void func_00150c18(W9Ent_50c18 *e, f32 *out) {
    f32 m[2][4];
    func_0015bad0(e->x98, e->x98->x134->x1c + e->x148->x140 * 20, m[0]);
    PlatVu0SubVector(out, m[1], e->x10);
    out[1] += 120.0f;
    if (e->x164.i == 191) PlatVu0CopyVector(e->x148->x130, out);
}
#undef func_0015bad0

/* func_00150cb0 (from auto/text_00150000_2.c). */
s32 func_00150cb0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}

/* func_00150cb8 (from auto/text_00150000.c). */
#define func_00150af0 ((M2C_UNK (*)()) func_00150af0)
s32 func_00150cb8(void) {
    func_00150af0();
    return 0;
}
#undef func_00150af0

/* func_00150cd8 (from auto/text_00150000_3.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_00150cd8(void) {
    func_0014f830(0x1A, 5, 0, &func_00150660, &func_00150bf8, &func_00150c18, &func_00150cb0, &func_00150b70, &func_00150cb8);
}

