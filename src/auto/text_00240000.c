/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0066.h"

M2C_UNK func_00149c80(u16, M2C_UNK *);
extern M2C_UNK D_0046A620;
#include "data/pieces/D_0046A628.h"
extern M2C_UNK D_0046A640;
#include "data/pieces/D_0046A650.h"
extern M2C_UNK D_0046A660;
extern M2C_UNK func_0024f008;
extern s32 D_0046A53C;
extern s32 D_0046A60C;
extern s32 D_0046A67C;
extern s32 D_00669A38;
extern s32 D_00669A3C;
extern u32 D_002C5AD8;
extern u32 D_002C5AE0;
extern void *D_0066AA84; /* src/data/bss_0066.c: s32 *D_0066AA84 */
s32 func_0026aaa0();

void func_0024ba00(s32 arg0) {
    D_00669A38 = arg0;
    D_00669A3C = func_0026aaa0();
}

s32 func_0024be58(void) {
    return D_002C5AD8 | (((u32) D_002C5AD8 >> 0x18) & 0xF0);
}

s32 func_0024be70(void) {
    return D_002C5AE0 | (((u32) D_002C5AE0 >> 0x18) & 0xF0);
}

s32 func_0024d490(void) {
    return D_0046A53C;
}

s32 func_0024d4a0(void) {
    return D_0046A60C;
}

M2C_UNK *func_0024d8a0(void) {
    return &D_0046A620;
}

M2C_UNK *func_0024d8b0(void) {
    return (M2C_UNK *)&D_0046A628;
}

M2C_UNK *func_0024d8c0(void) {
    return &D_0046A640;
}

M2C_UNK *func_0024d8d0(void) {
    return (M2C_UNK *)&D_0046A650;
}

M2C_UNK *func_0024d8e0(void) {
    return &D_0046A660;
}

s32 func_0024e078(void) {
    return D_0046A67C;
}

void func_0024f070(void) {
    func_00149c80(M2C_FIELD(D_0066AA84, u16 *, 0x4C), &func_0024f008);
}
#include "data/data_0046.h"
