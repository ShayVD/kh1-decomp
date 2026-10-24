/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00108180(s32);
M2C_UNK func_001081a0(s32);
M2C_UNK func_00122768(s32);
M2C_UNK func_001386f8(s32);
M2C_UNK func_0016f548();
M2C_UNK func_00176c60(M2C_UNK);
M2C_UNK func_00176cc8(M2C_UNK);
M2C_UNK func_001784c8();
M2C_UNK func_0017f178();
M2C_UNK func_00267370(s32, s32, s32);
M2C_UNK func_00267530(void *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_002675a8(s32, s32);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
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
#include "data/data_0035.h"
#include "data/data_0036.h"
