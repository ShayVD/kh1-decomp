/* pppKeShpDttDraw, -fno-strict-aliasing (docs/modules.md "Session 50"):
 * draws a shape's sprites as projected fans (keshpdtt.nostrict.c's
 * func_001a99e8 sets the batch up, func_001a9c30 writes each point's
 * packet, opdma.c's func_001aa6b0 / func_001aa750 send them).  Separate from
 * keshpdtt.nostrict.c because its prototypes of those helpers differ from
 * their definitions.  Read from the code, not proved by a boot. */

/* pppKeShpDttDraw (from hand/nostrict/text_00180000_b07.c). */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
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
extern s32 D_00616224;
void func_001aa6b0(void *, s32, s32, s32);
typedef struct {
    s32 frame;
    f32 d[3];     /* +0x4 */
    f32 sx, sy;   /* +0x10 */
    u8 mode;      /* +0x18 */
    u8 flags;     /* +0x19 */
} PppDttKey;
typedef struct {
    PppVec4 v;        /* +0x00 */
    f32 col[4];       /* +0x10 */
    void *p20;        /* +0x20 */
    u8 *p24;          /* +0x24 */
    void *p28;        /* +0x28 */
    s32 x2C;          /* +0x2C */
    PppVec4 pos;      /* +0x30 */
    u64 tag0;         /* +0x40 */
    u64 tag1;         /* +0x48 */
    u64 tag2;         /* +0x50 */
    f32 sx, sy;       /* +0x58 */
} PppDttDraw;
typedef unsigned int u128 __attribute__((mode(TI)));
extern u8 D_00616040[];
extern s32 D_00616228;
void func_001a99e8(PppDttDraw *);
s32 func_001a9c30(PppDttDraw *);
void func_001aa750(void *, u32, s32, s32);
/* --- pppKeShpDttDraw --- */
void pppKeShpDttDraw(PppObject *obj, PppDttKey *key, PppEntry *e) {
    u8 *w2 = PPP_WORK(u8, obj, e, 2);
    f32 *w0 = PPP_WORK(f32, obj, e, 0);
    u8 *w1;
    PppDttDraw d;
    PppSystem **ps = &D_00615E60;

    if (D_0061621C == 0 && !((*ps)->flags & 0xFF0000FF00ULL)) {
        w0[1] += w0[2];
        w0[0] += w0[1];
        if (obj->frame == key->frame) {
            w0[0] += key->d[0];
            w0[1] += key->d[1];
            w0[2] += key->d[2];
        }
    }
    w1 = PPP_WORK(u8, obj, e, 1);
    d.col[0] = w1[8];
    d.col[1] = w1[9];
    d.col[2] = w1[10];
    d.col[3] = w1[11];
    if (key->flags & 2) {
        f32 *w3 = PPP_WORK(f32, obj, e, 3);
        d.v[0] = w3[0];
        d.v[1] = w3[1];
        d.v[2] = 512.0f;
        d.v[3] = 1.0f;
        d.p28 = D_00616040;
    } else {
        *(u128 *) d.v = *(u128 *) (w2 + 48);
        d.p28 = D_00616040;
    }
    d.p20 = D_00616040;
    d.p24 = (u8 *) D_00616224 + 16;
    d.sx = key->sx * D_003701F0[0];
    d.sy = key->sy * D_003701F0[1];
    if (key->mode == 0) {
        d.tag0 = 0x2A8021A00ULL;
        d.tag2 = 0x740000007000ULL;
    } else {
        d.tag0 = 0x2A8020000ULL;
        d.tag2 = 0x720000007000ULL;
    }
    d.tag1 = 0x017F000001FF0000ULL;
    d.pos[0] = d.pos[1] = d.pos[2] = d.pos[3] = 0.0f;
    d.pos[1] = -w0[0];
    PlatVu0ApplyMatrix(d.pos, w2, d.pos);
    *(s32 *) &d.pos[3] = key->flags;
    func_001a99e8(&d);
    if (func_001a9c30(&d)) {
        if (key->flags & 2)
            func_001aa6b0((void *) D_00616224, (u32) (d.p24 - (u8 *) D_00616224) >> 4, 4, 0);
        else
            func_001aa750((void *) D_00616224, (u32) (d.p24 - (u8 *) D_00616224) >> 4, d.x2C / 0x3000, 0);
        D_00616228 += d.p24 - (u8 *) D_00616224;
        D_00616224 = (s32) d.p24;
    }
}
#undef PPP_WORK

