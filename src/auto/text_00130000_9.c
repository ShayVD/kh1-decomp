/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00132220(s32, s32);
M2C_UNK func_00132790(s32, M2C_UNK, M2C_UNK *);
M2C_UNK func_001452a0(void *);
M2C_UNK func_00267560(void *, void *, f32);
M2C_UNK func_002675a8(void *, M2C_UNK *);
extern M2C_UNK (*D_00525364)(s32);
#include "data/pieces/D_002C58A0.h"
extern M2C_UNK D_00350D94;
extern M2C_UNK D_00525328;
f32 func_001216d8(f32, f32, f32);
f32 func_00137688(void *, f32);

void func_00132240(void *arg0) {
    func_00132220(M2C_FIELD(arg0, s32 *, 0x15C), M2C_FIELD(arg0, s32 *, 0x1D0));
}

void func_00132e78(s32 arg0, s32 arg1, s32 arg2) {
    func_00132790(arg2, 0, &D_00525328);
    if (D_00525364 != NULL) {
        D_00525364(arg0);
    }
}

void func_0013e558(void *arg0) {
    M2C_UNK (*temp_v0)();

    temp_v0 = *(M2C_UNK *)((s8 *)(s8 *)&D_00350D94 + (M2C_FIELD(arg0, s32 *, 0x70) << 5));
    if (temp_v0 != NULL) {
        temp_v0();
    }
    if (M2C_FIELD(arg0, s32 *, 0x70) == 4) {
        func_002675a8(arg0 + 0x3C0, ((M2C_UNK *)&D_002C58A0));
        func_002675a8(arg0 + 0x20, ((M2C_UNK *)&D_002C58A0));
    }
    func_00137688(arg0, func_001216d8(M2C_FIELD(arg0, f32 *, 0x3C), M2C_FIELD(arg0, f32 *, 0x150), M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xCC)));
    if ((M2C_FIELD(arg0, s32 *, 0) & 0x400) && (M2C_FIELD(arg0, s32 *, 0x70) == 2)) {
        func_00267560(arg0 + 0x3C0, arg0 + 0x20, M2C_FIELD(arg0, f32 *, 0x2C));
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & ~0x800);
    func_001452a0(arg0);
}
#include "data/pieces/D_00350D94.h"
