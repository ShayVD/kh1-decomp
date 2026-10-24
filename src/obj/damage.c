/* Damage: the damage kinds and thresholds of the tuning block *D_00308CDC
 * (func_001347f0), the damage an attack does to an object (func_001349d0,
 * func_00134ba8), and the hit records D_005267C0 (64) and D_005277C0 (128)
 * with the hit test func_001350d8 and func_001354b8. Flag mode: default (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "m2c.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_003044A0.h"

/* func_001347f0 (from hand/text_00130000_h6.c). */
typedef struct W6Link {
    u8 pad00[0x10];
    u8 id;
    u8 pad11[0x54 - 0x11];
    struct W6Link *next;
} W6Link;
typedef struct W6Pend {
    u8 pad00[8];
    union {
        u64 bits;
        struct {
            u64 lo : 44;
            u64 cnt : 4;
            u64 hi : 16;
        } f;
    } u;
    u8 pad10[0x30 - 0x10];
    struct W6Pend *next;
} W6Pend;
typedef struct {
    u8 pad000[0x3EC];
    struct W6Pend *pend;
    u8 pad3f0[0x440 - 0x3F0];
    W6Link *links;
} W6Mgr;
typedef struct {
    u8 pad00[8];
    u64 bits;
} W6Kind;
f32 func_001348e0();
#define func_001348e0 ((f32 (*)(W6Mgr *m, W6Kind *k)) func_001348e0)
s32 func_001347f0(W6Mgr *m, W6Kind *k) {
    s32 r = (s32)(k->bits >> 32) & 0x1F;
    s32 v;
    if (r == 1) {
        v = func_001348e0(m, k) * 100.0f;
        if (v < (*(Cfg_308cdc **)&D_00308CDC)->lim0) {
            r = 3;
        } else if (v < (*(Cfg_308cdc **)&D_00308CDC)->lim1) {
            r = 4;
        } else {
            r = 5;
        }
    }
    return r;
}
#undef func_001348e0

/* func_00134870 (from auto/text_00130000_13.c). */
void func_0012bce0(s32, s32, s32, s32, s32);
void func_00134870(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[8];    s32 temp_v0;

    M2C_FIELD(sp, s32 *, 0x10) = arg1;
    M2C_FIELD(sp, s32 *, 0x14) = arg2;
    if ((s32) ((s64) ((s64) M2C_FIELD(arg0, u16 *, 0x376) << 0x20) >> 0x20) & 1) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x144);
        if (temp_v0 != 0) {
            M2C_FIELD(sp, s32 * *, 0x0) = &M2C_FIELD(sp, s32 *, 0x10);
            M2C_FIELD(sp, s32 *, 0x4) = 4;
            M2C_FIELD(sp, s32 * *, 0x8) = &M2C_FIELD(sp, s32 *, 0x14);
            M2C_FIELD(sp, s32 *, 0xC) = 4;
            func_0012bce0(temp_v0, 2, 2, (s32) sp, 0);
        }
    }
}

/* func_001348e0 (from auto/text_00130000.c). */
f32 func_001348e0(void *arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x40);
    if (temp_v0 > 0) {
        return (f32) M2C_FIELD(arg1, s32 *, 8) / (f32) temp_v0;
    }
    return 1.0f;
}

/* func_00134928 (from hand/text_00130000_h6.c). */
W6Pend *func_00134928(W6Mgr *m) {
    W6Pend *p = m->pend;
    if (p != 0) {
        s32 c = (s32)(p->u.bits >> 44) & 0xF;
        if (c > 0) {
            p->u.f.cnt = c - 1;
            p = 0;
        } else {
            m->pend = p->next;
            p->next = 0;
        }
    }
    return p;
}

/* func_00134998 (from auto/text_00130000_12.c). */
void func_00134998(void *arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x3EC);
    if (temp_a0 != NULL) {
        M2C_FIELD(temp_a0, s64 *, 8) = (s64) (M2C_FIELD(temp_a0, s64 *, 8) & (((((s64) 0xFFFF0FFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
    }
}

/* func_00134ba8 (from hand/text_00120000_b02.c). */
typedef struct { u8 p0[0x54]; s8 b54; } Y12;
typedef struct { u8 p0[0x4c]; u16 h4c; } Z12;
typedef struct { u8 p0[0x130]; Y12 *f130; } X12;
typedef struct { u8 p0[0x14]; s32 f14; u8 p18[8]; s32 f20; s32 f24; u8 p28[0x44 - 0x28]; s32 f44; s32 f48; s32 f4c; s32 f50; } P12;
typedef struct {
    u8 p0[0x2c];
    s32 f2c;
    union { u64 d; struct { s32 f30; X12 *f34; } s; } u30;
    u8 p38[0x5c - 0x38];
    P12 *f5c;
    u8 p60[0x94 - 0x60];
    f32 f94;
    s32 f98;
    u8 p9c[0xac - 0x9c];
    f32 fac;
} A12;
typedef struct {
    u8 p0[0x3c];
    s32 f3c;
    u8 p40[0x50 - 0x40];
    s32 f50;
    u8 p54[0x78 - 0x54];
    f32 f78[8];
    f32 f98;
    u8 p9c[0xc0 - 0x9c];
    u16 hc0;
    u16 hc2;
} Q12;
typedef struct { u8 p0[0x170]; union { u64 d; struct { u32 lo; u32 b0 : 4; u32 b36 : 1; } b; } f170; } R12;
typedef struct {
    u8 p0[6];
    u8 f6;
    u8 p7[0x6c - 7];
    Q12 *f6c;
    u8 p70[0x88 - 0x70];
    s32 f88;
    u8 p8c[0x148 - 0x8c];
    R12 *f148;
    u8 p14c[0x370 - 0x14c];
    u64 f370;
} B12;
extern f32 func_00176850(void);
extern s32 func_00122ff8(X12 *);
extern void func_001586a8(s32);
extern s32 func_0013bf68(void);
#define CALC12(q, v) ((s32)((f32)(q)->f3c * ((f32)(v) / 100.0f) * (q)->f98))
s32 func_00134ba8(A12 *a, B12 *b, u32 *fl) {
    s32 v;
    s32 hi;
    s32 lo;
    s32 m;
    Q12 *q;
    s32 i;

    switch (b->f6) {
    case 4:
    case 5:
    case 9:
    case 10:
        if (a->u30.s.f34 && a->u30.s.f34->f130->b54 == 1) return 0;
        return a->f5c->f44;
    }
    if (((b->f370 >> 37) & 3) == 2) {
        v = a->f2c + a->f5c->f48;
        lo = a->f5c->f4c;
        hi = a->f5c->f50;
    } else {
        v = a->f2c + a->f5c->f14;
        lo = a->f5c->f20;
        hi = a->f5c->f24;
    }
    if (!b->f6c || !v) return 0;
    if (func_00176850() < a->f94) {
        v += a->f98;
        *fl |= 0x20;
        if (func_00122ff8(a->u30.s.f34) && !((Z12 *)a->u30.s.f34->f130)->h4c) func_001586a8(8);
    }
    m = (s32)(a->u30.d >> 6) & 0xf;
    switch (m) {
    case 9:
    case 11:
    case 12:
        return v;
    case 8:
        m = CALC12(b->f6c, v) < (b->f6c->hc0 > 1 ? b->f6c->hc0 : 1) ? (b->f6c->hc0 > 1 ? b->f6c->hc0 : 1) : CALC12(b->f6c, v);
        return m;
    }
    q = b->f6c;
    i = v - q->f50;
    if (i < 0) i = 0;
    else if (i >= (*(u16 **)&D_003044A0)[0]) i = (*(u16 **)&D_003044A0)[0] - 1;
    v = (*(u16 **)&D_003044A0)[i + 1];
    if (lo) {
        lo = (f32)lo * a->fac;
        if (v < lo) v = lo;
    }
    if (hi) {
        hi = (f32)hi * a->fac;
        if (hi < v) v = hi;
    }
    if (q->hc0 && v < q->hc0) v = q->hc0;
    else if (q->hc2 && q->hc2 < v) v = q->hc2;
    v = (f32)v * q->f78[(s32)(a->u30.d >> 6) & 0xf];
    if (b->f88 & 8) v /= 2;
    if (((b->f370 >> 37) & 3) == 1) {
        if (func_0013bf68()) v *= 2;
    }
    if (b->f148 && b->f148->f170.b.b36) {
        if (v >= b->f6c->f3c) v = b->f6c->f3c - 1;
    }
    return v ? v : 1;
}
#undef CALC12

/* func_00134f80 (from hand/text_00130000_h6.c). */
typedef struct {
    union {
        u64 bits;
        struct {
            u64 used : 1;
            u64 rest : 63;
        } f;
    } u;
    u8 pad08[0x40 - 0x8];
} W6Blk;
void *memset(void *d, s32 c, u32 n);
W6Blk *func_00134f80(W6Blk *b, s32 n) {
    s32 i;
    for (i = 0; i < n; i++, b++) {
        if (!((s32)b->u.bits & 1)) {
            memset(b, 0, 64);
            b->u.f.used = 1;
            return b;
        }
    }
    return 0;
}

/* func_00135000 (from hand/text_00130000_h6.c). */
typedef struct W6Q {
    u8 pad00[0x24];
    s32 seq;
    u32 mask;
    u8 pad2c[0x30 - 0x2C];
    struct W6Q *next;
} W6Q;
typedef struct {
    u8 pad000[0x3E0];
    u32 mask;
    u8 pad3e4[0x3E8 - 0x3E4];
    u16 n;
    u8 pad3ea[0x3EC - 0x3EA];
    W6Q *head;
} W6QMgr;
void func_00135000(W6QMgr *m, W6Q *q) {
    W6Q *p = m->head;
    if (p == 0) {
        m->head = q;
    } else {
        while (p->next != 0) {
            p = p->next;
        }
        p->next = q;
    }
    m->mask |= q->mask;
    q->seq = ++m->n;
}

/* func_00135070 (from auto/text_00130000.c). */
extern M2C_UNK D_005267C0;
#define func_00135000 ((M2C_UNK (*)(s32, void *)) func_00135000)
#define func_00134f80 ((void *(*)(M2C_UNK *, M2C_UNK)) func_00134f80)
void *func_00135070(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00134f80(&D_005267C0, 0x40);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x28) = arg1;
        func_00135000(arg0, temp_v0);
    }
    return temp_v0;
}
#undef func_00135000
#undef func_00134f80

/* func_001350d0 (from auto/text_00130000.c). */
void func_001350d0(s32 *arg0) {
    *arg0 = 0;
}

/* func_00135640 (from auto/text_00130000.c). */
void func_00135640(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x3E0) = (s32) (M2C_FIELD(arg1, s32 *, 0x3E0) | M2C_FIELD(arg0, s32 *, 0x54));
}

/* func_00135658 (from auto/text_00130000_1.c). */
#define func_001350d0 ((M2C_UNK (*)(void *)) func_001350d0)
void func_00135658(void *arg0) {
    void *var_s0;

    var_s0 = M2C_FIELD(arg0, void **, 0x3EC);
    if (var_s0 != NULL) {
        do {
            func_001350d0(var_s0);
            var_s0 = M2C_FIELD(var_s0, void **, 0x30);
        } while (var_s0 != NULL);
    }
    M2C_FIELD(arg0, void **, 0x3EC) = NULL;
}
#undef func_001350d0

/* func_001356a8 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad[0x40];
} W6Cell;
typedef struct {
    u8 pad000[0x3EC];
    s32 x3ec;
    u8 pad3f0[0x4B0 - 0x3F0];
} W6Big;
extern W6Cell D_005277C0[];
extern W6Big D_002C64A0[];
extern W6Cell D_005267C0_001356a8[] __asm__("D_005267C0");
#define D_005267C0 D_005267C0_001356a8
#define func_001350d0 ((void (*)(W6Cell *c)) func_001350d0)
void func_001356a8(void) {
    W6Big *p;
    s32 i;
    for (i = 0; i < 64; i++) {
        func_001350d0(&D_005267C0[i]);
    }
    for (i = 0; i < 128; i++) {
        func_001350d0(&D_005277C0[i]);
    }
    p = D_002C64A0;
    for (i = 0; i < 96; i++, p++) {
        p->x3ec = 0;
    }
}
#undef D_005267C0
#undef func_001350d0

/* func_00135788 (from auto/text_00130000.c). */
M2C_UNK func_002675a8(s32, s32);
void func_00135788(void *arg0) {
    func_002675a8(arg0 + 0x10, arg0 + 0x100);
    M2C_FIELD(arg0, s32 *, 0x3A0) = 0;
}

/* func_001357b8 (from hand/text_00130000_h6.c). */
typedef struct {
    s32 a;
    s32 b;
} W6Pair;
W6Pair D_0052A110[0x8] ALIGNED(16);  /* moved from hand/text_00130000_h6.c (session 53) */
W6Pair *func_001357b8(void) {
    s32 v = D_0052A150;
    D_0052A150 = (v + 1) % 8;
    return &D_0052A110[v];
}

/* func_00135800 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad00[0x50];
    s16 h50;
} W6Sub;
typedef struct {
    u8 pad000[0x60];
    f32 x60;
    f32 x64;
    u8 pad068[0x130 - 0x68];
    W6Sub *sub;
    u8 pad134[0x38C - 0x134];
    u32 x38c;
    u32 x390;
    u8 pad394[0x3A0 - 0x394];
    s32 x3a0;
} W6Ch;
void func_00135800(W6Ch *c, f32 x, f32 t) {
    if (0.0f < t) {
        c->x64 = (x - c->x60) / t;
    } else {
        c->x60 = x;
        c->x64 = 0.0f;
    }
}

/* func_00135838 (from auto/text_00130000_13.c). */
s32 func_00135838(void *arg0) {
    return (s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x23) & 1;
}

/* func_00135848 (from auto/text_00130000_12.c). */
void func_00135848(void *arg0) {
    M2C_FIELD(arg0, s64 *, 0x370) = (s64) (M2C_FIELD(arg0, s64 *, 0x370) & (((((s64) 0xFFFDFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

/* func_00135870 (from auto/text_00130000_11.c). */
void func_00135870(void *arg0) {
    M2C_FIELD(arg0, s64 *, 0x370) = (s64) (M2C_FIELD(arg0, s64 *, 0x370) | ((s64) 0x8000 << 0x22));
}

/* func_00135888 (from auto/text_00130000.c). */
s32 func_00135888(void *arg0, s32 arg1) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x14C);
    if ((temp_v1 != NULL) && (arg1 & 0x10000)) {
        return M2C_FIELD(temp_v1, s32 *, 4);
    }
    return 0;
}

/* func_001358b8 (from auto/text_00130000_1.c). */
M2C_UNK func_00167ac0(s32, s32, s32);
#define func_00135888 ((s32 (*)()) func_00135888)
void func_001358b8(Actor *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0->unk15C;
    func_00167ac0(temp_s0, func_00135888(), arg1 & 0xFFFF);
}
#undef func_00135888

/* func_001358f8 (from auto/text_00130000_1.c). */
M2C_UNK func_00167fd0(s32, s32, s32);
#define func_00135888 ((s32 (*)()) func_00135888)
void func_001358f8(Actor *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0->unk15C;
    func_00167fd0(temp_s0, func_00135888(), arg1 & 0xFFFF);
}
#undef func_00135888

/* func_00135938 (from auto/text_00130000_1.c). */
M2C_UNK func_00167978(s32, s32, s32);
#define func_00135888 ((s32 (*)()) func_00135888)
void func_00135938(Actor *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0->unk15C;
    func_00167978(temp_s0, func_00135888(), arg1 & 0xFFFF);
}
#undef func_00135888

/* func_00135978 (from hand/text_00130000_h6.c). */
void func_00135978(W6Ch *c, s32 a, s32 b) {
    if (a-- > 0) {
        c->x38c |= 1 << a;
    }
    if (b-- > 0) {
        c->x390 |= 1 << b;
    }
}

/* func_001359c0 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad000[0x38C];
    u32 x38c;
    u32 x390;
    u32 x394;
} W6Ch2;
void func_001359c0(W6Ch2 *c, s32 a, s32 b) {
    if (a-- > 0) {
        c->x38c &= ~(1 << a);
    }
    if (b-- > 0) {
        c->x390 &= ~(1 << b);
    }
}

/* func_00135a10 (from hand/text_00130000_h6.c). */
void func_00135a10(W6Ch2 *c, s32 a) {
    if (a-- > 0) {
        c->x394 |= 1 << a;
    }
}

/* func_00135a38 (from hand/text_00130000_h6.c). */
void func_00135a38(W6Ch2 *c, s32 a) {
    if (a-- > 0) {
        c->x394 &= ~(1 << a);
    }
}

