/* Jump arcs shared by the object classes: func_0014cc88 starts a jump with
 * an upward speed and func_0014cce0 one that reaches a height (gravity
 * 0.48469386 per frame squared), func_0014cdc8 eases a value along the arc,
 * func_0014cb90 a landing. Flag mode: default (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 53"). */
#include "common.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h34.h"
#include "data/pieces/D_002E27C8.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00350D88.h"

/* func_0014cb90 (from hand/text_00140000_h34.c). */
typedef struct { u8 pad[0x100]; f32 x100; u64 f:32; } W34Tm;
s32 func_00130340(void *, s32, f32);
void func_0014f658(void *, s32);
typedef struct { u32 x0; u8 pad4[0x144]; W34Tm *x148; u8 pad14c[0x3b0 - 0x14c]; f32 x3b0; u8 pad3b4[0x3d0 - 0x3b4]; s32 x3d0; } W34Pl3;
s32 func_0014cb90(W34Pl3 *o) {
    s32 r;
    if (o->x0 & 0x2000) o->x3d0 = 171;
    else if ((*(u32 *)&D_002E27C8) >> 9 & 1) o->x3d0 = 5;
    else o->x3d0 = 0;
    r = func_00130340(o, (o->x3d0 + 4) | 0x10000, 0.0f);
    func_0014f658(o, 1);
    o->x3b0 = 0.0f;
    o->x148->x100 = 0.0f;
    return r;
}

/* func_0014cc38 (from auto/text_00140000_4.c). */
#define func_0014f658 ((s32 (*)(s32, s32)) func_0014f658)
void func_0014cc38(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    M2C_FIELD(arg0, s32 *, 0x3D0) = 0;
    M2C_FIELD(arg0, f32 *, 0x3B4) = (f32) M2C_FIELD(arg0, f32 *, 0x14);
    func_0014f658(arg0, 2);
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFFEFFFF);
}
#undef func_0014f658

/* func_0014cc88 (from auto/text_00140000_5.c). */
#define func_0014cc38 ((M2C_UNK (*)()) func_0014cc38)
f32 func_0014cc88(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x3B8) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) (fparg0 * fparg0 * -0.48469386f * 0.5f);
    func_0014cc38(arg0);
    return -M2C_FIELD(arg0, f32 *, 0x3BC);
}
#undef func_0014cc38

/* func_0014cce0 (from auto/text_00140000_15.c). */
f32 PlatSqrtf(f32);
f32 func_0014cce0(s32 arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x3B8) = PlatSqrtf((2.0f * fparg0) / 0.48469386f);
    M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) -fparg0;
    func_0014cc38(arg0);
    return M2C_FIELD(arg0, f32 *, 0x3B8);
}

/* func_0014cd38 (from auto/text_00140000_4.c). */
s32 func_00130578(s32, s32, f32);
#define func_00130340 ((s32 (*)(s32, s32, f32)) func_00130340)
void func_0014cd38(s32 arg0) {
    s32 temp_v0;

    if (!(M2C_FIELD(arg0, f32 *, 0x3B8) <= (M2C_FIELD(arg0, f32 *, 0x3B0) + 6.0f))) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x178) != 0) {
        return;
    }
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x3D0);
    if (M2C_FIELD(arg0, s32 *, 0x164) != (temp_v0 + 4)) {
        return;
    }
    func_00130340(arg0, temp_v0 + 5, 6.0f);
    func_00130578(arg0, M2C_FIELD(arg0, s32 *, 0x3D0) + 6, 0.0f);
}
#undef func_00130340

/* func_0014cdc8 (from hand/text_s7_w3.c). */
typedef struct {
    u8 pad0[0x14];
    f32 x14;
    u8 pad18[0x3b0 - 0x18];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 v3c0[4];
} Pc;
f32 sinf(f32);
extern f32 D_002BBDFC;
static inline f32 mn(f32 x, f32 l) { return x < l ? x : l; }
#define func_0014cd38 ((void (*)(Pc *)) func_0014cd38)
void func_0014cdc8(Pc *o, f32 *v) {
    f32 a;
    f32 b;
    f32 y;

    a = o->x3b0;
    b = o->x3b8;
    if (a < b) {
        a = sinf(a / b * 3.1415928f * 0.5f);
        a = sinf(a * 3.1415928f * 0.5f);
        y = o->x3b4 + a * o->x3bc; v[1] = y - o->x14;
        func_0014cd38(o);
    } else {
        a -= b;
        y = o->x3b4 + o->x3bc + 0.4846938625f * a * a * 0.5f;
        v[1] = mn(y - o->x14, D_002BBDFC * 20.0f);
    }
    o->v3c0[1] = v[1];
}
#undef func_0014cd38

