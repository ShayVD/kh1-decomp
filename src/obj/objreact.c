/* An object's reactions to commands and hits: the reaction handlers that
 * read the tuning block *D_00308CDC (func_00138a78, func_00138c30,
 * func_00139240 picks a reaction motion, func_00139840), the message loop
 * func_00139da8, the per-state update func_0013a0f0, and the nearest target
 * within a range and level (func_0013a440). Flag mode: default (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h32.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_00350CE0.h"
#include "data/types/text_00130000_h32_p.h"
#include "data/pieces/D_00304AD8.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00304B6C.h"
#include "data/pieces/D_00304B84.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002C58B0.h"

/* func_00138c30 (from hand/text_00130000_h6.c). */
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
typedef struct {
    u64 bits;
    u8 pad08[8];
    f32 v10[4];
} W6Cmd;
void func_00156260(W6Unit *u, f32 *v);
void func_00138c30(W6Unit *u, W6Cmd *c) {
    f32 v[4];
    PlatVu0CopyVector(v, c->v10);
    v[3] = (*(Cfg_308cdc **)&D_00308CDC)->x2c * u->p6c->fc4;
    func_00156260(u, v);
    c->bits |= 2;
}

/* func_00138ca0 (from auto/text_00130000_5.c). */
s32 func_00130040(s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
#define func_00138c30 ((void (*)(s32, s32)) func_00138c30)
void func_00138ca0(Actor *arg0, s32 arg1, f32 fparg0) {
    s32 var_v1;

    if (func_00130040(arg0, 0x48) == 0) {
        func_00138c30(arg0, arg1);
        return;
    }
    if (M2C_FIELD(arg1, s32 *, 0x20) == 0) {
        var_v1 = 0x4A;
        if (fparg0 < 0.0f) {
            var_v1 = 0x48;
        }
    } else {
        var_v1 = 0x49;
        if (!(fparg0 < 0.0f)) {
            var_v1 = 0x4B;
        }
    }
    if (arg0->unk164 == var_v1) {
        var_v1 = ((var_v1 - 0x48) ^ 1) + 0x48;
    }
    func_00130340(arg0, var_v1 | 0x01000000, 0.0f);
    func_00130578(arg0, 0x40000000, 8.0f);
    func_00138c30(arg0, arg1);
}
#undef func_00138c30

/* func_00138d88 (from auto/text_00130000_13.c). */
void func_00138a20(s32, s32, f32);
#define func_00130040 ((void (*)(s32, s32)) func_00130040)
#define func_00130340 ((void (*)(s32, s32, f32)) func_00130340)
#define func_00130578 ((void (*)(s32, s32, f32)) func_00130578)
void func_00138d88(s32 arg0, s32 arg1, f32 fparg0) {
    s32 sp[4];
    func_00130040(arg0, 0x4E);
    if (fparg0 < 0.0f) {
        func_00130340(arg0, 0x0100004E, 0.0f);
    } else {
        func_00130340(arg0, 0x0100004F, 0.0f);
    }
    func_00130578(arg0, 6, 8.0f);
    PlatVu0CopyVector((s32) sp, arg1 + 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD((*(void **)&D_00308CDC), f32 *, 0x38) * M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xC4);
    func_00138a20(arg0, (s32) sp, 2e+01f);
}
#undef func_00130040
#undef func_00130340
#undef func_00130578

/* func_00138e58 (from hand/text_00130000_h32.c). */
typedef struct {
    u64 flags;
    u8 pad08[0x10 - 0x8];
    f32 x10[4];
} W32Tgt;
typedef struct {
    u8 pad00[0x30];
    f32 x30[4];
} W32Src;
s32 func_001389c0(W32Src *o, W32Tgt *t);
s32 func_0014f5c8(W32Src *o);
s32 func_0014f600(W32Src *o);
#define func_00138c30 ((void (*)(W32Src *o, W32Tgt *t)) func_00138c30)
#define func_00138ca0 ((void (*)(W32Src *o, W32Tgt *t, f32 d)) func_00138ca0)
#define func_00138d88 ((void (*)(W32Src *o, W32Tgt *t, f32 d)) func_00138d88)
void func_00138e58(W32Src *o, W32Tgt *t) {
    f32 d;
    if (func_001389c0(o, t)) {
        func_00138c30(o, t);
    } else {
        d = PlatVu0InnerProduct(o->x30, t->x10);
        if (func_0014f5c8(o)) func_00138ca0(o, t, d);
        else if (func_0014f600(o)) func_00138d88(o, t, d);
        else func_00138ca0(o, t, d);
    }
    t->flags |= 2;
}
#undef func_00138c30
#undef func_00138ca0
#undef func_00138d88

/* func_00138f28 (from auto/text_00130000_6.c). */
f32 func_0026b9a8(f32, f32);
void func_00137688(s32, f32);
void func_00139408();
#define func_00138ca0 ((void (*)(s32, s32, f32)) func_00138ca0)
#define func_00139408 ((void (*)(s32, s32)) func_00139408)
void func_00138f28(Actor *arg0, s32 arg1, f32 fparg0) {
    f32 var_f0;

    if (func_00130040(arg0, 0x4C) == 0) {
        if (func_00130040(arg0, 0x52) != 0) {
            func_00139408(arg0, arg1);
            return;
        }
        func_00138ca0(arg0, arg1, fparg0);
        return;
    }
    if (fparg0 < 0.0f) {
        func_00130340(arg0, 0x0100004C, 0.0f);
        var_f0 = func_0026b9a8(-M2C_FIELD(arg1, f32 *, 0x10), -M2C_FIELD(arg1, f32 *, 0x18));
    } else {
        func_00130340(arg0, 0x0100004D, 0.0f);
        var_f0 = func_0026b9a8(M2C_FIELD(arg1, f32 *, 0x10), M2C_FIELD(arg1, f32 *, 0x18));
    }
    arg0->unk150 = var_f0;
    func_00137688(arg0, var_f0);
    func_00130578(arg0, 0x40000000, 8.0f);
    arg0->unk3CC = 0;
}
#undef func_00138ca0
#undef func_00139408

/* func_00139040 (from auto/text_00130000_14.c). */
f32 atan2f(f32, f32);
#define func_00130340 ((void (*)(s32, s32, f32)) func_00130340)
#define func_00130578 ((void (*)(s32, s32, f32)) func_00130578)
#define func_00139408 ((void (*)(s32, s32)) func_00139408)
void func_00139040(s32 arg0, s32 arg1, f32 fparg0) {
    s32 sp[4];    f32 var_f0;

    if (func_00130040(arg0, 0x50) == 0) {
        if (func_00130040(arg0, 0x5C) != 0) {
            func_00139408(arg0, arg1);
            return;
        }
        func_00138d88(arg0, arg1, fparg0);
        return;
    }
    if (fparg0 < 0.0f) {
        func_00130340(arg0, 0x01000050, 0.0f);
        var_f0 = atan2f(-M2C_FIELD(arg1, f32 *, 0x10), -M2C_FIELD(arg1, f32 *, 0x18));
    } else {
        func_00130340(arg0, 0x01000051, 0.0f);
        var_f0 = atan2f(M2C_FIELD(arg1, f32 *, 0x10), M2C_FIELD(arg1, f32 *, 0x18));
    }
    func_00130578(arg0, 6, 8.0f);
    M2C_FIELD(arg0, f32 *, 0x150) = var_f0;
    func_00137688(arg0, var_f0);
    PlatVu0CopyVector((s32) sp, arg1 + 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD((*(void **)&D_00308CDC), f32 *, 0x3C);
    func_00138a20(arg0, (s32) sp, 2e+01f);
}
#undef func_00130340
#undef func_00130578
#undef func_00139408

/* func_00139170 (from hand/text_00130000_h32.c). */
#define func_00138c30 ((void (*)(W32Src *o, W32Tgt *t)) func_00138c30)
#define func_00138f28 ((void (*)(W32Src *o, W32Tgt *t, f32 d)) func_00138f28)
#define func_00139040 ((void (*)(W32Src *o, W32Tgt *t, f32 d)) func_00139040)
void func_00139170(W32Src *o, W32Tgt *t) {
    f32 d;
    if (func_001389c0(o, t)) {
        func_00138c30(o, t);
    } else {
        d = PlatVu0InnerProduct(o->x30, t->x10);
        if (func_0014f5c8(o)) func_00138f28(o, t, d);
        else if (func_0014f600(o)) func_00139040(o, t, d);
        else func_00138f28(o, t, d);
    }
    t->flags |= 2;
}
#undef func_00138c30
#undef func_00138f28
#undef func_00139040

/* func_00139408 (from hand/text_00130000_h6.c). */
typedef Cfg_308cdc W6Lim;
f32 func_00176850(void);
void func_00139240(W6Unit *u, s32 a, s32 b, f32 x, f32 y, f32 z);
void func_00139408(W6Unit *u, s32 a) {
    W6Lim *c = (*(Cfg_308cdc **)&D_00308CDC);
    f32 lo = c->h14;
    f32 t = lo + (c->h16 - lo) * u->p6c->fc4;
    f32 k = c->f18;
    func_00139240(u, a, 0, t * k, t, func_00176850() * 30.0f);
}

/* func_001394a8 (from auto/text_00130000_8.c). */
void func_001394a8(s32 arg0) {
    func_00130340(arg0, 0x01000066, 0.0f);
    M2C_FIELD(arg0, f32 *, 0x404) = 68.0f;
}

/* func_001394e8 (from auto/text_00130000_4.c). */
s32 func_0014f658(s32, s32);
#define func_0014f5c8 ((s32 (*)(s32)) func_0014f5c8)
void func_001394e8(Actor *arg0) {
    if (func_0014f5c8(arg0) != 0) {
        func_0014f658(arg0, 0x17);
    } else {
        func_0014f658(arg0, 0x16);
    }
    func_00130340(arg0, 0x01000068, 0.0f);
    arg0->unk404 = 75.0f;
    arg0->unk02C = 0.0f;
}
#undef func_0014f5c8

/* func_00139568 (from auto/text_00130000_2.c). */
#define func_001394a8 ((M2C_UNK (*)(s32, s32)) func_001394a8)
#define func_001394e8 ((M2C_UNK (*)(s32, s32)) func_001394e8)
#define func_0014f5c8 ((s32 (*)()) func_0014f5c8)
#define func_0014f600 ((s32 (*)(s32)) func_0014f600)
void func_00139568(s32 arg0, s32 arg1) {
    if ((func_0014f5c8() != 0) || (func_0014f600(arg0) != 0)) {
        func_001394e8(arg0, arg1);
        return;
    }
    func_001394a8(arg0, arg1);
}
#undef func_001394a8
#undef func_001394e8
#undef func_0014f5c8
#undef func_0014f600

/* func_00139840 (from hand/text_00130000_h55.c). */
typedef struct {
    u8 pad00[0x6c];
    u8 *x6c;
    s32 x70;
    u8 pad74[0x164 - 0x74];
    s32 x164;
} W55ObA;
typedef struct { u8 pad[0x38]; f32 x38; } W55CamA;
extern s32 D_00304AF0[];
extern s32 D_00304AE0[];
void func_00138a78(void *o, void *b);
#define func_00130340 ((void (*)(void *o, s32 a, f32 f)) func_00130340)
#define func_00130578 ((void *(*)(void *, s32, f32)) func_00130578)
#define func_0014f600 ((s32 (*)(void *o)) func_0014f600)
#define func_00138a20 ((void (*)(void *o, void *v, f32 f)) func_00138a20)
void func_00139840(W55ObA *o, u8 *b) {
    f32 v[4];
    s32 i;
    func_00138a78(o, b);
    if (func_0014f600(o)) {
        i = (s32)(func_00176850() * 2.0f);
        if (o->x164 == D_00304AF0[i]) i = (i + 1) & 1;
        func_00130340(o, D_00304AF0[i] | 0x1000000, 0.0f);
        func_00130578(o, 0x40000006, 8.0f);
        PlatVu0CopyVector(v, b + 16);
        v[3] = ((W55CamA *)(*(u8 **)&D_00308CDC))->x38 * *(f32 *)(o->x6c + 0xc4);
        func_00138a20(o, v, 20.0f);
        return;
    }
    i = (s32)(func_00176850() * 4.0f);
    if (o->x164 == D_00304AE0[i]) i = (i + 1) & 3;
    func_00130340(o, D_00304AE0[i] | 0x1000000, 0.0f);
    func_00130578(o, 0x40000000, 8.0f);
}
#undef func_00130340
#undef func_00130578
#undef func_0014f600
#undef func_00138a20

/* func_001399a8 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad00[0xC4];
    f32 xc4;
} W32Scl;
typedef struct {
    u8 pad00[0x30];
    f32 x30[4];
    u8 pad40[0x6C - 0x40];
    W32Scl *x6c;
    u8 pad70[0x3C0 - 0x70];
    f32 x3c0[4];
} W32Act;
typedef struct {
    u8 pad00[0x40];
    u32 x40;
} W32Atk;
typedef struct {
    u8 pad00[0x8];
    s32 x8;
    u8 pad0c[0x2C - 0xC];
    W32Atk *x2c;
} W32Hit;
#define func_00156260 ((void (*)(W32Act *o, f32 *v)) func_00156260)
#define func_00130340 ((s32 (*)(W32Act *o, u32 f, f32 x)) func_00130340)
#define func_00130578 ((void *(*)(void *o, s32 k, f32 f)) func_00130578)
void func_001399a8(W32Act *o, W32Hit *h) {
    f32 v[4] __attribute__((aligned(16)));
    u32 f = h->x2c->x40;
    if (h->x8 < 0 && (f & 0x400000)) {
        f32 t;
        PlatVu0SubVector(v, (*(f32 (*)[0x4])&D_002C58A0), o->x30);
        t = (f32)-h->x8 * (*(Cfg_308cdc **)&D_00308CDC)->x28;
                v[3] = (t < (*(Cfg_308cdc **)&D_00308CDC)->x2c ? t : (*(Cfg_308cdc **)&D_00308CDC)->x2c) * o->x6c->xc4;
        func_00156260(o, v);
        f &= ~0x400000;
    }
    func_00130340(o, f | 0x1000000, 0.0f);
    func_00130578(o, 0x40000000, 8.0f);
}
#undef func_00156260
#undef func_00130340
#undef func_00130578

/* func_00139a90 (from hand/text_00130000_h32.c). */
void func_0014cce0(W32Act *o, f32 f);
#define func_00130340 ((s32 (*)(W32Act *o, u32 f, f32 x)) func_00130340)
#define func_00130578 ((void *(*)(void *o, s32 k, f32 f)) func_00130578)
void func_00139a90(W32Act *o, W32Hit *h) {
    func_00130340(o, (h->x2c->x40 & ~0x400000) | 0x1000000, 0.0f);
    func_00130578(o, 0x40000006, 0.0f);
    func_0014cce0(o, 20.0f);
    if (h->x8 < 0) {
                f32 t = (f32)h->x8 / 100.0f * (*(Cfg_308cdc **)&D_00308CDC)->x30;
        PlatVu0ScaleVector(o->x3c0, o->x30, (-(*(Cfg_308cdc **)&D_00308CDC)->x34 < t ? t : -(*(Cfg_308cdc **)&D_00308CDC)->x34) * o->x6c->xc4);
        return;
    }
    PlatVu0CopyVector(o->x3c0, (*(f32 (*)[0x4])&D_002C58A0));
}
#undef func_00130340
#undef func_00130578

/* func_00139b98 (from auto/text_00130000_13.c). */
#define func_001399a8 ((s32 (*)(s32, s32)) func_001399a8)
#define func_00139a90 ((s32 (*)(s32, s32)) func_00139a90)
#define func_0014f5c8 ((s32 (*)(s32)) func_0014f5c8)
#define func_0014f600 ((s32 (*)(s32)) func_0014f600)
void func_00139b98(s32 arg0, s32 arg1) {
    if (func_0014f5c8(arg0) != 0) {
        func_001399a8(arg0, arg1);
        return;
    }
    if ((func_0014f600(arg0) != 0) || ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x3D) & 1)) {
        func_00139a90(arg0, arg1);
        return;
    }
    func_001399a8(arg0, arg1);
}
#undef func_001399a8
#undef func_00139a90
#undef func_0014f5c8
#undef func_0014f600

/* func_00139c28 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad00[8];
    u64 bits;
} W6Kind;
void func_001473a8(s32 a, s32 b, void *c);
void func_00139c28(W6Unit *u, W6Kind *k) {
    u64 bits = k->bits;
    s32 n;
    s32 m;
    if (((bits >> 38) & 0xF) == 1) {
        n = u->p6c->hd2;
        if (n > 0) {
            m = (s32)(bits >> 32) & 0x1F;
            if (m != 0) {
                if (m >= 4) {
                    if (m >= 6) {
                        return;
                    }
                    n += 2;
                }
                u->b39c = (u->b39c + 1) & 1;
                func_001473a8(n + u->b39c, u->x4 + 1, u->x10);
            }
        }
    }
}

/* func_00139da8 (from hand/text_00130000_h55.c). */
typedef struct {
    u8 pad00[0x88];
    s32 x88;
    u8 pad8c[0x3e4 - 0x8c];
    s32 x3e4;
} W55ObB;
typedef struct { u64 x0; u64 x8; } W55Msg;
W55Msg *func_00134928(W55ObB *o);
void func_00134998(W55ObB *o);
void func_001350d0(W55Msg *m);
void func_00138900(W55ObB *o);
s32 func_00139cb8(W55ObB *o, W55Msg *m);
#define func_00138c30 ((void (*)(W55ObB *o, W55Msg *m)) func_00138c30)
#define func_00138e58 ((void (*)(W55ObB *o, W55Msg *m)) func_00138e58)
#define func_00139170 ((void (*)(W55ObB *o, W55Msg *m)) func_00139170)
#define func_00139408 ((void (*)(W55ObB *o, W55Msg *m)) func_00139408)
#define func_00139568 ((void (*)(W55ObB *o, W55Msg *m)) func_00139568)
#define func_00139b98 ((void (*)(W55ObB *o, W55Msg *m)) func_00139b98)
#define func_0014f5c8 ((s32 (*)(void *o)) func_0014f5c8)
void func_00139da8(W55ObB *o) {
    W55Msg *m = 0;
    s32 best = 0;
    s32 fl = o->x88;
    s32 k;
    for (;;) {
        if (m) func_001350d0(m);
        m = func_00134928(o);
        if (!m) break;
        if (o->x88 & 2) o->x88 = (o->x88 | 0x100) & ~2;
        k = func_00139cb8(o, m);
        o->x88 &= ~0x100;
        if (!k) continue;
        if (m->x0 & 0x22) continue;
        if ((s32)(m->x8 >> 43) & 1) {
            k = (s32)((s64)m->x8 >> 32) & 0x1f;
            switch (k) {
            case 2: case 3: case 4: case 5: func_00139840((void *)o, (void *)m); break;
            case 8: func_00139568(o, m); break;
            default: func_00134998(o); break;
            }
        } else {
            s32 j = (s32)((s64)m->x8 >> 32) & 0x1f;
            if (best < j) {
                best = j;
                switch (best) {
                case 0: case 1: break;
                case 2: func_00138c30(o, m); break;
                case 3: func_00138e58(o, m); break;
                case 5:
                    if (func_0014f5c8(o)) {
                case 4:
                        func_00139170(o, m);
                    } else {
                        func_00139408(o, m);
                    }
                    break;
                case 6: case 7: func_00139b98(o, m); break;
                case 8: func_00139568(o, m); break;
                }
            }
        }
    }
    if ((fl & 2) && !(o->x88 & 2)) {
        if (!best) {
            if (!(o->x88 & 1)) o->x3e4 = 0;
        } else {
            func_00138900(o);
        }
    }
}
#undef func_00138c30
#undef func_00138e58
#undef func_00139170
#undef func_00139408
#undef func_00139568
#undef func_00139b98
#undef func_0014f5c8

/* func_00139ff8 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad00[0xC];
    void (*xc)(void);
} W32Ev;
typedef struct {
    u8 pad000[0x20];
    f32 x20[3];
    s32 x2c;
    f32 x30[4];
    u8 pad040[0x88 - 0x40];
    u32 x88;
    u8 pad08c[0x164 - 0x8C];
    s32 x164;
    u8 pad168[0x3D0 - 0x168];
    s32 x3d0;
    u8 pad3d4[0x3EA - 0x3D4];
    u16 x3ea;
} W32Mot;
void func_00130398(W32Mot *o, s32 k, f32 f);
void func_00138948(void);
#define func_00130578 ((void *(*)(void *o, s32 k, f32 f)) func_00130578)
void func_00139ff8(W32Mot *o) {
    s32 b = o->x3ea;
    s32 m = o->x164;
    W32Ev *e;
    if (m == b || m == b + 1) {
        func_00130398(o, b + 2, 0.0f);
        e = func_00130578(o, o->x3ea + 3, 0.0f);
        if (o->x88 & 2) e->xc = func_00138948;
    } else if (m == b + 5 || m == b + 6) {
        func_00130398(o, b + 7, 0.0f);
        e = func_00130578(o, o->x3ea + 8, 0.0f);
        if (o->x88 & 2) e->xc = func_00138948;
    } else {
        func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
        func_00130578(o, 0x40000000, 8.0f);
    }
    PlatVu0CopyVector(o->x20, o->x30);
    o->x2c = 0;
}
#undef func_00130578

/* func_0013a0f0 (from hand/text_00130000_b03.c). */
typedef struct { u8 pad[0xcc]; f32 xcc; } B3Mv;
typedef struct B3Ob {
    u32 x0;
    s32 x4;
    u8 pad08[0x20 - 0x8];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    u8 pad40[0x6c - 0x40];
    B3Mv *x6c;
    s32 x70;
    u8 pad74[0x88 - 0x74];
    u32 x88;
    u8 pad8c[0x144 - 0x8c];
    s32 x144;
    u8 pad148[0x150 - 0x148];
    f32 x150;
    u8 pad154[0x164 - 0x154];
    s32 x164;
    u8 pad168[0x280 - 0x168];
    f32 x280;
    u8 pad284[0x370 - 0x284];
    u64 x370;
    s32 x378;
    u8 pad37c[0x3d0 - 0x37c];
    s32 x3d0;
    u8 pad3d4[0x3e4 - 0x3d4];
    f32 x3e4;
    u16 x3e8;
} B3Ob;
extern f32 D_002BBDFC;
extern u32 D_002C5958;
f32 func_001216d8(f32, f32, f32);
s32 func_00123368(B3Ob *);
s32 func_0012ba98(s32);
void func_00135658(B3Ob *);
s32 func_00137618(B3Ob *);
s32 func_00138988(B3Ob *);
void func_001395d8(B3Ob *);
#define func_00130340 ((void (*)(B3Ob *o, s32 a, f32 f)) func_00130340)
#define func_00130398 ((void (*)(B3Ob *o, s32 a, f32 f)) func_00130398)
#define func_00130578 ((void *(*)(B3Ob *, s32, f32)) func_00130578)
#define func_00137688 ((void (*)(B3Ob *, f32)) func_00137688)
#define func_00138900 ((void (*)(B3Ob *)) func_00138900)
#define func_00138948 ((void (*)(B3Ob *)) func_00138948)
#define func_00139da8 ((void (*)(B3Ob *)) func_00139da8)
#define func_00139ff8 ((void (*)(B3Ob *)) func_00139ff8)
void func_0013a0f0(B3Ob *o) {
    s32 v;
    o->x370 &= ~0x2000000000000000ULL;
    if (o->x0 & 0x400) {
        switch (o->x70) {
        case 0:
            switch (o->x378) {
            case 2:
            case 3:
                func_00139ff8(o);
                o->x370 |= 0x2000000000000000ULL;
                break;
            }
            break;
        case 2:
        case 3:
            func_00130340(o, 6, 8.0f);
            break;
        case 4:
            if (o->x378 == 5) {
                func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
                func_00130578(o, 0x40000000, 8.0f);
                PlatVu0CopyVector(o->x20, (*(f32 (*)[0x4])&D_002C58B0));
            }
            break;
        }
    }
    if (func_00138988(o) == 4) {
        o->x3e4 -= D_002BBDFC;
        if (o->x280 <= 2.0f || o->x3e4 <= 0.0f) {
            func_00138900(o);
            func_00130398(o, o->x164 + 1, 8.0f);
            func_00130578(o, 0x40000000, 8.0f);
        }
    } else if (o->x164 == 0x43) {
        o->x3e4 -= D_002BBDFC;
        if (o->x3e4 <= 0.0f) {
            func_00138900(o);
            func_00130398(o, 0x44, 0.0f);
            func_00130578(o, 0x40000000, 8.0f);
        }
    }
    func_001395d8(o);
    if (func_00123368(o)) {
        func_00139da8(o);
    } else {
        func_00135658(o);
    }
    if (o->x88 & 1) return;
    if (!((D_002C5958 >> 21) & 1) && func_00137618(o)) {
        if (o->x88 & 2) {
            func_00138948(o);
            func_00130340(o, 0x1000042, 8.0f);
            func_00130578(o, 0x43, 0.0f);
        } else if (((s32)(o->x370 >> 48) & 1) && o->x144) {
            func_00138900(o);
            if (func_0012ba98(o->x144) < 0) o->x144 = 0;
        }
    }
    if (!((s32)(o->x370 >> 44) & 1)) {
        func_00137688(o, func_001216d8(o->x3c, o->x150, o->x6c->xcc));
    }
    if (o->x3e8 && !(o->x0 & 4)) o->x3e8 = 0;
}
#undef func_00130340
#undef func_00130398
#undef func_00130578
#undef func_00137688
#undef func_00138900
#undef func_00138948
#undef func_00139da8
#undef func_00139ff8

/* func_0013a430 (from auto/text_00130000_2.c). */
s32 func_0013a430(s32 *arg0, s32 *arg1) {
    return *arg0 - *arg1;
}

/* func_0013a670 (from hand/text_00130000_h55.c). */
typedef struct W55ObC {
    u32 x0;
    u8 pad04[0x10 - 0x4];
    f32 pos[4];
    u8 pad20[0x6c - 0x20];
    s32 *x6c;
    u8 pad70[0x74 - 0x70];
    struct W55ObC *x74;
    u8 pad78[0x7c - 0x78];
    struct W55ObC *x7c;
    s32 x80;
    u8 pad84[0x88 - 0x84];
    s32 x88;
    u8 pad8c[0x370 - 0x8c];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } x370;
} W55ObC;
typedef struct { s32 d; W55ObC *p; } W55EntC;
void *func_00122048(s32 n, s32 a);
void func_001220b8(void *p);
void qsort(void *b, s32 n, s32 sz, void *cmp);
f32 func_00120bf8(f32 *v);
W55ObC *func_001231b8(W55ObC *o, W55ObC *p);
W55ObC *func_0013a670(W55ObC *o, s32 *w, f32 rng, f32 lim) {
    f32 v[4];
    W55ObC *p = 0;
    W55EntC *e, *base;
    s32 n, r;
    f32 q;
    base = e = func_00122048(0x300, 4);
    while ((p = func_001231b8(o, p))) {
        if (p->x6c[16] <= 0) continue;
        q = (f32)p->x6c[15] / (f32)p->x6c[16];
        if (lim < q) continue;
        PlatVu0SubVector(v, p->pos, o->pos);
        if (rng < func_00120bf8(v)) continue;
        e->p = p;
        e->d = q * 100.0f;
        e++;
    }
    n = e - base;
    qsort(base, n, 8, func_0013a430);
    if (n > 0) p = base[0].p;
    r = (s32)(func_00176850() * 100.0f);
    if ((r -= w[0]) >= 0) {
        if ((r -= w[1]) >= 0 && n >= 3) {
            p = base[2].p;
        } else if (n >= 2) {
            p = base[1].p;
        }
    }
    func_001220b8(base);
    return p;
}

/* func_0013a810 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad000[0x170];
    u64 x170;
} W32Sub;
typedef struct {
    u8 pad000[0x148];
    W32Sub *x148;
} W32Obj2;
void func_001373f8(W32Obj2 *o, f32 f);
typedef struct {
    u8 pad00[0x4C];
    u16 x4c;
} W32Pi;
typedef struct Actor_3a810 {
    u32 flags;
    u8 pad004[0x130 - 0x4];
    W32Pi *x130;
} W32Ply;
void func_00123460(W32Ply *p);
void func_00135800(W32Ply *p, f32 a, f32 b);
s32 func_0012f040(void *o, s32 a);
s32 func_0013c318(s32 k);
void func_002414a8(s32 a, s32 b);
void func_0013a810(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        W32Ply *p = D_002E26A0[i + 1];
        if (p == 0) continue;
        if (p->flags & 0x8000) continue;
        func_00123460(p);
        func_00135800(p, 0.0f, 0.0f);
        func_00135800(p, 1.0f, 30.0f);
        p->flags &= ~0x1000000;
        func_001373f8((W32Obj2 *)p, 30.0f);
        if (func_0012f040((void *)p, -1)) func_002414a8(func_0013c318(p->x130->x4c), 1);
    }
}

