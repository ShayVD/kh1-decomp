/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00108180(s32);
M2C_UNK func_001081a0(s32);
M2C_UNK func_00122768(s32);
M2C_UNK func_001386f8(s32);
M2C_UNK func_0016f548();
M2C_UNK func_001759c0();
M2C_UNK func_001759e8();
M2C_UNK func_00175be0(M2C_UNK *, s32, s32, s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00175da8(M2C_UNK *, s32);
M2C_UNK func_00175e38(M2C_UNK *);
M2C_UNK func_00175ec8(M2C_UNK *);
M2C_UNK func_00175f10(M2C_UNK *);
M2C_UNK func_00176c60(M2C_UNK);
M2C_UNK func_00176cc8(M2C_UNK);
M2C_UNK func_001784c8();
M2C_UNK func_0017f178();
M2C_UNK func_0017f910();
M2C_UNK func_0017f9d8();
M2C_UNK func_0017fa68();
M2C_UNK func_0017faa8();
M2C_UNK func_0017fb98();
M2C_UNK func_0017fc48();
M2C_UNK func_0017fd88();
M2C_UNK func_0017fe60();
M2C_UNK func_0017ff98();
M2C_UNK func_001a9e70();
M2C_UNK func_001a9eb8();
M2C_UNK func_001a9f88();
M2C_UNK func_001aa858();
M2C_UNK func_00267370(s32, s32, s32);
M2C_UNK func_00267530(void *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_002675a8(s32, s32);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_0035C710;
extern M2C_UNK D_0035E710;
extern M2C_UNK D_0035FB20;
extern M2C_UNK D_00360F30;
extern M2C_UNK D_00362660;
extern M2C_UNK D_00575010; /* src/data/bss_0057.c: s32 D_00575010 */
extern M2C_UNK D_005757B0; /* src/data/bss_0057.c: T44 D_005757B0[0x2] */
extern M2C_UNK D_005758D0; /* src/data/bss_0057.c: f32 D_005758D0[4] */
extern M2C_UNK D_005758E0; /* src/data/bss_0057.c: f32 D_005758E0[4] */
extern M2C_UNK D_005759B0;
extern f32 D_00362680;
extern s32 D_00575310; /* src/data/bss_0057.c: TalkEA D_00575310 */
f32 acosf(f32);
f32 func_00120c18(void *);
s32 func_001770b8();

void func_00170e98(void) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s0 = &D_00575310;
    var_s1 = 2;
    do {
        temp_a0 = *var_s0;
        var_s1 -= 1;
        if (temp_a0 != 0) {
            func_00122768(temp_a0);
            *var_s0 = 0;
        }
        var_s0 += 2;
    } while (var_s1 >= 0);
    func_0016f548();
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 0));
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 4));
}

void func_00175a20(void) {
    memset(&D_0035C710, 0, 0x2000);
}

void func_00175f58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(&D_0035E710, arg0, arg1, arg2, arg3, -1, 1);
}

void func_00176110(s32 arg0) {
    func_00175da8(&D_0035E710, arg0);
}

void func_00176130(s32 arg0) {
    func_00175da8(&D_0035FB20, arg0);
}

void func_00176150(s32 arg0) {
    func_00175da8(&D_00360F30, arg0);
}

void func_00176170(void) {
    func_00175e38(&D_0035E710);
    func_001759c0();
}

void func_00176190(void) {
    func_00175e38(&D_0035FB20);
    func_001759e8();
}

void func_001761f0(void) {
    func_00175ec8(&D_0035E710);
}

void func_00176210(void) {
    func_00175ec8(&D_0035FB20);
}

void func_00176230(void) {
    func_00175ec8(&D_00360F30);
}

void func_00176250(void) {
    func_00175f10(&D_0035E710);
}

void func_00176270(void) {
    func_00175f10(&D_0035FB20);
}

void func_00176290(void) {
    func_00175f10(&D_00360F30);
}

void func_001762b0(void) {
    func_0017f910();
}

void func_001762c8(void) {
    func_0017f9d8();
}

void func_001762e0(void) {
    func_0017fa68();
}

void func_001762f8(void) {
    func_0017faa8();
}

void func_00176310(void) {
    func_0017fb98();
}

void func_00176328(void) {
    func_0017fc48();
}

void func_00176358(void) {
    func_0017fd88();
}

void func_00176370(void) {
    func_0017fe60();
}

void func_001765f8(void) {
    func_0017ff98();
}

u16 func_00176610(void *arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), void **, 0x8C), u16 *, 0xFC);
}

void func_00176920(void *arg0) {
    func_002675a8(M2C_FIELD(arg0, s32 *, 4), *M2C_FIELD(arg0, s32 **, 0));
}

void func_00176940(void *arg0) {
    func_002675a8(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 8));
}

void func_001769f0(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    func_00267370(temp_v0, temp_v0, M2C_FIELD(arg0, s32 *, 4));
}

void func_00176aa0(void *arg0) {
    M2C_FIELD(&D_00362660, f32 *, 0) = (f32) ((M2C_FIELD(arg0, f32 *, 0) * 3.141592503f) / 180.0f);
    M2C_FIELD(&D_00362660, f32 *, 0xC) = (f32) M2C_FIELD(arg0, f32 *, 4);
    func_0017f178();
}

void func_00176b20(f32 *arg0) {
    *arg0 = acosf(*arg0);
}

void func_00176b50(s32 *arg0) {
    func_00108180(*arg0);
}

void func_00176b68(s32 *arg0) {
    func_001081a0(*arg0);
}

void func_00176ea8(void) {
    memset(&D_005757B0, 0, 0x58);
    func_00176c60(0);
    func_00176c60(1);
}

s32 func_00176ee0(void) {
    func_00176cc8(0);
    func_00176cc8(1);
    return 0;
}

void func_00178d90(void) {
    s32 sp[4];
    func_00267530(sp, &D_005758D0, &D_005758E0);
    if ((func_00120c18(sp) < 40.0f) && (D_00362680 < 1.0471975f) && (func_001770b8() != 0)) {
        func_001784c8();
    }
}

void func_0017dee0(void) {
    memset(&D_005759B0, 0, 0x50);
}

void func_0017f9a8(void) {
    func_001a9e70();
    func_001a9eb8();
    func_001a9f88();
    func_001aa858();
}
