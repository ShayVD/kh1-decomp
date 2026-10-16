/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK func_0011f090(s32, s32, s32);
M2C_UNK func_001247e8(s32);
M2C_UNK func_001358b8(s32, M2C_UNK);
M2C_UNK func_00137318();
M2C_UNK func_00146b90(void *, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0014cb90(s32);
M2C_UNK func_0014cce0();
M2C_UNK func_0014f658(s32, M2C_UNK);
M2C_UNK func_00150af0();
M2C_UNK func_00152538();
M2C_UNK func_001525f0(s32);
M2C_UNK func_00152648(s32);
M2C_UNK func_00155760(s32);
M2C_UNK func_001575b0(s8);
M2C_UNK func_00157910();
M2C_UNK func_001586a8(M2C_UNK);
M2C_UNK func_0015d1d0();
M2C_UNK func_00216180();
M2C_UNK func_00232ad0(M2C_UNK);
extern f32 D_002BBDFC;
extern s32 D_00304BE8;
extern s32 D_00551600;
extern s32 D_00559DB0;
extern s32 D_0055BDE0;
s32 func_001320a8();
s32 func_0013db30();
s32 func_00155a90();
s32 func_00158c78();
s64 *func_00156628();

void func_00150660(void) {
    func_00137318();
}

s32 func_00150cb8(void) {
    func_00150af0();
    return 0;
}

void func_00151b90(void) {

}

void func_001520c0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x144);
    M2C_FIELD(temp_v1, f32 *, 8) = (f32) (M2C_FIELD(temp_v1, f32 *, 8) + D_002BBDFC);
}

void func_001524b0(void) {
    func_00137318();
}

void func_00152730(s32 arg0) {
    func_00152538();
    func_001525f0(arg0);
    func_00152648(arg0);
    func_001586a8(0x11);
    func_001247e8(arg0);
}

s32 func_00153d78(Actor *arg0) {
    return arg0->unk088 & 0x30;
}

void func_00155730(void *arg0) {
    func_00146b90(arg0 + M2C_FIELD(arg0, s32 *, 0x1C), -6, 0, 0);
}

void func_001557b0(void) {
    func_00155760(func_001320a8());
}

void func_00156678(void) {
    s64 *temp_v0;

    temp_v0 = func_00156628();
    *temp_v0 |= 0x10000;
}

void func_00156c18(s32 arg0) {
    D_00551600 = arg0;
}

s32 func_001573d8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(M2C_UNK), 0x48)(-1);
    return 4;
}

void func_00157648(void *arg0) {
    func_001575b0(M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s8 *, 0xBD));
}

void func_00157a00(s32 arg0) {
    func_00157910();
    func_001358b8(arg0, 0x23);
}

u16 func_001586d8(s32 arg0) {
    return M2C_FIELD(((arg0 * 2) + D_00304BE8), u16 *, 0x848);
}

s32 func_00158d30(void) {
    s32 var_s0;

    var_s0 = 0;
    if (func_00158c78() != 0) {
        var_s0 = func_00155a90() == 0;
    }
    return var_s0;
}

void func_00159148(s32 arg0) {
    func_0014cce0();
    func_0014f658(arg0, 0x1F);
}

void func_0015a3d8(s32 arg0) {
    if (func_0013db30() != 0) {
        func_0014cb90(arg0);
    }
}

s32 func_0015d540(void) {
    func_0015d1d0();
    return 0;
}

void func_0015ed80(s32 arg0, s32 arg1) {
    func_0011f090(D_00559DB0, arg0, arg1);
}

void func_0015ee78(s32 arg0, s32 arg1) {
    func_0011f090(D_0055BDE0, arg0, arg1);
}

void func_0015f010(void) {

}

void func_0015f108(void) {
    func_00232ad0(6);
    func_00216180();
}
