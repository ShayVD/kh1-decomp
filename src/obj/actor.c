/* The actors: the actor lists (func_001230a0 walks them, NULL starts and
 * ends; func_00122ff8 whether one is live, func_00123488 finds one by id,
 * its kind in the id's byte 2), the player D_002E26A0, small actor tests
 * (func_00123158, func_00123368 ...), an actor's name (func_00122dc8,
 * sprintf), the actor records D_002C64A0 (func_00123810 clears them), the
 * room's actors set up (func_00124218) and placed (func_001238d0,
 * func_00123b40), the reset func_00124b90. Flag mode: default (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h53_p.h"
#include "data/types/text_00110000_h53_p2.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C5910.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h4_p.h"
#include "data/types/text_00110000_h4.h"
#include "data/pieces/D_002C5C60.h"
#include "m2c.h"
#include "data/pieces/D_002E26A0.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"
#include "data/types/text_00120000_h5.h"
#include "data/pieces/D_002E31B0.h"
#include "actor.h"
#include "data/pieces/D_002C6440.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C5C48.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002E26AC.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/text_00120000_h31_p.h"

/* func_00122dc8 (from hand/text_00110000_h53.c). */
typedef struct { u8 pad[0x130]; u8 *name; } Obj53;
extern s32 D_002C648C;
char D_004F7150[0x4][32] ALIGNED(16);
extern u8 D_0048D2C8[];
extern u8 D_0048D2D0[];
extern u8 D_0048D2D8[];
extern u8 D_0048D2E0[];
extern u8 D_0048D2E8[];
extern u8 D_0048D2F0[];
extern u8 D_0048D2F8[];
extern u8 D_0048D300[];
extern u8 D_0048D308[];
extern u8 D_0048D310[];
extern u8 D_0048D318[];
char *D_002C6460[0xb] ALIGNED(16) = {
    (void *)D_0048D318, (void *)D_0048D310, (void *)D_0048D308, (void *)D_0048D300,
    (void *)D_0048D2F8, (void *)D_0048D2F0, (void *)D_0048D2E8, (void *)D_0048D2E0,
    (void *)D_0048D2D8, (void *)D_0048D2D0, (void *)D_0048D2C8,
};
extern char D_0048D320[];
extern char D_0048D330[];
extern char D_0048D328[];
extern u8 D_00491A18[];
Obj53 *func_00123488_22dc8() __asm__("func_00123488");
u8 *func_001320a8(u32);
int sprintf(char *, const char *, ...);
u32 strlen(const char *);
static inline s32 w53_toupper(s32 c) {
    return ((D_00491A18 + 1)[c] & 2) ? c - 32 : c;
}
#define func_00123488 ((Obj53 *(*)(u32)) func_00123488_22dc8)
char *func_00122dc8(u32 id, char *buf) {
    Obj53 *o = func_00123488(id);
    u8 *p;
    s32 n, i;
    char c;
    if (o) {
        p = o->name;
    } else {
        p = func_001320a8(id);
    }
    if (!buf) {
        buf = D_004F7150[D_002C648C];
        D_002C648C = (D_002C648C + 1) % 4;
    }
    if (p) {
        sprintf(buf, D_0048D320, D_002C6460[(id >> 16) & 0xff], p + 104);
    } else if (((id >> 16) & 0xff) < 11) {
        sprintf(buf, D_0048D328, D_002C6460[(id >> 16) & 0xff], id);
    } else {
        sprintf(buf, D_0048D330, (id >> 16) & 0xff, id);
    }
    n = strlen(buf);
    for (i = 0; i < n; i++) {
        buf[i] = w53_toupper(buf[i]);
    }
    return buf;
}
#undef func_00123488

/* func_00122f20 (from hand/text_00110000_h4.c). */
typedef struct { u8 pad[0x44]; f32 f44; u8 pad2[0x16]; u8 b5e; u8 b5f; } Sub130;
typedef struct {
    u32 flags; u8 pad[0x12c]; Sub130 *p130; u8 pad2[0x18]; s32 x14c; s32 pad3; s32 x154;
    u8 pad4[0x78]; s32 x1d0; u8 pad5[0x19c]; u64 x370;
} Obj;
void func_00122f20(Obj *o, s32 *out) {
    out[0] = o->x154;
    if (o->x14c) out[1] = *(s32 *)o->x14c; else out[1] = 0;
    out[2] = o->x1d0;
}

/* func_00122f48 (from auto/text_00120000_2.c). */
void func_00122f48(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), f32 *, 0x44) = fparg0;
}

/* func_00122fd0 (from hand/text_00110000_h4.c). */
s32 func_00122fd0(Obj *o) {
    s32 r = 0;
    if (o->p130->b5f) {
        if (!(o->flags & 0x2000000)) r = 1;
    }
    return r;
}

/* func_00122ff8 (from hand/text_00110000_h4.c). */
s32 func_00122ff8(Obj *o) {
    s32 r = 0;
    if (o) {
        if ((o->x370 & 0x300000000) == 0x100000000) r = 1;
    }
    return r;
}

/* func_00123030 (from hand/text_00110000_h4.c). */
typedef struct Act {
    u8 pad0[6]; u8 b6; u8 pad7[0x6d]; struct Act *x74; s32 x78; s32 pad7c; s32 x80;
    u8 pad84[0x2ec];
    union { u64 x370; struct { u32 lo0; u32 lo : 5; u32 kind : 2; u32 hi : 25; } b370; } u370;
    u8 pad378[0x138];
} Act;
Act *func_001230a0(Act *a);
void func_00123030(Act *x, Act *a1, s32 a2) {
    Act *a;
    x->x74 = a1;
    x->x78 = a2;
    a = 0;
    while ((a = func_001230a0(a)) != 0) a->x80 = 0;
    while ((a = func_001230a0(a)) != 0) {
        if (a->x74) a->x74->x80++;
    }
}

/* func_001230a0 (from hand/text_00110000_h4.c). */
/* Entity walked by func_001230a0 (iterator: NULL starts, NULL ends). */
extern Act D_002C64A0[];
Act *func_001230a0(Act *a) {
    if (a == 0) a = D_002C64A0; else a++;
    for (; a < ((Act *)&D_002E26A0); a++) {
        if ((a->u370.x370 & 0x300000000) == 0x100000000) return a;
    }
    return 0;
}

/* func_00123118 (from auto/text_00120000_15.c). */
s32 func_00123118(void *arg0, void *arg1) {
    s32 temp_a1;
    s32 var_v1;

    var_v1 = 0;
    if (!(M2C_FIELD(arg1, s32 *, 0) & 0x200)) {
        temp_a1 = (s32) ((u64) M2C_FIELD(arg1, u64 *, 0x370) >> 0x25) & 3;
        if (temp_a1 != 0) {
            var_v1 = temp_a1 != ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x25) & 3);
        }
    }
    return var_v1;
}

/* func_00123158 (from hand/text_00110000_h4.c). */
#define func_00123118 ((s32 (*)(s32, Act *)) func_00123118)
Act *func_00123158(s32 k, Act *a) {
    while ((a = func_001230a0(a)) != 0) {
        if (func_00123118(k, a)) return a;
    }
    return 0;
}
#undef func_00123118

/* func_001231b8 (from hand/text_00110000_h4.c). */
Act *func_001231b8(Act *x, Act *a) {
    while ((a = func_001230a0(a)) != 0) {
        if (x != a && x->u370.b370.kind == a->u370.b370.kind) return a;
    }
    return 0;
}

/* func_00123220 (from hand/text_00110000_h4.c). */
Act *func_00123220(Act *a) {
    while ((a = func_001230a0(a)) != 0) {
        if (a->b6 == 2 || a->b6 == 9 || a->b6 == 10 || a->u370.b370.kind == 2) return a;
    }
    return 0;
}

/* func_00123298 (from hand/text_00120000_h5.c). */
typedef struct Ent {
    union {
        u64 flags; /* 0x000 */
        u8 b[8];
    };
    u8 pad008[0x134 - 8];
    u8 *info; /* 0x134 */
    u8 pad138[0x370 - 0x138];
    u64 f370; /* bits 37-38: 2-bit state */
    u8 pad378[0x3a0 - 0x378];
    s32 f3a0;
    u8 pad3a4[4];
    s32 f3a8;
} Ent;
#define func_001230a0 ((Ent *(*)(Ent *)) func_001230a0)
s32 func_00123298(void) {
    Ent *p = 0;
    s32 n = 0;
    while ((p = func_001230a0(p)) != 0) {
        if (((p->f370 >> 37) & 3) == 2) n++;
    }
    return n;
}
#undef func_001230a0

/* func_001232f0 (from hand/text_00120000_h5.c). */
s32 func_001232f0(Ent *e) {
    s32 r = 0;
    if (e->info && e->info[4] && e->f3a0 == 0) {
        r = 1;
        if ((e->flags & 0x8010) != 0x8000) r = 0;
    }
    return r;
}

/* func_00123330 (from hand/text_00120000_h5.c). */
s32 func_00123330(Ent *e) {
    s32 r = 0;
    if (e->info && e->info[5]) {
        r = 1;
        if ((e->flags & 0x8020) != 0x8000) r = 0;
    }
    return r;
}

/* func_001233e8 (from auto/text_00120000_3.c). */
s32 func_00123368();
s32 func_001233e8(Actor *arg0) {
    s32 var_s1;

    var_s1 = 0;
    if (func_00123368(arg0) != 0) {
        var_s1 = (arg0->unk000 & 0x01000080) == 0;
    }
    return var_s1;
}

/* func_00123438 (from hand/text_00120000_h5.c). */
typedef struct Stk {
    s32 cur;
    u8 pad004[0x37c - 4];
    s32 stack[3];
    s32 n;
} Stk;
void func_00123438(Stk *s, s32 v) {
    s32 *n = &s->n;
    s32 c = s->cur;
    s32 i = *n;
    s->stack[i] = c;
    *n = i + 1;
    s->cur = v;
}

/* func_00123460 (from auto/text_00120000.c). */
void func_00123460(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x388);
    temp_v1 = temp_v0 - 1;
    if (temp_v0 > 0) {
        M2C_FIELD(arg0, s32 *, 0x388) = temp_v1;
        M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x37C);
    }
}

/* func_00123488 (from hand/text_s7_w31.c). */
typedef struct { u8 pad[0x4c]; u16 x4c; u16 x4e; } Prm;
typedef struct Actor_23488 { u32 x0; u32 x4; u8 pad[0x128]; Prm *x130; } Ent_23488;
/* func_00123488 (w31): matches in hand and hand/nostrict. All "return 0" go to one shared r0 label at the end (keeps the explicit move v0,zero after each loop and the reloaded li 1 in case 0), and case 1 first loop shares the found: return e stub with the default loop. Needs func_001230a0 defined above it (CONTEXT_ONLY copy). */
Ent_23488 *func_00123488(u32 id) {
    Ent_23488 *e;
    s32 i;
    s32 t = (id >> 16) & 0xff;
    switch (t) {
    case 1:
        for (i = 0; i < 3; i++) {
            e = D_002E26A0[i];
            if (e && e->x130->x4c == (id & 0xffff)) goto found;
        }
        e = 0;
        while ((e = func_001230a0(e)) != 0) {
            if (e->x130->x4c == (id & 0xffff)) return e;
        }
        goto r0;
    case 0:
        switch ((s32)(id & 0xffff)) {
        case 0: return D_002E26A0[0];
        case 1: return D_002E26A0[1];
        case 2: return D_002E26A0[2];
        }
        goto r0;
    found:
        return e;
    case 11:
        e = 0;
        while ((e = func_001230a0(e)) != 0) {
            if (e->x130->x4e == (id & 0xffff)) return e;
        }
        goto r0;
    default:
        for (e = func_001230a0(0); e; e = func_001230a0(e)) {
            if (e->x4 == id) goto found;
        }
        goto r0;
    }
r0:
    return 0;
}

/* func_00123618 (from hand/text_00120000_h5.c). */
typedef struct S4c { u8 pad[0x4c]; u16 f4c; } S4c;
typedef struct S130 { u8 pad[0x130]; S4c *p; } S130;
#define func_00123488 ((void *(*)()) func_00123488)
s32 func_00123618(u32 id) {
    S130 *p = func_00123488(id);
    if (p) return p->p->f4c;
    return 255;
}
#undef func_00123488

/* func_00123648 (from auto/text_00120000_3.c). */
#define func_00123488 ((s32 *(*)()) func_00123488)
void func_00123648(s32 arg0, s32 arg1) {
    s32 *temp_v0;

    temp_v0 = func_00123488(arg0);
    *temp_v0 |= 1 << arg1;
}
#undef func_00123488

/* func_00123680 (from auto/text_00120000_3.c). */
#define func_00123488 ((s32 *(*)()) func_00123488)
void func_00123680(s32 arg0, s32 arg1) {
    s32 *temp_v0;

    temp_v0 = func_00123488(arg0);
    *temp_v0 &= ~(1 << arg1);
}
#undef func_00123488

/* func_001236c0 (from auto/text_00120000_3.c). */
#define func_00123488 ((s32 *(*)()) func_00123488)
s32 func_001236c0(s32 arg0, s32 arg1) {
    return *func_00123488(arg0) & (1 << arg1);
}
#undef func_00123488

/* func_001236f8 (from auto/text_00120000_3.c). */
M2C_UNK func_00149860(void *);
M2C_UNK func_00162110(s32, void *);
void func_001236f8(void *arg0) {
    s32 temp_v0;

    if (!(((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x27) & 1)) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x154);
        if (temp_v0 != 0) {
            func_00162110(temp_v0, arg0 + 0x15C);
            if (M2C_FIELD(arg0, s32 *, 0x14C) != 0) {
                func_00149860(arg0);
            }
            M2C_FIELD(arg0, s32 *, 0x154) = 0;
            M2C_FIELD(arg0, s32 *, 0x134) = 0;
        }
    }
}

/* func_00123760 (from auto/text_00120000_4.c). */
#define func_001236f8 ((M2C_UNK (*)()) func_001236f8)
void func_00123760(void *arg0) {
    func_001236f8(arg0);
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 0x374) = 0;
}
#undef func_001236f8

/* func_00123790 (from auto/text_00120000_14.c). */
#define func_00123760 ((M2C_UNK (*)(M2C_UNK *)) func_00123760)
#define D_002C64A0 (*(M2C_UNK (*)) &D_002C64A0)
s32 func_00123790(void) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_002C64A0;
    var_s1 = 0x5F;
    do {
        if ((M2C_FIELD(var_s0, s64 *, 0x370) & ((s64) 0x800002 << 0x20)) == ((s64) 0x8000 << 0x12)) {
            func_00123760(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x4B0;
    } while (var_s1 >= 0);
    return 0;
}
#undef func_00123760
#undef D_002C64A0

/* func_00123810 (from hand/text_00110000_h30.c). */
typedef struct { u8 pad0[880]; u64 flags; u8 pad378[312]; } Obj1200;
void *memset(void *, s32, u32);
extern Obj1200 D_002C64A0_00123810[] __asm__("D_002C64A0");
#define D_002C64A0 D_002C64A0_00123810
Obj1200 *func_00123810(void) {
    s32 i;
    Obj1200 *p;
    for (i = 0; i < 96; i++) {
        p = D_002E26AC;
        D_002E26AC = p + 1;
        if ((void *)D_002E26AC >= (void *)D_002E26A0) D_002E26AC = D_002C64A0;
        if (!((s32)(p->flags >> 32) & 1)) {
            memset(p, 0, sizeof(Obj1200));
            p->flags |= 1ULL << 32;
            return p;
        }
    }
    return 0;
}
#undef D_002C64A0

/* func_001238c0 (from auto/text_00120000_3.c). */
void func_001238c0(void *arg0, f32 fparg0, f32 fparg1) {
    M2C_FIELD(arg0, f32 *, 0x410) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x414) = fparg1;
}

/* func_001238d0 (from hand/text_00110000_h53.c). */
typedef struct { u8 pad[4]; u32 flags; } Info8;
typedef struct {
    u64 lo : 44;
    u64 b44 : 1;
    u64 b45 : 1;
    u64 b46 : 1;
    u64 hi : 17;
} F370;
typedef struct Act53 {
    u8 pad0[0x10];
    V53 pos;
    V53 rot;
    f32 x30, x34, x38, x3c;
    u8 pad40[0x10];
    V53 prev;
    u8 pad60[0x60];
    f32 xc0;
    f32 xc4;
    f32 xc8;
    f32 xcc;
    u8 padd0[0x50];
    V53 x120;
    Info8 *info;
    u8 pad134[0x1c];
    f32 x150;
    u8 pad154[0x14c];
    V53 x2a0;
    u8 pad2b0[0xa0];
    s32 col[4];
    u8 pad360[0x10];
    F370 f;
    u8 pad378[0x26];
    u8 x39e;
    u8 pad39f[0x11];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
} Act53;
typedef struct {
    union { u32 w; u64 d; struct { u64 lo : 16; u64 b16 : 1; u64 hi : 47; } b; } u;
    u8 pad8[0x88];
    Act53 *owner;
} Ent53;
f32 func_00120c88(f32);
float sinf(float);
float cosf(float);
void func_00136d38(Act53 *);
void func_00116660(V53 *);
Ent53 *func_0014a398(Ent53 *);
void func_001238d0(Act53 *o, V53 *p) {
    Ent53 *e;
    f32 a;
    PlatVu0CopyVector(&o->pos, p);
    o->pos.w = 1.0f;
    PlatVu0CopyVector(&o->prev, &o->pos);
    if (!((*(u64 *)&o->f >> 44) & 1)) {
        a = func_00120c88(p->w);
        o->x30 = sinf(a);
        o->x34 = 0.0f;
        o->x38 = cosf(a);
        o->x150 = a;
        o->x3c = a;
        PlatVu0CopyVector(&o->rot, (V53 *)&o->x30);
    }
    o->rot.w = 0.0f;
    o->x3b4 = p->y;
    o->x3b0 = 0.0f;
    o->x3b8 = 0.0f;
    o->x3bc = 0.0f;
    o->xc0 = 0.0f;
    o->xc4 = 1.0f;
    o->xcc = 1.0f;
    o->xc8 = 0.0f;
    func_00136d38(o);
    PlatVu0CopyVector(&o->x2a0, &o->pos);
    func_00116660(&o->x2a0);
    if (!(o->info->flags & 0x40000)) {
        o->col[3] = 128;
        o->col[2] = 128;
        o->col[1] = 128;
        o->col[0] = 128;
    }
    o->x39e = 0;
    o->f.b46 = 0;
    PlatVu0CopyVector(&o->x120, &D_002C58A0);
    for (e = 0; (e = func_0014a398(e)) != 0;) {
        if (e->owner == o && (e->u.w & 3) == 1) e->u.b.b16 = 0;
    }
}

/* func_00123a88 (from auto/text_00120000_4.c). */
#define func_001238d0 ((M2C_UNK (*)(s32, s32)) func_001238d0)
#define func_00123488 ((s32 (*)()) func_00123488)
void func_00123a88(s32 arg0, s32 arg1) {
    func_001238d0(func_00123488(arg0), arg1);
}
#undef func_001238d0
#undef func_00123488

/* func_00123ab8 (from auto/text_00120000_11.c). */
#define func_00136d38 ((M2C_UNK (*)(void *)) func_00136d38)
#define func_00123488 ((void *(*)()) func_00123488)
void func_00123ab8(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00123488(arg0);
    M2C_FIELD(temp_v0, s64 *, 0x370) = (s64) (M2C_FIELD(temp_v0, s64 *, 0x370) | ((s64) 0x8000 << 0x1D));
    PlatVu0CopyVector(temp_v0 + 0x30, arg1);
    func_00136d38(temp_v0);
}
#undef func_00136d38
#undef func_00123488

/* func_00123b10 (from auto/text_00120000_9.c). */
#define func_00123488 ((s32 (*)()) func_00123488)
void func_00123b10(s32 arg0, s32 arg1) {
    PlatVu0CopyVector(func_00123488(arg0) + 0x40, arg1);
}
#undef func_00123488

/* func_001247e8 (from hand/text_00110000_h30.c). */
typedef struct { u8 pad0[12]; s32 xC; u8 pad10[60]; u16 x4C; u8 pad4e[6]; s8 kind; u8 pad55[4]; u8 x59; } Info123;
typedef union {
    u64 v;
    struct { u32 lo0; u32 x0 : 1; u32 b33 : 1; u32 x2 : 14; u32 b48 : 1; u32 x17 : 5; u32 b54 : 1; u32 x23 : 9; } b;
    struct { u64 lo : 33; u64 b33 : 1; u64 m : 14; u64 b48 : 1; u64 m2 : 5; u64 b54 : 1; u64 hi : 9; } c;
} ObjFlags;
typedef struct Actor_247e8 {
    u32 x0;
    u8 pad4[300];
    Info123 *info;
    u8 pad134[4];
    s32 x138;
    u8 pad13c[8];
    s32 x144;
    u8 pad148[552];
    ObjFlags fl;
    u8 pad378[40];
    s32 x3a0;
} Obj123;
extern s32 D_00350D80;
s32 func_0014f658(Obj123 *, s32);
void func_001574b0(u16);
void func_00170e48(Obj123 *);
void func_0014ed30(Obj123 *);
#define func_00122ff8 ((s32 (*)(Obj123 *)) func_00122ff8)
void func_001247e8(Obj123 *o) {
    s32 i;
    if (func_00122ff8(o) == 0) return;
    func_0014f658(o, 0);
    for (i = 0; i < 3; i++) {
        if (D_002E26A0[i] == o) {
            func_001574b0(o->info->x4C);
            if (o->info->kind == 1) func_00170e48(o);
            D_002E26A0[i] = 0;
        }
    }
    o->fl.c.b33 = 1;
    if (!o->fl.b.b54) D_00350D80 -= o->info->x59;
    func_0014ed30(o);
}
#undef func_00122ff8

/* func_001248e8 (from auto/text_00120000.c). */
#define func_001247e8 ((M2C_UNK (*)(s32)) func_001247e8)
#define func_00123488 ((s32 (*)()) func_00123488)
void func_001248e8(u32 id) {
    s32 temp_v0;

    temp_v0 = func_00123488(id);
    if (temp_v0 != 0) {
        func_001247e8(temp_v0);
    }
}
#undef func_001247e8
#undef func_00123488

/* func_001249d8 (from hand/text_00120000_h5.c). */
extern void func_00124920(void);
#define func_001230a0 ((Ent *(*)(Ent *)) func_001230a0)
#define func_001247e8 ((void (*)(Ent *)) func_001247e8)
void func_001249d8(void) {
    Ent *p = 0;
    func_00124920();
    while ((p = func_001230a0(p)) != 0) func_001247e8(p);
}
#undef func_001230a0
#undef func_001247e8

/* func_00124b90 (from hand/text_00120000_h31.c). */
extern void func_0011ef10(s32, void *);
extern A2 D_002C6814[];
extern void func_001372a0(void);
extern void func_00138738(void);
extern s32 func_0011ef38(void *);
#define D_002C64A0 (*(void *(*)) &D_002C64A0)
void func_00124b90(void) {
    s32 i;
    for (i = 0; i < 96; i++) D_002C6814[i].f0 = 0;
    D_002E26AC = &D_002C64A0;
    for (i = 0; i < 3; i++) D_002E26A0[i] = 0;
    func_001372a0();
    func_00138738();
    if (func_0011ef38(func_00123790) == 0)
        func_0011ef10(0x27cb9, func_00123790);
}
#undef D_002C64A0

