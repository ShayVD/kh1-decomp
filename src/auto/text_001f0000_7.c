/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
void func_001fd5e0(s32, s32);
void func_001fd610(s32, s32);
void func_001fd660(s32, s32);

s32 func_001fd248(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s32 *, 0xB0) - 0x7000) >> 4;
}

void func_001fd420(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001fd660(arg0, arg2);
    func_001fd610(arg0, arg3);
    func_001fd5e0(arg0, arg1);
}

void func_001fd478(s32 arg0, s32 arg1, s32 arg2) {
    func_001fd660(arg0, arg2);
    func_001fd610(arg0, 1);
    func_001fd5e0(arg0, arg1);
}

void func_001fd4c0(s32 arg0, s32 arg1, s32 arg2) {
    func_001fd660(arg0, 1);
    func_001fd5e0(arg0, arg1);
    func_001fd610(arg0, arg2);
}
#include "data/data_003F.h"
