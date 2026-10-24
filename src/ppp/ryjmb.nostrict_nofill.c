/* The pppRyjMegaBirth class's two functions that match only without
 * delay-slot filling (-fno-strict-aliasing, no_fill; docs/modules.md "Session
 * 50"): func_0019c838 moves one particle (spin, size, speed, gravity, fade
 * in / out), func_0019d020 builds a particle's draw matrix by the key's mode
 * (inline VU0).  The rest of the class is in ryjmb.c and ryjmb.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
typedef struct {
    u8 pad[8];
    u8 r, g, b, a;
} DColWork;
extern PppMtx D_00616040;

typedef struct {
    PppVec4 pos;   /* +0x00 */
    PppVec4 vel;   /* +0x10 */
    u16 time;      /* +0x20 */
    u16 cur;       /* +0x22 */
    u16 prev;      /* +0x24 */
    u16 live;      /* +0x26 */
    u8 pad28[4];
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
    u8 pad0[0x22];
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
    u8 bCA, bCB;
    u8 padCC[2];
    u8 bCE;
} MegaKey;
typedef struct {
    PppMtx m;
    PppVec4 v;
} MegaObj;

void func_0019c838(MegaObj *w, MegaKey *key, MegaPart *pt, DColWork *c, f32 *b) {
    s32 a = c->a;
    f32 t;

    if (b) {
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
    pt->ang += pt->angv;
    if (key->bCB & 0x10)
        pt->angv += key->angv + pt->anga;
    else
        pt->angv += key->angv;
    while (pt->ang >= 180.0f)
        pt->ang -= 360.0f;
    while (pt->ang < -180.0f)
        pt->ang += 360.0f;
    pt->sx += pt->svx;
    pt->sy += pt->svy;
    if (key->bCA & 0x10) {
        pt->svx += key->svx + pt->sax;
        pt->svy += key->svy + pt->say;
    } else {
        pt->svx += key->svx;
        pt->svy += key->svy;
    }
    pt->spd += key->spda;
    if (!key->bCE) {
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
        : : "r"(pt->pos), "r"(pt->vel), "r"(&pt->spd), "r"(w->v), "r"(&pt->grav)
        : "$8", "$9", "memory");
    if (key->h22)
        pt->live--;
    pt->n++;
    if (pt->fin && pt->n <= pt->fin)
        pt->alpha -= (f32) a / (f32) pt->fin;
    if (pt->fout && pt->fout >= pt->live)
        pt->alpha += (f32) a / (f32) key->b25;
}

/* func_0019d020 (from text_00190000_c06.c). */
extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
#include "data/pieces/D_003701F0.h"

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
    PlatVu0UnitMatrix(m);
    m[0][0] = k->sx * D_003701F0[0];
    m[1][1] = k->sy * D_003701F0[1];
    m[2][2] = k->sx * D_003701F0[0];
    if (k->rot != 0.0f) {
        PlatVu0RotMatrixZ(m, m, k->rot * 3.141592562f / 180.0f);
    }
    PlatVu0AddVector(m[3], m[3], k->pos);
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
