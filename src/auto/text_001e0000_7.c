/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

M2C_UNK func_001ed000(M2C_UNK, s32, s32, s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_001efd20(s32, s32);
#include "data/pieces/D_003F34B8.h"
extern s32 D_00633640; /* src/data/bss_0063.c: u32 D_00633640[2048] */
extern s32 D_0063F540;
s32 func_001efc10();
u32 func_00232cc0(M2C_UNK);

s32 func_001ed220(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(4, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640;
}

s32 func_001ed460(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(0xB, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640;
}

s32 func_001ed658(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(3, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640;
}

s32 func_001ed780(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(0x28, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640;
}

void func_001ee4b8(void) {
    D_003F34B8 = (S34B8_3f34b8 *)(func_00232cc0(5));
}

void func_001efc38(s32 arg0, s32 arg1) {
    func_001efd20(func_001efc10(), arg1);
}
