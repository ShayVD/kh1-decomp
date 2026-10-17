/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_00121eb0(s32);
M2C_UNK func_002673b8(void *, void *);
M2C_UNK func_00267518(s32, s32, void *);
M2C_UNK func_00267560(void *, void *, f32);
M2C_UNK func_002675a8(s32, M2C_UNK *);
M2C_UNK func_00267e40(s32, s32);
extern M2C_UNK D_002C58A0;
extern M2C_UNK D_0054F750;
extern M2C_UNK D_0054F970;
f32 func_0015ca50(void *);
s32 func_00130398(s32, s32, f32);
s32 func_00147ed8(s32, s32, s32, s32);
void func_001247e8(s32);
void func_001315c0(s32, s32, s32, f32);
void func_00137418(s32, f32);
void func_00152730(s32);
void func_00152770(s32);

s32 func_00150bf8(s32 arg0) {
    return func_00130398(arg0, 0xBF, 0.0f);
}

void func_00150d70(void) {
    s8 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s0 = &D_0054F750;
    var_s1 = 7;
    do {
        temp_a0 = M2C_FIELD(var_s0, s32 *, 4);
        var_s1 -= 1;
        if ((temp_a0 != 0) && (M2C_FIELD(var_s0, s32 *, 0) == 0)) {
            func_00137418(temp_a0, 12.0f);
            M2C_FIELD(M2C_FIELD(var_s0, s32 *, 4), s32 *, 0x144) = 0;
            M2C_FIELD(var_s0, s32 *, 4) = 0;
        }
        var_s0 += 0x40;
    } while (var_s1 >= 0);
}

void func_001523e8(s32 arg0, s32 arg1) {
    func_002675a8(arg1, &D_002C58A0);
}

void func_00152880(Actor *arg0) {
    s32 sp[4];
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0xCB) {
        func_00152770(arg0);
        return;
    }
    func_001315c0(arg0, 0x8003, (s32) sp, 0.0f);
    func_00147ed8(arg0->unk068, 0, 0x4E20, (s32) sp);
    func_00152730(arg0);
}

s32 func_00156188(void) {
    func_0011f130(&D_0054F970, 0);
    return 0;
}

void func_0015ac30(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x3C0) = (f32) (M2C_FIELD(arg0, f32 *, 0x30) * 4.0f);
    M2C_FIELD(arg0, f32 *, 0x3C8) = (f32) (M2C_FIELD(arg0, f32 *, 0x38) * 4.0f);
}

s32 func_0015ace0(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 == -2) {
        func_00121eb0(M2C_FIELD(arg0, s32 *, 0x144));
    }
    return 0;
}

void func_0015cac0(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 sp[4];
    M2C_FIELD(sp, f32 *, 0x4) = 0.0f;
    M2C_FIELD(sp, f32 *, 0x8) = M2C_FIELD(arg2, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x0) = -M2C_FIELD(arg2, f32 *, 8);
    func_002673b8(sp, sp);
    func_00267560(sp, sp, M2C_FIELD(arg0, f32 *, 0x2C0));
    M2C_FIELD(sp, f32 *, 0x4) = func_0015ca50(arg0);
    func_00267518(arg3, arg1, sp);
}

void func_0015d518(s32 arg0, s32 arg1) {
    func_002675a8(arg1, &D_002C58A0);
}

s32 func_0015d538(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}

void func_0015e820(s32 arg0) {
    func_00267e40(arg0 + 0x3C0, arg0 + 0x30);
}

s32 func_0015ea38(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}
