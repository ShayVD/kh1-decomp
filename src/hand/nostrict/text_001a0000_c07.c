/* worker c07: nostrict region (0x1a3720-0x1a5c9c). */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
typedef f32 Vec[4] __attribute__((aligned(16)));
void sceVu0CopyMatrix(Mtx, Mtx);
void func_002672f8(f32 *, Mtx, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);

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
void func_00267e90(f32 *, f32 *, f32);
extern f32 D_00615F70[4];
extern u8 D_0061E730[];

void func_001a3720(Em *e, Pt *p, Sub *s);

void func_00267518(f32 *, f32 *, f32 *);
void func_002678b8(Mtx, Mtx, f32 *);
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
void func_00267e90(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
void func_002678b8(f32 (*)[4], f32 (*)[4], f32 *);
void func_002672f8(f32 *, f32 (*)[4], f32 *);
void func_00267560(f32 *, f32 *, f32);
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
    func_00267e90(v10, p->vel, p->f78);
    func_00267518(p->pos, p->pos, v10);
    p->pos[3] = 1.0f;
    func_00267530(v0, p->pos, D_00615F70);
    func_002673b8(v10, v0);
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
    if (func_00267390(v10, (f32 *)D_0061E730) < 0.0f) {
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
        func_002678b8(m30, D_006161C0, v20);
        func_002672f8(v20, m30, v10);
        func_00267560(v20, v20, -f);
        func_00267518(p->pos, D_00615F70, v20);
        p->pos[3] = 1.0f;
        func_001a3720(e, p, s);
    }
}

