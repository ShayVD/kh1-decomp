/* 4w off: nostrict. Regs right; original schedules ld v1,880(s0)/lw a0 before li v0,0x8000/dsll. Bitfield form (b35=1) keeps order but swaps v0/v1 (5w). */
#include "common.h"
typedef union { u64 x; struct { u32 lo; u32 x32:3; u32 b35:1; u32 hi:28; } b; } F370d;
typedef struct { u32 f0; u8 p4[0xd0-4]; u8 fd0[0x154-0xd0]; s32 f154; u8 p158[0x370-0x158]; F370d f370; } Ob8;
extern u32 D_002BC0A8;
extern void func_00135df0(Ob8 *, f32 *);
extern void func_00114a38(void *, s32, s32, f32 *);
extern void func_00128218(Ob8 *, f32);
void func_001369e8(Ob8 *o) {
    f32 v[4];
    s32 i;
    if (!(o->f0 & 1)) return;
    if (!(D_002BC0A8 & 1)) return;
    func_00135df0(o, v);
    for (i = 0; i < 4; i++) v[i] *= 0.0078125f;
    func_00114a38(o->fd0, o->f154, v[3] < 1.0f ? 0xc35a : 0x9c40, v);
    { u64 m = 0x800000000ULL; o->f370.x |= m; }
    if (o->f0 & 2) func_00128218(o, 1.0f);
}
