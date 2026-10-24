/* Hand-matched functions near 0x130000 (worker 6). */
#include "common.h"
#include "data/bss_0052.h"

typedef struct {
    u8 pad00[8];
    u64 bits;
} W6Kind;

#include "data/pieces/D_00308CDC.h"
typedef Cfg_308cdc W6Lim;
extern u32 D_002C5958;

typedef struct {
    s32 a;
    s32 b;
} W6Pair;
W6Pair D_0052A110[0x8] ALIGNED(16);

typedef struct {
    u32 flags;
    u8 pad04[0x2C - 0x4];
    f32 f2c;
    u8 pad30[0x88 - 0x30];
    u32 x88;
} W6Flg;
extern s32 D_003044D0;
#include "data/pieces/D_003044D8.h"

typedef struct {
    u32 flags;
    u8 pad004[0x40 - 0x4];
    f32 v40[3];
    u8 pad04c[0x4A4 - 0x4C];
    f32 f4a4;
} W6Fade;

typedef struct {
    u8 pad00[0xF];
    u8 b0f;
} W6Col;

typedef struct {
    u8 pad000[0x14C];
    W6Col *col;
} W6ColOwner;

typedef struct {
    u32 flags;
    u8 pad004[0xD0 - 0x4];
    u8 x0d0[0x154 - 0xD0];
    s32 x154;
    u8 pad158[0x39D - 0x158];
    u8 b39d;
} W6Reg;

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

#include "data/pieces/D_00304BE8_s.h"
typedef W606Mem_304be8 W6SEnt;

typedef struct {
    u8 pad00[0x40];
    u8 b40;
    u8 pad41[0x48 - 0x41];
    s32 w48;
    u8 pad4c[0xF0 - 0x4C];
} W6Info;

extern f32 D_002BBDFC;

void func_001247e8(W6Fade *o);
void func_001dce90(s32 a);
void func_001586a8(s32 a);
void func_002675a8(f32 *d, f32 *s);
void func_00156260(W6Unit *u, f32 *v);

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
} W6Blob;

#include "data/pieces/D_00304B78.h"
extern f32 D_00304B7C;
extern W6Blob *D_0052AE5C; /* src/data/bss_0052.c: void *D_0052AE5C */
extern s32 D_0052AE54;
extern u32 D_002C5978;

f32 func_00176850(void);
void func_00139240(W6Unit *u, s32 a, s32 b, f32 x, f32 y, f32 z);
void func_001473a8(s32 a, s32 b, void *c);
void func_00155be0(void *p);
void func_001763f0(void *p);
void FlushCache(s32 mode);
s32 D_00F20000(s32 a, s32 b);
void func_0013a810(void);

u8 D_0052AD58[0x10] ALIGNED(8);
extern u8 D_0052AD68[];
extern u8 D_00304B48[];

void func_0013bde8(void *a, void *b, s32 n);
void func_0011f130(void *a, s32 b);
s32 func_0013be00(void *a);
void func_00141b10(s32 i, W6Info *info);
void func_0013bef0(void);
void func_0014f778(void);
void func_0014f828(void);
void func_0014f830(s32 a, s32 b, s32 c, s32 d, void (*e)(void), void (*f)(void), void (*g)(void), s32 h, s32 i);

s32 func_00120748(s32 a, s32 b, void (*c)(void), s32 d);
void func_0011ef10(s32 a, void (*b)(void));

s32 func_00137450(struct Actor *id) {
    s32 i;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].x8 == id) {
            return i;
        }
    }
    return -1;
}

s32 func_001375f0(W6Flg *f) {
    return !(f->flags & 4) && !(f->x88 & 0x20);
}

s32 func_00137718(W6Flg *f) {
    if (f->flags & 4) {
        return 0;
    }
    if (f->f2c == 0.0f) {
        return 0;
    }
    return 1;
}
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

s32 func_00138988(W6Unit *u) {
    s32 d = u->x164 - u->h3ea;
    if ((u32)d >= 10) {
        return 0;
    }
    return d % 5 + 1;
}

void func_00138c30(W6Unit *u, W6Cmd *c) {
    f32 v[4];
    func_002675a8(v, c->v10);
    v[3] = (*(Cfg_308cdc **)&D_00308CDC)->x2c * u->p6c->fc4;
    func_00156260(u, v);
    c->bits |= 2;
}
void func_00139408(W6Unit *u, s32 a) {
    W6Lim *c = (*(Cfg_308cdc **)&D_00308CDC);
    f32 lo = c->h14;
    f32 t = lo + (c->h16 - lo) * u->p6c->fc4;
    f32 k = c->f18;
    func_00139240(u, a, 0, t * k, t, func_00176850() * 30.0f);
}

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

s32 func_0013aa60(void) {
    if (!(((*(u32 *)&D_00304B78) >> 3) & 1)) {
        return 1;
    }
    return D_00304B7C <= 0.0f;
}

void func_0013b1a0(void) {
    if (D_0052AE5C->x8 - D_0052AE5C->x4 > 0) {
        func_00155be0((u8 *)D_0052AE5C + D_0052AE5C->x4);
    }
    if (D_0052AE5C->xc - D_0052AE5C->x8 > 0) {
        func_00155be0((u8 *)D_0052AE5C + D_0052AE5C->x8);
    }
    if (D_0052AE5C->x10 - D_0052AE5C->xc > 0) {
        func_001763f0((u8 *)D_0052AE5C + D_0052AE5C->xc);
    }
    FlushCache(2);
    D_0052AE54 = 4;
}

s32 func_0013b8f0(void) {
    if (((D_002C5978 >> 8) & 3) != 1) {
        if (D_00F20000(1, 0) != 0) {
            return 0;
        }
    }
    func_0013a810();
    D_002C5958 &= ~0x2000;
    (*(u32 *)&D_00304B78) = 0;
    return 1;
}
s32 func_0013b958(u16 *p) {
    if (*p & 0x10) {
        func_0013bde8(D_0052AD58, D_00304B48, 4);
    }
    func_0011f130(D_0052AD68, 0);
    return func_0013be00(D_0052AD58) ? 0 : 4;
}

void func_0013bf20(void) {
    func_0014f830(40, 256, 0, 0, func_0013bef0, func_0014f778, func_0014f828, 0, 0);
}

void func_0013bf90(s32 on) {
    if (on) {
        D_00304BE8->f880 = 1;
    } else {
        D_00304BE8->f880 = 0;
    }
}

void func_0013c078(void) {
    W6Info info;
    W6SEnt *e;
    s32 i;
    for (i = 0; i < 10; i++) {
        e = &D_00304BE8->m[i];
        func_00141b10(i, &info);
        e->sub.x1 = info.b40;
        if (e->sub.x3 < info.w48) {
            e->sub.x38 = 0;
            e->sub.x3 = info.w48;
        }
    }
}
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5978.h"
#include "data/pieces/D_002BBDFC.h"
