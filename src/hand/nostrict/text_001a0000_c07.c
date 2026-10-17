/* worker c07: nostrict region (0x1a3720-0x1a5c9c). */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
typedef f32 Vec[4] __attribute__((aligned(16)));

typedef struct {
    Mtx ma;       /* 0x00 */
    Mtx m;        /* 0x40 */
    f32 off[3];   /* 0x80 */
    u8 pad8c[2];
    u8 b8e;
    u8 b8f;
    Vec v90;      /* 0x90 */
    f32 fa0;
    f32 fa4;
    f32 fa8;
} Obj57c0;

typedef struct {
    Obj57c0 *o;
    f32 *v;
    Mtx *mtx;
} Arg57c0;

extern Mtx D_00615FC0;
extern Mtx D_00616040;
void sceVu0CopyMatrix(Mtx, Mtx);
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);
void func_002672f8(f32 *, Mtx, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
f32 func_001a9350(f32 *);
f32 func_001a9388(f32 *);


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

void func_001a57c0(Arg57c0 *a) {
    Mtx m0;
    Mtx m1;
    Vec v80;
    Vec v90;
    Vec va0;
    Obj57c0 *o;

    f32 d;

    o = a->o;
    sceVu0CopyMatrix(m1, *a->mtx);
    if (o->b8f) {
        sceVu0CopyMatrix(m0, m1);
        m0[3][0] = 0;
        m0[3][1] = 0;
        m0[3][2] = 0;
        func_002672f8(v80, m0, a->v);
        func_00267560(v90, m1[3], -1.0f);
        func_00267530(va0, v90, v80);
    } else {
        *(u128 *)v80 = 0;
        *(u128 *)v90 = 0;
        v80[3] = 1.0f;
        v90[3] = 1.0f;
        sceVu0UnitMatrix(m0);
        m0[3][0] = D_00615FC0[3][0] + o->off[0];
        m0[3][1] = D_00615FC0[3][1] + o->off[1];
        m0[3][2] = D_00615FC0[3][2] + o->off[2];
        sceVu0MulMatrix(m0, D_00616040, m0);
        func_002672f8(v80, m0, v80);
        func_00267560(v80, v80, 1.0f / v80[3]);
        sceVu0UnitMatrix(m0);
        func_002675a8(m0[3], D_00615FC0[3]);
        sceVu0MulMatrix(m0, D_00616040, m0);
        func_002672f8(v90, m0, v90);
        func_00267560(v90, v90, 1.0f / v90[3]);
        func_00267530(va0, v90, v80);
        va0[2] = 512.0f;
    }
    sceVu0UnitMatrix(o->ma);
    func_002672f8(o->ma[3], m1, a->v);
    if (va0[0] == 0.0f && va0[1] == 0.0f) {
        func_002675a8(o->m[3], o->ma[3]);
    } else {
        __asm__ volatile(
        "lqc2 $vf18, 0(%1)\n"
        "vmul.xy $vf26xy, $vf18xy, $vf18xy\n"
        "vaddy.x $vf26x, $vf26x, $vf26y\n"
        "vsqrt Q, $vf26x\n"
        "vsub.zw $vf22zw, $vf0zw, $vf0zw\n"
        "vsub.w $vf21w, $vf0w, $vf0w\n"
        "vsub.xyw $vf20xyw, $vf0xyw, $vf0xyw\n"
        "vaddw.z $vf20z, $vf0z, $vf0w\n"
        "sqc2 $vf20, 32(%0)\n"
        "vwaitq\n"
        "vaddq.x $vf26x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf26x\n"
        "lqc2 $vf17, 0(%2)\n"
        "sqc2 $vf17, 48(%0)\n"
        "vwaitq\n"
        "vmulq.xy $vf22xy, $vf18xy, Q\n"
        "sqc2 $vf22, 0(%0)\n"
        "vopmula.xyz ACC, $vf22, $vf20\n"
        "vopmsub.xyz $vf21, $vf20, $vf22\n"
        "sqc2 $vf21, 16(%0)\n"
        : : "r"(o->m), "r"(va0), "r"(o->ma[3]) : "memory");
    }
    if (o->b8f) {
        o->m[3][2] = o->ma[3][2] * 0.001953125f;
    } else {
        o->m[3][2] = (D_00615FC0[3][2] + o->off[2]) * 0.001953125f;
    }
    func_002673b8(va0, va0);
    o->m[3][0] = va0[0] * o->m[3][2];
    o->m[3][1] = va0[1] * o->m[3][2];
    func_00267530(v90, v90, v80);
    d = func_001a9350(v90);
    o->fa4 = func_001a9388(v90);
    func_002673b8(v80, v90);
    if (o->b8f) {
        v90[0] = 0;
        v90[1] = 0;
        v90[2] = 1.0f;
        v90[0] = (1.0f - (1.0f - func_00267390(v90, v80)) * 0.5f) / 0.3f;
        o->m[3][3] = v90[0] > 1.0f ? 0.0f : 1.0f - v90[0];
        if (o->v90[3] >= 0.0f) {
            sceVu0CopyMatrix(m0, m1);
            m0[3][2] = m0[3][1] = m0[3][0] = 0.0f;
            func_002672f8(v90, m0, v90);
            v90[0] = (1.0f - func_00267390(o->v90, v80)) * 0.5f;
            v90[0] = v90[0] / o->v90[3];
            v90[0] = v90[0] > 1.0f ? 0.0f : 1.0f - v90[0];
            o->m[3][3] *= v90[0];
        }
        v80[0] = o->fa8 - (f32)o->b8e;
        if (v80[0] > 0.0f) {
            v80[0] = d / v80[0];
            d = 0.0f;
            if (!(v80[0] >= 1.0f)) d = 1.0f - v80[0];
            o->m[3][3] *= d;
        } else {
            o->m[3][3] = 0.0f;
        }
    } else {
        if (o->fa8 > 0.0f) {
            o->m[3][3] = o->fa4 / o->fa8;
            o->m[3][3] = o->m[3][3] > 1.0f ? 0.0f : 1.0f - o->m[3][3];
        } else {
            o->m[3][3] = 0.0f;
        }
    }
}
