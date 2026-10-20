/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001b9b30();
M2C_UNK func_001bb558();
M2C_UNK func_001bb740();
M2C_UNK func_001bd470();
M2C_UNK func_001efaf0();
extern s32 D_003772D0;
extern s32 D_00625640;
s32 func_001be5c8(s32);
s32 func_001be5d0(s32);
s32 func_001efbb8(s32);
s32 func_00232cc0(M2C_UNK);
void *func_001bb658();

u16 func_001ba1e8(void) {
    return M2C_FIELD(func_001bb658(), u16 *, 0x14);
}

u16 func_001ba208(void) {
    return M2C_FIELD(func_001bb658(), u16 *, 0x16);
}

s32 func_001ba228(s32 arg0) {
    s32 temp_s0;

    func_001bb558();
    temp_s0 = func_001efbb8(func_001be5c8(arg0));
    func_001efaf0();
    return temp_s0;
}

s32 func_001ba268(s32 arg0) {
    s32 temp_s0;

    func_001bb558();
    temp_s0 = func_001efbb8(func_001be5d0(arg0));
    func_001efaf0();
    return temp_s0;
}

void func_001ba3d8(void) {
    func_001bb740();
}

void func_001ba6f8(void) {
    D_003772D0 = 0;
}

s32 func_001ba980(void) {
    func_001b9b30();
    return func_00232cc0(4) + 8;
}

s32 func_001ba9a8(void) {
    func_001b9b30();
    return func_00232cc0(4) + 0x9A78;
}

s32 func_001ba9d8(s32 arg0) {
    func_001b9b30();
    return func_00232cc0(4) + (arg0 * 0xF70) + 0x18;
}

s32 func_001bb198(s32 arg0) {
    func_001b9b30();
    return func_00232cc0(4) + (arg0 << 6) + 0x9C20;
}

s32 func_001bb1d8(s32 arg0) {
    func_001b9b30();
    return func_00232cc0(4) + (arg0 << 6) + 0xA420;
}

s32 func_001bc4a8(void) {
    return D_00625640;
}

void func_001be5b0(void) {
    func_001bd470();
}
#include "data/data_0037.h"
