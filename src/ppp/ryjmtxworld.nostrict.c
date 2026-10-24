/* The ppp matrix classes' -fno-strict-aliasing frames (docs/modules.md
 * "Session 50"): pppRyjMatrixWorld (and its XZY / YXZ / YZX / ZXY / ZYX
 * rotation orders, pppmtx.c) builds the owner's matrix from the work area's
 * position, rotation and scale times the parent matrix; pppRyjMatrixNoRot
 * and pppRyjDrawMatrixWorldNoRot take only the position.  ryjmtxworld.c has
 * the Cons and the other DrawMatrixWorld classes.  Read from the code, not
 * proved by a boot. */

/* pppRyjDrawMatrixWorldNoRotFrame (from hand/nostrict/text_00180000_h40.c). */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h40.h"
#include "data/pieces/D_003701F0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef kh1_u128 u128;
typedef union {
    f32 f[4];
    u128 q;
} PppQv;
extern PppQv D_00616040[4];
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
extern PppMtx D_00615EB0;
void pppRyjDrawMatrixWorldNoRotFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    f32 *w = PPP_WORK(f32, obj, e, 1);

    PlatVu0UnitMatrix(m);
    m[3][0] = w[0];
    m[3][1] = w[1];
    m[3][2] = w[2];
    PlatVu0MulMatrix(m, D_00615EB0, m);
    PlatVu0ScaleVector(D_00615E68->m2[0], D_00615E68->m[0], w[4]);
    PlatVu0ScaleVector(D_00615E68->m2[1], D_00615E68->m[1], w[5]);
    PlatVu0ScaleVector(D_00615E68->m2[2], D_00615E68->m[2], w[6]);
    PlatVu0MulVector(D_00615E68->m2[3], D_00615E68->m[3], &w[4]);
    D_00615E68->m2[3][0] += m[3][0];
    D_00615E68->m2[3][1] += m[3][1];
    D_00615E68->m2[3][2] += m[3][2];
    PlatVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}

/* pppRyjMatrixWorldFrame (from hand/nostrict/text_00190000_h64.c). */
#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003701E0.h"
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef struct { f32 x, y, z; } PppFVec;
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner_98b50;
void func_00183be0(PppMtx, void *);
static inline void vu0ScaleRow(f32 *row, f32 s) {
#ifdef KH1_PS2
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
#else
    PlatVu0ScaleXYZ(row, s);
#endif
}
#define D_00615E68 ((PppMtxOwner_98b50 *) D_00615E68)
void pppRyjMatrixWorldFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_00183be0(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_00183be0(m, &D_003701E0);
    m[3][0] = (*(f32 (*)[4])&D_003701D0)[0];
    m[3][1] = (*(f32 (*)[4])&D_003701D0)[1];
    m[3][2] = (*(f32 (*)[4])&D_003701D0)[2];
    PlatVu0InversMatrix(m, m);
    PlatVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    PlatVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}
#undef D_00615E68

/* pppRyjMatrixWorldXZYFrame (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner_98d20;
void func_001a5250(PppMtx, void *);
#define D_00615E68 ((PppMtxOwner_98d20 *) D_00615E68)
void pppRyjMatrixWorldXZYFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5250(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5250(m, &D_003701E0);
    m[3][0] = (*(f32 (*)[4])&D_003701D0)[0];
    m[3][1] = (*(f32 (*)[4])&D_003701D0)[1];
    m[3][2] = (*(f32 (*)[4])&D_003701D0)[2];
    PlatVu0InversMatrix(m, m);
    PlatVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    PlatVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}
#undef D_00615E68

/* pppRyjMatrixWorldYXZFrame (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner_98ef0;
void func_001a5370(PppMtx, void *);
#define D_00615E68 ((PppMtxOwner_98ef0 *) D_00615E68)
void pppRyjMatrixWorldYXZFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5370(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5370(m, &D_003701E0);
    m[3][0] = (*(f32 (*)[4])&D_003701D0)[0];
    m[3][1] = (*(f32 (*)[4])&D_003701D0)[1];
    m[3][2] = (*(f32 (*)[4])&D_003701D0)[2];
    PlatVu0InversMatrix(m, m);
    PlatVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    PlatVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}
#undef D_00615E68

/* pppRyjMatrixWorldYZXFrame (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner_990c0;
void func_001a52e0(PppMtx, void *);
#define D_00615E68 ((PppMtxOwner_990c0 *) D_00615E68)
void pppRyjMatrixWorldYZXFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a52e0(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a52e0(m, &D_003701E0);
    m[3][0] = (*(f32 (*)[4])&D_003701D0)[0];
    m[3][1] = (*(f32 (*)[4])&D_003701D0)[1];
    m[3][2] = (*(f32 (*)[4])&D_003701D0)[2];
    PlatVu0InversMatrix(m, m);
    PlatVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    PlatVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}
#undef D_00615E68

/* pppRyjMatrixWorldZXYFrame (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner_99290;
void func_001a5400(PppMtx, void *);
#define D_00615E68 ((PppMtxOwner_99290 *) D_00615E68)
void pppRyjMatrixWorldZXYFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5400(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5400(m, &D_003701E0);
    m[3][0] = (*(f32 (*)[4])&D_003701D0)[0];
    m[3][1] = (*(f32 (*)[4])&D_003701D0)[1];
    m[3][2] = (*(f32 (*)[4])&D_003701D0)[2];
    PlatVu0InversMatrix(m, m);
    PlatVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    PlatVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}
#undef D_00615E68

/* pppRyjMatrixWorldZYXFrame (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner_99460;
void func_001a5490(PppMtx, void *);
#define D_00615E68 ((PppMtxOwner_99460 *) D_00615E68)
void pppRyjMatrixWorldZYXFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5490(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5490(m, &D_003701E0);
    m[3][0] = (*(f32 (*)[4])&D_003701D0)[0];
    m[3][1] = (*(f32 (*)[4])&D_003701D0)[1];
    m[3][2] = (*(f32 (*)[4])&D_003701D0)[2];
    PlatVu0InversMatrix(m, m);
    PlatVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    PlatVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}
#undef D_00615E68

/* pppRyjMatrixNoRotFrame (from hand/nostrict/text_00180000_h40.c). */
void pppRyjMatrixNoRotFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    PlatVu0InversMatrix(D_00615E68->m, D_00615EB0);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003727B0.h"
