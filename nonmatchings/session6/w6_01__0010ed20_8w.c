/* func_0010ed20: 8w off, hand/nostrict (same in hand, nogcse). Structure identical; regs only: original keeps x in t0 (move t0,a0), const 1 in v0, the lbu/ori in v1; here x->v1, 1->t0, lbu->v0. Store order, K&R/s16 params, bitfields, callee-above stubs tried. */
#include "common.h"
typedef struct {
    s32 x0; s32 x4; s16 x8; s16 xa; s16 xc; s16 xe;
    u8 x10; u8 x11; u8 x12; u8 x13; s32 x14; f32 x18; s32 x1c; s32 x20; s32 x24; s32 x28;
} TObj;
extern u8 D_002BBAA0[];
extern void func_00106b18();
extern void func_0010e4f0(TObj *);

void func_0010ed20(s32 x, s32 y, s32 n, s32 p, TObj *o) {
    o->xa = y;
    o->x4 = p;
    o->x13 |= 2;
    o->xc = x + 94;
    o->x18 = (f32)n;
    o->x8 = x;
    o->x10 = 1;
    o->x12 = 0;
    o->x0 = 0;
    o->x14 = 0;
    o->x24 = 0;
    o->x11 = 0;
    o->xe = 0;
    o->x1c = 0;
    o->x20 = 0;
    o->x28 = 0;
    func_00106b18(D_002BBAA0);
    func_0010e4f0(o);
}
