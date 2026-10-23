/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ee698();
M2C_UNK func_001efc10(M2C_UNK);
s32 func_001efd98();
s32 func_001efdb8();
u8 *func_001478a0(s32);
void *func_00147840();

/* func_001e93c8 is in src/screen/wave.c. */

/* func_001ebe80, func_001ebea8, func_001ebed0, func_001ebf18, func_001ebf48, func_001ebf98, func_001ebfc8, func_001ebff0, func_001ec0b0, func_001ec360, func_001ec3b0, func_001ec468, func_001ec4b8, func_001ec4e0, func_001ec510, func_001ec538, func_001ec5d8 are in src/save/flags.c. */

















u16 func_001ee708(void) {
    return M2C_FIELD(func_00147840(), u16 *, 8);
}

u16 func_001ee728(void) {
    return M2C_FIELD(func_00147840(), u16 *, 0xA);
}

s16 func_001ee748(void) {
    return M2C_FIELD(func_00147840(), s16 *, 6);
}

u8 func_001ee768(void) {
    return M2C_FIELD(func_00147840(), u8 *, 2);
}

u8 func_001ee788(void) {
    return M2C_FIELD(func_00147840(), u8 *, 3);
}

u16 func_001ee7a8(void) {
    return M2C_FIELD(func_00147840(), u16 *, 0x10);
}

s32 func_001ee7c8(void) {
    return M2C_FIELD(func_00147840(), u16 *, 4) & 1;
}

void func_001eeb88(s32 arg0) {
    if (arg0 != 0) {
        func_001ee698();
        return;
    }
    func_001efc10(0xA7);
}

void func_001eebb0(s32 arg0) {
    if (arg0 != 0) {
        func_001ee698();
        return;
    }
    func_001efc10(0xA7);
}

s32 func_001efe68(void) {
    return func_001efd98() + 1;
}

s32 func_001efe88(void) {
    return func_001efdb8() + 1;
}
