/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00F56D98;
extern s32 D_00F56DC4;
extern void *D_00F56DC0;
s32 func_001bb678();
void func_00f20e48();
void func_00f24240(s32, M2C_UNK);
void func_00f24780(s32);
void func_00f25630();
void func_00f2e238(M2C_UNK);
void func_00f2e280(M2C_UNK);
void func_00f32778(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
void func_00f33380(M2C_UNK);
void func_00f390f8(s32);

void func_00f39350(s32 arg0) {
    f32 unused_frame[4][4] __attribute__((aligned(16)));
    u16 temp_s0;

    func_00f33380(0);
    func_00f2e238(0);
    func_00f2e280(0);
    func_00f32778(-1, 0x23, 0x23, 0x41, 0);
    func_00f32778(2, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(0, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(5, 0x80, 0x80, 0x80, 0);
    D_00F56D98 = 1;
    func_00f390f8(arg0);
    func_00f24780(D_00F56DC4);
    func_00f24240(D_00F56DC4, 0);
    func_00f25630();
    temp_s0 = M2C_FIELD(D_00F56DC0, u16 *, 0xA6);
    if (temp_s0 != func_001bb678()) {
        func_00f20e48();
    }
    D_00F56D98 = 0;
}
