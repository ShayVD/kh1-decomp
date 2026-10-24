/* The pppRyjMegaBirthModelFilter class, -fno-strict-aliasing
 * (docs/modules.md "Session 49"; c07 renamed): func_001a3650 is a VU0
 * random number in 0 .. 1, func_001a3720 starts a particle from the key,
 * func_001a4168 moves one (as ryjmbfilter.nostrict_nofill.c's
 * func_001a2830 for the sprite class); the frame
 * (pppRyjMegaBirthModelFilterFrame) allocates the particles and fades the
 * emitter by distance; func_001a4a98 builds a particle's model matrix and
 * the draw (pppRyjMegaBirthModelFilterDraw) draws each live one through
 * opdma.c's func_001aaf88.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/pieces/D_003701D0.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
typedef f32 Vec[4] __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0x10];
    u16 life;       /* 0x10 */
    u8 fade;        /* 0x12 */
    u8 b13;         /* 0x13 */
    f32 f14[4];     /* 0x14 */
    f32 f24[4];     /* 0x24 */
    u8 col[4];      /* 0x34 */
    s32 rot[3];     /* 0x38 */
    s32 rotv[3];    /* 0x44 */
    s32 rota[3];    /* 0x50 */
    s32 rr[3];      /* 0x5c */
    f32 sc[3];      /* 0x68 */
    f32 scv[3];     /* 0x74 */
    f32 sca[3];     /* 0x80 */
    f32 sr[3];      /* 0x8c */
    f32 f98;
    f32 f9c;
    f32 fa0;
    f32 fa4;
    f32 fa8;
    f32 fac;
    f32 fb0;
    f32 fb4;
    u8 padb8[0xc];
    f32 fc4;
    f32 fc8;
    f32 fcc;
    u8 padd0[4];
    f32 fd4;
    f32 fd8;
    f32 fdc;
    u8 pade0[0x13];
    u8 sfl;         /* 0xf3 */
    u8 rfl;         /* 0xf4 */
    u8 afl;         /* 0xf5 */
    u8 mode;        /* 0xf6 */
} Em;

typedef struct {
    f32 pos[4];     /* 0x00 */
    f32 vel[4];     /* 0x10 */
    u16 life;       /* 0x20 */
    u8 col[4];      /* 0x22 */
    u8 pad26[2];
    s32 rot[3];     /* 0x28 */
    s32 rotv[3];    /* 0x34 */
    s32 rr[3];      /* 0x40 */
    u8 pad4c[8];
    f32 sc[3];      /* 0x54 */
    f32 scv[3];     /* 0x60 */
    f32 sr[3];      /* 0x6c */
    f32 f78;
    f32 f7c;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8c;
    f32 f90;
    f32 f94;
    union { u64 x; u8 b; } fl;  /* 0x98 */
} Pt;

typedef struct {
    f32 a[4];
    f32 b[4];
} Sub;

f32 func_001a3650(void);
s8 func_001a3698(u8);
extern f32 D_00615F70[4];
extern u8 D_0061E730[];

void func_001a3720(Em *e, Pt *p, Sub *s);

extern Mtx D_006161C0;

f32 func_001a3650(void) {
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
s8 func_001a3698(u8);
extern f32 D_00615F70[4];
extern f32 D_006161C0[4][4];
extern u8 D_0061E730[];

void func_001a3720(Em *e, Pt *p, Sub *s) {
    s32 i;
    s32 r;
    f32 f;

    p->col[0] = func_001a3698(e->col[0]);
    p->col[1] = func_001a3698(e->col[1]);
    p->col[2] = func_001a3698(e->col[2]);
    p->col[3] = func_001a3698(e->col[3]);
    if (e->fade) {
        p->fl.b = e->fade;
        p->fl.x |= 0x200;
    }
    p->rot[0] = e->rot[0];
    p->rot[1] = e->rot[1];
    p->rot[2] = e->rot[2];
    p->rotv[0] = e->rotv[0];
    p->rotv[1] = e->rotv[1];
    p->rotv[2] = e->rotv[2];
    if (e->rfl) {
        if (e->rfl & 0x20) {
            r = func_001a3650() * (f32)e->rr[0];
            p->rr[2] = r;
            p->rr[1] = r;
            p->rr[0] = r;
            if ((u8)(e->rfl & 1)) {
                if (e->rfl & 2) {
                    if (func_001a3650() > 0.5) {
                        for (i = 0; i < 3; i++) p->rr[i] = -p->rr[i];
                    }
                }
            } else if (e->rfl & 2) {
                for (i = 0; i < 3; i++) p->rr[i] = -p->rr[i];
            }
        } else {
            p->rr[0] = func_001a3650() * (f32)e->rr[0];
            p->rr[1] = func_001a3650() * (f32)e->rr[1];
            p->rr[2] = func_001a3650() * (f32)e->rr[2];
            if ((u8)(e->rfl & 1)) {
                if (e->rfl & 2) {
                    for (i = 0; i < 3; i++) {
                        if (func_001a3650() > 0.5) p->rr[i] = -p->rr[i];
                    }
                }
            } else if (e->rfl & 2) {
                for (i = 0; i < 3; i++) p->rr[i] = -p->rr[i];
            }
        }
    }
    if (e->rfl & 4) {
        for (i = 0; i < 3; i++) p->rot[i] += p->rr[i];
    }
    if (e->rfl & 8) {
        for (i = 0; i < 3; i++) p->rotv[i] += p->rr[i];
    }
    for (i = 0; i < 3; i++) {
        if (p->rot[i] > 0x7fff || p->rot[i] < -0x8000) p->rot[i] %= 0x8000;
    }
    p->sc[0] = e->sc[0];
    p->sc[1] = e->sc[1];
    p->sc[2] = e->sc[2];
    p->scv[0] = e->scv[0];
    p->scv[1] = e->scv[1];
    p->scv[2] = e->scv[2];
    if (e->sfl) {
        if (e->sfl & 0x20) {
            f = func_001a3650() * e->sr[0];
            p->sr[2] = f;
            p->sr[1] = f;
            p->sr[0] = f;
            if ((u8)(e->sfl & 1)) {
                if (e->sfl & 2) {
                    if (func_001a3650() > 0.5) {
                        for (i = 0; i < 3; i++) p->sr[i] = -p->sr[i];
                    }
                }
            } else if (e->sfl & 2) {
                for (i = 0; i < 3; i++) p->sr[i] = -p->sr[i];
            }
        } else {
            p->sr[0] = func_001a3650() * e->sr[0];
            p->sr[1] = func_001a3650() * e->sr[1];
            p->sr[2] = func_001a3650() * e->sr[2];
            if ((u8)(e->sfl & 1)) {
                if (e->sfl & 2) {
                    for (i = 0; i < 3; i++) {
                        if (func_001a3650() > 0.5) p->sr[i] = -p->sr[i];
                    }
                }
            } else if (e->sfl & 2) {
                for (i = 0; i < 3; i++) p->sr[i] = -p->sr[i];
            }
        }
    }
    if (e->sfl & 4) {
        for (i = 0; i < 3; i++) p->sc[i] += p->sr[i];
    }
    if (e->sfl & 8) {
        for (i = 0; i < 3; i++) p->scv[i] += p->sr[i];
    }
    p->f78 = e->fc4;
    if (e->fcc != 0.0f) {
        p->f78 += (e->fcc + e->fcc) * func_001a3650() - e->fcc;
    }
    p->f7c = e->f98;
    p->f80 = e->fa8;
    p->f84 = e->f9c;
    p->f88 = e->fac;
    if (e->afl) {
        if (e->afl & 0x20) {
            f = func_001a3650() * e->fa4;
            p->f90 = f;
            p->f8c = f;
            if ((u8)(e->afl & 1)) {
                if (e->afl & 2) {
                    if (func_001a3650() > 0.5) {
                        p->f8c = -p->f8c;
                        p->f90 = -p->f90;
                    }
                }
            } else if (e->afl & 2) {
                p->f8c = -p->f8c;
                p->f90 = -p->f90;
            }
        } else {
            p->f8c = func_001a3650() * e->fa4;
            p->f90 = func_001a3650() * e->fb4;
            if ((u8)(e->afl & 1)) {
                if (e->afl & 2) {
                    if (func_001a3650() > 0.5) p->f8c = -p->f8c;
                    if (func_001a3650() > 0.5) p->f90 = -p->f90;
                }
            } else if (e->afl & 2) {
                p->f8c = -p->f8c;
                p->f90 = -p->f90;
            }
        }
    }
    if (e->afl & 4) {
        p->f7c += p->f8c;
        p->f80 += p->f90;
    }
    if (e->afl & 8) {
        p->f84 += p->f8c;
        p->f88 += p->f90;
    }
    p->life = e->life ? e->life : 0xffff;
    if (s) {
        s->b[0] = e->f14[0];
        s->b[1] = e->f14[1];
        s->b[2] = e->f14[2];
        s->b[3] = e->f14[3];
    }
    p->f94 = 0;
    switch (e->mode) {
    case 1:
        if (func_001a3650() > 0.5f) p->sc[0] = -p->sc[0];
        break;
    case 2:
        if (func_001a3650() > 0.5f) p->sc[1] = -p->sc[1];
        break;
    case 3:
        if (func_001a3650() > 0.5f) p->sc[0] = -p->sc[0];
        if (func_001a3650() > 0.5f) p->sc[1] = -p->sc[1];
        break;
    }
}

void func_001a4168(s32 a0, Em *e, Pt *p, s32 a3, Sub *s) {
    f32 v0[4] __attribute__((aligned(16)));
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    Mtx m30;
    s32 i;
    f32 dist;
    f32 f;
    f32 *q;

    if (s) {
        s->a[0] += s->b[0];
        s->a[1] += s->b[1];
        s->a[2] += s->b[2];
        s->a[3] += s->b[3];
        s->b[0] += e->f24[0];
        s->b[1] += e->f24[1];
        s->b[2] += e->f24[2];
        s->b[3] += e->f24[3];
    }
    for (i = 0; i < 3; i++) p->rot[i] += p->rotv[i];
    if (e->rfl & 0x10) {
        p->rotv[0] += e->rota[0] + p->rr[0];
        p->rotv[1] += e->rota[1] + p->rr[1];
        p->rotv[2] += e->rota[2] + p->rr[2];
    } else {
        p->rotv[0] += e->rota[0];
        p->rotv[1] += e->rota[1];
        p->rotv[2] += e->rota[2];
    }
    for (i = 0; i < 3; i++) {
        if (p->rot[i] > 0x7fff) {
            while (p->rot[i] > 0x7fff) p->rot[i] -= 0x10000;
        } else if (p->rot[i] < -0x8000) {
            while (p->rot[i] > 0x7fff) p->rot[i] += 0x10000;
        }
    }
    for (i = 0; i < 3; i++) p->sc[i] += p->scv[i];
    if (e->sfl & 0x10) {
        p->scv[0] += e->sca[0] + p->sr[0];
        p->scv[1] += e->sca[1] + p->sr[1];
        p->scv[2] += e->sca[2] + p->sr[2];
    } else {
        p->scv[0] += e->sca[0];
        p->scv[1] += e->sca[1];
        p->scv[2] += e->sca[2];
    }
    p->f78 += e->fc8;
    PlatVu0ScaleVectorXYZ(v10, p->vel, p->f78);
    PlatVu0AddVector(p->pos, p->pos, v10);
    p->pos[3] = 1.0f;
    PlatVu0SubVector(v0, p->pos, D_00615F70);
    PlatVu0Normalize(v10, v0);
    v10[3] = 1.0f;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 %0, $vf10\n"
        : "=r"(dist) : "r"(v0) : "memory");
    p->f7c += p->f84;
    p->f80 += p->f88;
    p->f84 += e->fa0;
    p->f88 += e->fb0;
    if (e->life != 0 && e->life != 0xffff) p->life--;
    if (p->fl.x & 0x200) {
        if (p->fl.b) {
            p->f94 = 1.0f - (f32)p->fl.b / (f32)e->fade;
            p->fl.b--;
        } else {
            p->f94 = 1.0f;
            p->fl.x &= ~0x200;
        }
    } else if (p->fl.x & 0x400) {
        if (p->fl.b) {
            p->f94 = (f32)p->fl.b / (f32)e->fade;
            p->fl.b--;
        } else {
            p->f94 = 0;
            p->fl.x &= ~0x400;
        }
    } else {
        if (e->b13 && e->b13 >= p->life) {
            p->fl.b = e->b13;
            p->fl.x |= 0x400;
        }
        p->f94 = 1.0f;
    }
    if (e->fd8 + e->fdc < dist) {
        p->f94 = 0;
    } else if (e->fd8 < dist) {
        p->f94 *= 1.0f - (dist - e->fd8) / e->fd4;
    }
    if (PlatVu0InnerProduct(v10, (f32 *)D_0061E730) < 0.0f) {
        p->fl.x |= 0x100;
    } else {
        p->fl.x &= ~0x100;
    }
    f = e->fd8 + e->fdc;
    if (f < dist) {
        q = v20;
        for (i = 0; i < 3; i++) {
            *q++ = func_001a3650() * 1.2566368579864502f - 0.6283184289932251f;
        }
        PlatVu0RotMatrix(m30, D_006161C0, v20);
        PlatVu0ApplyMatrix(v20, m30, v10);
        PlatVu0ScaleVector(v20, v20, -f);
        PlatVu0AddVector(p->pos, D_00615F70, v20);
        p->pos[3] = 1.0f;
        func_001a3720(e, p, s);
    }
}

/* The frame (from text_001a0000_h65.c). */
typedef FV4_3701d0 FV4;
void *memset(void *, s32, u32);
void *func_0017f958(void *, s32);
extern void *D_00615E64;
typedef struct { u8 pad0[0x20]; u16 t; u16 idx; u16 prev; u16 alive; u8 pad28[0x38]; } MbPart;
typedef struct { u8 pad[0x20]; } MbSub;
static inline f32 vlen3_w65(FV4 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}


typedef struct { MbPart *parts; MbSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MbmWork;
typedef struct { u8 pad0[0xa]; u16 n; u8 padc[0xe8 - 0xc]; f32 dist; f32 fade; u8 test; u8 padf1; u8 sub; } MbmfKey;
s32 func_001a36f0();
void func_001a47b0(MbmWork *, MbmfKey *, void *);

void pppRyjMegaBirthModelFilterFrame(void *obj, MbmfKey *k, PppEntry *e) {
    MbmWork *w = (MbmWork *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;
    FV4 d;
    f32 len, r;

    if (w->parts == NULL) {
        w->n = k->n;
        w->parts = func_0017f958(D_00615E64, w->n * 0xA0);
        if (w->parts != NULL)
            memset(w->parts, 0, w->n * 0xA0);
        if (k->sub) {
            w->subs = func_0017f958(D_00615E64, w->n << 5);
            if (w->subs != NULL)
                memset(w->subs, 0, w->n << 5);
        }
    }
    if (!func_001a36f0(w, k))
        return;
    if (k->test) {
        PlatVu0SubVector((f32 *)&d, (f32 *)&D_00615F70, (f32 *)&D_003701D0);
        len = vlen3_w65(&d);
        if (k->dist < len) {
            w->active = 0;
        } else {
            w->active = 1;
            r = k->dist - len;
            if (r < k->fade)
                w->alpha = r / k->fade;
            else
                w->alpha = 1.0f;
        }
    }
    if (w->active)
        func_001a47b0(w, k, w2);
}



extern u8 D_00615EB0[];
extern f32 D_00616040[4][4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */

typedef f32 Mtx4[4][4];
typedef struct { u8 pad[0xe0]; f32 mul; f32 add; } RkKey;
typedef struct {
    u8 pad0[0x28];
    union { u64 d; s32 i[2]; } r01;
    s32 r2;
    u8 pad34[0x54 - 0x34];
    f32 scale[3];
} RkObj;

f32 func_001a4a98(void *a0, f32 (*m)[4], RkKey *k, void *a3, RkObj *o) {
    Mtx4 rm;
    f32 rot[3];
    f32 z;
    s32 i;
    PlatVu0UnitMatrix(m);
    if (o->r01.d || o->r2) {
        for (i = 0; i < 3; i++)
            rot[i] = (f32)o->r01.i[i] * 3.1415926f * 3.0517578125e-05f;
        PlatVu0RotMatrix(rm, D_006161C0, rot);
        PlatVu0MulMatrix(m, m, rm);
    }
    for (i = 0; i < 3; i++)
        PlatVu0ScaleVector(m[i], m[i], o->scale[i]);
    PlatVu0CopyVector(m[3], (f32 *)o);
    PlatVu0ApplyMatrix(m[3], (void *)D_00615EB0, m[3]);
    m[3][1] *= k->mul;
    z = m[3][2];
    m[3][1] += k->add;
    PlatVu0MulMatrix(m, D_00616040, m);
    return z;
}

/* The draw (from text_001a0000_b09.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
extern s32 D_00616224;
#define D_00616224 (*(volatile s32 *)&D_00616224)
typedef struct { u8 pad[0x10]; PppMtx m; PppMtx m2; s32 unk90; s32 unk94; } MfMtxOwner;
extern s32 D_00615E68;
#define D_00615E68 (*(MfMtxOwner **)&D_00615E68)
extern u8 D_00616240[];
typedef struct { s16 off; s16 dur; s32 pad; } FdFrame;
typedef struct { u8 pad0[0x10]; FdFrame f[1]; } FdShape;
typedef struct { FdShape *shape; s32 unk4; } FdShapeEnt;
typedef struct { u32 flags; u8 pad04[0x12]; u16 unk16; } MfMdl;
typedef struct { s32 pad0[7]; MfMdl *mdl; s32 unk20; } MfSlot;
typedef struct { u8 pad00[0x10]; MfSlot *slots; FdShapeEnt *shapes; } PppSys9;
#define D_00615E64 (*(PppSys9 **)&D_00615E64)

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
} MfParam;

typedef struct { u8 pad[8]; u8 r, g, b, a; } MfCol;
typedef struct { f32 f[4]; u8 pad[0x10]; } MfSub;
typedef struct {
    u8 pad0[0x20];
    u16 alive;
    s8 c[4];
    u8 pad26[0x7c - 0x26];
    f32 u, v;
    u8 pad84[0x94 - 0x84];
    f32 alpha;
    u64 flags;
} MfPart;
typedef struct { MfPart *parts; MfSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MfWork;
typedef struct { u8 pad0[4]; s32 id; u8 x08; u8 pad09[0xc7]; f32 dist; f32 fade; } MfKey;

void func_001a4a90(PppMtx m, MfKey *k, MfWork *w);
s32 func_001aaf88(MfMdl *, MfParam *, s32);

void pppRyjMegaBirthModelFilterDraw(void *obj, MfKey *k, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    MfParam p;
    MfWork *w = PPP_WORK(MfWork, obj, e, 2);
    MfCol *c = PPP_WORK(MfCol, obj, e, 1);
    MfPart *pt = w->parts;
    MfSub *sb = w->subs;
    s32 n = w->n;
    MfSlot *s;
    MfMdl *mdl;
    s32 cr, cg, cb, ca;
    s32 i;
    s32 id;
    u8 f8;

    if (!func_001a36f0(w, k))
        return;
    if (!w->active)
        return;
    id = k->id;
    if (id == 0xFFFF)
        return;
    func_001a4a90(m0, k, w);
    s = &D_00615E64->slots[id];
    mdl = s->mdl;
    p.p44 = 0;
    p.p2C = 0;
    p.p28 = 0;
    f8 = k->x08;
    p.p24 = 0;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p20 = m1;
    p.w0C = 0;
    p.t10.d = 0;
    p.p04 = D_00616240;
    p.flags = 4;
    p.w40 = 0;
    if (f8) p.flags = 0x204;
    p.b4D = 1;
    cr = c->r;
    cg = c->g;
    p.h08 = mdl->unk16;
    cb = c->b;
    ca = c->a;
    for (i = 0; i < n; i++) {
        if (pt->alive && !(pt->flags & 0x100)) {
            f32 d, dist, fade;
            s32 r, g, bl, al;
            d = func_001a4a98(m0, m1, (RkKey *)k, w, (RkObj *)pt);
            dist = k->dist;
            fade = k->fade;
            if (d < dist - fade) {
                pt->alpha = 0.0f;
            } else if (d < dist) {
                pt->alpha *= 1.0f - (dist - d) / fade;
            }
            r = cr + pt->c[0];
            g = cg + pt->c[1];
            bl = cb + pt->c[2];
            al = ca + pt->c[3];
            if (sb) {
                r += (s32)sb->f[0];
                g += (s32)sb->f[1];
                bl += (s32)sb->f[2];
                al += (s32)sb->f[3];
            }
            if (r < 0) r = 0; else if (r >= 256) r = 255;
            if (g < 0) g = 0; else if (g >= 256) g = 255;
            if (bl < 0) bl = 0; else if (bl >= 256) bl = 255;
            if (al < 0) al = 0; else if (al >= 128) al = 127;
            p.a = al;
            p.r = r;
            p.g = g;
            p.b = bl;
            p.a = p.a * pt->alpha * w->alpha;
            p.t10.s.u = pt->u * 65536.0f;
            p.t10.s.v = pt->v * 65536.0f;
            if (p.a) {
                p.w34 = D_00616224;
                D_00616224 = func_001aaf88(mdl, &p, s->unk20);
            }
        }
        if (sb)
            sb++;
        pt++;
    }
}

#undef D_00615E64
#undef D_00615E68
#undef D_00616224

