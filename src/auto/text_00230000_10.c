/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00233ac8();
M2C_UNK sceMcInit();
extern M2C_UNK D_00425F80;
extern M2C_UNK D_00425F88;
extern s32 D_002C5958;
extern s32 D_00425F78;
extern volatile s64 D_006477B0;
void func_00237660(s32, s32, s32);
void func_0023b570(void);
void func_0023c968(void);
void func_00242a38(void);
void func_00243a90(void);
void func_00244500(void);
void func_00245148(void);
void func_002456e8(void);
void func_00245e40(void);
void func_00246438(void);
void func_00246bc8(void);
void func_00247258(void);
void func_00248400(void);
void func_00248ea0(void);
void func_00249250(void);
void func_0024ae00(s32);
void func_0024af00(s32);

void func_00233a80(void) {
    s32 var_v0;
    s64 *var_v1;

    sceMcInit();
    var_v1 = &D_006477B0;
    var_v0 = 0x100;
    do {
        var_v0 -= 1;
        *var_v1 = 0;
        var_v1 += 1;
    } while (var_v0 > 0);
    func_00233ac8();
}

void func_00236f18(void) {
    func_00237660((s32) &D_00425F80, (s32) &D_00425F88, 8);
    func_0023b570();
    func_0023c968();
    func_00242a38();
    func_00243a90();
    func_00244500();
    func_00245148();
    func_002456e8();
    func_00245e40();
    func_00246438();
    func_00246bc8();
    func_00247258();
    func_00248400();
    func_00248ea0();
    func_00249250();
    D_00425F78 = 0;
}

void func_00236fd8(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s64 *, 8) = 0xE;
    M2C_FIELD(arg0, s64 *, 0) = (s64) ((((s32) (arg1 - arg0) >> 4) - 1) | 0x8000 | ((s64) 0x8000 << 0x2D));
}

void func_0023a8d0(s32 arg0) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;

    var_a1 = 0;
    temp_v1 = arg0 + 0x40;
    temp_a0 = arg0 + 0x100;
    if (D_002C5958 & 1) {
        if (M2C_FIELD(arg0, s32 *, 0x1C0) != temp_v1) {
            M2C_FIELD(arg0, s32 *, 0x1C0) = temp_v1;
            func_0024ae00(temp_v1);
            var_a1 = 1;
            M2C_FIELD(arg0, s32 *, 0x1C4) = 0;
        }
    } else if (M2C_FIELD(arg0, s32 *, 0x1C0) != temp_a0) {
        M2C_FIELD(arg0, s32 *, 0x1C0) = temp_a0;
        func_0024ae00(temp_a0);
        var_a1 = 1;
        M2C_FIELD(arg0, s32 *, 0x1C4) = 1;
    }
    if (var_a1 != 0) {
        return;
    }
    func_0024af00(M2C_FIELD(arg0, s32 *, 0x1C0));
}
