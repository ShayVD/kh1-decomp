/* The ppp wind classes and two empty classes, default flags
 * (docs/modules.md "Session 50"): pppEiWindFun keeps a wind direction (the
 * key's x / y, normalized) and a strength with speed and acceleration;
 * pppDrawShapeField and pppDrawMdlSea have empty draws, Cons and Dess.
 * pppEiWfacc is in eiwind.nostrict.c.  Read from the code, not proved by a
 * boot. */
#include "common.h"
#ifndef KH1_PS2
#include "platform/vu.h"
#endif
#include "data/pieces/D_00364130.h"
#include "ppp.h"
#include "data/types/text_00180000_h12.h"
#include "data/types/shared.h"
#include "data/types/text_00180000_h40.h"
#include "m2c.h"
#include "data/pieces/D_00370130.h"

/* pppEiWindFunCon (from hand/text_00180000_h12.c). */
typedef union {
    f32 f;
    s32 i;
} PppWord;
typedef struct {
    s32 pad[3];
    PppWord w0;  /* +0x0C */
    s32 w1;      /* +0x10 */
    s32 pad2;
    f32 a, b, c; /* +0x18 */
} PppWind;
void pppEiWindFunCon(void *obj, PppEntry *e) {
    PppWind *w = (PppWind *) ((u8 *) obj + e->offsets[0] + 0xA0);

    w->w0.i = 0;
    w->w1 = 0;
    w->a = w->b = w->c = w->w0.f;
}

/* pppEiWindFunFrame (from hand/text_00180000_h40.c). */
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
extern PppSystem *D_00615E60;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef struct { f32 a, b, c; } PppV12;
typedef struct {
    s32 frame;
    PppV12 v;    /* +0x4 */
    f32 x, y;    /* +0x10 */
    f32 d[3];    /* +0x18 */
} PppWindKey;
typedef struct {
    PppV12 v;
    f32 x, y;    /* +0xC */
    f32 r;       /* +0x14 */
    f32 d[3];    /* +0x18 */
} PppWindWork;
static inline f32 vu0Sqrt(f32 x) {
    f32 r;
#ifdef KH1_PS2
    __asm__ volatile(
        "mfc1 $2, %1\n"
        "qmtc2 $2, $vf2\n"
        "vsqrt Q, $vf2x\n"
        "vwaitq\n"
        "vaddq.x $vf2x, $vf0x, Q\n"
        "qmfc2 $2, $vf2\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "f"(x) : "$2");
#else
    r = PlatVu0Sqrt(x);
#endif
    return r;
}
void pppEiWindFunFrame(PppObject *obj, PppWindKey *key, PppEntry *e) {
    PppWindWork *w = PPP_WORK(PppWindWork, obj, e, 0);
    f32 x, y;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->d[1] += w->d[2];
        w->d[0] += w->d[1];
    }
    if (key->frame != obj->frame)
        return;
    w->v = key->v;
    w->x = x = key->x;
    w->y = y = key->y;
    w->r = x / vu0Sqrt(x * x + y * y);
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->d[0] += key->d[0];
        w->d[1] += key->d[1];
        w->d[2] += key->d[2];
    }
}
#undef PPP_WORK

/* pppDrawShapeFieldDraw (from auto/text_00180000.c). */
void pppDrawShapeFieldDraw(void) {

}

/* pppDrawShapeFieldCon (from auto/text_00180000.c). */
void pppDrawShapeFieldCon(void) {

}

/* pppDrawShapeFieldDes (from auto/text_00180000.c). */
void pppDrawShapeFieldDes(void) {

}

/* pppDrawMdlSeaDraw (from auto/text_00180000.c). */
void pppDrawMdlSeaDraw(void) {

}

/* pppDrawMdlSeaCon (from auto/text_00180000.c). */
void pppDrawMdlSeaCon(void) {

}

/* pppDrawMdlSeaDes (from auto/text_00180000.c). */
void pppDrawMdlSeaDes(void) {

}

