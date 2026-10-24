/* The objects' update tasks: func_00138400 picks an object's update task and
 * priority by its kind, func_00137ea8 / func_00138130 / func_00138258 are
 * the updates (the current object D_00304AD8, the lists D_0052AA58 /
 * D_0052AA68 / D_0052AA70), and small per-frame helpers (func_00137748
 * bobbing, func_00137868). Flag mode: default (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/types/text_00130000_h32.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002E2700.h"
#include "m2c.h"
#include "actor.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00350CE0.h"
#include "data/types/text_00130000_h32_p.h"
#include "data/pieces/D_00304AD8.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00304B6C.h"

/* func_00137718 (from hand/text_00130000_h6.c). */
typedef struct {
    u32 flags;
    u8 pad04[0x2C - 0x4];
    f32 f2c;
    u8 pad30[0x88 - 0x30];
    u32 x88;
} W6Flg;
s32 func_00137718(W6Flg *f) {
    if (f->flags & 4) {
        return 0;
    }
    if (f->f2c == 0.0f) {
        return 0;
    }
    return 1;
}

/* func_00137748 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad000[0x6C];
    u32 *x6c;
    u8 pad070[0x88 - 0x70];
    u32 x88;
    u8 pad08c[0x164 - 0x8C];
    s32 x164;
    u8 pad168[0x480 - 0x168];
    f32 x480;
    f32 x484;
} W32Bob;
f32 sinf(f32 x);
f32 func_00120c88(f32 x);
void func_00137748(W32Bob *o) {
    f32 t;
    if (o->x164 == 0x66 || o->x164 == 0x68 || o->x164 == 0x67) return;
    if (*o->x6c & 1) return;
    if (o->x88 & 4) {
        t = (o->x480 - 0.7999999523162842f) * 0.95f + 0.7999999523162842f;
        o->x480 = t - sinf(o->x484) * 0.05f;
        o->x484 = func_00120c88(o->x484 + 1.5707964f);
    } else {
        if (o->x480 < 1.0f) {
            o->x480 += 0.05f;
            if (o->x480 > 1.0f) o->x480 = 1.0f;
        }
        o->x484 = 0.0f;
    }
    o->x88 &= ~4;
}

/* func_00137868 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad00[0x54];
    s8 x54;
} W32Info;
typedef struct {
    u8 pad00[0x1C];
    s32 x1c;
} W32Sub2;
typedef struct {
    u8 pad000[0x6C];
    s32 x6c;
    u8 pad070[0x130 - 0x70];
    W32Info *x130;
    u8 pad134[0x144 - 0x134];
    s32 x144;
    s32 x148;
    W32Sub2 *x14c;
    u8 pad150[0x370 - 0x150];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x400 - 0x39C];
    s32 x400;
} W32Ch;
void func_0012b9b0(s32 a);
void func_00121eb0(s32 a);
s32 func_00137330(W32Ch *o, s32 a, s32 b);
void func_00141ab8(s32 a);
void func_00176310(s32 a);
void func_00145240(W32Ch *o);
void func_00137448(W32Ch *o);
void func_00135658(W32Ch *o);
void func_00137868(W32Ch *o) {
    if ((s32)(o->x370 >> 48) & 1) {
        if (o->x144) func_0012b9b0(o->x144);
    } else {
        s32 k = o->x130->x54;
        if (k != 1) {
            if (k <= 0) goto call;
            if (k >= 11) goto call;
            if (k < 9) goto call;
            if (o->x144) func_00121eb0(o->x144);
            goto done;
        call:
            func_00137330(o, 0, -2);
        }
    }
done:
    if (o->x6c) func_00141ab8(o->x6c);
    if (o->x400) func_00176310(o->x400);
    if (o->x148) func_00145240(o);
    if (o->x398) func_00137448(o);
    if (o->x14c && o->x14c->x1c) func_00176310(o->x14c->x1c);
    func_00135658(o);
}

/* func_00137990 (from auto/text_00130000_4.c). */
extern f32 D_002BBDFC;
void func_001247e8(s32);
void func_00137990(Actor *arg0) {
    f32 temp_f0;
    f32 temp_f2;

    temp_f2 = arg0->unk064;
    if (temp_f2 != 0.0f) {
        temp_f0 = arg0->unk060 + (temp_f2 * D_002BBDFC);
        arg0->unk060 = temp_f0;
        if (temp_f0 > 1.0f) {
            arg0->unk060 = 1.0f;
            arg0->unk064 = 0.0f;
        } else if (temp_f0 < 0.0f) {
            arg0->unk060 = 0.0f;
            arg0->unk064 = 0.0f;
            if (arg0->unk000 & 8) {
                func_001247e8(arg0);
            }
        }
    }
}

/* func_00137a20 (from hand/text_00130000_h6.c). */
typedef struct {
    u32 flags;
    u8 pad004[0x40 - 0x4];
    f32 v40[3];
    u8 pad04c[0x4A4 - 0x4C];
    f32 f4a4;
} W6Fade;
#define func_001247e8 ((void (*)(W6Fade *o)) func_001247e8)
void func_00137a20(W6Fade *o) {
    f32 d;
    s32 i;
    if (0.0f < o->f4a4) {
        d = o->f4a4 * D_002BBDFC;
        for (i = 0; i < 3; i++) {
            o->v40[i] -= d;
            if (o->v40[i] <= 0.0f) {
                o->v40[i] = 0.0f;
                o->f4a4 = 0.0f;
            }
        }
        if (o->f4a4 == 0.0f && (o->flags & 8)) {
            func_001247e8(o);
        }
    }
}
#undef func_001247e8

/* func_00137c70 (from hand/text_00130000_h6.c). */
extern s32 D_003044D0;
typedef struct {
    u32 flags;
    u8 pad004[0xD0 - 0x4];
    u8 x0d0[0x154 - 0xD0];
    s32 x154;
    u8 pad158[0x39D - 0x158];
    u8 b39d;
} W6Reg;
void func_00137c70(W6Reg *o) {
    ColEnt_3044d8 *e = &D_003044D8[D_003044D0++];
    e->x0 = (s32)o->x0d0;
    e->x4 = (u8 *)o->x154;
    *(s32 *)&e->x8 = (s32)o; /* an int store: the field's pointer alias set reorders the stores */
    if (o->flags & 0x20) {
        *(u32 *)&e->flags |= 1;
    } else {
        *(u32 *)&e->flags &= ~1;
    }
    e->flags.mask = o->b39d;
}

/* func_00137cf8 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad00[0xF];
    u8 b0f;
} W6Col;
typedef struct {
    u8 pad000[0x14C];
    W6Col *col;
} W6ColOwner;
void func_00137cf8(W6ColOwner *o) {
    W6Col *c = o->col;
    s32 v;
    if (c != 0 && (*(u32 *)o & 0x4000)) {
        v = c->b0f;
        if (v < 255) {
            v += 16;
            if (v > 255) {
                v = 255;
            }
            c->b0f = v;
        }
    }
}

/* func_00137d40 (from auto/text_00130000_4.c). */
void func_00137d40(void *arg0) {
    f32 temp_f0;
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0);
    if ((temp_a1 & 0x01000080) == 0x80) {
        if (temp_a1 & 0x100000) {
            temp_f0 = M2C_FIELD(arg0, f32 *, 0xC) - D_002BBDFC;
            M2C_FIELD(arg0, f32 *, 0xC) = temp_f0;
            if (temp_f0 <= 0.0f) {
                M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_a1 & 0xFFEFFF7F);
            }
        } else if (!(temp_a1 & 4)) {
            M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_a1 | 0x100000);
        }
    }
}

/* func_00137db0 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad00[0x10];
    u8 *x10;
    u32 x14;
} W32Eff;
typedef struct {
    u64 x0;
    u8 pad008[0x70 - 0x8];
    s32 x70;
    u8 pad074[0xB0 - 0x74];
    W32Eff *xb0;
} W32Pc;
extern u32 D_002C5958;
s32 func_001063c8(void);
W32Eff *func_00148768(s32 a, s32 b, W32Pc *o, s32 c, f32 f);
void func_00137db0(W32Pc *o) {
    if (o->xb0 && (o->xb0->x14 & 3) != 1) o->xb0 = 0;
    if (func_001063c8()) {
        if (o->xb0) {
            func_00176310((s32)o->xb0);
            o->xb0 = 0;
        }
        return;
    }
    if (o->x70 == 8 && (o->x0 & 0x8001) == 0x8001 && !(D_002C5958 & 0x104000) && !func_001063c8()) {
        if (o->xb0 == 0) o->xb0 = func_00148768(D_00350CE0, 20, o, 0x8003, 0.0f);
        return;
    }
    if (o->xb0) {
        *o->xb0->x10 = 1;
        o->xb0 = 0;
    }
}

/* func_00138130 (from hand/text_00130000_h32.c). */
extern W32Obj3 *D_0052AA70[];
void func_00130f18(W32Obj3 *o, f32 f);
s32 func_00138130(void) {
    s32 i;
    for (i = 0; i < D_0052AA68; i++) {
        W32Obj3 *o = D_0052AA70[i];
        D_00304AD8 = o;
        if (((s32)(o->x370 >> 39) & 1) || o->x154 == 0) {
            PlatVu0CopyVector(o->x50, o->x10);
        } else if (!(o->x130->x4 & 0x20000) || ((s32)(o->x370 >> 35) & 1)) {
            func_00130f18(o, (o->x88 & 1) ? 0.0f : D_002BBDFC);
            o->x370 |= 1ULL << 43;
        }
    }
    D_0052AA68 = 0;
    return 0;
}

/* func_001383d8 (from auto/text_00130000.c). */
M2C_UNK func_0011f090(M2C_UNK *, s32, s32);
extern M2C_UNK D_0052AA58;
M2C_UNK func_001383d8(s32 arg0, s32 arg1) {
    return func_0011f090(&D_0052AA58, arg0, arg1);
}

/* func_001386f8 (from auto/text_00130000_8.c). */
M2C_UNK func_0011f320(M2C_UNK *, s32);
void func_001386f8(s32 arg0) {
    func_0011f320(&D_0052AA58, arg0);
}

/* func_00138718 (from auto/text_00130000_8.c). */
M2C_UNK func_0011a0a0();
s32 func_00138718(void) {
    func_0011a0a0();
    return 0;
}

/* func_00138738 (from auto/text_00130000_17.c). */
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK D_0052A158[0x240] ALIGNED(8);  /* moved from auto/text_00130000_17.c (session 53) */
extern M2C_UNK D_0052ACF0;
void func_00138258();
s32 func_0011ef38(M2C_UNK *);
void func_0011ef10(M2C_UNK, M2C_UNK *);
#define func_0011f090 ((M2C_UNK (*)(M2C_UNK *, M2C_UNK, M2C_UNK *)) func_0011f090)
void func_00138738(void) {
  *((s32 *) (((s8 *) (&D_0052ACF0)) + 0)) = (*((s32 *) (((s8 *) (&D_0052ACF0)) + 4)) = 0);
  D_0052ACF8 = 0;
  func_0011efa8(&D_0052AA58, &D_0052A158, 0x18, 0x60);
  if (func_0011ef38(&func_00138258) == 0)
  {
    func_0011ef10(0x13880, &func_00138258);
  }
  func_0011f090(&D_0052AA58, 0x3E8, &func_00138718);
  func_0011f090(&D_0052AA58, -0x3E8, &func_00138130);
  func_0011f090(&D_0052AA58, 0x1388, &func_00138130);
  func_0011f090(&D_0052AA58, 0x1F40, &func_00138130);
}
#undef func_0011f090

/* func_00138808 (from auto/text_00130000_4.c). */
s32 func_00130040(s32, s32);
void func_00138808(Actor *arg0, f32 fparg0) {
    if (func_00130040(arg0, 0x42) != 0) {
        arg0->unk3E4 = fparg0;
        arg0->unk088 = (s32) (arg0->unk088 | 2);
    }
}

/* func_00138858 (from auto/text_00130000_2.c). */
u16 func_00138858(s32 arg0) {
    return M2C_FIELD(((arg0 * 2) + ((s32)D_00304BE8)), u16 *, 0x580);
}

/* func_00138870 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad00[0x4C];
    u16 h4c;
} W6Sub2;
typedef struct {
    u8 pad00[0x48];
    s32 x48;
    u8 pad4c[0xC4 - 0x4C];
    f32 fc4;
    u8 pad0c8[0xD2 - 0xC8];
    u16 hd2;
} W6Stat;
typedef struct {
    u8 pad000[4];
    s32 x4;
    u8 pad008[0x10 - 0x8];
    u8 x10[0x6C - 0x10];
    W6Stat *p6c;
    u8 pad070[0x130 - 0x70];
    W6Sub2 *sub;
    u8 pad134[0x164 - 0x134];
    s32 x164;
    u8 pad168[0x39C - 0x168];
    u8 b39c;
    u8 pad39d[0x3EA - 0x39D];
    u16 h3ea;
} W6Unit;
void func_001dce90(s32 a);
void func_001586a8(s32 a);
void func_00138870(W6Unit *u) {
    u16 v = u->sub->h4c;
    u32 k;
    func_001dce90(v);
    k = v - 300;
    if (k < 200) {
        func_001586a8(7);
    }
    if (k < 51) {
        if (D_00304BE8->cnt[k] < 9999) {
            D_00304BE8->cnt[k]++;
        }
    }
}

/* func_001388e8 (from auto/text_00130000_2.c). */
s32 func_001388e8(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0x190;
}

/* func_00138900 (from auto/text_00130000.c). */
#define func_00176310 ((M2C_UNK (*)(s32)) func_00176310)
void func_00138900(Actor *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unk400;
    if (temp_v0 != 0) {
        func_00176310(temp_v0);
        arg0->unk400 = 0;
    }
    arg0->unk088 = (s32) (arg0->unk088 & ~2);
}
#undef func_00176310

/* func_00138948 (from auto/text_00130000_4.c). */
s32 func_00148908(s32);
void func_00138948(Actor *arg0) {
    func_00138900(arg0);
    arg0->unk088 = (s32) (arg0->unk088 | 2);
    arg0->unk400 = func_00148908(arg0);
}

/* func_00138988 (from hand/text_00130000_h6.c). */
s32 func_00138988(W6Unit *u) {
    s32 d = u->x164 - u->h3ea;
    if ((u32)d >= 10) {
        return 0;
    }
    return d % 5 + 1;
}

/* func_001389c0 (from auto/text_00130000.c). */
#define func_00138988 ((s32 (*)()) func_00138988)
s32 func_001389c0(void) {
    return func_00138988() == 4;
}
#undef func_00138988

/* func_001389e8 (from auto/text_00130000_13.c). */
#define func_00138988 ((s32 (*)()) func_00138988)
s32 func_001389e8(void *arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (!((u32) (M2C_FIELD(arg0, s32 *, 0x164) - 0x48) >= 0x23U)) {
        return var_v0;
    }
    var_v0 = func_00138988() != 0;
    return var_v0;
}
#undef func_00138988

/* func_00138a20 (from auto/text_00130000.c). */
M2C_UNK func_00121fc4(void *, void *);
f32 func_0014cce0(s32, f32);
void func_00138a20(s32 arg0, void *arg1, f32 f) {
    f32 temp_f20;

    func_0014cce0(arg0, f);
    temp_f20 = M2C_FIELD(arg1, f32 *, 0xC);
    func_00121fc4(arg1, arg1);
    PlatVu0ScaleVector(arg0 + 0x3C0, arg1, temp_f20);
}

