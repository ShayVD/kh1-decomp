/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void func_001ba768(s32);
void func_001ba778(s32, s32, s32);
void func_001bfac8(void);

void func_00f4d070(s32 arg0) {
    func_001ba768(arg0);
    func_001bfac8();
    func_001ba768(0);
    func_001bfac8();
}

void func_00f4d0a0(s32 arg0, s32 arg1, s32 arg2) {
    func_001ba778(arg0, arg1, arg2);
    func_001bfac8();
    func_001ba778(arg0, 0, 0);
    func_001bfac8();
}
