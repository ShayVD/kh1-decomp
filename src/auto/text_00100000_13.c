/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0049.h"

extern s32 D_002A6B84;
#include "data/pieces/D_002B75A0.h"
extern s32 D_00494A90;
extern s32 D_00494A9C;
void func_00106b18(s32);
void func_00121eb0(s32);
void func_00266f38(s32, s32);
void iFlushCache(M2C_UNK);

s32 func_001019c8(void *arg0) {
    iFlushCache(0);
    func_00266f38(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x14));
    return 2;
}

s32 func_00101f30(void *arg0) {
    iFlushCache(0);
    func_00266f38(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x14));
    return 2;
}

s32 func_00101f80(void *arg0) {
    iFlushCache(0);
    func_00266f38(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x10));
    return 2;
}

s32 func_00106cd0(s32 arg0, s32 arg1) {
    s32 temp_a0;
    void *temp_v1;

    *(M2C_UNK *)((s32) ((D_00494A9C * 0x10)) + (s32) D_00494A90) = arg1 + 0x30000000;
    M2C_FIELD(((D_00494A9C * 0x10) + D_00494A90), s32 *, 4) = arg0;
    temp_v1 = (D_00494A9C * 0x10) + D_00494A90;
    M2C_FIELD(temp_v1, s32 *, 0xC) = 0;
    M2C_FIELD(temp_v1, s32 *, 8) = 0;
    temp_a0 = D_00494A9C + 1;
    D_00494A9C = temp_a0;
    return (D_00494A90 + (temp_a0 * 0x10)) - 0x10;
}

void func_00106d48(s32 arg0) {
    void *temp_v0;

    *(M2C_UNK *)((s32) ((D_00494A9C * 0x10)) + (s32) D_00494A90) = 0x70000000;
    temp_v0 = (D_00494A9C * 0x10) + D_00494A90;
    M2C_FIELD(temp_v0, s32 *, 0xC) = 0;
    M2C_FIELD(temp_v0, s32 *, 8) = 0;
    M2C_FIELD(temp_v0, s32 *, 4) = 0;
    D_00494A9C += 1;
    func_00106b18(arg0);
}

s32 func_0010c200(void) {
    s32 *var_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_v0;

    var_a1 = 0;
    var_a0 = ((s32 *)&D_002B75A0);
loop_1:
    temp_v1 = *var_a0;
    var_a0 += 3;
    var_v0 = 1;
    if (temp_v1 != 0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}
#include "data/data_002A.h"
