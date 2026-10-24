/* The field's text (fldtext.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/pieces/D_002BBAA0.h"

/* func_0010ed20 (from hand/nostrict/text_00100000_s10_w4.c). */
typedef struct {
    s32 x0; s32 x4; s16 x8; s16 xa; s16 xc; s16 xe;
    u8 x10; u8 x11; u8 x12; u8 x13; s32 x14; f32 x18; s32 x1c; s32 x20; s32 x24; s32 x28;
} TObj;
extern s32 func_00106b18(void *);
extern void func_0010e4f0(TObj *);
/* func_0010ed20: the fix was s32 func_00106b18(void *) (call sets v0 -> sb of v0 sinks in sched2) plus a hill-climbed store order. */
void func_0010ed20(s32 x, s32 y, s32 n, s32 p, TObj *o) {
    o->x10 = 1;
    o->xa = y;
    o->x4 = p;
    o->x13 |= 2;
    o->x12 = 0;
    o->x0 = 0;
    o->x14 = 0;
    o->x24 = 0;
    o->x11 = 0;
    o->x8 = x;
    o->xe = 0;
    o->xc = x + 94;
    o->x1c = 0;
    o->x20 = 0;
    o->x28 = 0;
    o->x18 = (f32)n;
    func_00106b18(D_002BBAA0);
    func_0010e4f0(o);
}

