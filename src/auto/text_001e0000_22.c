/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0010bd90(M2C_UNK *, M2C_UNK *);
M2C_UNK func_0010e3f0(M2C_UNK *);
M2C_UNK func_0010ef70(void *, M2C_UNK *, M2C_UNK);
M2C_UNK func_001ed000(M2C_UNK, s32, s32, s32, s32, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK D_003DAE30;
extern M2C_UNK D_003DCD70;
extern M2C_UNK D_00630300;
extern M2C_UNK D_006304E0;
extern M2C_UNK D_00630510;
extern M2C_UNK func_001e64e0;
extern M2C_UNK func_001e6c68;
extern s32 D_002C5BB8;
extern s32 D_003DAD38;
extern s32 D_003DD260;
extern s32 D_003DD28C;
extern s32 D_003E3C80;
extern s32 D_00633640;
void *func_00147840();
void func_001e05a8(s32);
void func_001e0608(void);

s32 func_001e0898(void) {
    s32 var_v0;

    var_v0 = 4;
    if (D_003DAD38 == 0) {
        return var_v0;
    }
    func_001e0608();
    func_001e05a8((s32) &D_003DAE30);
    var_v0 = 0;
    return var_v0;
}

s32 func_001e6500(void) {
    s32 var_v0;

    var_v0 = 4;
    if (D_003DD28C == 0) {
        return var_v0;
    }
    if (D_002C5BB8 & 2) {
        func_0010bd90(&D_00630300, &func_001e64e0);
        D_003DD28C = 0;
        D_003DD260 = -1;
        return 4;
    }
    var_v0 = 0;
    /* Duplicate return node #5. Try simplifying control flow for better match */
    return var_v0;
    return var_v0;
}

s32 func_001e6c90(void) {
    s32 var_v0;

    var_v0 = 4;
    if (D_003DD28C == 0) {
        return var_v0;
    }
    if (D_002C5BB8 & 2) {
        func_0010e3f0(&D_006304E0);
        func_0010ef70((s8 *)&D_006304E0 - 0x80, &D_003DCD70, 0);
        func_0010bd90(&D_00630510, &func_001e6c68);
        D_003DD28C = 0;
        return 4;
    }
    var_v0 = 0;
    /* Duplicate return node #4. Try simplifying control flow for better match */
    return var_v0;
    return var_v0;
}

s32 func_001ece70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_003E3C80 & 8) {
        return D_00633640;
    }
    func_001ed000(0x29, arg0, arg1, arg2, arg3, 0, 0, 0);
    return D_00633640;
}

s32 func_001eeac0(s32 arg0) {
    s32 var_v0;

    if (!((arg0 == 0) || (var_v0 = 1, (M2C_FIELD(func_00147840(), u8 *, 2) != 0)))) {
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}
