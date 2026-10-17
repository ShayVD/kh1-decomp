/* worker c06: nostrict, no delay-slot filling. */
#include "common.h"

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
extern PppMtx D_00615EB0;
extern PppMtx D_00616040;
extern f32 D_003701F0[3];
void sceVu0UnitMatrix(PppMtx);
void func_002676c0(PppMtx, PppMtx, f32);
void func_00267518(f32 *, f32 *, f32 *);

typedef struct {
    f32 pos[4];
    u8 pad10[0x1C];
    f32 rot;      /* +0x2C */
    u8 pad30[8];
    f32 sx, sy;   /* +0x38 */
} KeyD020;

typedef struct {
    u8 pad[0xCC];
    u8 mode;
} ObjD020;

void func_0019d020(PppMtx a, PppMtx m, ObjD020 *o, PppMtx c, KeyD020 *k, PppMtx b, PppMtx out, u8 flag) {
    sceVu0UnitMatrix(m);
    m[0][0] = k->sx * D_003701F0[0];
    m[1][1] = k->sy * D_003701F0[1];
    m[2][2] = k->sx * D_003701F0[0];
    if (k->rot != 0.0f) {
        func_002676c0(m, m, k->rot * 3.141592562f / 180.0f);
    }
    func_00267518(m[3], m[3], k->pos);
    switch (o->mode) {
    case 0:
        __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 16(%0)\n"
        "lqc2 $vf3, 32(%0)\n"
        "lqc2 $vf4, 48(%0)\n"
        "lqc2 $vf9, 0(%1)\n"
        "lqc2 $vf10, 16(%1)\n"
        "lqc2 $vf11, 32(%1)\n"
        "lqc2 $vf12, 48(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "lqc2 $vf6, 16(%2)\n"
        "lqc2 $vf7, 32(%2)\n"
        "lqc2 $vf8, 48(%2)\n"
        "vmulax.xyzw ACC, $vf9, $vf4x\n"
        "vmadday.xyzw ACC, $vf10, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf12, $vf4w\n"
        "beql $0, %4, 1f\n"
        "sqc2 $vf1, 0(%3)\n"
        "sqc2 $vf2, 16(%3)\n"
        "sqc2 $vf3, 32(%3)\n"
        "sqc2 $vf4, 48(%3)\n"
        "1:\n"
        "vmulax.xyzw ACC, $vf5, $vf1x\n"
        "vmadday.xyzw ACC, $vf6, $vf1y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf8, $vf1w\n"
        "vmulax.xyzw ACC, $vf5, $vf2x\n"
        "vmadday.xyzw ACC, $vf6, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf8, $vf2w\n"
        "vmulax.xyzw ACC, $vf5, $vf3x\n"
        "vmadday.xyzw ACC, $vf6, $vf3y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf8, $vf3w\n"
        "vmulax.xyzw ACC, $vf5, $vf4x\n"
        "vmadday.xyzw ACC, $vf6, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf8, $vf4w\n"
        "sqc2 $vf1, 0(%0)\n"
        "sqc2 $vf2, 16(%0)\n"
        "sqc2 $vf3, 32(%0)\n"
        "sqc2 $vf4, 48(%0)\n"
        : : "r"(m), "r"(a), "r"(D_00616040), "r"(out), "r"(flag) : "memory");
        break;
    case 1:
        __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 16(%0)\n"
        "lqc2 $vf3, 32(%0)\n"
        "lqc2 $vf4, 48(%0)\n"
        "lqc2 $vf9, 0(%1)\n"
        "lqc2 $vf10, 16(%1)\n"
        "lqc2 $vf11, 32(%1)\n"
        "lqc2 $vf12, 48(%1)\n"
        "lqc2 $vf13, 0(%2)\n"
        "lqc2 $vf14, 16(%2)\n"
        "lqc2 $vf15, 32(%2)\n"
        "lqc2 $vf16, 48(%2)\n"
        "lqc2 $vf17, 0(%3)\n"
        "lqc2 $vf18, 16(%3)\n"
        "lqc2 $vf19, 32(%3)\n"
        "lqc2 $vf20, 48(%3)\n"
        "lqc2 $vf5, 0(%4)\n"
        "lqc2 $vf6, 16(%4)\n"
        "lqc2 $vf7, 32(%4)\n"
        "lqc2 $vf8, 48(%4)\n"
        "vmulax.xyzw ACC, $vf9, $vf17x\n"
        "vmadday.xyzw ACC, $vf10, $vf17y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf17z\n"
        "vmaddw.xyzw $vf17, $vf12, $vf17w\n"
        "vmulax.xyzw ACC, $vf9, $vf18x\n"
        "vmadday.xyzw ACC, $vf10, $vf18y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf18z\n"
        "vmaddw.xyzw $vf18, $vf12, $vf18w\n"
        "vmulax.xyzw ACC, $vf9, $vf19x\n"
        "vmadday.xyzw ACC, $vf10, $vf19y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf19z\n"
        "vmaddw.xyzw $vf19, $vf12, $vf19w\n"
        "vmulax.xyzw ACC, $vf9, $vf20x\n"
        "vmadday.xyzw ACC, $vf10, $vf20y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf20z\n"
        "vmaddw.xyzw $vf20, $vf12, $vf20w\n"
        "vmulax.xyzw ACC, $vf13, $vf17x\n"
        "vmadday.xyzw ACC, $vf14, $vf17y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf17z\n"
        "vmaddw.xyzw $vf9, $vf16, $vf17w\n"
        "vmulax.xyzw ACC, $vf13, $vf18x\n"
        "vmadday.xyzw ACC, $vf14, $vf18y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf18z\n"
        "vmaddw.xyzw $vf10, $vf16, $vf18w\n"
        "vmulax.xyzw ACC, $vf13, $vf19x\n"
        "vmadday.xyzw ACC, $vf14, $vf19y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf19z\n"
        "vmaddw.xyzw $vf11, $vf16, $vf19w\n"
        "vmulax.xyzw ACC, $vf13, $vf20x\n"
        "vmadday.xyzw ACC, $vf14, $vf20y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf20z\n"
        "vmaddw.xyzw $vf12, $vf16, $vf20w\n"
        "vmulax.xyzw ACC, $vf9, $vf4x\n"
        "vmadday.xyzw ACC, $vf10, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf12, $vf4w\n"
        "beql $0, %6, 1f\n"
        "sqc2 $vf1, 0(%5)\n"
        "sqc2 $vf2, 16(%5)\n"
        "sqc2 $vf3, 32(%5)\n"
        "sqc2 $vf4, 48(%5)\n"
        "1:\n"
        "vmulax.xyzw ACC, $vf5, $vf1x\n"
        "vmadday.xyzw ACC, $vf6, $vf1y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf8, $vf1w\n"
        "vmulax.xyzw ACC, $vf5, $vf2x\n"
        "vmadday.xyzw ACC, $vf6, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf8, $vf2w\n"
        "vmulax.xyzw ACC, $vf5, $vf3x\n"
        "vmadday.xyzw ACC, $vf6, $vf3y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf8, $vf3w\n"
        "vmulax.xyzw ACC, $vf5, $vf4x\n"
        "vmadday.xyzw ACC, $vf6, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf8, $vf4w\n"
        "sqc2 $vf1, 0(%0)\n"
        "sqc2 $vf2, 16(%0)\n"
        "sqc2 $vf3, 32(%0)\n"
        "sqc2 $vf4, 48(%0)\n"
        : : "r"(m), "r"(b), "r"(D_00615EB0), "r"(D_00615E68->m), "r"(D_00616040), "r"(out), "r"(flag) : "memory");
        break;
    case 2:
        __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 16(%0)\n"
        "lqc2 $vf3, 32(%0)\n"
        "lqc2 $vf4, 48(%0)\n"
        "lqc2 $vf9, 0(%1)\n"
        "lqc2 $vf10, 16(%1)\n"
        "lqc2 $vf11, 32(%1)\n"
        "lqc2 $vf12, 48(%1)\n"
        "lqc2 $vf13, 0(%2)\n"
        "lqc2 $vf14, 16(%2)\n"
        "lqc2 $vf15, 32(%2)\n"
        "lqc2 $vf16, 48(%2)\n"
        "lqc2 $vf17, 0(%3)\n"
        "lqc2 $vf18, 16(%3)\n"
        "lqc2 $vf19, 32(%3)\n"
        "lqc2 $vf20, 48(%3)\n"
        "lqc2 $vf5, 0(%4)\n"
        "lqc2 $vf6, 16(%4)\n"
        "lqc2 $vf7, 32(%4)\n"
        "lqc2 $vf8, 48(%4)\n"
        "vmulax.xyzw ACC, $vf17, $vf9x\n"
        "vmadday.xyzw ACC, $vf18, $vf9y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf9z\n"
        "vmaddw.xyzw $vf9, $vf20, $vf9w\n"
        "vmulax.xyzw ACC, $vf17, $vf10x\n"
        "vmadday.xyzw ACC, $vf18, $vf10y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf10z\n"
        "vmaddw.xyzw $vf10, $vf20, $vf10w\n"
        "vmulax.xyzw ACC, $vf17, $vf11x\n"
        "vmadday.xyzw ACC, $vf18, $vf11y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf11z\n"
        "vmaddw.xyzw $vf11, $vf20, $vf11w\n"
        "vmulax.xyzw ACC, $vf17, $vf12x\n"
        "vmadday.xyzw ACC, $vf18, $vf12y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf12z\n"
        "vmaddw.xyzw $vf12, $vf20, $vf12w\n"
        "vmulax.xyzw ACC, $vf13, $vf9x\n"
        "vmadday.xyzw ACC, $vf14, $vf9y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf9z\n"
        "vmaddw.xyzw $vf9, $vf16, $vf9w\n"
        "vmulax.xyzw ACC, $vf13, $vf10x\n"
        "vmadday.xyzw ACC, $vf14, $vf10y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf10z\n"
        "vmaddw.xyzw $vf10, $vf16, $vf10w\n"
        "vmulax.xyzw ACC, $vf13, $vf11x\n"
        "vmadday.xyzw ACC, $vf14, $vf11y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf11z\n"
        "vmaddw.xyzw $vf11, $vf16, $vf11w\n"
        "vmulax.xyzw ACC, $vf13, $vf12x\n"
        "vmadday.xyzw ACC, $vf14, $vf12y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf12z\n"
        "vmaddw.xyzw $vf12, $vf16, $vf12w\n"
        "vmulax.xyzw ACC, $vf9, $vf4x\n"
        "vmadday.xyzw ACC, $vf10, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf12, $vf4w\n"
        "beql $0, %6, 1f\n"
        "sqc2 $vf1, 0(%5)\n"
        "sqc2 $vf2, 16(%5)\n"
        "sqc2 $vf3, 32(%5)\n"
        "sqc2 $vf4, 48(%5)\n"
        "1:\n"
        "vmulax.xyzw ACC, $vf5, $vf1x\n"
        "vmadday.xyzw ACC, $vf6, $vf1y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf8, $vf1w\n"
        "vmulax.xyzw ACC, $vf5, $vf2x\n"
        "vmadday.xyzw ACC, $vf6, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf8, $vf2w\n"
        "vmulax.xyzw ACC, $vf5, $vf3x\n"
        "vmadday.xyzw ACC, $vf6, $vf3y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf8, $vf3w\n"
        "vmulax.xyzw ACC, $vf5, $vf4x\n"
        "vmadday.xyzw ACC, $vf6, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf8, $vf4w\n"
        "sqc2 $vf1, 0(%0)\n"
        "sqc2 $vf2, 16(%0)\n"
        "sqc2 $vf3, 32(%0)\n"
        "sqc2 $vf4, 48(%0)\n"
        : : "r"(m), "r"(b), "r"(D_00615EB0), "r"(c), "r"(D_00616040), "r"(out), "r"(flag) : "memory");
        break;
    }
}

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
extern f32 D_006161C0[4];
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
