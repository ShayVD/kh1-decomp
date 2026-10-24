/* Attack hits: the 64 hit records D_0054C440 (func_0014a450 takes one,
 * func_0014a4a8 fills one from an attack definition, func_0014bdc0 updates
 * them all) and their mask D_0054F440, the hit timers (func_0014a0f0), a
 * follow offset (func_0014a238). Flag mode: default (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00140000_h34.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00350CE0.h"
#include "data/bss_0053.h"
#include "vm/script_vm.h"
#include "data/types/text_00140000_h8.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_00350CE8.h"
#include "data/pieces/D_002C58D0.h"

/* func_0014a0f0 (from hand/text_00140000_h34.c). */
extern f32 D_002BBDFC;
typedef struct { u8 pad[0x3e0]; s32 x3e0; } W34A3e0;
typedef struct { u8 pad[0x9c]; s32 x9c; } W34A9c;
typedef struct { u8 pad[0x50]; f32 x50; s32 x54; u8 pad58[0xa4 - 0x58]; f32 xa4; } W34Tmr;
W34A3e0 *func_001230a0(W34A3e0 *);
W34A9c *func_0014a398_4a0f0(W34A9c *) __asm__("func_0014a398");
#define func_0014a398 func_0014a398_4a0f0
void func_0014a0f0(W34Tmr *a) {
    if (a->x50 > 0.0f) {
        a->xa4 += D_002BBDFC;
        if (a->x50 <= a->xa4) {
            W34A3e0 *p;
            W34A9c *q;
            for (p = 0; (p = func_001230a0(p)); ) p->x3e0 &= ~a->x54;
            for (q = 0; (q = func_0014a398(q)); ) q->x9c &= ~a->x54;
            a->xa4 -= a->x50;
        }
    }
}
#undef func_0014a398

/* func_0014a238 (from hand/text_00140000_h34.c). */
typedef struct { u8 pad[4]; f32 x4; f32 x8; u8 padc[4]; f32 pos[4]; } W34Fol;
typedef struct { u8 pad[0x10]; f32 pos[4]; } W34Pos;
void func_0014a238(W34Pos *a, W34Fol *b, f32 *out) {
    f32 v[4] __attribute__((aligned(16)));
    f32 y, k, t, lim;
    PlatVu0SubVector(v, a->pos, b->pos);
    y = v[1];
    lim = b->x8;
    if (lim < y) y = lim;
    else { t = -lim; if (y < t) y = t; }
    t = fabsf(y / lim);
    k = (1.0f < t) ? 1.0f : t;
    k = PlatSqrtf(1.0f - k * k);
    v[1] = 0.0f;
    PlatVu0Normalize(v, v);
    PlatVu0ScaleVector(v, v, b->x4 * k);
    v[1] = y;
    PlatVu0AddVector(out, b->pos, v);
}

/* func_0014a330 (from auto/text_00140000_10.c). */
M2C_UNK func_0014a1b0(s32, s32, void *);
#define func_0014a238 ((M2C_UNK (*)(s32, s32, void *)) func_0014a238)
void func_0014a330(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    func_0014a238(arg2, arg3, sp);
    func_0014a1b0(arg0, arg1, sp);
}
#undef func_0014a238

/* func_0014a380 (from auto/text_00140000_4.c). */
void func_001412f8(s32, s32);
void func_0014a380(s32 arg0, s32 arg1) {
    func_001412f8(arg0, M2C_FIELD(arg1, s32 *, 0x30));
}

/* func_0014a398 (from hand/text_00140000_h8.c). */
typedef struct {
    union { u64 x; struct { u64 b0:11; u64 f11:1; u64 b12:2; u64 f14:1; u64 f15:1; u64 f16:1; u64 r:47; } b; struct { u32 lo; u32 hi; } w; } f;
    u8 pad8[8];
    u8 x10[0x30];
    u8 x40[0x14];
    u32 x54;
    u8 x58[0x18];
    u8 x70[0x10];
    u8 x80[0x34];
    void (*xb4)(void *, s32);
    s32 xb8;
    u8 xbc[4];
} W8P;
extern W8P D_0054C440[];
W8P *func_0014a398(W8P *p) {
    if (p == 0) p = D_0054C440;
    else p++;
    for (; p < &D_0054C440[64]; p++) {
        if ((s32)(p->f.x >> 11) & 1) return p;
    }
    return 0;
}

/* func_0014a408 (from hand/text_00140000_h8.c). */
extern u32 D_0054F440;
s32 func_0014a408(void) {
    s32 i;
    for (i = 0; i < 31; i++) {
        if (!(D_0054F440 & (1 << i))) return 1 << i;
    }
    return 0;
}

/* func_0014a450 (from hand/text_00140000_h8.c). */
W8P *func_0014a450(void) {
    s32 i;
    W8P *p = D_0054C440;
    for (i = 0; i < 64; i++, p++) {
        if (!((s32)(p->f.x >> 11) & 1)) {
            p->f.w.lo = 0;
            p->f.b.f11 = 1;
            break;
        }
    }
    return p;
}

/* func_0014a898 (from hand/text_00140000_h8.c). */
void func_0014a898(W8P *p, void *v) {
    PlatVu0CopyVector(p->x70, v);
    PlatVu0CopyVector(p->x80, v);
    PlatVu0CopyVector(p->x10, v);
    PlatVu0CopyVector(p->x40, v);
    p->f.b.f14 = 0;
    p->f.b.f16 = 1;
}

/* func_0014aa10 (from auto/text_00140000_10.c). */
M2C_UNK func_0014a908(s32, s32, s32);
s32 func_001477e0(s32);
void func_0014aa10(s32 arg0, s32 arg1, s32 arg2) {
    func_0014a908(arg0, arg1, func_001477e0(arg2));
}

/* func_0014aa50 (from hand/text_00140000_h8.c). */
void func_0014aa50(u32 m) {
    W8P *p = 0;
    while ((p = func_0014a398(p)) != 0) {
        if (p->x54 & m) return;
    }
    *(volatile u32 *)&D_0054F440 &= ~m;
}

/* func_0014aab0 (from hand/text_00140000_h8.c). */
void func_0014aab0(W8P *p) {
    if (p->xb4) p->xb4(p, p->xb8);
    p->f.w.lo = 0;
    p->f.w.hi = 0;
    func_0014aa50(p->x54);
}

/* func_0014aaf0 (from auto/text_00140000_15.c). */
void func_0014aaf0(s64 *arg0) {
    s64 temp_v1;

    temp_v1 = *arg0;
    if (!((s32) ((s64) (temp_v1 << 0x18) >> 0x20) & 1)) {
        *arg0 = temp_v1 | 0x200000;
    }
}

/* func_0014ab18 (from auto/text_00140000_10.c). */
#define func_0014aa50 ((s32 (*)(s32)) func_0014aa50)
s32 func_0014ab18(s32 arg0) {
    M2C_FIELD(arg0, s64 *, 0) = (s64) (M2C_FIELD(arg0, s64 *, 0) | 0x400);
    return func_0014aa50(M2C_FIELD(arg0, s32 *, 0x54));
}
#undef func_0014aa50

/* func_0014ab48 (from auto/text_00140000_10.c). */
extern s32 D_0054F440_0014ab48 __asm__("D_0054F440");
#define D_0054F440 D_0054F440_0014ab48
void func_0014ab48(void *arg0) {
    M2C_FIELD(arg0, s64 *, 0) = (s64) (M2C_FIELD(arg0, s64 *, 0) & ~0x400);
    D_0054F440 |= M2C_FIELD(arg0, s32 *, 0x54);
}
#undef D_0054F440

/* func_0014ab78 (from auto/text_00140000_15.c). */
#define func_0014aab0 ((M2C_UNK (*)(M2C_UNK *)) func_0014aab0)
#define D_0054C440 (*(M2C_UNK (*)) &D_0054C440)
void func_0014ab78(s32 arg0) {
    s8 *var_s0;
    s32 var_s2;

    var_s0 = &D_0054C440;
    var_s2 = 0x3F;
    do {
        if (((s32) ((s64) (M2C_FIELD(var_s0, s64 *, 0) << 0x15) >> 0x20) & 1) && ((M2C_FIELD(var_s0, s32 *, 0x34) == arg0) || (M2C_FIELD(var_s0, s32 *, 0x90) == arg0))) {
            func_0014aab0(var_s0);
        }
        var_s2 -= 1;
        var_s0 += 0xC0;
    } while (var_s2 >= 0);
}
#undef func_0014aab0
#undef D_0054C440

/* func_0014ac00 (from auto/text_00140000_15.c). */
void func_0014ac00(void *arg0, s32 arg1) {
    s32 *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 **, 0x60);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) | arg1);
    if (temp_v1 != NULL) {
        *temp_v1 |= arg1;
    }
    if (!((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x30) << 0x16) >> 0x20) & 1)) {
        M2C_FIELD(arg0, s64 *, 0) = (s64) (M2C_FIELD(arg0, s64 *, 0) | 0x100000);
    }
}

/* func_0014af60 (from hand/text_00140000_h34.c). */
f32 func_00121748(f32 *, f32 *);
typedef struct { u8 pad[0x30]; f32 x30[4]; u8 pad40[0x10]; f32 x50[4]; } W34Xf;
typedef struct { u8 pad[0x60]; f32 x60; f32 x64; } W34Rng;
typedef struct {
    u64 x0;
    u8 pad8[8];
    f32 x10[4];
    u8 pad20[0x10];
    union { u64 d; struct { s32 lo; W34Xf *x34; } w; } x30;
    u8 pad38[0x24];
    W34Rng *x5c;
    u8 pad60[0x10];
    f32 x70[4];
} W34Act2;
s32 func_0014af60(W34Act2 *a, W34Act2 *b) {
    f32 m[4][4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    s32 k;
    s32 r;
    if (!((s32)(b->x0 >> 6) & 1)) {
        k = (s32)(a->x0 >> 17) & 7;
        if (k == 1 || k == 3 || k == 4 || k == 2) {
            PlatVu0RotMatrixY(m, D_002C58D0[0], a->x5c->x60);
            PlatVu0CopyVector(v, a->x30.w.x34->x30);
            v[3] = 0;
            PlatVu0ApplyMatrix(v, m, v);
            if ((s32)(b->x30.d >> 10) & 1) PlatVu0SubVector(d, b->x70, b->x10);
            else PlatVu0SubVector(d, b->x30.w.x34->x50, a->x30.w.x34->x50);
            if (func_00121748(v, d) < a->x5c->x64) { r = 0; return r; }
            r = 1;
        } else r = 1;
    } else r = 1;
    return r;
}

/* func_0014b958 (from hand/text_00140000_h8.c). */
s32 func_0014b768(W8P *, f32 *, f32 *);
/* 0x14bba8 (needs func_0014b958 defined above) */
void func_0014b958(W8P *p) {
    f32 a[4];
    f32 b[4];
    if ((s32)(p->f.x >> 16) & 1) {
        PlatVu0InterVector(a, p->x70, p->x80, 0.5f);
        PlatVu0InterVector(b, p->x10, p->x40, 0.5f);
        func_0014b768(p, a, b);
    }
}

/* func_0014bba8 (from hand/text_00140000_h8.c). */
typedef struct {
    union { u64 flags; s32 w; } u;
    u8 pad8[4];
    f32 f0c;
    f32 v10[4];
    s32 i20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x34-0x2c];
    s32 i34;
    u8 pad38[0x3c-0x38];
    f32 f3c;
    f32 v40[4];
    u8 pad50[0x54-0x50];
    s32 i54;
    u8 pad58[0x70-0x58];
    f32 v70[4];
    f32 v80[4];
    s32 i90;
} Src57;
typedef struct { s32 kind; s32 a4; s32 a8; s32 src; s32 a10; f32 f14; f32 f18; s32 pad1c; f32 v[4]; } Ent57;
void func_001315c0(s32, s32, f32 *, f32);
s32 func_0014b9e0(Src57 *s, f32 *a, f32 *b, f32 f0, f32 f1, Ent57 *tbl, s32 n);
s32 func_0014bba8(Src57 *s, Ent57 *tbl, s32 cnt) {
    s32 k;

    if ((s->u.w & 3) == 1) {
        func_001315c0(s->i90, s->i20, s->v10, s->f24);
    }
    k = (s32)(s->u.flags >> 17) & 7;
    if (k != 1 && k != 4 && k != 2 && ((s32)(s->u.flags >> 16) & 1)) {
        cnt += func_0014b9e0(s, s->v10, s->v70, s->f0c, s->f0c, tbl, cnt);
    }
    switch (s->u.w & 3) {
    case 0:
        PlatVu0CopyVector(s->v40, s->v10);
        k = (s32)(s->u.flags >> 17) & 7;
        if (k == 1 || k == 4 || k == 2 || !((s32)(s->u.flags >> 16) & 1)) {
            cnt += func_0014b9e0(s, s->v10, s->v10, s->f0c, s->f0c, tbl, cnt);
        }
        break;
    case 1:
        func_001315c0(s->i90, s->i20, s->v40, s->f28);
        cnt += func_0014b9e0(s, s->v10, s->v40, s->f0c, s->f0c, tbl, cnt);
        break;
    case 2:
        cnt += func_0014b9e0(s, s->v10, s->v40, s->f0c, s->f3c, tbl, cnt);
        break;
    }
    if (!((s32)(s->u.flags >> 20) & 1)) {
        if ((s->u.w & 3) != 2 || func_0014b768((W8P *)s, s->v40, s->v10)) {
            func_0014b958((W8P *)s);
        }
    }
    return cnt;
}

/* func_0014c330 (from hand/text_00140000_h8.c). */
void func_0014c330(void) {
    W8P *p = 0;
    while ((p = func_0014a398(p)) != 0) func_0014aab0(p);
}

/* func_0014c378 (from hand/text_00140000_h8.c). */
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_0014c130();
void func_0014c378(void) {
    s32 i;
    for (i = 63; i >= 0; i--) D_0054C440[i].f.w.lo = 0;
    D_0054F440 = 0;
    if (!func_0011ef38(func_0014c130)) func_0011ef10(0x13881, func_0014c130);
}

