/* The pppRyjMegaBirth class, -fno-strict-aliasing (docs/modules.md
 * "Session 50"): a particle emitter of shapes, the model of the
 * pppRyjMegaBirthModel / Filter / ModelFilter classes.  func_0019bbf0 starts
 * a particle (position by the key's type: a direction cone, a box, or a
 * vertex of a mesh set; speed, spin, size and colour from the key's ranges,
 * random numbers from vu0.c's func_0019baf8); func_0019cb88 moves the live
 * ones (func_0019c838, ryjmb.nostrict_nofill.c) and steps each one's shape
 * animation, starting new ones after the key's wait.  The frame
 * (pppRyjMegaBirthFrame) allocates n particles of 0x60 bytes (and the
 * optional 64-byte and 32-byte extras) on its first frame; the draw
 * (pppRyjMegaBirthDraw) builds each live particle's matrix (func_0019cfc0
 * in ryjmb.c, func_0019d020 in ryjmb.nostrict_nofill.c) and colour and draws
 * its shape frame with func_001b8198.  The Con, Des and the gate
 * func_0019bb98 are in ryjmb.c.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"

typedef struct { s16 x, y, z; } MgV6;
typedef struct { s16 h0; u16 n; u16 *idx; } MgSet;
typedef struct { u8 pad[0x14]; MgV6 *v; u8 pad18[0xC]; } MgSlot;
typedef struct { u8 pad[0x10]; MgSlot *slots; u8 pad14[4]; MgSet *sets; } MgSys;
typedef struct { u8 pad[0x10]; f32 m10[4][4]; u8 pad50[0x40]; MgV6 *v90; } MgCur;
extern MgSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern MgCur *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */

typedef struct {
    u8 pad0[0x22];
    u16 live;      /* 0x22 */
    u8 b24, b25, type, b27;
    f32 f28, f2C, f30, f34; /* 0x28 */
    u8 pad38[0x10];
    u8 col[4];     /* 0x48 */
    f32 f4C, f50, f54, f58, f5C; /* 0x4C */
    u8 pad60[0x10];
    f32 f70, f74, f78, f7C, f80, f84, f88; /* 0x70 */
    f32 v8C[3];    /* 0x8C */
    u8 pad98[0xC];
    f32 fA4, fA8, fAC, fB0, fB4, fB8; /* 0xA4 */
    f32 sc[3];     /* 0xBC */
    u8 c8, c9, ca, cb, cc, cd; /* 0xC8 */
    u8 padCE[2];
    s16 set;       /* 0xD0 */
} MgKey;

typedef struct {
    f32 pos[4];
    f32 dir[4];
    u8 pad20[6];
    u16 live;      /* 0x26 */
    s8 col[4];     /* 0x28 */
    f32 f2C, f30, f34, f38, f3C, f40, f44, f48, f4C, f50, f54, f58; /* 0x2C */
    u8 b5C, b5D, b5E, b5F;
} MgPart;

typedef struct { u8 pad[0x10]; f32 f10, f14, f18, f1C; } MgB;
typedef struct { u8 pad[0x62]; u16 h62; } MgObj;
typedef struct { u8 pad[0xB]; u8 bB; } MgE;

f32 func_0019baf8(void);
s8 func_0019bb40(u8);
void *memset(void *, s32, u32);

CONTEXT_ONLY f32 func_0019baf8(void) {
    f32 ret;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=&r"(ret)
        :
        : "$8", "memory");
    return ret;
}

CONTEXT_ONLY s8 func_0019bb40(u8 a) {
    f32 f = func_0019baf8();

    return (f32) (a * 2) * f - (f32) (a >> 1);
}

#define R func_0019baf8()
/* rodata (jump tables at 0x0048FBF0) */
#define TAIL(E) { v = tbl[E]; t = v.x; p->pos[0] = (f32)t * key->sc[0]; u = v.y; p->pos[1] = (f32)u * key->sc[1]; p->pos[2] = (f32)v.z * key->sc[2]; }
void func_0019bbf0(MgObj *obj, s32 keyi, MgE *e, MgPart *p, void *a, MgB *b) {
    f32 vec[4] __attribute__((aligned(16)));
    f32 ang[4] __attribute__((aligned(16)));
    f32 m[4][4] __attribute__((aligned(16)));
    MgKey *key = (MgKey *)keyi;
    f32 rng = key->b27;
    f32 rng2 = 2.0f * rng;
    s32 i;
    s32 t;
    s32 u;
    f32 f, h, r1, r2, r3, r4, r;
    MgV6 v;

    memset(p, 0, sizeof(MgPart));
    if (a)
        memset(a, 0, 0x40);
    if (b)
        memset(b, 0, 0x20);
    switch (key->type) {
    case 0 ... 7:
        { f32 x0 = key->v8C[0], x1 = key->v8C[1], x2 = key->v8C[2]; vec[0] = x0; vec[1] = x1; vec[2] = x2; }
        vec[3] = 1.0f;
        for (i = 0; i < 3; i++)
            ang[i] = (rng2 * func_0019baf8() - rng) * 3.141592562f / 180.0f;
        if ((u8)(key->type - 2) < 2) {
            ang[0] = 0.0f;
            ang[1] = 0.0f;
        }
        PlatVu0UnitMatrix(m);
        PlatVu0RotMatrix(m, m, ang);
        PlatVu0ApplyMatrix(p->dir, m, vec);
        p->dir[0] *= key->sc[0];
        p->dir[1] *= key->sc[1];
        p->dir[2] *= key->sc[2];
        PlatVu0Normalize(p->dir, p->dir);
    }
    switch (key->type) {
    case 0: case 1: case 2: case 3:
    default:
        f = key->fB8;
        if (f == 0.0f)
            break;
        switch (key->c8) {
        case 0:
            break;
        case 1:
            func_0019baf8();
            f = key->fB8 * func_0019baf8();
            break;
        case 2:
            f = key->fB8 * R * R;
            break;
        case 3:
            f = key->fB8 - key->fB8 * R * R * 0.7f;
            break;
        case 4:
            f = key->fB8 * R * R * R * R;
            break;
        case 5:
            f = key->fB8 - key->fB8 * R * R * R * 0.5f;
            break;
        }
        PlatVu0ScaleVectorXYZ(p, p->dir, f);
        break;
    case 4: case 5:
        if (key->fB8 == 0.0f)
            break;
        rng2 = key->fB8 * 0.5f;
        switch (key->c8) {
        case 0:
        default:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * func_0019baf8() - rng2;
            break;
        case 1:
            func_0019baf8();
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * func_0019baf8() - rng2;
            break;
        case 2:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * R * R - rng2;
            break;
        case 3:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 - key->fB8 * R * R * 0.7f - rng2;
            break;
        case 4:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * R * R * R * R - rng2;
            break;
        case 5:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 - key->fB8 * R * R * R * 0.5f - rng2;
            break;
        }
        p->pos[0] *= key->sc[0];
        p->pos[1] *= key->sc[1];
        p->pos[2] *= key->sc[2];
        break;
    case 6: case 7: case 8: case 9: {
        s16 id = key->set;
        MgV6 *tbl = D_00615E68->v90;
        MgSet *s;
        u16 *ip;
        if (id < 0)
            break;
        s = &D_00615E64->sets[id];
        if (!tbl)
            tbl = D_00615E64->slots[s->h0].v;
        switch (key->c8) {
        case 0:
        default:
            if (obj->h62 >= (s16)s->n)
                obj->h62 = 0;
            { s32 k = s->idx[obj->h62++]; TAIL(k); }
            goto ty;
        case 1:
            R;
            r = R;
            break;
        case 2:
            r = R * R * R;
            break;
        case 3:
            r = 1.0 - R * R * R;
            break;
        case 4:
            r = R * R * R * R;
            break;
        case 5:
            r = 1.0 - R * R * R * R * R;
            break;
        }
        if (obj->h62 >= (s16)s->n)
            obj->h62 = 0;
        { s32 k = s->idx[(s32)(r * (f32)(s16)s->n)]; TAIL(k); }
    ty:
        if ((u8)(key->type - 8) < 2)
            PlatVu0Normalize(p->dir, p->pos);
        break;
    }
    }
    p->col[0] = func_0019bb40(key->col[0]);
    p->col[1] = func_0019bb40(key->col[1]);
    p->col[2] = func_0019bb40(key->col[2]);
    p->col[3] = func_0019bb40(key->col[3]);
    if (key->b24) {
        p->f58 = e->bB;
        p->b5D = key->b24;
    }
    if (key->b25)
        p->b5E = key->b25;
    p->f2C = key->f7C;
    p->f30 = key->f80;
    if (key->cb) {
        p->f34 = func_0019baf8() * key->f88;
        if (key->cb & 1) {
            if (key->cb & 2) {
                if (func_0019baf8() > 0.5)
                    p->f34 = -p->f34;
            }
        } else if (key->cb & 2) {
            p->f34 = -p->f34;
        }
    }
    if (key->cb & 4)
        p->f2C += p->f34;
    if (key->cb & 8)
        p->f30 += p->f34;
    while (p->f2C >= 180.0f)
        p->f2C -= 360.0f;
    while (p->f2C < -180.0f)
        p->f2C += 360.0f;
    p->f38 = key->f4C;
    p->f3C = key->f50;
    p->f40 = key->f58;
    p->f44 = key->f5C;
    if (key->ca) {
        if (key->ca & 0x20) {
            p->f48 = p->f4C = func_0019baf8() * key->f70;
            if (key->ca & 1) {
                if (key->ca & 2) {
                    if (func_0019baf8() > 0.5) {
                        p->f48 = -p->f48;
                        p->f4C = -p->f4C;
                    }
                }
            } else if (key->ca & 2) {
                p->f48 = -p->f48;
                p->f4C = -p->f4C;
            }
        } else {
            p->f48 = func_0019baf8() * key->f70;
            p->f4C = func_0019baf8() * key->f74;
            if (key->ca & 1) {
                if (key->ca & 2) {
                    if (func_0019baf8() > 0.5)
                        p->f48 = -p->f48;
                    if (func_0019baf8() > 0.5)
                        p->f4C = -p->f4C;
                }
            } else if (key->ca & 2) {
                p->f48 = -p->f48;
                p->f4C = -p->f4C;
            }
        }
    }
    if (key->ca & 4) {
        p->f38 += p->f48;
        p->f3C += p->f4C;
    }
    if (key->ca & 8) {
        p->f40 += p->f48;
        p->f44 += p->f4C;
    }
    p->f50 = key->fA4;
    p->f54 = key->fB0;
    if (key->fAC != 0.0f)
        p->f50 += 2.0f * key->fAC * func_0019baf8() - key->fAC;
    if (key->live) p->live = key->live; else p->live = -1;
    p->b5C = 0;
    switch (key->cc) {
    case 1:
        PlatVu0CopyMatrix(a, obj);
        break;
    case 2:
        PlatVu0CopyMatrix(a, D_00615E68->m10);
        break;
    }
    if (b) {
        b->f10 = key->f28;
        b->f14 = key->f2C;
        b->f18 = key->f30;
        b->f1C = key->f34;
    }
}

#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} DMdl;

typedef struct {
    s32 pad0[4];
    u32 tex;    /* +0x10 */
    s32 pad14[2];
    DMdl *mdl;  /* +0x1C */
    s32 unk20;  /* +0x20 */
} DSlot;

typedef struct {
    s16 off;   /* +0x0 */
    s16 dur;   /* +0x2 */
    s8 flags;  /* +0x4 */
    u8 pad5[3];
} PppShapeFrame;

typedef struct {
    u8 pad0[6];
    s16 n;                  /* +0x6 */
    u8 pad8[8];
    PppShapeFrame f[1];     /* +0x10 */
} PppShape;

typedef struct {
    PppShape *shape;
    s32 unk4;
} PppShapeEnt;

typedef struct {
    u8 pad00[0x10];
    DSlot *slots;        /* +0x10 */
    PppShapeEnt *shapes; /* +0x14 */
} DSys;

extern s32 D_00616224;

typedef struct {
    u8 pad[8];
    u8 r, g, b, a; /* +0x8 */
} DColWork;

typedef struct {
    u8 pad[0x20];
    u16 time;   /* +0x20 */
    u16 cur;    /* +0x22 */
    u16 prev;   /* +0x24 */
    u16 live;   /* +0x26 */
    u8 pad28[0x38];
} PppMegaPart; /* 0x60 */

typedef struct {
    s32 frame;
    s32 id;     /* +0x4 */
    u16 speed;  /* +0x8 */
    u8 padA[0x12];
    u16 n;      /* +0x1C */
    u16 max;    /* +0x1E */
    u16 wait;   /* +0x20 */
    u8 pad22[4];
    u8 mode;    /* +0x26 */
    u8 pad27[0x71];
    f32 dir[3]; /* +0x98 */
    u8 padA4[0x25];
    u8 bC9;     /* +0xC9 */
    u8 padCA[2];
    u8 bCC;     /* +0xCC */
} PppMegaKey;

typedef struct { u8 b[0x40]; } PppMegaA;
typedef struct { u8 b[0x20]; } PppMegaB;

typedef struct {
    PppMtx m;           /* +0x00 */
    PppVec4 v;          /* +0x40 */
    PppMegaPart *parts; /* +0x50 */
    PppMegaA *a;        /* +0x54 */
    PppMegaB *b;        /* +0x58 */
    s32 n;              /* +0x5C */
    u16 timer;          /* +0x60 */
} PppMegaObj;

void func_0019c838(PppMegaObj *, PppMegaKey *, PppMegaPart *, PppEntry *, PppMegaB *);

void func_0019cb88(PppMegaObj *obj, PppMegaKey *key, PppEntry *e) {
    PppMegaPart *p = obj->parts;
    PppMegaA *a = obj->a;
    PppMegaB *b = obj->b;
    s32 n = obj->n;
    s32 born = 0;
    s32 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->id == 0xFFFF)
        return;
    obj->timer++;
    for (i = 0; i < n; i++) {
        if (p->live) {
            PppShape *s;
            PppShapeFrame *f;
            s8 fl;

            func_0019c838(obj, key, p, e, b);
            { PppShapeEnt *se = &((DSys *)D_00615E64)->shapes[key->id]; s = se->shape; }
            f = &s->f[p->prev];
            p->prev = p->cur;
            p->time += key->speed;
            if (p->time < f->dur)
                goto next;
            p->time -= f->dur;
            p->cur++;
            if (p->cur < s->n)
                goto next;
            if (f->flags & 0x80) {
                p->cur = 0;
                p->time = 0;
            } else {
                p->time = 0;
                p->cur--;
            }
        } else if (key->wait <= obj->timer && born < key->max) {
            func_0019bbf0((MgObj *)obj, (s32)key, (MgE *)e, (MgPart *)p, a, (MgB *)b);
            born++;
        }
    next:
        if (a)
            a++;
        if (b)
            b++;
        p++;
    }
    if (born > 0)
        obj->timer = 0;
}

/* pppRyjMegaBirthFrame (from text_00190000_h64.c). */
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701D0.h"
extern PppMtx D_00615E70;
void *func_0017f958(DSys *, s32);
s32 func_0019bb98(void *, void *);

void pppRyjMegaBirthFrame(PppObject *obj, PppMegaKey *key, PppEntry *e) {
    PppMegaObj *w = PPP_WORK(PppMegaObj, obj, e, 2);
    void *w1 = PPP_WORK(void, obj, e, 1);

    if (w->parts == 0) {
        w->n = key->n;
        w->parts = func_0017f958((DSys *) D_00615E64, w->n * 96);
        if (w->parts)
            memset(w->parts, 0, w->n * 96);
        if ((u8) (key->bCC - 1) < 2) {
            w->a = func_0017f958((DSys *) D_00615E64, w->n * 64);
            if (w->a)
                memset(w->a, 0, w->n * 64);
        }
        if (key->bC9) {
            w->b = func_0017f958((DSys *) D_00615E64, w->n * 32);
            if (w->b)
                memset(w->b, 0, w->n * 32);
        }
        w->v[0] = key->dir[0];
        w->v[1] = key->dir[1];
        w->v[2] = key->dir[2];
        w->v[3] = 0.0f;
        PlatVu0Normalize(w->v, w->v);
    }
    if (!func_0019bb98(w, key))
        return;
    switch (key->mode) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        PlatVu0UnitMatrix(w->m);
        PlatVu0ScaleVectorXYZ(w->m[0], w->m[0], D_003701F0[0]);
        PlatVu0ScaleVectorXYZ(w->m[1], w->m[1], D_003701F0[1]);
        PlatVu0ScaleVectorXYZ(w->m[2], w->m[2], D_003701F0[2]);
        PlatVu0CopyVector(w->m[3], (*(f32 (*)[4])&D_003701D0));
        w->m[3][3] = 1.0f;
        break;
    default:
        PlatVu0CopyMatrix(w->m, D_00615E70);
        break;
    }
    func_0019cb88(w, key, w1);
}

/* pppRyjMegaBirthDraw's views (from text_00190000_b08.c). */
typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    u64 d8;
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} DShpParam;

typedef struct {
    u8 pad00[0x14];
    PppShapeEnt *shapes;
} DSysS;

typedef struct {
    PppVec4 pos;   /* +0x00 */
    PppVec4 vel;   /* +0x10 */
    u16 time;      /* +0x20 */
    u16 cur;       /* +0x22 */
    u16 prev;      /* +0x24 */
    u16 live;      /* +0x26 */
    s8 c[4];       /* +0x28 */
    f32 ang;       /* +0x2C */
    f32 angv;      /* +0x30 */
    f32 anga;      /* +0x34 */
    f32 sx, sy;    /* +0x38 */
    f32 svx, svy;  /* +0x40 */
    f32 sax, say;  /* +0x48 */
    f32 spd;       /* +0x50 */
    f32 grav;      /* +0x54 */
    f32 alpha;     /* +0x58 */
    u8 n;          /* +0x5C */
    u8 fin;        /* +0x5D */
    u8 fout;       /* +0x5E */
    u8 pad5F;
} MegaPart;

typedef struct {
    s32 frame;
    s32 id;         /* +0x04 */
    u8 pad8[4];
    u8 bC, bD, bE, bF;
    f32 v10[3];     /* +0x10 */
    u8 pad1C[6];
    u16 h22;
    u8 pad24;
    u8 b25;
    u8 pad26[0x12];
    f32 c38[4];     /* +0x38 */
    u8 pad48[0x1C];
    f32 svx, svy;   /* +0x64 */
    u8 pad6C[0x18];
    f32 angv;       /* +0x84 */
    u8 pad88[0x1C];
    f32 spdv;       /* +0xA4 */
    f32 spda;       /* +0xA8 */
    u8 padAC[8];
    f32 grav;       /* +0xB4 */
    u8 padB8[0x12];
    u8 bCA, bCB, bCC, bCD;
    u8 bCE;
} MegaKey;

typedef struct { u8 b[0x40]; } MegaA;
typedef struct { f32 f[8]; } MegaB;

typedef struct {
    PppMtx m;        /* +0x00 */
    PppVec4 v;       /* +0x40 */
    MegaPart *parts; /* +0x50 */
    MegaA *a;        /* +0x54 */
    MegaB *b;        /* +0x58 */
    s32 n;           /* +0x5C */
    u16 timer;       /* +0x60 */
} MegaObj;

extern PppMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
s32 func_001b8198(void *, DShpParam *, s32);
void func_0019cfc0(PppMtx, MegaKey *, MegaObj *);
void func_0019d020(PppMtx, PppMtx, MegaKey *, MegaObj *, MegaPart *, MegaA *, PppMtx, u8);

#define D_00616224 (*(volatile s32 *) &D_00616224)
void pppRyjMegaBirthDraw(PppObject *obj, MegaKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppMtx mtx;
    PppVec4 v;
    DShpParam p;
    MegaObj *w = PPP_WORK(MegaObj, obj, e, 2);
    DColWork *c = PPP_WORK(DColWork, obj, e, 1);
    MegaPart *pt = w->parts;
    MegaA *a = w->a;
    MegaB *b = w->b;
    s32 n = w->n;
    PppShapeEnt *s;
    PppShape *sh;
    s32 cr, cg, cb, ca;
    s32 i;

    if (!func_0019bb98(w, key))
        return;
    if (key->id == 0xFFFF)
        return;
    func_0019cfc0(m0, key, w);
    s = &((DSysS *) D_00615E64)->shapes[key->id];
    if (!key->bF)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->bCD == 1)
        p.flags |= 0x10;
    if (key->bC)
        p.flags |= 0x800;
    if (key->bD)
        p.flags |= 0x400;
    if (key->bE) {
        p.p1C = mtx;
        v[0] = key->v10[0];
        v[1] = key->v10[1];
        v[2] = key->v10[2];
        v[3] = 0.0f;
    } else {
        p.p1C = 0;
    }
    p.d8 = 0;
    p.b18 = 0;
    p.p10 = m1;
    sh = s->shape;
    cr = c->r;
    cg = c->g;
    cb = c->b;
    ca = c->a;
    for (i = 0; i < n; i++) {
        if (pt->live) {
            s32 r, g, bl, al;
            u8 *src;
            func_0019d020(m0, m1, key, w, pt, a, mtx, key->bE);
            if (key->bE) {
                PlatVu0AddVector(mtx[3], mtx[3], v);
                PlatVu0MulMatrix(mtx, D_00616040, mtx);
            }
            r = cr + pt->c[0];
            { PppShapeFrame *f = &sh->f[pt->prev]; src = (u8 *) sh + f->off; }
            al = (f32) ca + (f32) pt->c[3] - pt->alpha;
            g = cg + pt->c[1];
            bl = cb + pt->c[2];
            if (b) {
                r += (s32) b->f[0];
                g += (s32) b->f[1];
                bl += (s32) b->f[2];
                al += (s32) b->f[3];
            }
            if (r < 0) r = 0; else if (r >= 256) r = 255;
            if (g < 0) g = 0; else if (g >= 256) g = 255;
            if (bl < 0) bl = 0; else if (bl >= 256) bl = 255;
            if (al < 0) al = 0; else if (al >= 128) al = 127;
            p.r = r;
            p.g = g;
            p.b = bl;
            p.a = al;
            p.w14 = D_00616224;
            D_00616224 = func_001b8198(src, &p, s->unk4);
        }
        if (a)
            a++;
        if (b)
            b++;
        pt++;
    }
}
#undef D_00616224

