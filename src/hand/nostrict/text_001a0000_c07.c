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

/* func_001a7718 with its GNU C nested functions func_001a67f0, func_001a6c90,
 * func_001a72c8, func_001a7600, func_001a7668 (static chain in $v0).
 * Uses rodata: three 0.0f literals (one per nested function, 0x48fd98..0x48fda0). */

typedef union {
    u128 q;
    u64 d[2];
    u32 w[4];
    f32 f[4];
} Qw;

typedef struct {
    f32 pos[4];
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
} Vtx;

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    u16 n34;
    u16 pad36;
    u16 n38;
    u16 pad3a;
    u16 n3c;
    u16 f3e;
    Vtx v[1];
} Obj;

typedef struct {
    u8 b[8];
    u8 pad8[4];
    f32 f0c;
    s8 s[8];
    u8 pad18[4];
    f32 f1c;
    u8 pad20[0x10];
    f32 f30;
    u8 pad34[4];
    f32 f38;
} Cfg;

typedef struct {
    Mtx *m;
    Obj *o;
    Qw *pk;
    Cfg *c;
    f32 *uv;
    Qw *last;
    u64 d18;
    u64 d20;
} Arg7718;

void sceVu0CopyMatrix(Mtx, Mtx);
void func_002675a8(f32 *, f32 *);
void func_002675f0(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267908(f32 *, f32 *, f32, f32);
f32 func_001a9058(f32, f32);
void func_001a9080(f32 *, f32 *);
void func_001a9098(f32 *, f32 *);
void func_001a90e0(f32 *, f32 *, f32 *);
void func_001a9128(f32 *, f32 *, f32 *);
u32 func_001a9140(f32 *, f32 *, f32 *);
u32 func_001a91b0(f32 *, f32 *);
void func_001a9218(f32 *, f32 *);
s32 func_001a9248(f32 *, Mtx, f32 *);

#define pkt s.pkt_
#define vp s.vp_
#define stride s.stride_
#define base s.base_
#define cnt s.cnt_
#define tagp s.tagp_
#define flag s.flag_
#define n0 s.n0_
#define n1 s.n1_
#define p0 s.p0_
#define p1 s.p1_
s32 func_001a7718(Arg7718 *a) {
    Mtx m;
    Vec c0;
    Vec c1;
    Vec uv;
    Vec d0;
    Vec d1;
    Vec k144;
    Vec v160;
    Vec v176;
    Vec v192;
    Vec v208;
    Vec v224;
    Vec v240;
    Qw tag0;
    Qw tag1;
    Vec pad288[2];
    Vec v320;
    Qw tag2;
    Vec pad352;
    Vec v368;
    Vec v384;
    Vec v400;
    Vec v416;
    Vec v432;
    Vec v448;
    Vec v464;
    Vec tmp;
    struct {
        Qw *pkt_;
        u8 *vp_;
        s32 x504[3];
        s32 stride_;
        Qw *base_;
        s32 cnt_;
        Qw *tagp_;
        u32 flag_;
        s32 n0_;
        s32 n1_;
        Vtx *p0_;
        Vtx *p1_;
        s32 x552[2];
    } s;

    auto void func_001a67f0(void) asm("func_001a67f0");
    auto void func_001a6c90(void) asm("func_001a6c90");
    auto void func_001a72c8(void) asm("func_001a72c8");
    auto void func_001a7600(void) asm("func_001a7600");
    auto void func_001a7668(void) asm("func_001a7668");

    void func_001a67f0(void) {
        tagp = pkt;
        pkt->q = tag2.q;
        pkt++;
        v320[3] = 1.0f - ((Vtx *)vp)->f1c * k144[2];
        func_002675f0(tmp, c0);
        func_001a9098(v400, tmp);
        func_002675a8(pkt->f, v400);
        pkt++;
        flag = func_001a91b0(pkt->f, v160);
        pkt->w[3] |= flag;
        pkt++;
        func_002675f0(v384, c1);
        func_00267518(tmp, c1, d1);
        func_00267908(c1, tmp, 0.0f, uv[2]);
        func_002675f0(v368, c1);
        func_002675a8(tmp, (f32 *)vp);
        func_001a9248(v192, m, tmp);
        v320[2] = 1.0f / v192[3];
        vp += stride;
        func_001a9128(tmp, v192, v176);
        func_001a9218(v448, tmp);
        func_001a90e0(tmp, v208, v448);
        func_001a9218(tmp, tmp);
        v320[0] += v240[3];
        v320[0] = func_001a9058(v320[0], 0.0f);
        v464[0] = tmp[1];
        v464[1] = -tmp[0];
        v464[0] = v464[0] * v320[0] * v320[1] * (v320[3] * uv[0]);
        v464[1] = v464[1] * v320[0] * v320[1] * (v320[3] * uv[1]);
        func_001a9080(v208, v448);
        v320[1] = v320[2];
        func_001a9098(v400, v368);
        func_002675a8(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v464);
        pkt->w[3] |= flag;
        pkt++;
        func_002675a8(v224, v464);
        func_00267560(v416, v464, uv[3]);
        func_002675a8(pkt->f, v368);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v416);
        pkt->w[3] |= flag;
        pkt++;
        func_00267518(tmp, c0, d0);
        func_00267908(c0, tmp, 0.0f, 255.0f);
        func_002675f0(v448, c0);
        func_002675a8(pkt->f, v448);
        pkt++;
        flag |= func_001a91b0(pkt->f, v176);
        pkt->w[3] |= flag;
        pkt++;
        func_00267560(v416, v464, v240[1]);
        func_00267560(v448, v416, uv[3]);
        func_002675a8(pkt->f, v368);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v448);
        pkt->w[3] |= flag;
        pkt++;
        func_001a9098(v400, v368);
        func_002675a8(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v416);
        pkt->w[3] |= flag;
        pkt++;
        func_002675a8(v160, v176);
        func_002675a8(v176, v192);
        cnt--;
    }

    void func_001a6c90(void) {
        while (cnt > 0) {
            v320[3] = 1.0f - ((Vtx *)vp)->f1c * k144[2];
            tagp = pkt;
            pkt->q = tag1.q;
            pkt++;
            func_002675f0(v384, c1);
            func_00267518(tmp, c1, d1);
            func_00267908(c1, tmp, 0.0f, uv[2]);
            func_002675f0(v368, c1);
            func_002675a8(tmp, (f32 *)vp);
            func_001a9248(v192, m, tmp);
            v320[2] = 1.0f / v192[3];
            vp += stride;
            func_001a9128(tmp, v192, v176);
            func_001a9218(v448, tmp);
            func_001a90e0(tmp, v208, v448);
            func_001a9218(tmp, tmp);
            v320[0] += v240[3];
            v320[0] = func_001a9058(v320[0], 0.0f);
            v464[0] = tmp[1];
            v464[1] = -tmp[0];
            v464[0] = v464[0] * v320[0] * v320[1] * (v320[3] * uv[0]);
            v464[1] = v464[1] * v320[0] * v320[1] * (v320[3] * uv[1]);
            func_001a9080(v208, v448);
            v320[1] = v320[2];
            func_001a9098(v400, v384);
            func_002675a8(pkt->f, v400);
            pkt++;
            flag = func_001a9140(pkt->f, v160, v224);
            pkt->w[3] |= flag;
            pkt++;
            func_001a9098(v400, v368);
            func_002675a8(pkt->f, v400);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v464);
            pkt->w[3] |= flag;
            pkt++;
            func_00267560(v448, v224, uv[3]);
            func_00267560(v432, v224, v240[1]);
            func_002675a8(v224, v464);
            func_00267560(v416, v464, uv[3]);
            func_002675a8(pkt->f, v384);
            pkt++;
            flag |= func_001a9140(pkt->f, v160, v448);
            pkt->w[3] |= flag;
            pkt++;
            func_002675a8(pkt->f, v368);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v416);
            pkt->w[3] |= flag;
            pkt++;
            func_002675f0(v416, c0);
            func_00267518(tmp, c0, d0);
            func_00267908(c0, tmp, 0.0f, 255.0f);
            func_002675f0(v448, c0);
            func_002675a8(pkt->f, v416);
            pkt++;
            flag |= func_001a91b0(pkt->f, v160);
            pkt->w[3] |= flag;
            pkt++;
            func_002675a8(pkt->f, v448);
            pkt++;
            flag |= func_001a91b0(pkt->f, v176);
            pkt->w[3] |= flag;
            pkt++;
            func_00267560(v416, v464, v240[1]);
            func_00267560(v464, v432, uv[3]);
            func_00267560(v448, v416, uv[3]);
            func_002675a8(pkt->f, v384);
            pkt++;
            flag |= func_001a9140(pkt->f, v160, v464);
            pkt->w[3] |= flag;
            pkt++;
            func_002675a8(pkt->f, v368);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v448);
            pkt->w[3] |= flag;
            pkt++;
            func_001a9098(v400, v384);
            func_002675a8(pkt->f, v400);
            pkt++;
            flag |= func_001a9140(pkt->f, v160, v432);
            pkt->w[3] |= flag;
            pkt++;
            func_001a9098(v400, v368);
            func_002675a8(pkt->f, v400);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v416);
            pkt->w[3] |= flag;
            pkt++;
            func_002675a8(v160, v176);
            func_002675a8(v176, v192);
            cnt--;
        }
    }

    void func_001a72c8(void) {
        tagp = pkt;
        pkt->q = tag2.q;
        pkt++;
        func_002675f0(v416, c0);
        func_00267518(tmp, c0, d0);
        func_00267908(c0, tmp, 0.0f, 255.0f);
        func_002675f0(v448, c0);
        func_001a9098(tmp, v448);
        func_002675a8(pkt->f, tmp);
        pkt++;
        flag = func_001a91b0(pkt->f, v176);
        pkt->w[3] |= flag;
        pkt++;
        func_002675f0(v384, c1);
        func_001a9098(v400, v384);
        func_002675a8(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v224);
        pkt->w[3] |= flag;
        pkt++;
        func_00267560(v448, v224, uv[3]);
        func_00267560(v432, v224, v240[1]);
        func_002675a8(pkt->f, v384);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v448);
        pkt->w[3] |= flag;
        pkt++;
        func_002675a8(pkt->f, v416);
        pkt++;
        flag |= func_001a91b0(pkt->f, v160);
        pkt->w[3] |= flag;
        pkt++;
        func_00267560(v464, v432, uv[3]);
        func_002675f0(v384, c1);
        func_002675a8(pkt->f, v384);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v464);
        pkt->w[3] |= flag;
        pkt++;
        func_001a9098(v400, v384);
        func_002675a8(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v432);
        pkt->w[3] |= flag;
        pkt++;
        a->last = tagp;
        a->pk = pkt;
    }

    void func_001a7600(void) {
        func_002675a8(tmp, (f32 *)vp);
        func_001a9248(v160, m, tmp);
        vp += stride;
        cnt--;
    }

    void func_001a7668(void) {
        func_002675a8(tmp, (f32 *)vp);
        func_001a9248(v176, m, tmp);
        v320[1] = 1.0f / v176[3];
        func_00267530(tmp, v176, v160);
        func_001a9218(v208, tmp);
        vp += stride;
        cnt--;
    }

    if (a->o->n38 + a->o->n3c < 3) return 0;
    pkt = base = a->pk;
    stride = 48;
    sceVu0CopyMatrix(m, *a->m);
    c0[0] = a->c->b[0];
    c0[1] = a->c->b[1];
    c0[2] = a->c->b[2];
    c0[3] = a->c->b[3];
    c1[0] = a->c->b[4];
    c1[1] = a->c->b[5];
    c1[2] = a->c->b[6];
    c1[3] = a->c->b[7];
    d0[0] = a->c->s[0];
    d0[1] = a->c->s[1];
    d0[2] = a->c->s[2];
    d0[3] = a->c->s[3];
    d1[0] = a->c->s[4];
    d1[1] = a->c->s[5];
    d1[2] = a->c->s[6];
    d1[3] = a->c->s[7];
    v240[1] = -1.0f;
    v320[0] = a->c->f0c;
    k144[2] = a->c->f38;
    uv[3] = a->c->f30;
    v240[3] = a->c->f1c;
    uv[2] = 255.0f;
    ((s32 *)v400)[3] = 0;
    k144[0] = 4096.0f;
    k144[1] = 4096.0f;
    ((s32 *)k144)[3] = 0x8000;
    uv[0] = a->uv[0];
    uv[1] = a->uv[1];
    tag0.d[0] = 0x2000000000000001;
    tag0.d[1] = 238;
    tag1.d[0] = 0x202640000000000a;
    tag2.d[0] = 0x2026c00000000006;
    tag1.d[1] = 81;
    tag2.d[1] = 81;
    if (!(a->o->f3e & 0x1000)) {
        v464[0] = a->o->f30;
        func_00267560(tmp, d0, v464[0]);
        func_00267518(tmp, c0, tmp);
        func_00267908(c0, tmp, 0.0f, uv[2]);
        func_00267560(tmp, d1, v464[0]);
        func_00267518(tmp, c1, tmp);
        func_00267908(c1, tmp, 0.0f, uv[2]);
        tmp[0] = v320[0] + v240[3] * v464[0];
        if (tmp[0] < 0.0f) {
            v320[0] = 0.0f;
        } else {
            v320[0] = tmp[0];
        }
        n0 = a->o->n38;
        n1 = a->o->n3c;
        p0 = a->o->v + a->o->n34;
        p1 = a->o->v;
    } else {
        n0 = a->o->n3c;
        n1 = a->o->n38;
        p0 = a->o->v + a->o->n3c - 1;
        p1 = a->o->v + a->o->n34 + a->o->n38 - 1;
        stride = -stride;
    }
    tagp = pkt;
    pkt->q = tag0.q;
    pkt++;
    pkt->d[0] = a->d20;
    pkt->d[1] = 71;
    pkt++;
    pkt->d[0] = a->d18;
    pkt->d[1] = 66;
    pkt++;
    if (n0 != 0) {
        vp = (u8 *)p0;
        cnt = n0;
        func_001a7600();
        if (cnt == 0) {
            vp = (u8 *)p1;
            cnt = n1;
            goto l7668;
        }
        func_001a7668();
        if (cnt == 0) {
            vp = (u8 *)p1;
            cnt = n1;
            goto l67f0;
        }
        func_001a67f0();
        n0--;
        func_001a6c90();
        if (n1 == 0) goto end;
        cnt = n1;
        vp = (u8 *)p1;
        goto l6c90;
    }
    vp = (u8 *)p1;
    cnt = n1;
    func_001a7600();
l7668:
    func_001a7668();
l67f0:
    func_001a67f0();
l6c90:
    func_001a6c90();
end:
    func_001a72c8();
    return 1;
}
