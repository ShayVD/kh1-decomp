#include "common.h"

typedef struct { s16 x, y, z; } MgV6;
typedef struct { s16 h0; u16 n; u16 *idx; } MgSet;
typedef struct { u8 pad[0x14]; MgV6 *v; u8 pad18[0xC]; } MgSlot;
typedef struct { u8 pad[0x10]; MgSlot *slots; u8 pad14[4]; MgSet *sets; } MgSys;
typedef struct { u8 pad[0x10]; f32 m10[4][4]; u8 pad50[0x40]; MgV6 *v90; } MgCur;
extern MgSys *D_00615E64;
extern MgCur *D_00615E68;
extern f32 D_00615E70[4][4];

typedef struct {
    u8 pad0[0x22];
    u16 live;      /* 0x22 */
    u8 b24, b25, type, b27;
    f32 f28, f2C, f30, f34; /* 0x28 */
    u8 pad38[0x10];
    u8 col[4];     /* 0x48 */
    s32 i4C[3];    /* 0x4C */
    s32 i58[3];    /* 0x58 */
    u8 pad64[0xC];
    s32 i70[3];    /* 0x70 */
    f32 f7C[3];    /* 0x7C */
    f32 f88[3];    /* 0x88 */
    u8 pad94[0xC];
    f32 fA0[3];    /* 0xA0 */
    f32 fAC, fB0, fB4, fB8, fBC; /* 0xAC */
    f32 fC0;
    f32 v[3];      /* 0xC4 */
    u8 padD0[0xC];
    f32 fDC, fE0, fE4, fE8, fEC, fF0; /* 0xDC */
    f32 sc[3];     /* 0xF4 */
    u8 c8, c9, ca, cb, cc, cd; /* 0x100 */
    u8 pad106[2];
    s16 set;       /* 0x108 */
} MgKey2;

typedef struct {
    f32 m[4][4];
    u16 live;      /* 0x40 */
    s8 col[4];     /* 0x42 */
    u8 pad46[2];
    s32 a[3];      /* 0x48 */
    s32 b[3];      /* 0x54 */
    s32 d[3];      /* 0x60 */
    f32 fa[3];     /* 0x6C */
    f32 fb[3];     /* 0x78 */
    f32 g[3];      /* 0x84 */
    f32 f90, f94, f98, f9C, fA0, fA4, fA8; /* 0x90 */
    u8 bAC, bAD, bAE, bAF;
} MgPart2;

typedef struct { u8 pad[0x10]; f32 f10, f14, f18, f1C; } MgB;
typedef struct { u8 pad[0x22]; u16 h22; } MgObj2;
typedef struct { u8 pad[0xB]; u8 bB; } MgE;

f32 func_0019f100(void);
s8 func_0019f148(u8);
void *memset(void *, s32, u32);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0CopyMatrix(void *, void *);
void func_002678b8(f32 (*)[4], f32 (*)[4], f32 *);
void func_002672f8(f32 *, f32 (*)[4], f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);

CONTEXT_ONLY f32 func_0019f100(void) {
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

CONTEXT_ONLY s8 func_0019f148(u8 a) {
    f32 f;

    func_0019f100();
    f = func_0019f100();
    return (f32) (a * 2) * f - (f32) (a >> 1);
}

#define R func_0019f100()
#define ORTHO do { \
        p->m[1][0] *= key->sc[0]; \
        p->m[1][1] *= key->sc[1]; \
        p->m[1][2] *= key->sc[2]; \
        func_002673b8(y, y); \
        func_00267370(z, y, p->m[0]); \
        func_002673b8(z, z); \
        func_00267370(p->m[0], z, y); \
        func_002673b8(p->m[0], p->m[0]); \
    } while (0)
#define TAIL do { \
        v = tbl[*ip]; \
        p->m[3][0] = (f32)v.x * key->sc[0]; \
        p->m[3][1] = (f32)v.y * key->sc[1]; \
        p->m[3][2] = (f32)v.z * key->sc[2]; \
        p->m[3][3] = 1.0f; \
        if ((u8)(key->type - 8) < 2) { \
            f32 *y = p->m[1], *z = p->m[2]; \
            func_002673b8(y, p->m[3]); \
            ORTHO; \
        } \
    } while (0)

CONTEXT_ONLY void func_0019f1f0(MgObj2 *obj, s32 keyi, MgE *e, MgPart2 *p, void *a, MgB *b) {
    f32 vec[4] __attribute__((aligned(16)));
    f32 ang[4] __attribute__((aligned(16)));
    f32 m[4][4] __attribute__((aligned(16)));
    MgV6 v;
    MgKey2 *key = (MgKey2 *)keyi;
    f32 rng = key->b27;
    f32 rng2 = 2.0f * rng;
    s32 i;
    f32 f, r;

    memset(p, 0, sizeof(MgPart2));
    if (a)
        memset(a, 0, 0x40);
    if (b)
        memset(b, 0, 0x20);
    sceVu0UnitMatrix(p->m);
    switch (key->type) {
    case 0 ... 7: {
        f32 *y, *z;
        { f32 x0 = key->v[0], x1 = key->v[1], x2 = key->v[2]; vec[0] = x0; vec[1] = x1; vec[2] = x2; }
        vec[3] = 1.0f;
        for (i = 0; i < 3; i++)
            ang[i] = (rng2 * R - rng) * 3.141592562f / 180.0f;
        if ((u8)(key->type - 2) < 2) {
            ang[0] = 0.0f;
            ang[1] = 0.0f;
        }
        y = p->m[1];
        z = p->m[2];
        sceVu0UnitMatrix(m);
        func_002678b8(m, m, ang);
        func_002672f8(y, m, vec);
        ORTHO;
    }
    }
    switch (key->type) {
    case 0: case 1: case 2: case 3:
    default:
        f = key->fF0;
        if (f == 0.0f)
            break;
        switch (key->c8) {
        case 0:
            break;
        case 1:
            R;
            f = key->fF0 * R;
            break;
        case 2:
            f = key->fF0 * R * R;
            break;
        case 3:
            f = key->fF0 - key->fF0 * R * R * 0.7f;
            break;
        case 4:
            f = key->fF0 * R * R * R * R;
            break;
        case 5:
            f = key->fF0 - key->fF0 * R * R * R * 0.5f;
            break;
        }
        func_00267e90(p->m[3], p->m[1], f);
        p->m[3][3] = 1.0f;
        break;
    case 4: case 5:
        if (key->fF0 == 0.0f)
            break;
        rng2 = key->fF0 * 0.5f;
        switch (key->c8) {
        case 0:
        default:
            for (i = 0; i < 3; i++)
                p->m[3][i] = key->fF0 * R - rng2;
            break;
        case 1:
            R;
            for (i = 0; i < 3; i++)
                p->m[3][i] = key->fF0 * R - rng2;
            break;
        case 2:
            for (i = 0; i < 3; i++)
                p->m[3][i] = key->fF0 * R * R - rng2;
            break;
        case 3:
            for (i = 0; i < 3; i++)
                p->m[3][i] = key->fF0 - key->fF0 * R * R * 0.7f - rng2;
            break;
        case 4:
            for (i = 0; i < 3; i++)
                p->m[3][i] = key->fF0 * R * R * R * R - rng2;
            break;
        case 5:
            for (i = 0; i < 3; i++)
                p->m[3][i] = key->fF0 - key->fF0 * R * R * R * 0.5f - rng2;
            break;
        }
        p->m[3][0] *= key->sc[0];
        p->m[3][1] *= key->sc[1];
        p->m[3][2] *= key->sc[2];
        p->m[3][3] = 1.0f;
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
            if (obj->h22 >= (s16)s->n)
                obj->h22 = 0;
            { s32 k = obj->h22++; ip = s->idx; ip += k; }
            goto got;
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
        if (obj->h22 >= (s16)s->n)
            obj->h22 = 0;
        ip = (u16 *)((s32)(r * (f32)(s16)s->n) * 2 + (u32)s->idx);
    got:
        TAIL;
        break;
    }
    }
    p->col[0] = func_0019f148(key->col[0]);
    p->col[1] = func_0019f148(key->col[1]);
    p->col[2] = func_0019f148(key->col[2]);
    p->col[3] = func_0019f148(key->col[3]);
    if (key->b24) {
        p->fA8 = e->bB;
        p->bAD = key->b24;
    }
    if (key->b25)
        p->bAE = key->b25;
    p->a[0] = key->i4C[0];
    p->a[1] = key->i4C[1];
    p->a[2] = key->i4C[2];
    p->b[0] = key->i58[0];
    p->b[1] = key->i58[1];
    p->b[2] = key->i58[2];
    if (key->cb) {
        if (key->cb & 0x20) {
            p->d[0] = p->d[1] = p->d[2] = R * (f32)key->i70[0];
            if (key->cb & 1) {
                if (key->cb & 2) {
                    if (R > 0.5)
                        for (i = 0; i < 3; i++)
                            p->d[i] = -p->d[i];
                }
            } else if (key->cb & 2) {
                for (i = 0; i < 3; i++)
                    p->d[i] = -p->d[i];
            }
        } else {
            p->d[0] = R * (f32)key->i70[0];
            p->d[1] = R * (f32)key->i70[1];
            p->d[2] = R * (f32)key->i70[2];
            if (key->cb & 1) {
                if (key->cb & 2) {
                    for (i = 0; i < 3; i++)
                        if (R > 0.5)
                            p->d[i] = -p->d[i];
                }
            } else if (key->cb & 2) {
                for (i = 0; i < 3; i++)
                    p->d[i] = -p->d[i];
            }
        }
    }
    if (key->cb & 4)
        for (i = 0; i < 3; i++)
            p->a[i] += p->d[i];
    if (key->cb & 8)
        for (i = 0; i < 3; i++)
            p->b[i] += p->d[i];
    for (i = 0; i < 3; i++)
        if (p->a[i] > 0x7FFF || p->a[i] < -0x8000)
            p->a[i] %= 0x8000;
    p->fa[0] = key->f7C[0];
    p->fa[1] = key->f7C[1];
    p->fa[2] = key->f7C[2];
    p->fb[0] = key->f88[0];
    p->fb[1] = key->f88[1];
    p->fb[2] = key->f88[2];
    if (key->ca) {
        if (key->ca & 0x20) {
            p->g[0] = p->g[1] = p->g[2] = R * key->fA0[0];
            if (key->ca & 1) {
                if (key->ca & 2) {
                    if (R > 0.5)
                        for (i = 0; i < 3; i++)
                            p->g[i] = -p->g[i];
                }
            } else if (key->ca & 2) {
                for (i = 0; i < 3; i++)
                    p->g[i] = -p->g[i];
            }
        } else {
            p->g[0] = R * key->fA0[0];
            p->g[1] = R * key->fA0[1];
            p->g[2] = R * key->fA0[2];
            if (key->ca & 1) {
                if (key->ca & 2) {
                    for (i = 0; i < 3; i++)
                        if (R > 0.5)
                            p->g[i] = -p->g[i];
                }
            } else if (key->ca & 2) {
                for (i = 0; i < 3; i++)
                    p->g[i] = -p->g[i];
            }
        }
    }
    if (key->ca & 4)
        for (i = 0; i < 3; i++)
            p->fa[i] += p->g[i];
    if (key->ca & 8)
        for (i = 0; i < 3; i++)
            p->fb[i] += p->g[i];
    p->f90 = key->fDC;
    p->f94 = key->fE8;
    if (key->fE4 != 0.0f)
        p->f90 += 2.0f * key->fE4 * R - key->fE4;
    p->f98 = key->fAC;
    p->f9C = key->fB8;
    p->fA0 = key->fB0;
    p->fA4 = key->fBC;
    switch (key->cc) {
    case 1:
        p->f98 *= R;
        break;
    case 4:
        p->f98 *= R;
    case 2:
        p->f9C *= R;
        break;
    case 3:
        { f32 t = R; p->f98 *= t; p->f9C *= t; }
        break;
    }
    if (key->live)
        p->live = key->live;
    else
        p->live = -1;
    p->bAC = 0;
    if (a)
        sceVu0CopyMatrix(a, D_00615E70);
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
    u8 pad[0x40];
    u16 live;   /* +0x40 */
    u8 pad42[0x6E];
} PppMega2Part; /* 0xB0 */

typedef struct {
    s32 frame;
    u8 pad4[0x1A];
    u16 max;    /* +0x1E */
    u16 wait;   /* +0x20 */
} PppMega2Key;

typedef struct { u8 b[0x40]; } PppMega2A;
typedef struct { u8 b[0x20]; } PppMega2B;

typedef struct {
    u8 pad[0x10];
    PppMega2Part *parts; /* +0x10 */
    PppMega2A *a;        /* +0x14 */
    PppMega2B *b;        /* +0x18 */
    s32 n;               /* +0x1C */
    u16 timer;           /* +0x20 */
} PppMega2Obj;

void func_001a0190(PppMega2Obj *, PppMega2Key *, PppMega2Part *, void *, PppMega2B *);

void func_001a0628(PppMega2Obj *obj, PppMega2Key *key, void *e) {
    PppMega2Part *p = obj->parts;
    PppMega2A *a = obj->a;
    PppMega2B *b = obj->b;
    s32 n = obj->n;
    s32 born = 0;
    s32 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    obj->timer++;
    for (i = 0; i < n; i++) {
        if (p->live) {
            func_001a0190(obj, key, p, e, b);
        } else if (key->wait <= obj->timer && born < key->max) {
            func_0019f1f0((MgObj2 *)obj, (s32)key, (MgE *)e, (MgPart2 *)p, a, (MgB *)b);
            born++;
        }
        if (a)
            a++;
        if (b)
            b++;
        p++;
    }
    if (born > 0)
        obj->timer = 0;
}
