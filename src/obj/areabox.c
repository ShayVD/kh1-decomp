/* The room's area boxes D_00350D78 (a set of boxes with group ids;
 * func_0014f1b8 installs a set, func_0014e5b8 says which boxes hold a point,
 * func_0014ee88 which ones an object's capsule touches, func_0014f028 tracks
 * the leader's box each frame, func_0014e878 picks a spawn position in a
 * box), the per-group state D_0054F450 and the masks D_0054F448 /
 * D_0054F44C, and func_0014e510 counts the live objects of a key. Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h34.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_00350D78.h"
#include "data/types/text_00140000_h57_p.h"
#include "data/types/text_00140000_h57.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58D0.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/types/text_00140000_h9.h"

/* func_0014e510 (from hand/text_00140000_h34.c). */
typedef struct { u8 pad[0x3c]; s32 cur; s32 max; s32 mcur; s32 mmax; } W34St;
typedef union { u64 x; struct { u32 lo; u32 l19:19; u32 b51:1; u32 hi:12; } b; } W34F370;
typedef struct { u8 pad[0x6c]; W34St *st; u8 pad70[0x370 - 0x70]; W34F370 x370; } W34Act;
W34Act *func_00123488(u32);
typedef struct { s32 x0; u8 pad4[0x44]; s16 x48; u8 pad4a[0xe]; u8 x58; u8 x59; } W34Ent;
W34Ent *func_00132040(W34Ent *);
s32 func_00142240(s32);
s32 func_0014e510(s32 key) {
    W34Ent *p = 0;
    s32 n = 0;
    while ((p = func_00132040(p))) {
        if (p->x58 == key) {
            W34Act *a = func_00123488(p->x0);
            if (!a) {
                if (func_00142240(p->x0) != 1) n++;
            } else if (!a->x370.b.b51) n++;
        }
    }
    return n;
}

/* func_0014e5b8 (from hand/text_00140000_h34.c). */
s32 func_0014e5b8(f32 *p) {
    Box57_f1b8 *b;
    s32 m, n, i;
    if (!D_00350D78) return 0;
    n = D_00350D78->n;
    b = D_00350D78->box;
    m = 0;
    for (i = 0; i < n; i++, b++) {
        if ((b->u.flags & 0x200) || (p[0] >= b->lo[0] && p[0] <= b->hi[0] && p[2] >= b->lo[2] && p[2] <= b->hi[2]))
            m |= 1 << (b->u.c.id - 1);
    }
    return m;
}

/* func_0014e668 (from hand/text_00140000_h57.c). */
f32 func_00120c88(f32);
f32 func_00176850(void);
f32 sinf(f32);
f32 cosf(f32);
void func_001426a8(f32 *, f32);
s32 func_0012f0f8(f32 *, f32 *, s32);
s32 func_0014e668(f32 *pos, s32 n, f32 *out, f32 min, f32 max) {
    f32 base[4];
    f32 t[4];
    f32 r;
    f32 ang;
    f32 a;
    s32 i;

    PlatVu0CopyVector(base, pos);
    r = func_00176850() * (max - min) + min;
    ang = func_00176850() * 6.2831855f;
    for (; r >= min; r -= 100.0f) {
        for (i = 0; i < 18; i++) {
            a = func_00120c88(ang + (f32)(i ^ 5) * 0.349065847695f);
            t[0] = sinf(a) * r;
            t[1] = 0.0f;
            t[2] = cosf(a) * r;
            t[3] = 1.0f;
            PlatVu0AddVector(out, base, t);
            if (n == 0 || ((func_0014e5b8(out) >> (n - 1)) & 1)) {
                func_001426a8(out, 1000.0f);
                out[1] += -100.0f;
                if (func_0012f0f8(base, out, 2)) {
                    out[1] -= -100.0f;
                    return 1;
                }
            }
        }
    }
    PlatVu0CopyVector(out, pos);
    out[1] += -100.0f;
    func_001426a8(out, 1000.0f);
    return 0;
}

/* func_0014e878 (from hand/text_00140000_h57.c). */
s32 func_0014e878(f32 *pos, s32 id, f32 *out, f32 min, f32 max) {
    f32 t[4];
    f32 r;
    f32 ang;
    f32 a;
    s32 i;
    s32 j;
    Box57_f1b8 *b;

    r = func_00176850() * (max - min) + min;
    ang = func_00176850() * 6.2831855f;
    for (; r >= min; r -= 100.0f) {
        for (i = 0; i < 18; i++) {
            a = func_00120c88(ang + (f32)(i ^ 5) * 0.349065847695f);
            t[0] = sinf(a) * r;
            t[1] = 0.0f;
            t[2] = cosf(a) * r;
            t[3] = 1.0f;
            PlatVu0AddVector(out, pos, t);
            if (id == 0) return 1;
            b = D_00350D78->box;
            for (j = 0; j < D_00350D78->n; j++, b++) {
                if (b->u.c.id == id && out[0] >= b->lo[0] && out[0] <= b->hi[0]
                    && out[2] >= b->lo[2] && out[2] <= b->hi[2]) {
                    out[1] = func_00176850() * (b->hi[1] - b->lo[1]) + b->lo[1] + -100.0f;
                    if (func_0012f0f8(pos, out, 1)) {
                        out[1] -= -100.0f;
                        return 1;
                    }
                }
            }
        }
    }
    PlatVu0CopyVector(out, pos);
    return 0;
}

/* func_0014eab0 (from auto/text_00140000_10.c). */
#define func_0014e668 ((M2C_UNK (*)(void *, u8, s32, f32, f32)) func_0014e668)
void func_0014eab0(void *arg0, s32 arg1) {
    s32 sp[4];    f32 var_f20;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x134);
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, u8 *, 5) != 0)) {
        var_f20 = M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x14), f32 *, 0xC);
    } else {
        var_f20 = 0.0f;
    }
    PlatVu0CopyVector(sp, (*(s32 *)&D_002E26A0) + 0x10);
    M2C_FIELD(sp, f32 *, 0x4) += -200.0f;
    func_0014e668(sp, M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u8 *, 0x58), arg1, var_f20 + 100.0f, var_f20 + 600.0f);
}
#undef func_0014e668

/* func_0014eb60 (from auto/text_00140000_10.c). */
#define func_0014e878 ((M2C_UNK (*)(void *, u8, s32, f32, f32)) func_0014e878)
void func_0014eb60(void *arg0, s32 arg1) {
    s32 sp[4];    f32 var_f20;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x134);
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, u8 *, 5) != 0)) {
        var_f20 = M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x14), f32 *, 0xC);
    } else {
        var_f20 = 0.0f;
    }
    PlatVu0CopyVector(sp, (*(s32 *)&D_002E26A0) + 0x10);
    M2C_FIELD(sp, f32 *, 0x4) += -200.0f;
    func_0014e878(sp, M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u8 *, 0x58), arg1, var_f20 + 100.0f, var_f20 + 600.0f);
}
#undef func_0014e878

/* func_0014ec10 (from auto/text_00140000.c). */
void func_0014ec10(s32 arg0) {
    D_0054F44C &= ~(1 << (arg0 - 1));
}

/* func_0014ec38 (from auto/text_00140000.c). */
void func_0014ec38(s32 arg0) {
    D_0054F44C |= 1 << (arg0 - 1);
}

/* func_0014ec60 (from hand/text_00140000_h34.c). */
typedef struct { s32 x0; s32 x4; f32 x8; f32 xc; s32 x10; s32 x14; } W34Grp;
extern W34Grp D_0054F450[];
/* 0x14ED30 (calls func_0014ec60 above) */
void func_0014ec60(s32 g) {
    W34Grp *e = &D_0054F450[g - 1];
    s32 n = 0;
    W34Ent *p = 0;
    while ((p = func_00132040(p))) {
        if (p->x58 == g && e->x14 >= p->x48 && func_00142240(p->x0) != 1) n += p->x59;
    }
    if (e->x10 >= n) e->x14++;
}

/* func_0014ed30 (from hand/text_00140000_h34.c). */
extern W34Grp D_0054F438[];
typedef struct { u8 pad[0x58]; u8 x58; } W34O130b;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x128]; W34O130b *x130; u8 pad134[0x370 - 0x134]; W34F370 x370; } W34Act4;
void func_001421d0(s32, s32);
void func_0014ed30(W34Act4 *o) {
    s32 i;
    if (o->x370.b.b51) {
        if (o->x130->x58) {
            if (!(D_0054F438[o->x130->x58].x0 & 1)) func_001421d0(o->x4, 1);
            func_0014ec60(o->x130->x58);
        } else {
            func_001421d0(o->x4, 1);
        }
    }
    for (i = 0; i < 31; i++) {
        if (D_0054F448 >> i & 1) D_0054F450[i].xc = D_0054F450[i].x8;
    }
}

/* func_0014ee08 (from hand/text_00140000_h9.c). */
s32 func_0014ee08(f32 *lo, f32 *hi, f32 *box) {
    s32 r = 0;
    if (hi[0] >= box[4] && lo[0] <= box[8] &&
        hi[1] >= box[5] && lo[1] <= box[9] &&
        hi[2] >= box[6] && lo[2] <= box[10]) r = 1;
    return r;
}

/* func_0014ee88 (from hand/text_00140000_s6_07.c). */
typedef struct { u8 x[20]; } Col20;
typedef struct { u8 pad[5]; u8 n; u8 pad6[0xe]; Col20 *cols; } ColSet;
typedef struct { u8 pad[0x134]; ColSet *cs; } Ob88;
typedef struct { f32 a[4]; f32 b[4]; } Cap88;
void func_0015bad0(Ob88 *, Col20 *, void *);
s32 func_0014ee88(Ob88 *o) {
    Cap88 cap;
    f32 lo[4];
    f32 hi[4];
    f32 q[4];
    s32 i;
    s32 m;
    Box57_f1b8 *b;
    ColSet *cs;

    if (!D_00350D78 || !o || !(cs = o->cs) || !cs->n) return 0;
    i = 0;
    m = 0;
    func_0015bad0(o, cs->cols, &cap);
    q[0] = q[2] = cap.a[1];
    q[1] = cap.a[2];
    PlatVu0SubVector(lo, cap.b, q);
    PlatVu0AddVector(hi, cap.b, q);
    b = D_00350D78->box;
    for (; i < D_00350D78->n; i++, b++) {
        if ((b->u.flags & 0x200) || func_0014ee08(lo, hi, (f32 *)b)) m |= 1 << (b->u.c.id - 1);
    }
    return m & D_0054F44C;
}

/* func_0014efe0 (from auto/text_00140000_15.c). */
#define func_0014ee88 ((s32 (*)()) func_0014ee88)
s32 func_0014efe0(s32 arg0, s32 arg1) {
    s32 var_v0;

    if (!((arg1 <= 0) || (var_v0 = 1, (((func_0014ee88() >> (arg1 - 1)) & 1) == 0)))) {
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}
#undef func_0014ee88

/* func_0014f028 (from hand/text_00140000_h57.c). */
typedef struct { s32 x0; u8 pad4[0x48-4]; s16 x48; u8 pad4a[0x58-0x4a]; u8 x58; } Ent57_f028;
extern f32 D_002BBDFC;
extern u32 D_002C5958;
s32 func_00124218(s32);
extern Grp57_f1b8 D_0054F450_0014f028[] __asm__("D_0054F450");
#define D_0054F450 D_0054F450_0014f028
#define func_0014ee88 ((s32 (*)(void *)) func_0014ee88)
#define func_00132040 ((Ent57_f028 *(*)(Ent57_f028 *)) func_00132040)
#define func_00123488 ((s32 (*)(s32)) func_00123488)
s32 func_0014f028(void) {
    u32 m;
    s32 id;
    s32 i;
    Ent57_f028 *p;
    Grp57_f1b8 *e;

    if (!D_00350D78) return 4;
    if ((D_002C5958 >> 14) & 1) return 0;
    m = func_0014ee88(D_002E26A0[0]);
    if (m) {
        p = 0;
        while ((p = func_00132040(p)) != 0) {
            if (p->x58 == 0) continue;
            e = &D_0054F450[p->x58 - 1];
            if ((m & (1 << (p->x58 - 1))) == 0) continue;
            if (e->fc > 0.0f) continue;
            if (func_00123488(p->x0)) continue;
            if (func_00142240(p->x0) == 1) continue;
            if (e->x14 < p->x48) continue;
            if (!func_00124218(p->x0)) continue;
            e->fc = e->f4;
            if (e->fc > 0.0f) break;
        }
    }
    D_0054F448 = m;
    e = D_0054F450;
    for (i = 0; i < 31; i++, e++) {
        if (e->fc > 0.0f) e->fc -= D_002BBDFC;
    }
    return 0;
}
#undef D_0054F450
#undef func_0014ee88
#undef func_00132040
#undef func_00123488

/* func_0014f1b8 (from hand/text_00140000_h57.c). */
extern s32 D_00350D7C;
extern s32 D_00350D80;
extern s32 D_002BC128;
extern s32 D_002BC130;
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
s32 func_0013c968(s32, s32);
s32 func_00142058(s32);
extern Grp57_f1b8 D_0054F438_0014f1b8[] __asm__("D_0054F438");
#define D_0054F438 D_0054F438_0014f1b8
extern Grp57_f1b8 D_0054F450_0014f1b8[] __asm__("D_0054F450");
#define D_0054F450 D_0054F450_0014f1b8
s32 func_0014f1b8(BoxSet57_f1b8 *set) {
    s32 i;
    s32 r;
    Box57_f1b8 *b;
    Grp57_f1b8 *g;

    D_00350D7C = 0;
    D_0054F448 = 0;
    D_0054F44C = -1;
    D_00350D80 = 0;
    for (i = 0; i < 31; i++) {
        D_0054F450[i].fc = 0.0f;
    }
    r = 2;
    D_00350D78 = set;
    if (set) {
        b = set->box;
        D_00350D7C = set->x3;
        for (i = 0; i < D_00350D78->n; i++, b++) {
            g = &D_0054F438[b->u.c.id];
            g->b0 = (u8)(b->u.flags >> 8);
            g->b1 = (u8)(b->u.flags >> 9);
            g->f4 = b->u.c.b2;
            g->f8 = b->u.c.b3;
            g->x10 = b->u.c.b4;
            g->x14 = 0;
        }
        r = D_00350D78->x5;
        if (!func_0011ef38(func_0014f028)) func_0011ef10(0x1387f, func_0014f028);
    }
    if (D_002BC128 != 16 || (D_002BC130 != 30 && D_002BC130 != 33)) {
        if (func_0013c968(61, 0)) r = 0;
    }
    return func_00142058(r);
}
#undef D_0054F438
#undef D_0054F450

