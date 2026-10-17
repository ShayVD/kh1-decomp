/* 2w off (any mode): o->p148 pointer for the fb0 test loaded into v1, original v0 (0x144844/48). Tried temps, literal 0.0f, comparison forms, callee-above stubs. */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[0xb0]; f32 fb0; } S148;
typedef struct { u8 pad[0xc]; void *cb; } Ev;
typedef struct {
    u32 flags;
    u8 pad4[0x14 - 4];
    f32 x14;
    u8 pad18[0x148 - 0x18];
    S148 *p148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x310 - 0x154];
    u16 x310;
} O4810;
f32 atan2f(f32, f32);
void func_00105a30(s32, s32, V4f *);
f32 func_00121748(V4f *, V4f *);
void func_00130398(O4810 *, s32, f32);
Ev *func_00130578(O4810 *, s32, f32);
f32 func_00144378(O4810 *);
void func_0014f658(O4810 *, s32);
void func_001447a0();
s32 func_00144810(O4810 *o, V4f *v) {
    V4f t;
    f32 z = 0.0f;
    u16 id;
    f32 d;
    if (v->w == z) goto r0;
    if (o->p148->fb0 > z) return 0;
    id = o->x310;
    if (id == 0xffff) {
r0:
        return 0;
    }
    d = func_00144378(o);
    if (fabsf(d) > 5.0f) return 0;
    func_00105a30(-1, id, &t);
    if (func_00121748(&t, v) > -0.7f) return 0;
    o->x14 -= d;
    o->x150 = atan2f(-t.x, -t.z);
    func_00130398(o, 0x1000031, 8.0f);
    func_00130578(o, 0x40000006, z)->cb = func_001447a0;
    func_0014f658(o, 16);
    return 1;
}
