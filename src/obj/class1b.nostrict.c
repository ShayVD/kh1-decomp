/* Object class 0x1B, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_001524c8 registers in the class table D_00350D88
 * (func_0014f830(0x1B, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1b.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C58A0.h"
#include "data/bss_0054.h"
#include "data/types/nostrict_text_00140000_h57.h"
#include "data/types/nostrict_text_00140000_h57_p.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "m2c.h"
#include "platform/math.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/nostrict_text_00140000_b04.h"
#include "data/types/nostrict_text_00150000_s8_w16.h"
#include "data/pieces/D_00351530.h"

/* func_00150de0 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { s32 x0; u8 pad4[0x1c]; f32 x20[4]; } W34Tgt;
typedef struct { s32 x0; W34Tgt *x4; u8 pad8[4]; f32 xc; f32 x10[4]; u8 pad20[0x20]; } W34Lk;
extern W34Lk D_0054F750[8];
extern f32 D_00306840;
void func_00150de0(s32 a) {
    W34Lk *e = D_0054F750;
    s32 i;
    if (a) {
        for (i = 0; i < 8; i++, e++) {
            if (e->x4 && !e->x0) {
                e->x4->x0 |= 0x30;
                e->x0 = 3;
                e->xc = D_00306840;
                PlatVu0CopyVector(e->x10, e->x4->x20);
            }
        }
    } else {
        for (i = 0; i < 8; i++, e++) {
            if (e->x4 && e->x0 == 3) {
                e->x0 = 4;
                e->xc = D_00306840;
            }
        }
    }
}

/* func_00150ec8 (from hand/nostrict/text_00140000_h57.c). */
typedef struct { u8 pad0[0x4c]; u16 h4c; } Info57_0ec8;
typedef struct Actor_50ec8 { u8 pad0[0x130]; Info57_0ec8 *info; } Pl57_0ec8;
typedef struct { s32 i0; u8 pad4[4]; s32 i8; f32 fc; f32 v10[4]; u8 pad20[0x2c-0x20]; f32 f2c; u8 pad30[4]; s32 i34; } Ev57_0ec8;
typedef struct {
    s32 flags;
    u8 pad4[0x10-4];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[0x144-0x30];
    Ev57_0ec8 *ev;
} Obj57_0ec8;
void func_001315c0(Pl57_0ec8 *, s32, f32 *, f32);
s32 func_001453a8(Pl57_0ec8 *, f32 *, s32);
s32 func_0013c9e0(s32, s32);
void func_00243630(s32, s32);
void func_001473a8(s32, s32, f32 *);
s32 func_00150ec8(Obj57_0ec8 *o) {
    f32 v[4];
    Pl57_0ec8 *pl;
    Ev57_0ec8 *e;
    s32 r;

    pl = D_002E26A0[0];
    func_001315c0(pl, 0x8003, v, 0.0f);
    e = o->ev;
    if (!(o->flags & 0x20)) {
        if (func_001453a8(pl, o->v10, e->i34)) {
            r = func_0013c9e0(e->i8, pl->info->h4c);
            if (r == 255) {
                if (e->f2c <= 0.0f) func_00243630(2, e->i8);
                e->f2c = 60.0f;
                goto end;
            }
            e->i0 = 2;
            PlatVu0SubVector(e->v10, o->v10, v);
            func_00243630(r == 12, e->i8);
            func_001473a8(27, 0, o->v10);
            e->fc = 30.0f;
            o->flags |= 0x30;
            PlatVu0CopyVector(o->v20, (*(f32 (*)[0x4])&D_002C58B0));
            return 1;
        }
    }
end:
    return 0;
}

/* func_00151010 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { u8 pad[0x24]; f32 x24; } W34Sc;
typedef struct { u32 x0; u8 pad4[0xc]; f32 x10[4]; f32 x20; f32 x24; f32 x28; u8 pad2c[0x144 - 0x2c]; W34Sc *x144; u8 pad148[0x2d0 - 0x148]; s32 x2d0; } W34Bnc;
void func_00151010(W34Bnc *o) {
    W34Sc *sc = o->x144;
    if (o->x24 > 0.0f) {
        o->x0 &= ~0x20;
        if (!(o->x2d0 & 1)) {
            if (o->x24 > 5.0f) {
                f32 t = o->x24 / 20.0f;
                if (t > 0.5f) sc->x24 = 1.0f - t * 0.199999988079071044921875f;
                o->x24 *= -0.7999999523162841796875f;
                func_001473a8(50, 0, o->x10);
            } else {
                PlatVu0CopyVector(&o->x20, (*(f32 (*)[0x4])&D_002C58A0));
            }
        }
    }
    o->x24 += 3.0f;
    if (o->x24 > 20.0f) o->x24 = 20.0f;
    o->x20 *= 0.949999988079071044921875f;
    o->x28 *= 0.949999988079071044921875f;
}

/* func_00151148 (from hand/nostrict/text_00150000.c). */
void func_00151148(void *arg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    void *temp_s0;

    temp_f1 = M2C_FIELD(arg0, f32 *, 0x24);
    temp_s0 = M2C_FIELD(arg0, void **, 0x144);
    if (temp_f1 < 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x24) = (f32) (temp_f1 + M2C_FIELD(temp_s0, f32 *, 0x30));
        goto block_4;
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & ~0x20);
    temp_f1_2 = M2C_FIELD(temp_s0, f32 *, 0x30) + -0.05f;
    M2C_FIELD(temp_s0, f32 *, 0x30) = temp_f1_2;
    temp_f0 = M2C_FIELD(arg0, f32 *, 0x24) + temp_f1_2;
    M2C_FIELD(arg0, f32 *, 0x24) = temp_f0;
    if (temp_f0 < 0.0f) {
        PlatVu0CopyVector(arg0 + 0x20, ((M2C_UNK *)&D_002C58A0));
        M2C_FIELD(temp_s0, s32 *, 0) = 1;
        return;
    }
block_4:
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (M2C_FIELD(arg0, f32 *, 0x20) * 0.95f);
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) (M2C_FIELD(arg0, f32 *, 0x28) * 0.95f);
}

/* func_00151268 (from hand/nostrict/text_00140000_b04.c). */
extern f32 D_002BBDFC;
typedef struct { u32 x0; u32 *x4; u8 pad8[4]; f32 xc; f32 x10[4]; f32 x20; f32 x24; u8 pad28[4]; f32 x2c; u8 pad30[4]; s32 x34; } B4W51;
typedef struct {
    u32 x0; u8 pad4[0xc]; f32 x10[4]; f32 x20[4]; u8 pad30[0xc]; f32 x3c; f32 x40; f32 x44; f32 x48;
    u8 pad4c[0x144 - 0x4c]; B4W51 *x144;
} B4A51;
f32 sinf(f32);
f32 func_00121b08(f32);
f32 func_00120c88(f32);
void func_001247e8(B4A51 *);
void func_00137688(B4A51 *, f32);
void func_00151208(B4A51 *);
#define func_001315c0 ((void (*)(void *, s32, f32, void *)) func_001315c0)
#define func_00150ec8 ((s32 (*)(B4A51 *)) func_00150ec8)
#define func_00151010 ((void (*)(B4A51 *)) func_00151010)
#define func_00151148 ((void (*)(B4A51 *)) func_00151148)
void func_00151268(B4A51 *e) {
    f32 v[4];
    f32 u[4];
    f32 k;
    B4W51 *w = e->x144;
    if (!w) return;
    func_001315c0(D_002E26A0[0], 0x8003, 0.0f, v);
    if (w->x24 < 1.0f) {
        w->x24 += 0.09999999590218067169189453125f;
        if (1.0f < w->x24) w->x24 = 1.0f;
    }
    w->x2c = func_00121b08(w->x2c);
    e->x40 = e->x48 = e->x44 = w->x20;
    e->x44 *= w->x24;
    switch (w->x0) {
    case 0:
        if (func_00150ec8(e)) break;
        switch (w->x34) {
        case 0: func_00151010(e); break;
        case 1: func_00151148(e); break;
        }
        func_00151208(e);
        break;
    case 1:
        func_00150ec8(e);
        break;
    case 2:
        w->xc -= D_002BBDFC;
        if (!(0.0f < w->xc)) {
            func_001247e8(e);
            e->x144 = 0;
            w->x4 = 0;
            return;
        }
        k = w->xc / 30.0f;
        k = 1.0f - sinf((1.0f - k) * 3.1415928f * 0.5f);
        PlatVu0ScaleVector(u, w->x10, k);
        u[1] -= sinf(k * 3.1415928f) * 50.0f;
        func_00137688(e, func_00120c88(e->x3c + (1.0f - k) * 0.52359874546527862548828125f));
        PlatVu0AddVector(e->x10, v, u);
        if (k < 1.0f) e->x40 = e->x44 = e->x48 = w->x20 * k;
        PlatVu0CopyVector(e->x20, (*(f32 (*)[0x4])&D_002C58B0));
        break;
    case 3:
        w->xc -= 1.0f;
        if (w->xc <= 0.0f) {
            e->x0 &= ~3;
        } else {
            k = w->xc / D_00306840;
            e->x40 = e->x44 = e->x48 = w->x20 * k;
        }
        PlatVu0CopyVector(e->x20, (*(f32 (*)[0x4])&D_002C58B0));
        break;
    case 4:
        e->x0 |= 3;
        w->xc -= 1.0f;
        if (w->xc <= 0.0f) {
            k = 1.0f;
            *w->x4 &= ~0x30;
            PlatVu0CopyVector(e->x20, w->x10);
            w->x0 = 0;
        } else {
            k = 1.0f - w->xc / D_00306840;
            PlatVu0CopyVector(e->x20, (*(f32 (*)[0x4])&D_002C58B0));
        }
        e->x40 = e->x44 = e->x48 = w->x20 * k;
        break;
    }
}
#undef func_001315c0
#undef func_00150ec8
#undef func_00151010
#undef func_00151148

/* func_001515d0 (from hand/nostrict/text_00140000_h57.c). */
typedef struct { u8 pad0[3]; u8 b3; } Q57_15d0;
extern Kind57_15d0 D_003514E8[];
s32 func_0014f658(void *, s32);
void func_00137418(Obj57_15d0 *, f32);
Q57_15d0 *func_00147840(void *);
Obj57_15d0 *func_00124218(s32);
f32 func_00176850(void);
extern Slot57_15d0 D_0054F750_001515d0[8] __asm__("D_0054F750");
#define D_0054F750 D_0054F750_001515d0
s32 func_001515d0(void *owner, f32 *pos, s32 type) {
    Slot57_15d0 *best;
    Slot57_15d0 *e;
    s32 i;
    Q57_15d0 *q;
    Obj57_15d0 *o;

    best = 0;
    e = D_0054F750;
    for (i = 0; i < 8; i++, e++) {
        if (e->obj == 0) break;
        if (best == 0 || best->age > e->age) best = e;
    }
    if (i >= 8) {
        func_00137418(best->obj, 12.0f);
        best->obj->slot = 0;
        e = best;
    }
    q = func_00147840(owner);
    o = func_00124218(D_003514E8[q->b3].id);
    o->f40 = o->f44 = o->f48 = e->f20 = D_003514E8[q->b3].f4;
    e->owner = owner;
    e->obj = o;
    e->x0 = 0;
    e->f24 = 1.0f;
    e->age = D_0054F740++;
    e->x2c = 0;
    e->x34 = type;
    o->slot = e;
    o->flags |= 0x20;
    PlatVu0CopyVector(o->v10, pos);
    o->f20 = func_00176850() * 10.0f - 5.0f;
    o->f28 = func_00176850() * 10.0f - 5.0f;
    switch (type) {
    case 0:
        o->f24 = func_00176850() * 10.0f + -30.0f;
        break;
    case 1:
        o->f24 = func_00176850() * 10.0f + -20.0f;
        e->f30 = 1.0f;
        break;
    }
    return func_0014f658(o, 20);
}
#undef D_0054F750

/* func_001519c0 (from hand/nostrict/text_00150000_s8_w16.c). */
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; } G958;
extern G958 D_0054F958;
typedef struct { u8 pad[0x48]; s16 x48; } C130f;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x130 - 8]; C130f *x130; } Bf;
typedef struct { u8 pad[0x440]; u64 x440; } Af;
typedef union { u16 h; struct { u8 b0; u8 b1; } b; } Pf;
s32 func_001ba2f8(s32);
void func_001ef7b0(s32);
Pf *func_00147778(s32);
void func_0013c638(s32, s32);
void func_001586a8(s32);
void func_00130340(Af *, s32, f32);
void func_001373f8(Af *, f32);
s32 func_001337e0(s32, Bf *, G958 *);
#define func_0013c9e0 ((u8 (*)(s32, s32)) func_0013c9e0)
s32 func_001519c0(Af *a, Bf *b) {
    s32 k;
    s32 e;
    Pf *p;

    k = b->x130->x48;
    D_0054F958.x0 = b->x4;
    D_0054F958.x10 = 0;
    e = D_00351530[k].h;
    D_0054F958.x4 = k;
    D_0054F958.xc = (u16)e >> 4;
    D_0054F958.x8 = ((u16)e >> 1) & 7;
    switch (D_0054F958.x8) {
    case 0:
        D_0054F958.x10 = func_0013c9e0((e & 0xffff) >> 4, 12) == 0xff;
        break;
    case 1:
        D_0054F958.x10 = func_001ba2f8((e & 0xffff) >> 4) == 0;
        break;
    case 3:
        D_0054F958.xc *= 10;
        func_001ef7b0(D_0054F958.xc);
        break;
    case 7:
        e = D_0054F958.xc;
        p = func_00147778(e);
        if (!(p->h & 0xf)) {
            D_0054F958.x8 = 0;
            D_0054F958.xc = p->b.b1;
            D_0054F958.x10 = func_0013c9e0(p->b.b1, 12) == 0xff;
        }
        break;
    case 2: case 4: case 5: case 6:
        break;
    }
    if (!D_0054F958.x10) {
        func_0013c638(k, 1);
        func_001586a8(16);
    }
    a->x440 |= 0x200000000ULL;
    func_00130340(a, 0x900a6, 0.0f);
    func_001373f8(a, 0.0f);
    return func_001337e0(5, b, &D_0054F958);
}
#undef func_0013c9e0

/* func_00151b98 (from hand/nostrict/text_00140000_h34.c). */
void *func_00147138(void *, s32);
typedef struct { u8 pad[4]; s32 x4; u16 x8; } W34Fx;
typedef struct { u8 pad[0x10]; W34Fx *x10; } W34Sx;
typedef struct { u8 pad[0x14]; f32 x14; u8 pad18[0x108]; f32 x120[4]; } W34Gnd;
typedef struct { u8 pad[0x14]; f32 x14; u8 pad18[0x58]; s32 x70; u8 pad74[0x24]; W34Gnd *x98; u8 pad9c[0x144 - 0x9c]; W34Sx *x144; } W34Pl7;
void func_00147278(s32, s32, s32);
void func_00151b98(W34Pl7 *o, f32 *v) {
    W34Sx *s = o->x144;
    if (o->x70 == 0) {
        if (v[0] == 0.0f || v[2] == 0.0f) {
            if (o->x98 && fabsf(o->x14 + v[1] - o->x98->x14) >= 10.0f) goto zero;
        } else {
        zero:
            PlatVu0CopyVector(v, (*(f32 (*)[0x4])&D_002C58A0));
        }
    }
    if (v[0] != 0.0f || v[2] != 0.0f) {
        if (o->x98) {
            if (!s->x10) s->x10 = func_00147138(o, 0);
            PlatVu0AddVector(o->x98->x120, o->x98->x120, v);
        }
    } else if (s->x10) {
        func_00147278(s->x10->x8, s->x10->x4, 60);
        s->x10 = 0;
    }
}

/* func_00151cd0 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { s32 x0; } W34Cnt;
typedef struct { u8 pad[0x144]; W34Cnt *x144; } W34Pl8;
typedef struct { u8 pad[0x68]; s32 x68; } W34P68;
void func_00147ed8(s32, s32, s32, f32 *);
#define func_001315c0 ((void (*)(void *, s32, f32 *, f32)) func_001315c0)
#define func_001247e8 ((void (*)(void *)) func_001247e8)
void func_00151cd0(W34Pl8 *o) {
    f32 v[4] __attribute__((aligned(16)));
    func_001315c0(o, 0x8003, v, 0.0f);
    func_00147ed8(((W34P68 *)o)->x68, 0, 20000, v);
    func_001247e8(o);
}
#undef func_001315c0
#undef func_001247e8

/* func_00151d20 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { u8 pad[8]; s32 x8; u8 padc[4]; f32 x10[4]; } W34Hit;
W34Hit *func_00134928(W34Pl8 *);
void func_001350d0(W34Hit *);
void func_00145008(W34Pl8 *, s32);
void func_00156260(W34Pl8 *, f32 *);
void func_00151d20(W34Pl8 *o) {
    W34Cnt *c = o->x144;
    W34Hit *e;
    while ((e = func_00134928(o))) {
        s32 n = e->x8;
        func_00147138(o, 4);
        if (n > 0) {
            c->x0 += n;
            if (c->x0 >= 7) {
                func_00145008(o, 0);
                func_00151cd0(o);
            } else {
                f32 d[4] __attribute__((aligned(16)));
                PlatVu0CopyVector(d, e->x10);
                if (fabsf(d[0]) > fabsf(d[2])) d[2] = 0.0f;
                else d[0] = 0.0f;
                PlatVu0Normalize(d, d);
                d[3] = 15.0f;
                func_00156260(o, d);
            }
        }
        func_001350d0(e);
    }
}

/* func_00151fa0 (from hand/nostrict/text_00150000_1.c). */
M2C_UNK func_00137308(void *, void *);
f32 atan2f(f32, f32);
f32 fabsf(f32);
s32 func_0014f600(void *);
s32 func_00151e28();
#define func_0014f658 ((M2C_UNK (*)(void *, M2C_UNK)) func_0014f658)
#define func_00151cd0 ((M2C_UNK (*)(void *)) func_00151cd0)
void func_00151fa0(void *arg0) {
    s32 sp[4];    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f12;
    f32 var_f13;
    void *temp_a0;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x144);
    if (func_00151e28() != 0) {
        temp_f0 = M2C_FIELD(temp_s1, f32 *, 4) + D_002BBDFC;
        M2C_FIELD(temp_s1, f32 *, 4) = temp_f0;
        if (temp_f0 > 12.0f) {
            func_00137308(arg0, M2C_FIELD(arg0, void **, 8));
            PlatVu0CopyVector(sp, M2C_FIELD(arg0, void **, 8) + 0x30);
            var_f12 = M2C_FIELD(sp, f32 *, 0x0);
            var_f13 = M2C_FIELD(sp, f32 *, 0x8);
            if (fabsf(var_f13) < fabsf(var_f12)) {
                var_f13 = 0.0f;
                M2C_FIELD(sp, f32 *, 0x8) = 0.0f;
            } else {
                var_f12 = 0.0f;
                M2C_FIELD(sp, f32 *, 0x0) = 0.0f;
            }
            M2C_FIELD(M2C_FIELD(arg0, void **, 8), f32 *, 0x150) = atan2f(var_f12, var_f13);
            func_0014f658(M2C_FIELD(arg0, void **, 8), 0x1B);
        }
    } else {
        M2C_FIELD(temp_s1, f32 *, 4) = 0.0f;
    }
    temp_a0 = M2C_FIELD(arg0, void **, 8);
    if ((temp_a0 != NULL) && (func_0014f600(temp_a0) != 0)) {
        temp_f0_2 = M2C_FIELD(temp_s1, f32 *, 0xC) + D_002BBDFC;
        M2C_FIELD(temp_s1, f32 *, 0xC) = temp_f0_2;
        if (temp_f0_2 >= 1.2e+02f) {
            func_00151cd0(arg0);
        }
    } else {
        M2C_FIELD(temp_s1, f32 *, 0xC) = 0.0f;
    }
}
#undef func_0014f658
#undef func_00151cd0

/* func_00152140 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { s32 x0; s32 x4; f32 x8; s32 xc; s32 x10; } W34St20;
typedef struct { u32 x0; u8 pad4[0x6c]; s32 x70; u8 pad74[0x144 - 0x74]; W34St20 *x144; u8 pad148[0x4a0 - 0x148]; void (*x4a0)(); } W34Pl9;
W34St20 *func_00121e28(s32, W34St20 **);
void func_001520e0();
void func_001520c0(W34Pl9 *);
#define func_00151fa0 ((s32 (*)(W34Pl9 *)) func_00151fa0)
s32 func_00152140(W34Pl9 *o) {
    W34St20 *s = o->x144;
    if (!s) {
        s = func_00121e28(20, &o->x144);
        s->x0 = 0; s->x4 = 0; s->x8 = 0.0f; s->xc = 0; s->x10 = 0;
        o->x4a0 = func_001520e0;
    }
    if (o->x0 & 0x400) {
        switch (o->x70) {
        case 0:
            if (s->x8 >= 60.0f) func_00151cd0((W34Pl8 *)o);
            else func_00147138((W34Pl8 *)o, 2);
            s->x4 = 0;
            break;
        case 2:
            s->x8 = 0.0f;
            break;
        }
    }
    func_00151d20((W34Pl8 *)o);
    switch (o->x70) {
    case 0:
        return func_00151fa0(o);
    case 2:
        func_001520c0(o);
        break;
    }
}
#undef func_00151fa0

/* func_00152250 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { u8 pad[0x30]; f32 x30[4]; u8 pad40[0x58]; s32 x98; u8 pad9c[0x150 - 0x9c]; f32 x150; } W34Pl10;
s32 func_00122ff8(s32);
void func_00130578(W34Pl10 *, s32, f32);
#define func_0014f658 ((void (*)(void *, s32)) func_0014f658)
#define func_00130340 ((s32 (*)(W34Pl10 *, s32, f32)) func_00130340)
void func_00152250(W34Pl10 *o, s32 b, f32 *v) {
    if (v[3] > 0.0f && PlatVu0InnerProduct(o->x30, v) > 0.766f && func_00122ff8(o->x98)) {
        if (fabsf(v[0]) > fabsf(v[2])) v[2] = 0.0f;
        else v[0] = 0.0f;
        PlatVu0Normalize(v, v);
        v[3] = 3.0f;
        o->x150 = atan2f(v[0], v[2]);
    } else {
        func_00130340(o, 0x10000be, 6.0f);
        func_00130578(o, 0x40000000, 0.0f);
        func_0014f658(o, 0);
        PlatVu0CopyVector(v, o->x30);
        v[3] = 0.0f;
    }
}
#undef func_0014f658
#undef func_00130340

