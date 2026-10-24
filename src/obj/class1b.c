/* Object class 0x1B, default flags (docs/modules.md "Session 52"): the
 * handlers func_001524c8 registers in the class table D_00350D88
 * (func_0014f830(0x1B, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1b.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_002C58A0.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304BE8.h"

/* func_00150d30 (from hand/text_00140000_h9.c). */
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
typedef struct Actor_50d30 {
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
s32 func_0013c9e0(W9Ent *e);
void func_00243630(s32 a, W9Ent *e);
void func_00150d30(W9Ent *e) {
    s32 v = func_0013c9e0(e);
    func_00243630(v == 255 ? 2 : v == 12, e);
}

/* func_00150d70 (from auto/text_00150000_16.c). */
extern M2C_UNK D_0054F750;
void func_00137418(s32, f32);
void func_00150d70(void) {
    s8 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s0 = &D_0054F750;
    var_s1 = 7;
    do {
        temp_a0 = M2C_FIELD(var_s0, s32 *, 4);
        var_s1 -= 1;
        if ((temp_a0 != 0) && (M2C_FIELD(var_s0, s32 *, 0) == 0)) {
            func_00137418(temp_a0, 12.0f);
            M2C_FIELD(M2C_FIELD(var_s0, s32 *, 4), s32 *, 0x144) = 0;
            M2C_FIELD(var_s0, s32 *, 4) = 0;
        }
        var_s0 += 0x40;
    } while (var_s1 >= 0);
}

/* func_00151208 (from auto/text_00150000_23.c). */
extern void *D_0054F950;
void func_00151208(s32 arg0) {
  if ((D_0054F950 != 0) && ((*((f32 *) (((s8 *) D_0054F950) + 8))) < (*((f32 *) (((s8 *) arg0) + 0x14)))))
  {
 do { func_00137418(arg0, 12.0f); } while (0);
    *((s32 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x144)))) + 4)) = 0;
    *((void **) (((s8 *) arg0) + 0x144)) = 0;
  }
}

/* func_00151808 (from hand/text_00140000_h9.c). */
W9Tab12 *func_0014dab8(void);
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x38];
} W9Slot64;
extern W9Slot64 D_0054F750_00151808[] __asm__("D_0054F750");
#define D_0054F750 D_0054F750_00151808
extern W9Tab12 *D_0054F950_00151808 __asm__("D_0054F950");
#define D_0054F950 D_0054F950_00151808
void func_00151808(void) {
    s32 i;
    for (i = 7; i >= 0; i--) D_0054F750[i].x4 = 0;
    D_0054F740 = 0;
    D_0054F950 = func_0014dab8();
}
#undef D_0054F750
#undef D_0054F950

/* func_00151860 (from auto/text_00150000_2.c). */
M2C_UNK func_0012cc38(M2C_UNK, M2C_UNK);
M2C_UNK func_0012ccb0(M2C_UNK);
M2C_UNK func_00176310(s32);
extern s32 D_002C5958;
s32 func_0013c6a8(s16);
s32 func_00151860(void *arg0, void *arg1, s32 arg2) {
    f32 temp_f1;
    s32 temp_a0;

    if (arg2 != -2) {
        if ((arg2 == -1) && (M2C_FIELD(arg1, s32 *, 0x70) == 0) && (func_0013c6a8(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), s16 *, 0x48)) == 0)) {
            temp_f1 = M2C_FIELD(arg0, f32 *, 0x14) - M2C_FIELD(arg1, f32 *, 0x14);
            if ((temp_f1 > -50.0f) && (temp_f1 < 20.0f)) {
                func_0012cc38(3, 0x37);
                if (D_002C5958 & 1) {
                    func_0012ccb0(3);
                }
            }
        }
    } else {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x144);
        if (temp_a0 != 0) {
            func_00176310(temp_a0);
        }
    }
    return 0;
}

/* func_00151940 (from hand/text_00140000_h9.c). */
typedef struct Actor_51940 {
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
} W9Ent_51940;
W9Obj144 *func_00148a40(W9Ent_51940 *e, s32 a);
void func_00148068(W9Obj144 *p, f32 t);
void func_00151940(W9Ent_51940 *e) {
    W9Obj144 *p;
    if (!e->x4a0) {
        e->x4a0 = func_00151860;
        e->x144 = func_00148a40(e, 0);
    }
    p = e->x144;
    if (p) {
        if ((p->w[5].i & 3) != 1) {
            e->x144 = 0;
        } else if (e->x164.i) {
            func_00148068(p, 20.0f);
            e->x144 = 0;
        }
    }
}

/* func_00151b90 (from auto/text_00150000.c). */
void func_00151b90(void) {

}

/* func_00151e28 (from hand/text_00151e28_s7_w37.c). */
typedef struct { u8 pad[0x4c]; u16 x4c; } C130g;
typedef struct {
    u32 x0;
    u8 pad4[0x10 - 4];
    f32 pos[4];
    u8 pad20[0x30 - 0x20];
    f32 x30;
    u8 pad34[4];
    f32 x38;
    u8 pad3c[0x70 - 0x3c];
    s32 x70;
    u8 pad74[0x98 - 0x74];
    s32 x98;
    u8 pad9c[0x130 - 0x9c];
    C130g *x130;
} Tg;
typedef struct { u8 pad[8]; Tg *x8; u8 padc[4]; f32 pos[4]; } Og;
void func_00267530(f32 *, f32 *, f32 *);
f32 fabsf(f32);
s32 func_00151e28(Og *o) {
    f32 d[4];
    Tg *t = o->x8;
    f32 x;
    f32 lim;

    if (!t || t->x98 || t->x70 || t->x130->x4c || (t->x0 & 4)) return 0;
    func_00267530(d, o->pos, t->pos);
    lim = 10.0f;
    if (fabsf(d[1]) > lim) return 0;
    lim = 25.0f;
    x = d[0];
    if (fabsf(x) < lim) {
        f32 n = o->x8->x38;
        if (0.94f < n && 0.0f < d[2]) goto r1;
        if (!(n < -0.94f)) return 0;
        if (!(d[2] < 0.0f)) goto r0;
        return 1;
    } else if (fabsf(d[2]) < lim) {
        f32 n = o->x8->x30;
        if (0.94f < n && 0.0f < x) goto r1;
        if (!(n < -0.94f)) return 0;
        if (!(x < 0.0f)) goto r0;
        return 1;
    }
    return 0;
r1:
    return 1;
r0:
    return 0;
}

/* func_001520c0 (from auto/text_00150000.c). */
extern f32 D_002BBDFC;
void func_001520c0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x144);
    M2C_FIELD(temp_v1, f32 *, 8) = (f32) (M2C_FIELD(temp_v1, f32 *, 8) + D_002BBDFC);
}

/* func_001520e0 (from hand/text_00140000_h9.c). */
typedef struct Actor_520e0 {
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
} W9Ent_520e0;
#define func_0012cc38 ((void (*)(s32 a, s32 b)) func_0012cc38)
s32 func_001520e0(W9Ent_520e0 *e, s32 a1, s32 a2) {
    W9Ent_520e0 *p = D_002E26A0[0];
    if (a2 == -1 && e->x70 == 0 && e->x8c == 0 && p->x70 == 28) func_0012cc38(0, 29);
    return 0;
}
#undef func_0012cc38

/* func_00152370 (from hand/text_00140000_h9.c). */
typedef struct Actor_52370 {
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
} W9Ent_52370;
void func_00267560(void *out, void *in, f32 s);
void func_00267518(void *out, void *a, void *b);
void func_00152370(W9Ent_52370 *e, f32 *v) {
    if (e->x98) {
        func_00267560(e->x20, v, v[3] * D_002BBDFC);
        func_00267518(e->x98->x120, e->x98->x120, e->x20);
    }
}

/* func_001523e8 (from auto/text_00150000_16.c). */
M2C_UNK func_002675a8(s32, M2C_UNK *);
void func_001523e8(s32 arg0, s32 arg1) {
    func_002675a8(arg1, ((M2C_UNK *)&D_002C58A0));
}

/* func_00152408 (from hand/text_00140000_h9.c). */
typedef struct Actor_52408 {
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
} W9Ent_52408;
void func_00137318(W9Ent_52408 *e);
#define func_00267530 ((void (*)(void *out, void *a, void *b)) func_00267530)
s32 func_00152408(W9Ent_52408 *e, s32 a1) {
    f32 t[4];
    s32 r = 2;
    if (a1 == 0) {
        func_00267530(t, e->x10, e->x490);
        if (fabsf(t[0] - e->x120[0]) > 0.001f || fabsf(t[1] - e->x120[1]) > 0.001f ||
            fabsf(t[2] - e->x120[2]) > 0.001f) func_00137318(e);
        r = e->x70;
    }
    return r;
}
#undef func_00267530

/* func_001524a8 (from auto/text_00150000_2.c). */
void func_001524a8(void) {

}

/* func_001524b0 (from auto/text_00150000.c). */
#define func_00137318 ((M2C_UNK (*)()) func_00137318)
void func_001524b0(void) {
    func_00137318();
}
#undef func_00137318

/* func_001524c8 (from auto/text_00150000_4.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, s32);
void func_00152250();
void func_001524c8(void) {
    func_0014f830(0x1B, 0, &func_001524a8, &func_001524b0, &func_00152370, &func_001523e8, &func_00152408, &func_00152250, 0);
}

