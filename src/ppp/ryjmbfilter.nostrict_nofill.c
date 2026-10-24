/* The pppRyjMegaBirthFilter particle step, -fno-strict-aliasing and no
 * delay-slot fill (docs/modules.md "Session 49"): func_001a2830 moves one
 * particle (spin, size, a step along its rotation), fades it in / out and
 * by its distance from D_00615F70 (near, near + far), flags it when it
 * faces away from D_0061E720, and past near + far puts it back at a random
 * point on that sphere and restarts it with ryjmbfilter.c's func_001a2248.
 * Read from the code, not proved by a boot. */
#include "common.h"

typedef f32 Mtx2830[4][4] __attribute__((aligned(16)));
typedef struct {
    u8 pad0[0x14];
    u16 h14;
    u8 b16;
    u8 b17;
    u8 pad18[0x10];
    f32 acc[4];     /* +0x28 */
    u8 pad38[0x1C];
    f32 ax, ay;     /* +0x54 */
    u8 pad5C[0x18];
    f32 angacc;     /* +0x74 */
    u8 pad78[0x14];
    f32 spin;       /* +0x8C */
    u8 pad90[8];
    f32 fade;       /* +0x98 */
    f32 near;       /* +0x9C */
    f32 far;        /* +0xA0 */
    u8 padA4[0x13];
    u8 bB7;
    u8 bB8;
} E2830;

typedef struct {
    f32 pos[4];     /* +0x00 */
    f32 rot[4];     /* +0x10 */
    u8 pad20[6];
    u16 h26;
    u8 pad28[4];
    f32 ang;        /* +0x2C */
    f32 angv;       /* +0x30 */
    f32 anga;       /* +0x34 */
    f32 sx, sy;     /* +0x38 */
    f32 svx, svy;   /* +0x40 */
    f32 sax, say;   /* +0x48 */
    f32 spin;       /* +0x50 */
    f32 alpha;      /* +0x54 */
    union { u64 d; u8 cnt; } fl; /* +0x58 */
} P2830;

extern f32 D_00615F70[4];
extern f32 D_006161C0[4]; /* src/data/bss_0061.c: u8 D_006161C0[0x40] */
extern u8 D_0061E720[];
f32 func_001a2178(void);
void func_001a2248(E2830 *, P2830 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
f32 func_00267390(f32 *, void *);
void func_002678b8(Mtx2830, f32 *, f32 *);
void func_002672f8(f32 *, Mtx2830, f32 *);
void func_00267560(f32 *, f32 *, f32);

static inline f32 vlen3_2830(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 %0, $vf10\n"
        : "=r"(r) : "r"(v) : "memory");
    return r;
}

void func_001a2830(s32 a0, E2830 *e, P2830 *p, s32 a3, f32 *b) {
    f32 d[4] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    f32 r[4] __attribute__((aligned(16)));
    Mtx2830 m;
    f32 v, len, lim;
    s32 i;

    if (b) {
        b[0] += b[4];
        b[1] += b[5];
        b[2] += b[6];
        b[3] += b[7];
        b[4] += e->acc[0];
        b[5] += e->acc[1];
        b[6] += e->acc[2];
        b[7] += e->acc[3];
    }
    p->ang += p->angv;
    if (e->bB8 & 0x10) p->angv += e->angacc + p->anga;
    else p->angv += e->angacc;

    while (p->ang >= 180.0f) p->ang -= 360.0f;
    while (p->ang < -180.0f) p->ang += 360.0f;

    p->sx += p->svx;
    p->sy += p->svy;
    if (e->bB7 & 0x10) {
        p->svx += e->ax + p->sax;
        p->svy += e->ay + p->say;
    } else {
        p->svx += e->ax;
        p->svy += e->ay;
    }
    p->spin += e->spin;
    func_00267e90(t, p->rot, p->spin);
    func_00267518(p->pos, p->pos, t);
    p->pos[3] = 1.0f;
    func_00267530(d, p->pos, D_00615F70);
    func_002673b8(t, d);
    t[3] = 1.0f;
    len = vlen3_2830(d);
    if (e->h14 != 0 && e->h14 != 0xFFFF) p->h26 += 0xFFFF;
    if (p->fl.d & 0x200) {
        if (p->fl.cnt) {
            p->alpha = 1.0f - (f32)p->fl.cnt / (f32)e->b16;
            p->fl.cnt--;
        } else {
            p->alpha = 1.0f;
            p->fl.d &= ~0x200;
        }
    } else if (p->fl.d & 0x400) {
        if (p->fl.cnt) {
            p->alpha = (f32)p->fl.cnt / (f32)e->b16;
            p->fl.cnt--;
        } else {
            p->alpha = 0.0f;
            p->fl.d &= ~0x400;
        }
    } else {
        if (e->b17 && e->b17 >= p->h26) {
            p->fl.cnt = e->b17;
            p->fl.d |= 0x400;
        }
        p->alpha = 1.0f;
    }
    if (e->near + e->far < len) {
        p->alpha = 0.0f;
    } else if (e->near < len) {
        p->alpha *= 1.0f - (len - e->near) / e->fade;
    }
    if (func_00267390(t, D_0061E720) < 0.0f) p->fl.d |= 0x100;
    else p->fl.d &= ~0x100;
    lim = e->near + e->far;
    if (lim < len) {
        for (i = 0; i < 3; i++) r[i] = func_001a2178() * 1.256636888f - 0.6283184439f;
        func_002678b8(m, D_006161C0, r);
        func_002672f8(r, m, t);
        func_00267560(r, r, -lim);
        func_00267518(p->pos, D_00615F70, r);
        p->pos[3] = 1.0f;
        func_001a2248(e, p, b);
    }
}
