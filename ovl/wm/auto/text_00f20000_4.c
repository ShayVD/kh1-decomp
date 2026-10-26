/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00FBA800;
extern volatile s32 D_002BC148[];
s32 func_0010a0d8(void);
s32 func_001bb4f0(void);
void func_0010a3c0(void);
void func_00113028();
void func_001bfac8(void);
void func_001efaf0(void);
void func_00248b00(void);
void func_00f680a0(void);

void func_00f202b0(s32 arg0, s32 arg1) {
    func_00248b00();
    func_00f680a0();
    func_0010a0d8();
    func_0010a3c0();
    D_002BC148[3] = arg1;
    D_002BC148[2] = arg0;
    func_001efaf0();
    func_00113028(func_001bb4f0());
    D_00FBA800 = 3;
    for (;;) {
        func_001bfac8();
    }
}
