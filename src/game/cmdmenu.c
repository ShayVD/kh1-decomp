/* The command menu (a guess from the code): the command lists in D_002E2FD8
 * (func_0012cb78 / func_0012cc38 add an entry, func_0012cb40 sets one), the
 * submenu stack D_00524F40 over D_002E3170 (func_0012dce0 pushes,
 * func_0012dd38 pops), the pad input func_0012e1b0, the choice func_0012dea0
 * (an entry's record from func_001478c8; a beep through func_0011d768 when
 * it is greyed out), the per-frame update func_0012e4b0; then the action
 * command: its target and kind D_002E31B0 / D_002E31B8 (func_0012fb20 sets
 * them, func_0012fc20 clears, func_0012f868 picks the nearest target) and
 * the range test func_0012fa98. Flag mode: default (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_00304BE8.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E27A4.h"
#include "data/pieces/D_002C5C48.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"
#include "data/types/text_00120000_h5.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/pieces/D_00308CDC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002BC098.h"
#include "actor.h"
#include "data/pieces/D_002C6440.h"
#include "data/pieces/D_002E319C.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E2F28.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002BBDE4.h"

/* func_0012ca98 (from auto/text_00120000_2.c). */
s32 func_0012ca98(void) {
    return (((s32) M2C_FIELD(D_00304BE8, s32 *, 0x874) >> 1) ^ 1) & 1;
}

/* func_0012cab8 (from auto/text_00120000_2.c). */
extern s32 D_00524F74;
void func_0012cab8(s32 arg0) {
    D_00524F74 = arg0;
}

/* func_0012cac8 (from auto/text_00120000_2.c). */
void func_0012cac8(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        M2C_FIELD(D_00304BE8, s32 *, 0x874) = (s32) (M2C_FIELD(D_00304BE8, s32 *, 0x874) | (1 << arg0));
        return;
    }
    M2C_FIELD(D_00304BE8, s32 *, 0x874) = (s32) (M2C_FIELD(D_00304BE8, s32 *, 0x874) & ~(1 << arg0));
}

/* func_0012cb18 (from auto/text_00120000_8.c). */
extern s32 D_002E2FD8[];
void func_0012cb18(void) {
    D_002E2FD8[30] = -1;
    D_002E2FD8[1] = (s32) (D_002E2FD8[1] | 4);
    D_002E2FD8[29] = -1;
}

/* func_0012cb40 (from hand/text_00120000_h5.c). */
typedef struct Sub { u32 m0; u32 m1; u8 pad[8]; u8 arr[8]; } Sub;
typedef struct E6 { u8 pad[4]; Sub s; } E6;
void func_0012cb40(E6 *a, s32 i, u8 v) {
    Sub *s = &a->s;
    u32 m;
    s->arr[i] = v;
    m = ~(1 << i);
    s->m0 &= m;
    a->s.m1 &= m;
}

/* func_0012cb78 (from hand/text_00120000_h31.c). */
extern void *D_00524F58[];
typedef struct { u8 pad[0x10]; volatile s32 n; } Q14;
typedef struct {
    u8 pad0[4];
    s32 f4;
    s32 f8;
    u8 padc[8];
    u8 f14, f15, f16, f17;
    u8 pad18[0xe0 - 0x18];
    Q14 a;
    u8 pad2[0x150 - 0xf4];
    Q14 b;
} D14;
extern s32 D_002E3160[];
extern volatile u32 D_00524F44;
#define func_0012cb40 ((void (*)(Q14 *, s32, s32)) func_0012cb40)
static inline s32 add(Q14 *q, s32 x) {
    s32 i = q->n++;
    func_0012cb40(q, i, x);
    return i;
}
#define D_002E2FD8 (*(D14 (*)) &D_002E2FD8)
void func_0012cb78(s32 v, s32 x) {
    D14 *d = &D_002E2FD8;
    s32 i = add(&d->a, x);
    s32 j = add(&d->b, x);
    D_002E3160[j] = v;
    D_00524F58[i] = (void *)v;
    D_00524F44 |= 0x10;
}
#undef D_002E2FD8
#undef func_0012cb40

/* func_0012cc38 (from auto/text_00120000_9.c). */
#define func_0012cb40 ((M2C_UNK (*)(M2C_UNK *, s32, s32)) func_0012cb40)
#define D_002E2FD8 (*(M2C_UNK (*)) &D_002E2FD8)
extern s32 D_00524F44_0012cc38 __asm__("D_00524F44");
#define D_00524F44 D_00524F44_0012cc38
s32 func_0012cc38(s32 arg0, s32 arg1) {
    if (!(((s32) D_00524F44 >> arg0) & 1)) {
        func_0012cb40(&D_002E2FD8, arg0, arg1);
        D_00524F44 |= 1 << arg0;
        return 1;
    }
    return 0;
}
#undef func_0012cb40
#undef D_002E2FD8
#undef D_00524F44

/* func_0012ccb0 (from hand/text_00120000_h5.c). */
extern struct { u8 pad[4]; u32 f4; u32 f8; s32 f0c; } D_002E2FD8_0012ccb0 __asm__("D_002E2FD8");
#define D_002E2FD8 D_002E2FD8_0012ccb0
extern u32 D_00524F44_0012ccb0 __asm__("D_00524F44");
#define D_00524F44 D_00524F44_0012ccb0
void func_0012ccb0(s32 i) {
    u32 m = 1 << i;
    D_002E2FD8.f4 |= m;
    D_002E2FD8.f8 |= m;
    D_00524F44 &= ~m;
}
#undef D_002E2FD8
#undef D_00524F44

/* func_0012ccf8 (from auto/text_00120000_3.c). */
extern M2C_UNK D_002E2FEC;
u8 func_0012ccf8(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_002E2FEC + arg0);
}

/* func_0012cf38 (from auto/text_00120000_2.c). */
s32 func_0012cf38(s32 *arg0, s32 *arg1) {
    return *arg0 - *arg1;
}

typedef struct Actor_2d818 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0xf0];
    s32 f164;
    u8 pad168[0x172];
    u16 f2da;
    u8 pad2dc[0x94];
    u64 f370;
} O16;

/* func_0012d068 (from hand/text_00120000_h31.c). */
extern s32 func_00122ff8(void *);
typedef struct { u8 pad[0x30]; u32 f30; } P16;
typedef struct { u8 pad[0x14c]; P16 *f14c; u8 pad150[0x14]; s32 f164; } E16;
extern s32 D_002BC128;
extern s32 D_002BC130;
#define D_002E2FD8 (*(D14 (*)) &D_002E2FD8)
void func_0012d068(E16 *e, u32 *fl) {
    D14 *d = &D_002E2FD8;
    s32 v;
    if (D_002BC128 == 6 || (D_002BC128 == 16 && D_002BC130 == 24)) {
        d->f14 = 98;
    } else if ((((*(u32 *)&D_002E27C8) >> 2) & 1) && func_00122ff8((void *)D_002E31B0.f0)
               && ((s32)(((O16 *)D_002E31B0.f0)->f370 >> 37) & 3) == 2 && e->f164 == 110
               && (e->f14c->f30 & ~0x102)) {
        d->f14 = 99;
    } else {
        d->f14 = 1;
    }

    d->f15 = 66;
    d->f16 = 66;
    d->f17 = 66;
    v = ((*fl >> 4) & 1) ? -2 : -1;
    d->f4 = d->f8 = v;
}
#undef D_002E2FD8

/* func_0012d368 (from hand/text_00120000_h31.c). */
extern D17 D_002E30F0;
extern s32 func_00132fe0(s32);
void func_0012d368(s32 a0, s32 a1, s32 *fl) {
    D17 *d = &D_002E30F0;
    s32 mask = -1;
    s32 i;
    for (i = 0; i < 3; i++) {
        s32 id = D_00304BE8->x844[i];
        if (id == -1) {
            d->f14[i] = 66;
        } else {
            d->f14[i] = id * 3 + func_00132fe0(id) + 6;
            if (fl[id]) mask &= ~(1 << i);
            D_00524F50 = 1;
        }
    }
    d->f4 = d->f8 = mask;
}

/* func_0012d818 (from hand/text_00120000_h31.c). */
typedef struct { u8 pad[0x10]; s32 f10; u8 f14[4]; } D18;
typedef O16 E18;
extern D18 D_002E30B8;
extern s32 D_002E3138;
extern s32 func_0013daa8(s32);
extern s32 func_0012f040(E18 *, s32);
void func_0012d818(void) {
    s32 i, n, k;
    u8 id;
    E18 *e;
    D18 *d = &D_002E30B8;
    n = 0;
    for (i = 0; i < 3; i++) {
        id = D_00304BE8->x48e[i];
        if (id == 0xff) continue;
        k = func_0013daa8(id);
        if (k < 0) continue;
        e = D_002E26A0[k];
        if (!func_0012f040(e, -1)) continue;
        if (!(e->f0 & 0x8000)) continue;
        d->f14[n] = id + 56;
        D_00524F58[n] = e;
        n++;
    }
    d->f10 = n;
    D_002E3138 = 1;
}

/* func_0012dc70 (from auto/text_00120000_3.c). */
s32 func_0012d930(s32);
void func_0012d468(s32, s32);
void func_0012d6c0(s32, s32);
#define func_0012d068 ((void (*)(s32, s32)) func_0012d068)
void func_0012dc70(void) {
    void *temp_s0;
    void *temp_s1;

    temp_s1 = D_002E26A0[0];
    temp_s0 = ((s8 *)&D_00350D88) + (M2C_FIELD(temp_s1, s32 *, 0x70) << 5);
    func_0012d068((s32) temp_s1, (s32) temp_s0);
    func_0012d468((s32) temp_s1, (s32) temp_s0);
    func_0012d6c0((s32) temp_s1, (s32) temp_s0);
    func_0012d818();
    func_0012d930((s32) temp_s0);
}
#undef func_0012d068

/* func_0012dce0 (from hand/text_00120000_h5.c). */
extern void **D_00524F40;
extern void func_0011d768(s32);
typedef struct E7 { s32 f0; u8 pad[8]; s32 f0c; } E7;
void func_0012dce0(E7 *e) {
    if (e) {
        *++D_00524F40 = e;
        func_0011d768(6);
        if (e->f0 == 4) e->f0c = 0;
    }
}

/* func_0012dd38 (from auto/text_00120000_15.c). */
extern u32 D_00524F40_0012dd38 __asm__("D_00524F40");
#define D_00524F40 D_00524F40_0012dd38
s32 func_0012dd38(void) {
    u32 temp_a1;
    u32 var_a0;

    var_a0 = D_00524F40;
    temp_a1 = var_a0 - 4;
    if ((u32) &D_002E3170 < var_a0) {
        *(M2C_UNK *)var_a0 = 0;
        D_00524F40 = temp_a1;
        var_a0 = temp_a1;
    }
    return *(M2C_UNK *)var_a0;
}
#undef D_00524F40

/* func_0012e120 (from auto/text_00120000_3.c). */
s32 func_0012dea0(void *, s32);
#define D_002E2FD8 (*(M2C_UNK (*)) &D_002E2FD8)
void func_0012e120(void) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;

    temp_a0 = *D_00524F40;
    if (func_0012dea0(temp_a0, M2C_FIELD(temp_a0, s32 *, 0xC)) != 0) {
        temp_a1 = *D_00524F40;
        if (temp_a1 == &D_002E2FD8) {
            if (!(D_002E319C->f0 & 0x10)) {
                M2C_FIELD(temp_a1, s32 *, 0xC) = 0;
            }
        }
    } else {
        temp_a0_2 = M2C_FIELD(D_002E26A0[0], void **, 0x14C);
        M2C_FIELD(temp_a0_2, s32 *, 0x28) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 0x28) & 0xFFFEFFFF);
    }
}
#undef D_002E2FD8

/* func_0012e970 (from hand/text_00120000_h31.c). */
extern volatile s32 D_00524F48;
extern void func_0023b4b8(s32);
s32 func_0012e970(void) {
    s32 ch;
    s32 cur = D_00524F48;
    ch = D_00524F4C;
    ch ^= cur;
    D_00524F4C = cur;
    if (ch & 1) {
        if (cur & 1) {
            func_0023b4b8(3);
            D_00524F48 &= ~4;
        } else {
            func_0023b4b8(2);
            D_00524F48 |= 4;
        }
    } else if (ch & 2) {
        if (cur & 2) {
            if (!(cur & 4)) {
                func_0023b4b8(1);
                D_00524F48 |= 4;
            }
        } else if (cur & 4) {
            func_0023b4b8(0);
            D_00524F48 &= ~4;
        }
    }
    return 0;
}

/* func_0012eaf8 (from auto/text_00120000.c). */
s32 func_0012eaf8(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), s32 *, 4) & 0x1000;
}

/* func_0012eb08 (from hand/text_00120000_h5.c). */
extern float fabsf(float);
f32 func_0012ed88();
#define func_0012f040 ((s32 (*)(struct Actor_2eb08 *, s32)) func_0012f040)
#define func_0012eaf8 ((s32 (*)(s32)) func_0012eaf8)
#define func_0012ed88 ((f32 (*)(void *, void *, void *, void *)) func_0012ed88)
s32 func_0012eb08(s32 *p) {
    f32 a[4];
    f32 b[4];
    if (!func_0012f040(D_002E31B0.f0, D_002E31B0.f4)) return 1;
    if (func_0012eaf8(*p)) {
        if (func_0012ed88(D_002E26A0[0], p, a, b) > 1500.0f) return 1;
        if (fabsf(b[1]) > 1000.0f) return 1;
    }
    return 0;
}
#undef func_0012f040
#undef func_0012eaf8
#undef func_0012ed88

/* func_0012eba0 (from hand/text_00120000_h31.c). */
typedef struct { u16 h0; u16 h2; f32 f4, f8, fc; } P21;
typedef struct { u8 pad[5]; u8 b5; u8 pad6[0xe]; P21 *f14; } I21;
typedef struct { u8 pad[0x10]; f32 f10[12]; f32 f40, f44; u8 pad48[0x134 - 0x48]; I21 *f134; } E21;
extern P21 *func_0015c960(E21 *, s32, s32, s32);
extern void func_001315c0(E21 *, s32, f32 *, f32);
f32 func_0012eba0(E21 *e, s32 a, s32 b, s32 c, f32 *out) {
    P21 *p = func_0015c960(e, a, b, c);
    f32 r;
    if (!p) {
        I21 *i = e->f134;
        if (i && i->b5) p = i->f14;
    }
    if (!p) {
        PlatVu0CopyVector(out, e->f10);
        r = 0.0f;
    } else {
        func_001315c0(e, p->h2, out, p->f4);
        out[1] -= p->f8 * e->f44;
        r = p->fc * e->f40;
    }
    out[3] = 1.0f;
    return r;
}

/* func_0012ec60 (from auto/text_00120000_3.c). */
#define func_0012eba0 ((f32 (*)(s32, s32, s32, s32, s32)) func_0012eba0)
f32 func_0012ec60(s32 arg0, s32 arg1, s32 arg2) {
    return func_0012eba0(arg0, 0, -1, arg1, arg2);
}
#undef func_0012eba0

/* func_0012ec88 (from auto/text_00120000_4.c). */
#define func_0012ec60 ((f32 (*)(s32, s32, s32)) func_0012ec60)
f32 func_0012ec88(s32 arg0, s32 arg1) {
    return func_0012ec60(arg0, 0, arg1);
}
#undef func_0012ec60

/* func_0012eca8 (from auto/text_00120000_3.c). */
#define func_001315c0 ((f32 (*)(void *, u16, void *, f32)) func_001315c0)
#define func_0015c960 ((u8 *(*)(void *, M2C_UNK, u32, s32)) func_0015c960)
f32 func_0012eca8(void *arg0, void *arg1) {
    u8 *var_s0;
    void *temp_a0;
    void *temp_v1;

    var_s0 = func_0015c960(M2C_FIELD(arg0, void **, 0), 0, -1U, M2C_FIELD(arg0, s32 *, 4));
    if (var_s0 != NULL) {
        var_s0 = func_0015c960(M2C_FIELD(arg0, void **, 0), 2, (u8) *var_s0 >> 4, 0);
        if (var_s0 != NULL) {
            goto block_9;
        }
        goto block_4;
    }
block_4:
    temp_a0 = M2C_FIELD(arg0, void **, 0);
    temp_v1 = M2C_FIELD(temp_a0, void **, 0x134);
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, u8 *, 5) != 0)) {
        var_s0 = M2C_FIELD(temp_v1, u8 **, 0x14);
    }
    if (var_s0 == NULL) {
        PlatVu0CopyVector(arg1, temp_a0 + 0x10);
        return 0.0f;
    }
block_9:
    func_001315c0(M2C_FIELD(arg0, void **, 0), M2C_FIELD(var_s0, u16 *, 2), arg1, M2C_FIELD(var_s0, f32 *, 4));
    M2C_FIELD(arg1, f32 *, 4) = (f32) (M2C_FIELD(arg1, f32 *, 4) - (M2C_FIELD(var_s0, f32 *, 8) * M2C_FIELD(M2C_FIELD(arg0, void **, 0), f32 *, 0x44)));
    return M2C_FIELD(var_s0, f32 *, 0xC);
}
#undef func_001315c0
#undef func_0015c960

/* func_0012ed88 (from hand/text_00120000_h31.c). */
typedef S31b0_2e31b0 S31b0;
extern void func_00121fc4(f32 *, f32 *);
typedef struct { u8 pad[0x10]; f32 f10[16]; } E22;
static inline f32 fmx(f32 a, f32 b) { return (b < a) ? a : b; }
#define func_0012ec60 ((f32 (*)(struct Actor_2ed88 *, s32, f32 *)) func_0012ec60)
f32 func_0012ed88(E22 *e, S31b0 *s, f32 *pos, f32 *out) {
    f32 r = func_0012ec60(s->f0, s->f4, pos);
    f32 y, w;
    PlatVu0SubVector(out, pos, e->f10);
    if (0.0f < out[1]) {
        y = 0.0f;
        if (0.0f < out[1] - r) y = out[1] - r;
    } else {
        f32 t = out[1] + r;
        y = (t < 0.0f) ? t : 0.0f;
    }
    out[1] = 0.0f;
    func_00121fc4(out, out);
    w = fmx(out[3] - r, 0.0f);
    out[1] = y;
    out[3] = w;
    return w;
}
#undef func_0012ec60

/* func_0012ee70 (from hand/text_00120000_h31.c). */
typedef struct { u8 b0; u8 pad[19]; } T23;
typedef struct { u8 pad[7]; u8 b7; u8 pad8[0x14]; T23 *f1c; } I23;
typedef struct { u8 pad[0x134]; I23 *f134; u8 pad138[0x3ac - 0x138]; u32 f3ac; } E23;
s32 func_0012ee70(E23 *e, s32 i) {
    I23 *m = e->f134;
    if (i < 0) {
        if (!m || !m->b7) return 0;
        i = 0;
    } else {
        if (!m || !m->b7) return -1;
        i++;
    }
    for (; i < e->f134->b7; i++) {
        if (!(e->f3ac & (1 << i)) && !(e->f134->f1c[i].b0 & 0xf)) return i;
    }
    return -1;
}

/* func_0012ef30 (from hand/text_00120000_h31.c). */
extern void *func_00123158(void *, void *);
extern f32 func_00121748(f32 *, f32 *);
typedef struct { u8 pad[0x10]; f32 f10[4]; } T24;
extern f32 func_00120bf8(f32 *);
T24 *func_0012ef30(void *e, f32 *mat, f32 *dir, f32 maxd) {
    T24 *p, *best = 0;
    f32 bd = maxd;
    f32 d;
    f32 v[4];
    for (p = func_00123158(e, 0); p; p = func_00123158(e, p)) {
        PlatVu0SubVector(v, p->f10, mat);
        d = func_00120bf8(v);
        if (d < maxd) {
            d *= (1.0f - func_00121748(v, dir)) * dir[3] + 1.0f;
            if (best == 0 || d < bd) {
                bd = d;
                best = p;
            }
        }
    }
    return best;
}

/* func_0012f0f8 (from hand/text_00120000_h31.c). */
typedef struct { f32 a[4]; f32 b[4]; u8 pad[16]; s16 h30; s16 pad2; u8 pad3[12]; } S0f8;
extern s32 func_00119788(void *);
extern s32 func_00119688(void *);
extern void func_00118648(void *);
s32 func_0012f0f8(void *p, void *q, u32 mode) {
    S0f8 s;
    u8 r;
    PlatVu0CopyVector(s.a, p);
    PlatVu0SubVector(s.b, q, p);
    r = 0;
    s.a[3] = 1.0f;
    s.b[3] = 1.0f;
    switch (mode) {
    case 0:
        r = func_00119788(&s) < 0;
        break;
    case 1:
        r = func_00119688(&s) < 0;
        break;
    case 2:
        func_00118648(&s);
        if (s.h30 < 0) r = (u32)func_00119688(&s) >> 31;
        break;
    }
    return r;
}

/* func_0012f1d0 (from auto/text_00120000_8.c). */
#define func_0012f0f8 ((s32 (*)(s32, s32, s32)) func_0012f0f8)
#define func_001315c0 ((void (*)(s32, s32, s32, f32)) func_001315c0)
s32 func_0012f1d0(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_001315c0(arg1, 0x8003, (s32) sp, 0.0f);
    return func_0012f0f8(arg0, (s32) sp, 0);
}
#undef func_0012f0f8
#undef func_001315c0

/* func_0012f5c0 (from hand/text_00120000_h31.c). */
extern P5c0 D_00524F80[];
extern P5c0 *D_00525288;
extern void func_0012f3d0(P5c0 *);
extern void func_0012f560(P5c0 *);
void func_0012f5c0(P5c0 *e) {
    P5c0 *c = D_00525288;
    if (c - D_00524F80 < D_0052528C - 1) {
        D_00525288 = c + 1;
        *e = c[1];
        return;
    }
    func_0012f3d0(e);
    if (e->a) {
        func_0012f560(e);
        return;
    }
    if (D_00525288 != D_00524F80) {
        D_00525288 = D_00524F80;
        *e = D_00524F80[0];
    }
}

/* func_0012fa98 (from hand/text_00120000_h5.c). */
typedef O8_2e319c S31a0;
extern s32 D_002E31BC;
#define func_0012ed88 ((f32 (*)(void *, void *, void *, void *)) func_0012ed88)
void func_0012fa98(void) {
    f32 a[4];
    f32 b[4];
    f32 d = func_0012ed88(D_002E26A0[0], &D_002E31B0, a, b);
    s32 *o = &D_002E31BC;
    S31a0 *x = D_002E31A0;
    s32 r = 0;
    if (x) {
        if (!(d < x->f0c)) {
            if (d < x->f0e) r = 1;
            else r = 2;
        }
        *o = r;
    }
}
#undef func_0012ed88

/* func_0012fb20 (from hand/text_00120000_h31.c). */
typedef struct Actor_2fb20 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0xf0];
    s32 f164;
    u8 pad168[0x172];
    u16 f2da;
    u8 pad2dc[0x94];
    u64 f370;
} O16_2fb20;
typedef O16_2fb20 E18_2fb20;
typedef E18_2fb20 Gb20;
extern s32 D_00524F78;
extern void func_001337e0(s32, struct Actor_2fb20 *, s32);
extern void func_00123030(Gb20 *, struct Actor_2fb20 *, s32);
extern void func_0017ef40(struct Actor_2fb20 *);
void func_0012fb20(S31b0 *e, s32 m) {
    switch (m) {
    case 3:
        func_001337e0(3, e->f0, 0);
        if ((D_00350D88[((O16_2fb20 *)D_002E26A0[0])->f70].f0 >> 2) & 1) func_0011d768(68);
        break;
    case 4:
        D_00524F78 = 0;
        break;
    }
    if (D_002E26A0[0]) func_00123030(D_002E26A0[0], e->f0, e->f4);
    if (m >= 3) func_0017ef40(e->f0);
    D_002E31B0 = *e;
    D_002E31B8 = m;
    D_002E31BC = 0;
    func_0012fa98();
}

/* func_0012fc20 (from auto/text_00120000_6.c). */
extern s32 D_00525288_0012fc20 __asm__("D_00525288");
#define D_00525288 D_00525288_0012fc20
void func_0012fc20(void) {
    M2C_FIELD(&D_002E31B0, s32 *, 0) = 0;
    D_002E31B8 = 0;
    M2C_FIELD(&D_002E31B0, s32 *, 4) = -1;
    D_00525288 = 0;
    D_0052528C = 0;
    D_002E31BC = 0;
}
#undef D_00525288

/* func_0012fc58 (from auto/text_00120000_2.c). */
M2C_UNK func_0017eff8();
#define func_00123030 ((M2C_UNK (*)(s32, M2C_UNK, M2C_UNK)) func_00123030)
#define func_0012fc20 ((M2C_UNK (*)()) func_0012fc20)
void func_0012fc58(void) {
    if (D_002E31B8 != 0) {
        if (D_002E31B8 >= 3) {
            func_0017eff8();
        }
        func_0012fc20();
        if ((*(s32 *)&D_002E26A0) != 0) {
            func_00123030((*(s32 *)&D_002E26A0), 0, 0);
        }
    }
}
#undef func_00123030
#undef func_0012fc20

/* func_0012fcc0 (from auto/text_00120000_2.c). */
void func_0012fcc0(void) {
    D_00524F78 = 0;
}

/* func_0012ff80 (from auto/text_00120000_4.c). */
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
void func_0012fcd0();
s32 func_0011ef38(M2C_UNK *);
#define func_0012fc20 ((M2C_UNK (*)()) func_0012fc20)
void func_0012ff80(void) {
    func_0012fc20();
    if (func_0011ef38(&func_0012fcd0) == 0) {
        func_0011ef10(0x14C08, &func_0012fcd0);
    }
}
#undef func_0012fc20

/* func_0012ffd0 (from auto/text_00120000.c). */
s32 func_0012ffd0(void *arg0) {
    s32 var_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0x398);
    var_v0 = 0;
    if (temp_v1 != NULL) {
        temp_v1_2 = M2C_FIELD(temp_v1, void **, 0x3A0);
        if (temp_v1_2 != NULL) {
            var_v0 = M2C_FIELD(temp_v1_2, u8 *, 6) == 3;
        }
    }
    return var_v0;
}

