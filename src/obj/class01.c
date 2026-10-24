/* Object classes 1, 2, 3 and 5: the handlers func_0014d890 registers in the
 * class table D_00350D88 (func_0014f830(1 / 2 / 3 / 5, ...)) and their
 * helpers (class 1's func_00126e80 is elsewhere). Flag mode: default (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h57_p.h"
#include "data/types/text_00140000_h57.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350D78.h"
#include "data/pieces/D_002C58D0.h"
#include "platform/math.h"
#include "data/types/text_00140000_h34.h"
#include "data/pieces/D_002E27C8.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "m2c.h"
#include "actor.h"

/* func_0014cee8 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[8]; f32 f8; u8 pad0c[0x14-0xc]; f32 f14; f32 f18; } Prm57_cee8;
typedef struct {
    s32 flags;
    u8 pad4[0x14-4];
    f32 f14;
    u8 pad18[0x20-0x18];
    f32 v20[3];
    f32 f2c;
    u8 pad30[0x6c-0x30];
    Prm57_cee8 *prm;
    u8 pad70[0x124-0x70];
    f32 f124;
    u8 pad128[0x3b0-0x128];
    f32 f3b0;
    f32 f3b4;
    f32 f3b8;
    u8 pad3bc[4];
    f32 v3c0[4];
} Obj57_cee8;
extern f32 D_002BBDFC;
void func_00121fc4(f32 *, f32 *);
f32 func_00120c18(f32 *);
void func_0014cdc8(Obj57_cee8 *, f32 *);
void func_0014cee8(Obj57_cee8 *o, f32 *v) {
    f32 d;

    if (o->flags & 0x1000) {
        o->f3b0 = o->f3b8 = 0.0f;
        o->f3b4 = o->f14;
        PlatVu0CopyVector(v, (*(f32 (*)[0x4])&D_002C58A0));
    } else {
        if (o->f2c > 0.0f) {
            d = func_00120c18(o->v3c0);
            PlatVu0ScaleVector(v, o->v20, o->f2c * o->prm->f14);
            PlatVu0AddVector(v, v, o->v3c0);
            v[1] = 0.0f;
            func_00121fc4(v, v);
            if (!(o->prm->f8 < d)) d = o->prm->f8;
            if (d < v[3]) v[3] = d;
            PlatVu0ScaleVectorXYZ(v, v, v[3]);
        } else {
            PlatVu0ScaleVector(v, o->v3c0, o->prm->f18);
        }
        PlatVu0CopyVector(o->v3c0, v);
        PlatVu0ScaleVectorXYZ(v, v, D_002BBDFC);
        o->f3b0 += D_002BBDFC;
        func_0014cdc8(o, v);
    }
    o->f3b4 += o->f124;
}

/* func_0014d070 (from hand/text_00140000_h34.c). */
s32 func_00130340(void *, s32, f32);
void func_00130578(void *, s32, f32);
f32 func_0014cc88(void *, f32);
typedef struct {
    u8 pad[0x70];
    s32 x70;
    u8 pad74[0x2a0 - 0x74];
    f32 x2a0[4];
    u8 pad2b0[0x20];
    s32 x2d0;
    u8 pad2d4[0xc];
    f32 x2e0[4];
    u8 pad2f0[0x3b4 - 0x2f0];
    f32 x3b4;
    u8 pad3b8[0x3c4 - 0x3b8];
    f32 x3c4;
    u8 pad3c8[8];
    s32 x3d0;
} W34Pl4;
void func_0014d070(W34Pl4 *o, f32 *b) {
    f32 v[4] __attribute__((aligned(16)));
    PlatVu0SubVector(v, o->x2e0, o->x2a0);
    if (b[1] < v[1]) {
        switch (o->x70) {
        case 2:
            o->x3b4 += v[1] - b[1];
            if (b[1] < 0.0f && (o->x2d0 & 8)) {
                func_0014cc88(o, 0.0f);
                o->x3b4 = o->x2e0[1];
                func_00130340(o, o->x3d0 + 5, 6.0f);
                func_00130578(o, o->x3d0 + 6, 0.0f);
            }
            break;
        case 3:
            if (b[1] < 0.0f && (o->x2d0 & 8)) o->x3c4 = 0.0f;
            break;
        }
    }
}

/* func_0014d180 (from hand/text_00140000_h9.c). */
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
typedef struct Actor_4d180 {
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
s32 func_00137618(void *);
s32 func_0014d180(W9Ent *e) {
    s32 r;
    s32 f, g;
    r = func_00137618(e);
    if (r) {
        f = e->flags;
        g = f & 4;
        if ((f & 0x10000) && e->x3b0 < 15.0f) return 0;
        r = 0;
        if (e->x3b8 == 0.0f || e->x3b8 + 6.0f < e->x3b0) r = g == 0;
    }
    return r;
}

/* func_0014d210 (from hand/text_00140000_h34.c). */
void func_00130398(void *, s32, f32);
f32 atan2f(f32, f32);
typedef struct { u32 x0; u8 pad4[0x1c]; f32 x20[4]; u8 pad30[0x150 - 0x30]; f32 x150; u8 pad154[0x10]; s32 x164; } W34Pl5;
extern s32 D_002C5C54;
s32 func_00140370(W34Pl5 *, f32 *);
s32 func_0013f618(W34Pl5 *, f32 *);
s32 func_0015cc48(W34Pl5 *, f32 *);
s32 func_001507d0(W34Pl5 *, f32 *);
s32 func_00144510(W34Pl5 *, f32 *);
#define func_0014d180 ((s32 (*)(W34Pl5 *)) func_0014d180)
void func_0014d210(W34Pl5 *o, f32 *v) {
    if (!(o->x0 & 0x2000) && func_0014d180(o)) {
        if (func_00140370(o, v)) return;
        if (func_0013f618(o, v)) return;
        if (!D_002C5C54 && func_0015cc48(o, v)) return;
        if (func_001507d0(o, v)) return;
    }
    if (func_00144510(o, v)) return;
    if (v[3] > 0.0f && !(o->x0 & 0x400)) {
        o->x150 = atan2f(v[0], v[2]);
        if (o->x164 == 220) func_00130398(o, 6, 8.0f);
    }
    PlatVu0CopyVector(o->x20, v);
}
#undef func_0014d180

/* func_0014d330 (from hand/text_00140000_h9.c). */
typedef struct Actor_4d330 {
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
} W9Ent_4d330;
extern u32 D_002C5958;
s32 func_001443a8(W9Ent_4d330 *e);
s32 func_0014db20(W9Ent_4d330 *e);
s32 func_0014d330(W9Ent_4d330 *e, s32 a1) {
    s32 f;
    if (a1 == 0 && func_001443a8(e) == 0) {
        f = e->flags;
        if (!(f & 0x1000)) goto L;
    }
    if ((D_002C5958 >> 5) & 1) {
        if (func_0014db20(e)) {
            e->flags &= ~4;
            return 8;
        }
    }
    return e->x70;
L:
    return (f & 0x2000) ? 6 : 0;
}

/* func_0014d3c8 (from auto/text_00140000_16.c). */
M2C_UNK func_0014c530();
M2C_UNK func_0014dcd8();
s32 func_0014d3c8(void *a) {
  unsigned long long new_var;
  if ((D_002C5958 >> 5) & 1)
  {
    func_0014dcd8(a);
  }
  else
  {
    new_var = (u64) (*(u8 *)&D_002E27C8);
    if ((new_var >> 7) != 0)
    {
      func_0014c530(a);
    }
  }
  return 0;
}

/* func_0014d428 (from auto/text_00140000_6.c). */
M2C_UNK func_0014f658(void *, M2C_UNK);
void func_0014d428(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
    f32 temp_f0;
    f32 temp_f20;

    PlatVu0CopyVector(arg0 + 0x3C0, arg1);
    M2C_FIELD(arg0, f32 *, 0x3CC) = fparg0;
    temp_f20 = fparg1 * 0.5f;
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    temp_f0 = (2.0f * M2C_FIELD(arg1, f32 *, 4)) / (temp_f20 * temp_f20);
    M2C_FIELD(arg0, f32 *, 0x3B8) = temp_f20;
    M2C_FIELD(arg0, f32 *, 0x3B4) = temp_f0;
    M2C_FIELD(arg0, f32 *, 0x3C4) = (f32) (-temp_f0 * temp_f20);
    if (M2C_FIELD(arg0, s32 *, 0x70) == 4) {
        func_0014f658(arg0, 5);
        M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) M2C_FIELD(arg0, f32 *, 0x3D4);
    } else {
        func_0014f658(arg0, 3);
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFFEFFFF);
}

/* func_0014d4f8 (from auto/text_00140000_16.c). */
void func_0014d4f8(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
  f32 *new_var;
  f32 *new_var2;
  PlatVu0CopyVector(arg0 + 0x3C0, arg1);
  *((f32 *) (((s8 *) arg0) + 0x3CC)) = fparg0;
  *((f32 *) (((s8 *) arg0) + 0x3B4)) = fparg1;
  new_var2 = (f32 *) (((s8 *) arg0) + 0x3B8);
  new_var = (s32 *) (((s8 *) arg0) + 0x3B0);
  *new_var = 0;
  new_var = (f32 *) (((s8 *) arg1) + 4);
  *new_var2 = (f32) ((-(*new_var)) / fparg1);
  func_0014f658(arg0, 3);
}

/* func_0014d570 (from hand/text_00140000_s6_07.c). */
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void func_0014d570(f32 *v, f32 lo, f32 hi, f32 max, f32 g) {
    f32 h;
    f32 a;
    f32 c;
    f32 t;
    f32 b;
    f32 k;

    h = -v[1];
    v[1] = 0.0f;
    func_00121fc4(v, v);
    k = 0.5f;
    a = g * k;
    c = a * 4.0f * h;
    t = MIN(MAX(lo, v[3] / max), hi);
    b = (-g * t) * k;
    t = (PlatSqrtf(b * b - c) - b) / (a + a);
    PlatVu0ScaleVector(v, v, MIN(v[3] / t, max));
    v[1] = b;
}
#undef MAX
#undef MIN

/* func_0014d6b0 (from auto/text_00140000_10.c). */
M2C_UNK func_0014cd38(void *);
void func_0014d6b0(void *arg0, s32 arg1) {
    f32 temp_f3;

    PlatVu0ScaleVectorXYZ(arg1, arg0 + 0x3C0, D_002BBDFC);
    M2C_FIELD(arg0, f32 *, 0x3C0) = (f32) (M2C_FIELD(arg0, f32 *, 0x3C0) * M2C_FIELD(arg0, f32 *, 0x3CC));
    temp_f3 = M2C_FIELD(arg0, f32 *, 0x3C4) + (M2C_FIELD(arg0, f32 *, 0x3B4) * D_002BBDFC);
    M2C_FIELD(arg0, f32 *, 0x3C8) = (f32) (M2C_FIELD(arg0, f32 *, 0x3C8) * M2C_FIELD(arg0, f32 *, 0x3CC));
    M2C_FIELD(arg0, f32 *, 0x3C4) = temp_f3;
    if (temp_f3 > 20.0f) {
        M2C_FIELD(arg0, f32 *, 0x3C4) = 20.0f;
    }
    M2C_FIELD(arg0, f32 *, 0x3B0) = (f32) (M2C_FIELD(arg0, f32 *, 0x3B0) + D_002BBDFC);
    func_0014cd38(arg0);
}

/* func_0014d760 (from auto/text_00140000_10.c). */
s32 func_0014d760(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (arg1 != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

/* func_0014d778 (from auto/text_00140000_2.c). */
s32 func_0014d778(void *arg0, s32 arg1) {
    if ((M2C_FIELD(arg0, f32 *, 0x3C4) >= 0.0f) && ((M2C_FIELD(arg0, f32 *, 0x3D4) <= M2C_FIELD(arg0, f32 *, 0x3BC)) || (arg1 == 0))) {
        return 4;
    }
    return M2C_FIELD(arg0, s32 *, 0x70);
}

/* func_0014d7b8 (from auto/text_00140000_17.c). */
f32 func_0014cce0(s32, f32);
#define func_0014f658 ((s32 (*)(s32, s32)) func_0014f658)
void func_0014d7b8(s32 arg0, s32 arg1) {
  f32 temp_f1;
  s32 temp_s0;
  s32 temp_v1;
  temp_f1 = *((f32 *) (((s8 *) arg0) + 0x3B0));
  if (temp_f1 >= 4.0f)
  {
    temp_v1 = *((s32 *) (((s8 *) arg0) + 0x164));
    if ((temp_v1 != 4) && (temp_v1 != 9))
    {
      func_0014f658(arg0, 0);
      *((s32 *) (((s8 *) arg1) + 0xC)) = 0;
    }
    else
    {
      temp_s0 = *((s32 *) (((s8 *) arg0) + 0x3D0));
      func_0014cce0(arg0, *((f32 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x6C)))) + 0x10)));
      *((s32 *) (((s8 *) arg0) + 0x3D0)) = temp_s0;
    }
    *((s32 *) (((s8 *) arg0) + 0)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0))) | 0x60000);
  }
  else
  {
    *((f32 *) (((s8 *) arg0) + 0x3B0)) = (f32) (temp_f1 + D_002BBDFC);
 do { *((s32 *) (((s8 *) arg1) + 0xC)) = 0; } while (0);
  }
  PlatVu0CopyVector(arg0 + 0x20, arg1);
}
#undef func_0014f658

/* func_0014d878 (from auto/text_00140000_10.c). */
s32 func_0014d878(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 2;
    if (arg1 == 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

/* func_0014d890 (from auto/text_00140000_7.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_00126e80();
void func_0014d890(void) {
    func_0014f830(1, 0x34, 0, 0, &func_0014d7b8, NULL, &func_0014d878, &func_00126e80, NULL);
    func_0014f830(2, 0x3D, 0, 0, &func_0014d210, &func_0014cee8, &func_0014d330, NULL, &func_0014d3c8);
    func_0014f830(3, 5, 0, 0, &func_0014d210, &func_0014d6b0, &func_0014d760, NULL, NULL);
    func_0014f830(5, 2, 0, 0, NULL, &func_0014d6b0, &func_0014d778, NULL, NULL);
}

