/* The pppRyjMegaBirthModel class, -fno-strict-aliasing (docs/modules.md
 * "Session 49"): a particle emitter of models.  The frame
 * (pppRyjMegaBirthModelFrame) allocates n particles of 0xB0 bytes (and the
 * optional 64-byte and 32-byte extras) on its first frame, then
 * func_001a0628 moves the live ones (func_001a0190: spin, scale, speed,
 * gravity, size, fade in / out) and starts new ones with func_0019f1f0
 * (defined here since session 50; its random numbers come from vu0.c's
 * func_0019f100, a CONTEXT_ONLY copy here, as is ryjmbmodel.c's
 * func_0019f148) after the key's wait.  The draw (pppRyjMegaBirthModelDraw) builds each live
 * particle's matrix (func_001a0908, func_001a09d0) and colour and draws the
 * model through opdma.c's func_001aaf88.  The Con and Des are in
 * ryjmbmodel.c.  Read from the code, not proved by a boot. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    s32 unk0;
    u8 *inst;
    s32 time;
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x80];
    PppSlot *slots;
    u8 pad84[0x2C];
    u64 flags;
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;
    u8 pad10[0x8D];
    u8 unk9D;
} PppObject;

typedef struct {
    u32 flags;
    u8 pad04[0x12];
    u16 unk16;
} DMdl;

typedef struct {
    s32 pad0[4];
    u32 tex;
    s32 pad14[2];
    DMdl *mdl;
    s32 unk20;
} DSlot;

typedef struct {
    u8 pad00[0x10];
    DSlot *slots;
    void *shapes;
} DSys;

extern DSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern s32 D_00616224;
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern PppMtx D_00615E70;
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_001a9098(void *, void *);
typedef struct {
    s32 flags;
    void *p04;
    u16 h08;
    u8 b0A;
    s32 w0C;
    union { u64 d; struct { s32 u, v; } s; } t10;
    u8 r, g, b, a;
    s32 w1C;
    void *p20;
    void *p24;
    void *p28;
    void *p2C;
    void *p30;
    s32 w34;
    s32 w38;
    s32 w3C;
    s32 w40;
    void *p44;
    s32 w48;
    u8 b4C;
    u8 b4D;
    u8 pad4E[0x12];
} DParam;
typedef struct {
    u8 pad[8];
    u8 r, g, b, a;
} DColWork;
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern PppMtx D_00615FC0;
s32 func_001aaf88(DMdl *, DParam *, s32);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void sceVu0UnitMatrix(PppMtx);
typedef struct { u8 b[0x40]; } MegaA;
typedef struct { f32 f[8]; } MegaB;

typedef struct {
    u8 pad0[0x10];
    PppVec4 vel;     /* +0x10 */
    u8 pad20[0x10];
    PppVec4 pos;     /* +0x30 */
    u16 live;        /* +0x40 */
    u8 pad42[6];
    s32 ang[3];      /* +0x48 */
    s32 angv[3];     /* +0x54 */
    s32 anga[3];     /* +0x60 */
    f32 sc[3];       /* +0x6C */
    f32 scv[3];      /* +0x78 */
    f32 sca[3];      /* +0x84 */
    f32 spd;         /* +0x90 */
    f32 grav;        /* +0x94 */
    f32 sx, sy;      /* +0x98 */
    f32 svx, svy;    /* +0xA0 */
    f32 alpha;       /* +0xA8 */
    u8 n, fin, fout; /* +0xAC */
} MPart;
typedef struct {
    u8 pad0[0x22];
    u16 h22;
    u8 pad24;
    u8 b25;
    u8 pad26[0x12];
    f32 c38[4];      /* +0x38 */
    u8 pad48[0x1C];
    s32 angv[3];     /* +0x64 */
    u8 pad70[0x24];
    f32 scv[3];      /* +0x94 */
    u8 padA0[0x14];
    f32 svx;         /* +0xB4 */
    u8 padB8[8];
    f32 svy;         /* +0xC0 */
    u8 padC4[0x18];
    f32 spdv;        /* +0xDC */
    f32 spda;        /* +0xE0 */
    u8 padE4[8];
    f32 grav;        /* +0xEC */
    u8 padF0[0x12];
    u8 b102, b103;
    u8 pad104[7];
    u8 b10B;
} MKeyM;

void func_001a0190(f32 *w, MKeyM *key, MPart *pt, DColWork *c, f32 *b) {
    s32 a = c->a;
    s32 i;

    if (b) {
        f32 t;
        b[0] += b[4];
        b[1] += b[5];
        b[2] += b[6];
        b[3] += b[7];
        t = b[3];
        b[4] += key->c38[0];
        b[5] += key->c38[1];
        b[6] += key->c38[2];
        b[7] += key->c38[3];
        a = c->a + (s32) t;
        if (a >= 256)
            a = 255;
    }
    for (i = 0; i < 3; i++)
        pt->ang[i] += pt->angv[i];
    if (key->b103 & 0x10) {
        pt->angv[0] += key->angv[0] + pt->anga[0];
        pt->angv[1] += key->angv[1] + pt->anga[1];
        pt->angv[2] += key->angv[2] + pt->anga[2];
    } else {
        pt->angv[0] += key->angv[0];
        pt->angv[1] += key->angv[1];
        pt->angv[2] += key->angv[2];
    }
    for (i = 0; i < 3; i++) {
        if (pt->ang[i] > 32767) {
            while (pt->ang[i] > 32767)
                pt->ang[i] -= 0x10000;
        } else if (pt->ang[i] < -32768) {
            while (pt->ang[i] > 32767)
                pt->ang[i] += 0x10000;
        }
    }
    for (i = 0; i < 3; i++)
        pt->sc[i] += pt->scv[i];
    if (key->b102 & 0x10) {
        pt->scv[0] += key->scv[0] + pt->sca[0];
        pt->scv[1] += key->scv[1] + pt->sca[1];
        pt->scv[2] += key->scv[2] + pt->sca[2];
    } else {
        pt->scv[0] += key->scv[0];
        pt->scv[1] += key->scv[1];
        pt->scv[2] += key->scv[2];
    }
    pt->spd += key->spda;
    if (!key->b10B) {
        if (0.0f < key->spdv && key->spda < 0.0f) {
            if (pt->spd < 0.0f)
                pt->spd = 0.0f;
        } else if (key->spdv < 0.0f && 0.0f < key->spda) {
            if (0.0f < pt->spd)
                pt->spd = 0.0f;
        }
    }
    pt->grav += key->grav;
    __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf3\n"
        "lqc2 $vf4, 0(%3)\n"
        "lw $9, 0(%4)\n"
        "qmtc2 $9, $vf5\n"
        "vmulx.xyz $vf2xyz, $vf2xyz, $vf3x\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "vadd.xyz $vf1xyz, $vf1xyz, $vf2xyz\n"
        "vadd.xyz $vf1xyz, $vf1xyz, $vf4xyz\n"
        "sqc2 $vf1, 0(%0)\n"
        : : "r"(pt->pos), "r"(pt->vel), "r"(&pt->spd), "r"(w), "r"(&pt->grav)
        : "$8", "$9", "memory");
    pt->sx += pt->svx;
    pt->sy += pt->svy;
    pt->svx += key->svx;
    pt->svy += key->svy;
    if (key->h22)
        pt->live--;
    pt->n++;
    if (pt->fin && pt->n <= pt->fin)
        pt->alpha -= (f32) a / (f32) pt->fin;
    if (pt->fout && pt->fout >= pt->live)
        pt->alpha += (f32) a / (f32) key->b25;
}

/* func_001a0628's own views of the system and the current owner (from
 * text_001a0000_ctx.c, which also gave it the CONTEXT_ONLY copies). */
typedef struct { s16 x, y, z; } MgV6;
typedef struct { s16 h0; u16 n; u16 *idx; } MgSet;
typedef struct { u8 pad[0x14]; MgV6 *v; u8 pad18[0xC]; } MgSlot;
typedef struct { u8 pad[0x10]; MgSlot *slots; u8 pad14[4]; MgSet *sets; } MgSys;
typedef struct { u8 pad[0x10]; f32 m10[4][4]; u8 pad50[0x40]; MgV6 *v90; } MgCur;
#define D_00615E64 (*(MgSys **)&D_00615E64)
#define D_00615E68 (*(MgCur **)&D_00615E68)

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

/* func_0019f1f0 (from text_00190000_s12_s12w8.c): two empty do { } while
 * (0) barriers per TAIL copy (after the int loads, before the stores)
 * reproduce the original sched order; the FP register swap is fixed by
 * making fz, fu and one function-level variables (set in both TAIL copies, so
 * global-alloc assigns them after local-alloc: ft takes f1 locally, then fu
 * f2, fz f3, one f4 by global priority) and multiplying in place (`fu *=
 * key->sc[1]`). */
#define R func_0019f100()
#define ORTHO { \
        p->m[1][0] *= key->sc[0]; \
        p->m[1][1] *= key->sc[1]; \
        p->m[1][2] *= key->sc[2]; \
        func_002673b8(y, y); \
        func_00267370(z, y, p->m[0]); \
        func_002673b8(z, z); \
        func_00267370(p->m[0], z, y); \
        func_002673b8(p->m[0], p->m[0]); \
    }
#define TAIL(E) { \
        v = tbl[E]; \
        t = v.x; p->m[3][0] = (f32)t * key->sc[0]; \
        u = v.y; p->m[3][1] = (f32)u * key->sc[1]; \
        p->m[3][2] = (f32)v.z * key->sc[2]; \
            }
#define TAIL2 { \
        p->m[3][3] = 1.0f; \
        if ((u8)(key->type - 8) < 2) { \
            f32 *y = p->m[1], *z = p->m[2]; \
            func_002673b8(y, p->m[3]); \
            ORTHO; \
        } \
    }

/* FLAGGED: empty do { } while (0) sched barriers in the TAIL copies */
void func_0019f1f0(MgObj2 *obj, s32 keyi, MgE *e, MgPart2 *p, void *a, MgB *b) {
    f32 vec[4] __attribute__((aligned(16)));
    f32 ang[4] __attribute__((aligned(16)));
    f32 m[4][4] __attribute__((aligned(16)));
    MgV6 v;
    MgKey2 *key = (MgKey2 *)keyi;
    f32 rng = key->b27;
    f32 rng2 = 2.0f * rng;
    s32 i;
    s32 t, u, k;
    f32 f, r, fz, fu, one;

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
            { s32 k = s->idx[obj->h22++]; { f32 ft, s0; s32 z; v = tbl[k]; t = v.x; ft = (f32)t; s0 = key->sc[0]; z = v.z; u = v.y; do { } while (0); fz = (f32)z; one = 1.0f; fu = (f32)u; do { } while (0); p->m[3][0] = ft * s0; fu *= key->sc[1]; p->m[3][1] = fu; fz *= key->sc[2]; p->m[3][2] = fz; p->m[3][3] = one; } }
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
        if (obj->h22 >= (s16)s->n)
            obj->h22 = 0;
        { s32 k = s->idx[(s32)(r * (f32)(s16)s->n)]; { f32 ft, s0; s32 z; v = tbl[k]; t = v.x; ft = (f32)t; s0 = key->sc[0]; z = v.z; u = v.y; do { } while (0); fz = (f32)z; one = 1.0f; fu = (f32)u; do { } while (0); p->m[3][0] = ft * s0; fu *= key->sc[1]; p->m[3][1] = fu; fz *= key->sc[2]; p->m[3][2] = fz; p->m[3][3] = one; } }
    ty:
        if ((u8)(key->type - 8) < 2) {
            f32 *y = p->m[1], *z = p->m[2];
            func_002673b8(y, p->m[3]);
            ORTHO;
        }
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
            func_001a0190((f32 *)obj, (MKeyM *)key, (MPart *)p, e, (f32 *)b);
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
#undef D_00615E64
#undef D_00615E68
#undef R
#undef ORTHO
#undef TAIL

typedef struct {
    f32 x, y, z, w;
    void *p10;
    void *p14;
    void *p18;
    s32 n;
} MbmW;

typedef struct {
    u8 pad0[0x1c];
    u16 n;
    u8 pad1e[0xd0 - 0x1e];
    f32 x, y, z;
    u8 paddc[0x101 - 0xdc];
    u8 b101;
    u8 pad102[4];
    u8 b106;
} MbmK;
void *memset(void *, s32, u32);
void *func_0017f958(void *, s32);
s32 func_0019f1a8(void *, void *);

void pppRyjMegaBirthModelFrame(void *obj, MbmK *k, PppEntry *e) {
    MbmW *w = (MbmW *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;

    if (w->p10 == NULL) {
        w->n = k->n;
        w->p10 = func_0017f958(D_00615E64, w->n * 0xB0);
        if (w->p10 != NULL)
            memset(w->p10, 0, w->n * 0xB0);
        if (k->b106) {
            w->p14 = func_0017f958(D_00615E64, w->n << 6);
            if (w->p14 != NULL)
                memset(w->p14, 0, w->n << 6);
        }
        if (k->b101) {
            w->p18 = func_0017f958(D_00615E64, w->n << 5);
            if (w->p18 != NULL)
                memset(w->p18, 0, w->n << 5);
        }
        w->x = k->x;
        w->y = k->y;
        w->z = k->z;
        w->w = 0;
        func_002673b8((f32 *)w, (f32 *)w);
    }
    if (func_0019f1a8(w, k))
        func_001a0628((PppMega2Obj *)w, (PppMega2Key *)k, w2);
}

/* needs make: uses rodata */
typedef struct {
    u8 pad[0x26];
    u8 mode;   /* +0x26 */
} PppMdlMode;

typedef struct {
    u8 pad[0x14];
    s32 parent; /* +0x14 */
} PppMdlOwn;

void func_001a0908(PppMtx m, PppMdlMode *p, PppMdlOwn *o) {
    s32 parent = o->parent;

    sceVu0UnitMatrix(m);
    switch (p->mode) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
    default:
        if (parent == 0)
            sceVu0MulMatrix(m, (f32 (*)[4]) D_00615FC0, D_00615E68->m);
        return;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        sceVu0MulMatrix(m, (f32 (*)[4]) D_00615FC0, D_00615E68->m);
        return;
    }
}

extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern PppMtx D_00616000;
extern PppMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
void func_00267560(f32 *, f32 *, f32);
typedef struct {
    u8 pad0[0x26];
    u8 kind;
    u8 pad27[0x105 - 0x27];
    u8 b105;
} O09d0;
typedef struct {
    PppMtx m;
    u8 pad40[8];
    u64 rot;
    s32 rz;
    u8 pad54[0x6C - 0x54];
    f32 scale[3];
} K09d0;
/* rodata */
/* rodata */
void func_001a09d0(PppMtx base, PppMtx m, O09d0 *o, K09d0 *k, PppMtx parent, PppMtx out, u8 flag) {
    PppVec4 tmp;
    PppMtx t;
    PppMtx rm;
    PppVec4 r;
    s32 i;
    f32 *sc;
    if (o->b105) {
        sceVu0CopyMatrix(m, k->m);
    } else {
        sceVu0UnitMatrix(m);
        func_002675a8(m[3], k->m[3]);
    }
    if (k->rot != 0 || k->rz != 0) {
        for (i = 0; i < 3; i++) r[i] = (f32)((s32 *)&k->rot)[i] * 3.1415927f * (1.0f / 32768.0f);
        sceVu0UnitMatrix(rm);
        func_002678b8(rm, rm, r);
        sceVu0MulMatrix(m, m, rm);
    }
    sc = k->scale;
    for (i = 0; i < 3; i++) func_00267560(m[i], m[i], *sc++);
    switch (o->kind) {
    case 0: case 2: case 4: case 6: case 8:
    default:
        if (parent == 0) {
            func_002675a8(tmp, m[3]);
            sceVu0MulMatrix(m, D_00615FC0, m);
            func_002672f8(m[3], base, tmp);
            if (flag) sceVu0CopyMatrix(out, m);
            sceVu0MulMatrix(m, D_00616040, m);
        } else {
            sceVu0MulMatrix(t, parent, D_00615E68->m);
            sceVu0MulMatrix(t, D_00615EB0, t);
            func_002675a8(tmp, m[3]);
            sceVu0MulMatrix(m, D_00615FC0, m);
            func_002672f8(m[3], t, tmp);
            if (flag) sceVu0CopyMatrix(out, m);
            sceVu0MulMatrix(m, D_00616040, m);
        }
        break;
    case 1: case 3: case 5: case 7: case 9:
        func_002672f8(tmp, base, m[3]);
        sceVu0MulMatrix(m, D_00616000, m);
        func_002675a8(m[3], tmp);
        if (flag) sceVu0CopyMatrix(out, m);
        sceVu0MulMatrix(m, D_00616040, m);
        break;
    }
}

typedef struct {
    PppMtx m;        /* +0x00 */
    u16 live;        /* +0x40 */
    s8 c[4];         /* +0x42 */
    u8 pad46[0x52];
    f32 sx, sy;      /* +0x98 */
    u8 padA0[8];
    f32 alpha;       /* +0xA8 */
    u8 padAC[4];
} MdPart; /* 0xB0 */
typedef struct {
    s32 frame;
    s32 id;          /* +0x04 */
    u8 flags, b9, bA, bB, bC, bD, bE, bF;
    f32 v10[3];      /* +0x10 */
    u8 pad1C[0xEE];
    u8 b10A;         /* +0x10A */
} MdKey;
typedef struct {
    PppVec4 v;       /* +0x00 */
    MdPart *parts;   /* +0x10 */
    MegaA *a;        /* +0x14 */
    MegaB *b;        /* +0x18 */
    s32 n;           /* +0x1C */
} MdObj;
#define D_00616224 (*(volatile s32 *) &D_00616224)

void func_00267518(PppVec4, PppVec4, PppVec4);
void pppRyjMegaBirthModelDraw(PppObject *obj, MdKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppMtx mtx;
    PppVec4 v;
    DParam p;
    MdObj *w = PPP_WORK(MdObj, obj, e, 2);
    DColWork *c = PPP_WORK(DColWork, obj, e, 1);
    MdPart *pt = w->parts;
    MegaA *a = w->a;
    MegaB *b = w->b;
    s32 n = w->n;
    DSlot *s;
    DMdl *m;
    s32 cr, cg, cb, ca;
    s32 i;

    if (!func_0019f1a8(w, key))
        return;
    if (key->id == 0xFFFF)
        return;
    func_001a0908(m0, (PppMdlMode *)key, (PppMdlOwn *)w);
    s = &D_00615E64->slots[key->id];
    m = s->mdl;
    if (key->bD) {
        p.p44 = mtx;
        v[0] = key->v10[0];
        v[1] = key->v10[1];
        v[2] = key->v10[2];
        v[3] = 0.0f;
    } else {
        p.p44 = 0;
    }
    p.p2C = 0;
    p.p28 = 0;
    p.p24 = 0;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p20 = m1;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->b9)
        p.flags |= 0x200;
    if (key->bB)
        p.flags |= 0x100;
    p.h08 = m->unk16;
    cr = c->r;
    cg = c->g;
    cb = c->b;
    ca = c->a;
    p.b4C = key->bC;
    p.b4D = key->b10A;
    for (i = 0; i < n; i++) {
        if (pt->live) {
            s32 r, g, bl, al;
            func_001a09d0(m0, m1, (O09d0 *)key, (K09d0 *)pt, (void *)a, mtx, key->bD);
            if (key->bD) {
                func_00267518(mtx[3], mtx[3], v);
                sceVu0MulMatrix(mtx, D_00616040, mtx);
            }
            r = cr + pt->c[0];
            g = cg + pt->c[1];
            al = (f32) ca + (f32) pt->c[3] - pt->alpha;
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
            p.t10.s.u = pt->sx * 65536.0f;
            p.t10.s.v = pt->sy * 65536.0f;
            p.w34 = D_00616224;
            D_00616224 = func_001aaf88(m, &p, s->unk20);
        }
        if (a)
            a++;
        if (b)
            b++;
        pt++;
    }
}
#undef D_00616224
