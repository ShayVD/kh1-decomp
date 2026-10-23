/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011fbb0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
extern M2C_UNK D_003F3530;
extern M2C_UNK D_00641080; /* src/data/bss_0064.c: u8 D_00641080[0xb0] */
extern M2C_UNK D_00641130; /* src/data/bss_0064.c: u8 D_00641130[0xb0] */
extern s32 D_002BCC94;
void func_00121eb0(s32);
void func_00162110(s32, s32);

void func_0020a1d8(void) {
    s8 *var_s0;
    s32 temp_v0;
    s32 var_s1;

    var_s0 = &D_003F3530;
    var_s1 = 3;
    do {
        if (M2C_FIELD(var_s0, s32 *, 0xCC) != 0) {
            func_00162110(M2C_FIELD(var_s0, s32 *, 0), (s32) (var_s0 + 0x14));
            temp_v0 = M2C_FIELD(var_s0, s32 *, 0xC0);
            if (temp_v0 != 0) {
                func_00121eb0(temp_v0);
            }
        }
        var_s1 -= 1;
        var_s0 += 0xD0;
    } while (var_s1 >= 0);
}

void func_0020b338(void) {
    func_0011fbb0(0x3600, 2, 0x13, 0, 0, 0x68, 0x38, 0x16C, D_002BCC94 + 0x40, &D_00641080);
    func_0011fbb0(0x3640, 1, 0, 0, 0, 0x10, 0x10, 0x40, D_002BCC94 + 0x1700, &D_00641130);
}
#include "data/data_002B.h"
#include "data/data_003F.h"
