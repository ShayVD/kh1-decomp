/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"

extern M2C_UNK D_00623230; /* src/data/bss_0062.c: Ent D_00623230[0xc0] */
extern M2C_UNK D_00623E40;
extern M2C_UNK D_00625750; /* src/data/bss_0062.c: IdCnt D_00625750[0x10] */
extern s32 *D_00623210;
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
extern s32 D_0037A128;
extern s32 D_0037A148;
extern s32 D_0037A150;
extern s32 D_0037A158;
s32 D_00621318 ALIGNED(8);
extern s32 D_00623214;
extern s32 D_00623218;
extern s32 D_00623220;
extern s32 D_00623224;
extern s32 D_00623228;
extern s32 D_00623E30;
extern s32 D_00625748;
extern s32 D_006257D0; /* src/data/bss_0062.c: u8 *D_006257D0 */
f32 func_0026b6f8(f32);
f32 func_0026b7d0(f32);
s32 func_001ba458(s32);
s32 func_001ba9a8();

s32 func_001ba1e0(void) {
    return 0xB040;
}

void func_001ba358(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_s2;
    u8 temp_s1;

    temp_s2 = func_001ba9a8() + arg0;
    temp_s1 = *temp_s2;
    if (func_001ba458(arg0) < (temp_s1 + arg1)) {
        var_v0 = func_001ba458(arg0);
    } else {
        var_v0 = *temp_s2 + arg1;
    }
    *temp_s2 = (u8) var_v0;
}

s32 func_001ba848(void) {
    return 0;
}

f32 func_001ba850(void) {
    return 0.0f;
}

f32 func_001ba860(void) {
    return 0.0f;
}

void func_001ba910(s32 arg0) {
    D_00621318 = arg0;
}

s32 func_001ba920(void) {
    return D_00621318;
}

void func_001bb428(s32 arg0) {
    D_0037A128 = arg0;
}

s32 func_001bb4e0(void) {
    return D_0037A150;
}

s32 func_001bb4f0(void) {
    return D_0037A148 - 0x400;
}

s32 func_001bb720(void) {
    return D_00623214;
}

s32 func_001bb730(void) {
    return D_00623218;
}

s32 func_001bb740(void) {
    return *D_00623210;
}

void func_001bb7b0(s32 arg0) {
    D_00623224 = arg0;
    D_00623220 = 0;
}

s32 func_001bb848(void) {
    return D_00623220;
}

void func_001bb858(s32 arg0, s32 arg1) {
    D_002BC140 = arg0;
    D_002BC144 = arg1;
}

void func_001bb870(s32 arg0) {
    D_006257D0 = arg0;
}

M2C_UNK *func_001bc4d0(void) {
    return &D_00623230;
}

M2C_UNK *func_001bc4e0(void) {
    return &D_00623E40;
}

M2C_UNK *func_001bc4f0(void) {
    return &D_00625750;
}

s32 func_001bc500(void) {
    return D_00623228;
}

s32 func_001bc510(void) {
    return D_00623E30;
}

s32 func_001bc520(void) {
    return D_00625748;
}

s32 func_001be660(void) {
    return D_0037A158;
}

void func_001be670(s32 arg0) {
    D_0037A158 = arg0;
}

void func_001be7d8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x140)(M2C_FIELD(arg0, s32 *, 0x144));
}

s32 func_001be800(u32 arg0, u32 arg1) {
    return arg0 + (arg1 - (arg0 % arg1));
}

void func_001bf098(void *arg0, void *arg1) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) M2C_FIELD(arg1, f32 *, 0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) M2C_FIELD(arg1, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) M2C_FIELD(arg1, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) M2C_FIELD(arg1, f32 *, 0x18);
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) M2C_FIELD(arg1, f32 *, 0x20);
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) M2C_FIELD(arg1, f32 *, 0x24);
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) M2C_FIELD(arg1, f32 *, 0x28);
}

void func_001bf360(void *arg0, void *arg1) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f3;

    temp_f1 = M2C_FIELD(arg1, f32 *, 0);
    temp_f2 = M2C_FIELD(arg1, f32 *, 0xC);
    temp_f3 = M2C_FIELD(arg1, f32 *, 4);
    temp_f0 = M2C_FIELD(arg1, f32 *, 8);
    temp_f2_2 = (temp_f2 * temp_f2) + (temp_f1 * temp_f1) + (temp_f3 * temp_f3) + (temp_f0 * temp_f0);
    M2C_FIELD(arg0, f32 *, 0) = (f32) (-temp_f1 / temp_f2_2);
    M2C_FIELD(arg0, f32 *, 4) = (f32) (-M2C_FIELD(arg1, f32 *, 4) / temp_f2_2);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (-M2C_FIELD(arg1, f32 *, 8) / temp_f2_2);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) (M2C_FIELD(arg1, f32 *, 0xC) / temp_f2_2);
}

void func_001bf698(void *arg0, void *arg1, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f20;

    temp_f20 = fparg0 * 0.5f;
    M2C_FIELD(arg0, f32 *, 0xC) = func_0026b6f8(temp_f20);
    temp_f0 = func_0026b7d0(temp_f20);
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg1, f32 *, 0) * temp_f0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg1, f32 *, 4) * temp_f0);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg1, f32 *, 8) * temp_f0);
}
#include "data/data_0037.h"
