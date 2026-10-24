/* Object class 0x0F, default flags (docs/modules.md "Session 52"): the
 * handlers func_0015d560 registers in the class table D_00350D88
 * (func_0014f830(0x0F, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class0f.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58A0.h"
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8.h"

/* func_0015ca50 (from auto/text_00150000_3.c). */
extern M2C_UNK D_00351B60;
f32 func_0015ca50(void *arg0) {
    return *(f32 *)((s8 *)&D_00351B60 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4));
}

/* func_0015ca70 (from auto/text_00150000_3.c). */
extern M2C_UNK D_00351B88;
f32 func_0015ca70(void *arg0) {
    return *(f32 *)((s8 *)&D_00351B88 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4));
}

/* func_0015ca90 (from auto/text_00150000_2.c). */
void func_0015ca90(s32 *arg0) {
    *arg0 |= 0x200000;
}

/* func_0015caa8 (from auto/text_00150000_3.c). */
void func_0015caa8(s32 *arg0) {
    *arg0 &= 0xFFDFFFFF;
}

/* func_0015cac0 (from auto/text_00150000_16.c). */
void func_0015cac0(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 sp[4];
    M2C_FIELD(sp, f32 *, 0x4) = 0.0f;
    M2C_FIELD(sp, f32 *, 0x8) = M2C_FIELD(arg2, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x0) = -M2C_FIELD(arg2, f32 *, 8);
    PlatVu0Normalize(sp, sp);
    PlatVu0ScaleVector(sp, sp, M2C_FIELD(arg0, f32 *, 0x2C0));
    M2C_FIELD(sp, f32 *, 0x4) = func_0015ca50(arg0);
    PlatVu0AddVector(arg3, arg1, sp);
}

/* func_0015d1d0 (from hand/text_00150000_h10.c). */
void func_00130398(void *, s32, f32);
void func_0014cc88(void *, f32);
typedef struct { u32 flags; u8 pad[0x2C]; f32 pos[4]; } ObjD1;
void func_0015d1d0(ObjD1 *a, f32 *v) {
    PlatVu0SubVector(v, (*(f32 (*)[0x4])&D_002C58A0), a->pos);
    v[3] = 0.0f;
    func_0014cc88(a, v[3]);
    a->flags |= 0x10000;
    func_00130398(a, 0x40000006, 16.0f);
}

/* func_0015d248 (from hand/text_00150000_h10.c). */
extern f32 D_002BBDFC;
typedef struct { u32 flags; u8 pad4[0x1FC]; u8 x200[0x1B0]; f32 f3B0; f32 f3B4; u8 pad3b8[8]; u8 x3C0[4]; } ObjD2;
void func_0015d248(ObjD2 *a) {
    func_0014cc88(a, 0.0f);
    a->flags &= ~0x400;
    a->f3B0 = 6.0f;
    a->f3B4 -= 8.724489212036133f;
    PlatVu0ScaleVector(a->x3C0, a->x200, 1.0f / D_002BBDFC);
}

/* func_0015d4e0 (from auto/text_00150000_3.c). */
void func_0015d4e0(s32 arg0, s32 arg1, void *arg2) {
    M2C_FIELD(arg2, f32 *, 0xC) = 0.0f;
    if (M2C_FIELD(arg2, f32 *, 4) < M2C_FIELD(arg2, f32 *, 0xC)) {
        M2C_FIELD(arg2, f32 *, 4) = -1.0f;
        M2C_FIELD(arg2, f32 *, 0xC) = 1.0f;
    }
}

/* func_0015d518 (from auto/text_00150000_16.c). */
void func_0015d518(s32 arg0, s32 arg1) {
    PlatVu0CopyVector(arg1, ((M2C_UNK *)&D_002C58A0));
}

/* func_0015d538 (from auto/text_00150000_16.c). */
s32 func_0015d538(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}

/* func_0015d540 (from auto/text_00150000.c). */
#define func_0015d1d0 ((M2C_UNK (*)()) func_0015d1d0)
s32 func_0015d540(ObjD1 *a, f32 *v) {
    func_0015d1d0(a, v);
    return 0;
}
#undef func_0015d1d0

/* func_0015d560 (from auto/text_00150000_7.c). */
void func_0015d3b8();
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_0015d560(void) {
    func_0014f830(0xF, 1, &func_0015ca90, &func_0015caa8, &func_0015d3b8, &func_0015d518, &func_0015d538, &func_0015d4e0, &func_0015d540);
}

